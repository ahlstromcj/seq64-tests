/**
 * \file          keystroke_helpers.cpp
 * \library       libseq64 (from the Sequencer64 project)
 * \author        Chris Ahlstrom
 * \date          2015-10-10
 * \updates       2015-10-10
 * \version       $Revision$
 * \license       $XPC_SUITE_GPL_LICENSE$
 *
 *    This module provides helper functions for the unit tests of
 *    the keystroke module of the libseq64 library.
 */

#include <string>

#include "keystroke.hpp"               /* seq64::keystroke class              */
#include "keystroke_helpers.hpp"       /* constructor_test_t and functions    */

/**
 *    Check the given keystroke and test it against the given (and expected)
 *    parameters. Note that the defaults of the expected parameters match
 *    the values assumed by the default keystroke constructor.  This match is
 *    set up for convenience in testing.
 *
 *    Most of the tests are done via keystroke accessor functions.
 */

bool
check_keystroke
(
   const seq64::keystroke & k,
   unsigned int key, bool press, int modkey
)
{
   bool result = false;
   if (key < SEQ64_KEYSTROKE_MIN || key > SEQ64_KEYSTROKE_MAX)
      result = k.key() == SEQ64_KEYSTROKE_BAD_VALUE;
   else
      result = k.key() == key;

   if (result)
      result = k.is_press() == press;

   if (result)
   {
      unsigned int um = static_cast<unsigned int>(modkey);
      bool bad = um >= static_cast<unsigned int>(seq64::SEQ64_MASK_MAX);
      if (bad)
         result = k.modifier() == seq64::SEQ64_MASK_MAX;
      else
         result = k.modifier() == seq64::seq_modifier_t(modkey);

      if (result)
      {
         if (seq64::seq_modifier_t(modkey) & seq64::SEQ64_CONTROL_MASK)
         {
            if (seq64::seq_modifier_t(modkey) & seq64::SEQ64_SHIFT_MASK)
               result = k.mod_control_shift();
            else
               result = k.mod_control();
         }
         else if (seq64::seq_modifier_t(modkey) & seq64::SEQ64_MOD4_MASK)
            result = k.mod_super();
      }
   }
   if (! result)
   {
      std::string pb = press ? "true" : "false" ;
      fprintf
      (
         stderr, "? Bad value: keystroke(%d, %s, %d)\n",
         key, pb.c_str(), modkey
      );
   }
   return result;
}

/**
 *    Check an existing keystroke against itself and another one.  Use for
 *    checking the copy constructor and principal assignment operator.
 *    Note that the comparison does not use an operator ==(), since there is
 *    none defined for seq64::keystroke -- none is needed.  Instead, the
 *    keystroke getter functions are used.
 */

bool
compare_keystrokes
(
   const seq64::keystroke & k1,
   const seq64::keystroke & k2,
   unsigned int key,
   bool press,
   int modkey
)
{
   bool result = check_keystroke(k1, key, press, modkey);
   if (result)
      result = check_keystroke(k2, key, press, modkey);

   if (result)
   {
      result = k1.is_press() == k2.is_press();
      if (result)
         result = k1.key() == k2.key();

      if (result)
         result = k1.modifier() == k2.modifier();
   }
   return result;
}

/**
 *    Passes a wide range of parameters to the principal constructor, copy
 *    constructor, and principle assignment operator for a complete-enough
 *    test of these functions.
 */

bool
keystroke_ctor_tests (constructor_test_t testitem)
{
   bool result;
   for (int key = SEQ64_KEYSTROKE_MIN - 1; key < SEQ64_KEYSTROKE_MAX + 1; ++key)
   {
      for (int i = 0; i <= 1; ++i)
      {
         bool press = i == 1;
         for (int m = 0; m < key_mod_list_size(); ++m)
         {
            seq64::seq_modifier_t smt = key_mod(m);
            seq64::keystroke k(key, press, smt);
            if (testitem == CTOR_PRINCIPAL_CONSTRUCTOR)
               result = check_keystroke(k, key, press, smt);

            else if (testitem == CTOR_COPY_CONSTRUCTOR)
            {
               seq64::keystroke k2(k);                   /* copy object    */
               result = compare_keystrokes(k, k2, key, press, smt);
            }
            else if (testitem == CTOR_PRINCIPAL_ASSIGNMENT_OPERATOR)
            {
               seq64::keystroke k2;

               /*
                * Make sure the compiler doesn't "optimize" assignment into a
                * copy constructor, unlikely though that may be.
                */

               (void) k2.operator =(k);
               result = compare_keystrokes(k, k2, key, press, smt);
            }
            if (! result)
               break;
         }
         if (! result)
            break;
      }
      if (! result)
         break;
   }
   return result;
}

/*
 * keystroke_helpers.cpp
 *
 * vim: ts=3 sw=3 et ft=cpp
 */
