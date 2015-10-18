/**
 * \file          midifile_unit_test.cpp
 * \library       libseq64 (from the Sequencer64 project)
 * \author        Chris Ahlstrom
 * \date          2015-10-18
 * \updates       2015-10-18
 * \version       $Revision$
 * \license       $XPC_SUITE_GPL_LICENSE$
 *
 *    This application provides unit tests for the midifile module of the
 *    libseq64 library.
 *
 * Group:   1     "seq64::midifile"
 * Cases:
 *
 *    -# Basic parse test.
 */

#include "midifile.hpp"                /* seq64::midifile class               */
#include "midifile_helpers.hpp"        /* formerly static test functions      */
#include "midifile_unit_test.hpp"

static std::string
resources_file (const std::string & s)
{
   std::string result("../../resources/");
   result += s;
   return result;
}

/**
 *    Provides a basic "smoke test" for the midifile module.  A smoke test is a
 *    test of the basic functionality of the object or function.  It is an
 *    easy test that makes sure the code has basic integrity.  This test is
 *    about the simplest unit test function that can be written.
 *
 * \group
 *    1. seq64::midifile
 *
 * \case
 *    1. Basic parse test.
 *
 * \tests
 *    -  seq64::midifile::midifile()
 *
 * \param options
 *    Provides the command-line options for the unit-test application.
 *
 * \return
 *    Returns the unit-test status object needed by the protocol.
 */

xpc::cut_status
midifile_unit_test_01_01 (const xpc::cut_options & options)
{
   xpc::cut_status status(options, 1, 1, "seq64::midifile", _("Parse Test"));
   bool ok = status.valid();                       /* invalidity not an error */
   if (ok)
   {
      if (! status.can_proceed())                  /* is test allowed to run? */
      {
         status.pass();                            /* no, force it to pass    */
      }
      else
      {
         if (status.next_subtest("Parse test"))
         {
            ok = midifile_parse_test(resources_file("b4uacuse-snipped.midi"));
            status.pass(ok);
         }
      }
   }
   return status;
}

/*
 * midifile_unit_test.cpp
 *
 * vim: ts=3 sw=3 et ft=cpp
 */
