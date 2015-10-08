/**
 * \file          click_unit_test.cpp
 * \library       libseq64 (from the Sequencer64 project)
 * \author        Chris Ahlstrom
 * \date          2015-10-07
 * \updates       2015-10-07
 * \version       $Revision$
 * \license       $XPC_SUITE_GPL_LICENSE$
 *
 *    This application provides unit tests for the click module of the
 *    libseq64 library.
 *
 * Group:   1
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

/*
 * click_unit_test.cpp
 *
 * vim: ts=3 sw=3 et ft=cpp
 */
