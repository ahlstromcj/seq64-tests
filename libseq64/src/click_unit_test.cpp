/**
 * \file          click_unit_test.cpp
 * \library       libseq64 (from the Sequencer64 project)
 * \author        Chris Ahlstrom
 * \date          2015-10-07
 * \updates       2015-10-09
 * \version       $Revision$
 * \license       $XPC_SUITE_GPL_LICENSE$
 *
 *    This application provides unit tests for the click module of the
 *    libseq64 library.
 *
 * Group:   1     "seq64::click"
 * Cases:
 *
 *    -# Default constructor and smoke test.
 *    -# Principal constructor.
 *    -# Copy constructor.
 *    -# Principal assignment operator.
 *    -# is_press()
 *    -# is_left(), is_middle(), is_right()
 *    -# x() and y()
 *    -# modifier(), mod_control(), mod_control_shift(), and mod_super()
 */

#include "click.hpp"                   /* seq64::click class                  */
#include "click_helpers.hpp"           /* formerly static test functions      */
#include "click_unit_test.hpp"

/**
 *    Provides a basic "smoke test" for the click module.  A smoke test is a
 *    test of the basic functionality of the object or function.  It is an
 *    easy test that makes sure the code has basic integrity.  This test is
 *    about the simplest unit test function that can be written.
 *
 * \group
 *    1. seq64::click
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
 *    -  seq64::click::click()
 *
 * \param options
 *    Provides the command-line options for the unit-test application.
 *
 * \return
 *    Returns the unit-test status object needed by the protocol.
 */

xpc::cut_status
click_unit_test_01_01 (const xpc::cut_options & options)
{
   xpc::cut_status status(options, 1, 1, "seq64::click", _("Smoke Test"));
   bool ok = status.valid();                       /* invalidity not an error */
   if (ok)
   {
      if (! status.can_proceed())                  /* is test allowed to run? */
      {
         status.pass();                            /* no, force it to pass    */
      }
      else
      {
         if (status.next_subtest("click::click()"))
         {
            seq64::click c;
            ok = ! c.is_press();
            if (ok)
               ok = c.x() == 0;

            if (ok)
               ok = c.y() == 0;

            if (ok)
               ok = c.button() == 0;

            if (ok)
               ok = c.modifier() == seq64::SEQ64_NO_MASK;

            status.pass(ok);
         }
      }
   }
   return status;
}

/**
 * \group
 *    1. seq64::click
 *
 * \case
 *    2. Principal constructor
 *
 * \tests
 *    -  seq64::click::click(int parameters)
 *
 * \param options
 *    Provides the command-line options for the unit-test application.
 *
 * \return
 *    Returns the unit-test status object needed by the protocol.
 */

xpc::cut_status
click_unit_test_01_02 (const xpc::cut_options & options)
{
   xpc::cut_status status
   (
      options, 1, 2, "seq64::click", _("Principal constructor")
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
         if (status.next_subtest("click::click()"))
         {
            ok = click_ctor_tests();
            status.pass(ok);
         }
      }
   }
   return status;
}

/**
 * \group
 *    1. seq64::click
 *
 * \case
 *    3. Copy constructor
 *
 * \tests
 *    -  seq64::click::click(click)
 *
 * \param options
 *    Provides the command-line options for the unit-test application.
 *
 * \return
 *    Returns the unit-test status object needed by the protocol.
 */

xpc::cut_status
click_unit_test_01_03 (const xpc::cut_options & options)
{
   xpc::cut_status status
   (
      options, 1, 3, "seq64::click", _("Copy constructor")
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
            seq64::click c1;
            seq64::click c2;
            ok = compare_clicks(c1, c2);
            status.pass(ok);
         }
         if (status.next_subtest("Copy default"))
         {
            seq64::click c1;
            seq64::click c2(c1);
            ok = compare_clicks(c1, c2);
            status.pass(ok);
         }
         if (status.next_subtest("Assign default"))
         {
            seq64::click c1;
            seq64::click c2;
            c2 = c1;
            ok = compare_clicks(c1, c2);
            status.pass(ok);
         }
         if (status.next_subtest("operator =()"))
         {
            seq64::click c1;
            seq64::click c2;
            (void) c2.operator =(c1);
            ok = compare_clicks(c1, c2);
            status.pass(ok);
         }
         if (status.next_subtest("Copy principal"))
         {
            ok = click_ctor_tests(CT_COPY_CONSTRUCTOR);
            status.pass(ok);
         }
      }
   }
   return status;
}

/**
 * \group
 *    1. seq64::click
 *
 * \case
 *    4. Principal assignment operator
 *
 * \tests
 *    -  seq64::click::operator =(click)
 *
 * \param options
 *    Provides the command-line options for the unit-test application.
 *
 * \return
 *    Returns the unit-test status object needed by the protocol.
 */

xpc::cut_status
click_unit_test_01_04 (const xpc::cut_options & options)
{
   xpc::cut_status status
   (
      options, 1, 4, "seq64::click", _("Principal assignment operator")
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
            seq64::click c1;
            seq64::click c2;
            c2 = c1;
            ok = compare_clicks(c1, c2);
            status.pass(ok);
         }
         if (status.next_subtest("operator =()"))
         {
            seq64::click c1;
            seq64::click c2;
            (void) c2.operator =(c1);
            ok = compare_clicks(c1, c2);
            status.pass(ok);
         }
         if (status.next_subtest("Assign principal"))
         {
            ok = click_ctor_tests(CT_PRINCIPAL_ASSIGNMENT_OPERATOR);
            status.pass(ok);
         }
      }
   }
   return status;
}

/*
 * click_unit_test.cpp
 *
 * vim: ts=3 sw=3 et ft=cpp
 */
