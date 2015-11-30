/**
 * \file          click_helpers.cpp
 * \library       libseq64 (from the Sequencer64 project)
 * \author        Chris Ahlstrom
 * \date          2015-10-09
 * \updates       2015-11-29
 * \version       $Revision$
 * \license       $XPC_SUITE_GPL_LICENSE$
 *
 *    This module provides helper functions for the unit tests of
 *    the click module of the libseq64 library.
 */

#include <string>

#include "click.hpp"                   /* seq64::click class                  */
#include "click_helpers.hpp"           /* constructor_test_t and functions    */

/**
 *    Check the given click and test it against the given (and expected)
 *    parameters. Note that the defaults of the expected parameters match
 *    the values assumed by the default click constructor.  This match is
 *    set up for convenience in testing.
 *
 *    Most of the tests are done via click accessor functions.
 */

bool
check_click
(
   const seq64::click & c,
   int x, int y, int button, bool press, int modkey
)
{
   bool result = false;
   if (x < SEQ64_CLICK_X_MIN || x >= SEQ64_CLICK_X_MAX)
      result = c.x() == SEQ64_CLICK_BAD_VALUE;
   else
      result = c.x() == x;

   if (result)
   {
      if (y < SEQ64_CLICK_Y_MIN || y >= SEQ64_CLICK_Y_MAX)
         result = c.y() == SEQ64_CLICK_BAD_VALUE;
      else
         result = c.y() == y;
   }
   if (result)
   {
      if (button < SEQ64_CLICK_BUTTON_MIN || button > SEQ64_CLICK_BUTTON_MAX)
         result = c.button() == SEQ64_CLICK_BAD_VALUE;
      else
      {
         result = c.button() == button;
         if (SEQ64_CLICK_LEFT(button))
         {
            result = c.is_left();
            if (result)
               result = ! c.is_middle();

            if (result)
               result = ! c.is_right();
         }
         else if (SEQ64_CLICK_MIDDLE(button))
         {
            result = ! c.is_left();
            if (result)
               result = c.is_middle();

            if (result)
               result = ! c.is_right();
         }
         else if (SEQ64_CLICK_RIGHT(button))
         {
            result = ! c.is_left();
            if (result)
               result = ! c.is_middle();

            if (result)
               result = c.is_right();
         }
         else
            result = false;
      }
   }
   if (result)
      result = c.is_press() == press;

   if (result)
   {
      unsigned int um = static_cast<unsigned int>(modkey);
      bool bad = um >= static_cast<unsigned int>(seq64::SEQ64_MASK_MAX);
      if (bad)
         result = c.modifier() == seq64::SEQ64_MASK_MAX;
      else
         result = c.modifier() == seq64::seq_modifier_t(modkey);

      if (result)
      {
         if (seq64::seq_modifier_t(modkey) & seq64::SEQ64_CONTROL_MASK)
         {
            if (seq64::seq_modifier_t(modkey) & seq64::SEQ64_SHIFT_MASK)
               result = c.mod_control_shift();
            else
               result = c.mod_control();
         }
         else if (seq64::seq_modifier_t(modkey) & seq64::SEQ64_MOD4_MASK)
            result = c.mod_super();
      }
   }
   if (! result)
   {
      std::string pb = press ? "true" : "false" ;
      fprintf
      (
         stderr, "? Bad value: click(%d, %d, %d, %s, %d)\n",
         x, y, button, pb.c_str(), modkey
      );
   }
   return result;
}

/**
 *    Check an existing click against itself and another one.  Use for
 *    checking the copy constructor and principal assignment operator.
 *    Note that the comparison does not use an operator ==(), since there is
 *    none defined for seq64::click -- none is needed.  Instead, the
 *    click getter functions are used.
 */

bool
compare_clicks
(
   const seq64::click & c1,
   const seq64::click & c2,
   int x,
   int y,
   int button,
   bool press,
   int modkey
)
{
   bool result = check_click(c1, x, y, button, press, modkey);
   if (result)
      result = check_click(c2, x, y, button, press, modkey);

   if (result)
   {
      result = c1.is_press() == c2.is_press();
      if (result)
         result = c1.x() == c2.x();

      if (result)
         result = c1.y() == c2.y();

      if (result)
         result = c1.button() == c2.button();

      if (result)
         result = c1.modifier() == c2.modifier();
   }
   return result;
}

/**
 *    Provides a list of click x-values to test; the full range is a bit much.
 */

int s_x_list [] =
{
   -1,
   SEQ64_CLICK_X_MIN,
   1, 2, 3,
   SEQ64_CLICK_X_MAX-2,
   SEQ64_CLICK_X_MAX-1,
   SEQ64_CLICK_X_MAX,
   SEQ64_CLICK_X_MAX+1
};
int s_x_list_size = sizeof(s_x_list) / sizeof(int);

/**
 *    Provides a list of click y-values to test; the full range is a bit much.
 */

int s_y_list [] =
{
   -1,
   SEQ64_CLICK_Y_MIN,
   1, 2, 3,
   SEQ64_CLICK_Y_MAX-2,
   SEQ64_CLICK_Y_MAX-1,
   SEQ64_CLICK_Y_MAX,
   SEQ64_CLICK_Y_MAX+1
};
int s_y_list_size = sizeof(s_y_list) / sizeof(int);

/**
 *    Passes a wide range of parameters to the principal constructor, copy
 *    constructor, and principle assignment operator for a complete-enough
 *    test of these functions.
 */

bool
click_ctor_tests (constructor_test_t testitem)
{
   bool result;
   for (int xi = 0; xi < s_x_list_size; ++xi)
   {
      for (int yi = 0; yi < s_y_list_size; ++yi)
      {
         for
         (
            int button = SEQ64_CLICK_BUTTON_MIN - 1;
            button < SEQ64_CLICK_BUTTON_MAX + 1;
            ++button
         )
         {
            for (int i = 0; i <= 1; ++i)
            {
               bool press = i == 1;
               for (int m = 0; m < key_mod_list_size(); ++m)
               {
                  int x = s_x_list[xi];
                  int y = s_y_list[yi];
                  seq64::seq_modifier_t smt = key_mod(m);
                  seq64::click c(x, y, button, press, smt);
                  if (testitem == CTOR_PRINCIPAL_CONSTRUCTOR)
                     result = check_click(c, x, y, button, press, smt);
                  else if (testitem == CTOR_COPY_CONSTRUCTOR)
                  {
                     seq64::click c2(c);                    /* copy object    */
                     result = compare_clicks(c, c2, x, y, button, press, smt);
                  }
                  else if (testitem == CTOR_PRINCIPAL_ASSIGNMENT_OPERATOR)
                  {
                     seq64::click c2;

                     /*
                      * Make sure the compiler doesn't "optimize" assignment
                      * into a copy constructor, unlikely though that may be.
                      */

                     (void) c2.operator =(c);
                     result = compare_clicks(c, c2, x, y, button, press, smt);
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
         if (! result)
            break;
      }
      if (! result)
         break;
   }
   return result;
}

/*
 * click_helpers.cpp
 *
 * vim: ts=3 sw=3 et ft=cpp
 */
