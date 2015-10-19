/**
 * \file          keystroke_unit_test.cpp
 * \library       libseq64 (from the Sequencer64 project)
 * \author        Chris Ahlstrom
 * \date          2015-10-10
 * \updates       2015-10-18
 * \version       $Revision$
 * \license       $XPC_SUITE_GPL_LICENSE$
 *
 *    This application provides unit tests for the keystroke module of the
 *    libseq64 library.
 *
 * Group:   1     "seq64::keystroke"
 * Cases:
 *
 *    -# Default constructor and smoke test.
 *    -# Principal constructor.
 *    -# Copy constructor.
 *    -# Principal assignment operator.
 *    -# All the accessors, indirectly:
 *       -  is_press()
 *       -  key()
 *       -  modifier(), mod_control(), mod_control_shift(), and mod_super()
 */

#include "keystroke.hpp"               /* seq64::keystroke class              */
#include "keystroke_helpers.hpp"       /* formerly static test functions      */
#include "keystroke_unit_test.hpp"

/**
 *    Provides a basic "smoke test" for the keystroke module.  A smoke test is
 *    a test of the basic functionality of the object or function.  It is an
 *    easy test that makes sure the code has basic integrity.  This test is
 *    about the simplest unit test function that can be written.
 *
 * \group 1. seq64::keystroke
 *
 * \case
 *    1. Basic smoke test.
 *
 * \note
 *    It all of these unit-tests, it is important to understand that a
 *    status coming up invalid [i.e. status.valid() == false] is \e not a
 *    test failure -- it only indicates that the status object is invalid \e
 *    or that the test is not allowed to run.
 *
 * \tests
 *    -  seq64::keystroke::keystroke()
 *
 * \param options
 *    Provides the command-line options for the unit-test application.
 *
 * \return
 *    Returns the unit-test status object needed by the protocol.
 */

xpc::cut_status
keystroke_unit_test_01_01 (const xpc::cut_options & options)
{
   xpc::cut_status status(options, 1, 1, "seq64::keystroke", _("Smoke Test"));
   bool ok = status.valid();                       /* invalidity not an error */
   if (ok)
   {
      if (! status.can_proceed())                  /* is test allowed to run? */
      {
         status.pass();                            /* no, force it to pass    */
      }
      else
      {
         if (status.next_subtest("keystroke::keystroke()"))
         {
            seq64::keystroke k;
            ok = check_keystroke(k);               /* checks default values   */
            status.pass(ok);
         }
      }
   }
   return status;
}

/**
 * \group
 *    1. seq64::keystroke
 *
 * \case
 *    2. Principal constructor
 *
 * \tests
 *    -  seq64::keystroke::keystroke(int parameters)
 *
 * \param options
 *    Provides the command-line options for the unit-test application.
 *
 * \return
 *    Returns the unit-test status object needed by the protocol.
 */

xpc::cut_status
keystroke_unit_test_01_02 (const xpc::cut_options & options)
{
   xpc::cut_status status
   (
      options, 1, 2, "seq64::keystroke", _("Principal constructor")
   );
   bool ok = status.valid();                       /* invalidity not an error */
   if (ok)
   {
      if (! status.can_proceed())                  /* is test allowed to run? */
      {
         status.pass();                            /* no, force it to pass    */
      }
      else
      {
         if (status.next_subtest("keystroke::keystroke()"))
         {
            ok = keystroke_ctor_tests();
            status.pass(ok);
         }
      }
   }
   return status;
}

/**
 * \group
 *    1. seq64::keystroke
 *
 * \case
 *    3. Copy constructor
 *
 * \tests
 *    -  seq64::keystroke::keystroke(keystroke)
 *
 * \param options
 *    Provides the command-line options for the unit-test application.
 *
 * \return
 *    Returns the unit-test status object needed by the protocol.
 */

xpc::cut_status
keystroke_unit_test_01_03 (const xpc::cut_options & options)
{
   xpc::cut_status status
   (
      options, 1, 3, "seq64::keystroke", _("Copy constructor")
   );
   bool ok = status.valid();                       /* invalidity not an error */
   if (ok)
   {
      if (! status.can_proceed())                  /* is test allowed to run? */
      {
         status.pass();                            /* no, force it to pass    */
      }
      else
      {
         if (status.next_subtest("Default"))
         {
            seq64::keystroke k1;
            seq64::keystroke k2;
            ok = compare_keystrokes(k1, k2);
            status.pass(ok);
         }
         if (status.next_subtest("Copy default"))
         {
            seq64::keystroke k1;
            seq64::keystroke k2(k1);
            ok = compare_keystrokes(k1, k2);
            status.pass(ok);
         }
         if (status.next_subtest("Assign default"))
         {
            seq64::keystroke k1;
            seq64::keystroke k2;
            k2 = k1;
            ok = compare_keystrokes(k1, k2);
            status.pass(ok);
         }
         if (status.next_subtest("operator =()"))
         {
            seq64::keystroke k1;
            seq64::keystroke k2;
            (void) k2.operator =(k1);
            ok = compare_keystrokes(k1, k2);
            status.pass(ok);
         }
         if (status.next_subtest("Copy principal"))
         {
            ok = keystroke_ctor_tests(CTOR_COPY_CONSTRUCTOR);
            status.pass(ok);
         }
      }
   }
   return status;
}

/**
 * \group
 *    1. seq64::keystroke
 *
 * \case
 *    4. Principal assignment operator
 *
 * \tests
 *    -  seq64::keystroke::operator =(keystroke)
 *
 * \param options
 *    Provides the command-line options for the unit-test application.
 *
 * \return
 *    Returns the unit-test status object needed by the protocol.
 */

xpc::cut_status
keystroke_unit_test_01_04 (const xpc::cut_options & options)
{
   xpc::cut_status status
   (
      options, 1, 4, "seq64::keystroke", _("Principal assignment operator")
   );
   bool ok = status.valid();                       /* invalidity not an error */
   if (ok)
   {
      if (! status.can_proceed())                  /* is test allowed to run? */
      {
         status.pass();                            /* no, force it to pass    */
      }
      else
      {
         if (status.next_subtest("Assign default"))
         {
            seq64::keystroke k1;
            seq64::keystroke k2;
            k2 = k1;
            ok = compare_keystrokes(k1, k2);
            status.pass(ok);
         }
         if (status.next_subtest("operator =()"))
         {
            seq64::keystroke k1;
            seq64::keystroke k2;
            (void) k2.operator =(k1);
            ok = compare_keystrokes(k1, k2);
            status.pass(ok);
         }
         if (status.next_subtest("Assign principal"))
         {
            ok = keystroke_ctor_tests(CTOR_PRINCIPAL_ASSIGNMENT_OPERATOR);
            status.pass(ok);
         }
      }
   }
   return status;
}

/*
 * keystroke_unit_test.cpp
 *
 * vim: ts=3 sw=3 et ft=cpp
 */
