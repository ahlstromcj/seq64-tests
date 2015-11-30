/**
 * \file          calculations_unit_test.cpp
 * \library       libseq64 (from the Sequencer64 project)
 * \author        Chris Ahlstrom
 * \date          2015-11-29
 * \updates       2015-11-29
 * \version       $Revision$
 * \license       $XPC_SUITE_GPL_LICENSE$
 *
 *    This application provides unit tests for the calculations module of the
 *    libseq64 library.
 *
 * Group:   4     "seq64::calculations"
 * Cases:
 *
 *    -# Basic parse test.
 */

#include <iostream>                    /* std::cout, std::endl             */

#include "calculations.hpp"            /* seq64::calculations module       */
#include "calculations_unit_test.hpp"

/**
 *    Tests the helper function seq64::extract_timing_number().
 *
 * \group
 *    4. seq64::calculations module
 *
 * \case
 *    1. Basic parse tests.
 *
 * \tests
 *    -  seq64::extract_timing_numbers()
 *
 * \param options
 *    Provides the command-line options for the unit-test application.
 *
 * \return
 *    Returns the unit-test status object needed by the protocol.
 */

xpc::cut_status
calculations_unit_test_04_01 (const xpc::cut_options & options)
{
   xpc::cut_status status(options, 4, 1, "seq64::calculations", _("Parse Test"));
   bool ok = status.valid();                       /* invalidity not an error */
   if (ok)
   {
      if (! status.can_proceed())                  /* is test allowed to run? */
      {
         status.pass();                            /* no, force it to pass    */
      }
      else
      {
         std::string s1, s2, s3, s4;
         if (status.next_subtest("0:0:0"))
         {
            std::string test = "0:0:0";            /* kind of a smoke test    */
            bool ok = seq64::extract_timing_numbers(test, s1, s2, s3, s4);
            if (options.is_verbose())
            {
               std::cout
                  << "Source = '" << test << "' --> "
                  << std::endl
                  << "   '" << s1 << "'; "
                  << "   '" << s2 << "'; "
                  << "   '" << s3 << "'"
                  << std::endl
                  ;
            }
            if (ok)
               ok = s1 == "0" && s2 == "0" && s3 == "0";

            status.pass(ok);
         }
         if (status.next_subtest("0:0:0.0"))
         {
            std::string test = "0:0:0.0";          /* kind of a smoke test    */
            bool ok = seq64::extract_timing_numbers(test, s1, s2, s3, s4);
            if (options.is_verbose())
            {
               std::cout
                  << "Source = '" << test << "' --> "
                  << std::endl
                  << "   '" << s1 << "'; "
                  << "   '" << s2 << "'; "
                  << "   '" << s3 << "'; "
                  << "   '" << s4 << "'"
                  << std::endl
                  ;
            }
            if (ok)
               ok = s1 == "0" && s2 == "0" && s3 == "0" && s4 == ".0";

            status.pass(ok);
         }
         if (status.next_subtest("100:04:10"))
         {
            std::string test = "100:04:10";
            bool ok = seq64::extract_timing_numbers(test, s1, s2, s3, s4);
            if (options.is_verbose())
            {
               std::cout
                  << "Source = '" << test << "' --> "
                  << std::endl
                  << "   '" << s1 << "'; "
                  << "   '" << s2 << "'; "
                  << "   '" << s3 << "'"
                  << std::endl
                  ;
            }
            if (ok)
               ok = s1 == "100" && s2 == "04" && s3 == "10";

            status.pass(ok);
         }
         if (status.next_subtest("100:04:10.0123"))
         {
            std::string test = "100:04:10.0123";
            bool ok = seq64::extract_timing_numbers(test, s1, s2, s3, s4);
            if (options.is_verbose())
            {
               std::cout
                  << "Source = '" << test << "' --> "
                  << std::endl
                  << "   '" << s1 << "'; "
                  << "   '" << s2 << "'; "
                  << "   '" << s3 << "';"
                  << "   '" << s4 << "'"
                  << std::endl
                  ;
            }
            if (ok)
               ok = s1 == "100" && s2 == "04" && s3 == "10" && s4 == ".0123";

            status.pass(ok);
         }
      }
   }
   return status;
}

/*
 * calculations_unit_test.cpp
 *
 * vim: ts=3 sw=3 et ft=cpp
 */
