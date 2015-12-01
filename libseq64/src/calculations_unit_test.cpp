/**
 * \file          calculations_unit_test.cpp
 * \library       libseq64 (from the Sequencer64 project)
 * \author        Chris Ahlstrom
 * \date          2015-11-29
 * \updates       2015-12-01
 * \version       $Revision$
 * \license       $XPC_SUITE_GPL_LICENSE$
 *
 *    This application provides unit tests for the calculations module of the
 *    libseq64 library.
 *
 * Group:   4     "seq64::calculations"
 * Cases:
 *
 *    -# seq64::extract_timing_numbers() [string input]
 *    -# seg64::timestring_to_pulses() [string input]
 *
 *    -# seg64::pulses_to_timestring() [string output]
 *
 *    -# seg64::pulses_to_midi_measures()
 *    -# seg64::pulses_to_measuresstring() [string output]
 *    -# seg64::midi_measures_to_pulses()
 *    -# seg64::measurestring_to_pulses() [string input]
 */

#include <iostream>                    /* std::cout, std::endl             */

#include "calculations.hpp"            /* seq64::calculations module       */
#include "calculations_unit_test.hpp"

/**
 *    Tests the helper function seq64::extract_timing_numbers().
 *
 * \group
 *    4. seq64::calculations (module)
 *
 * \case
 *    1. seq64::extract_timing_numbers()
 *
 * \tests
 *    -  seq64::extract_timing_numbers("0:0:0"))
 *    -  seq64::extract_timing_numbers("0:0:0.0"))
 *    -  seq64::extract_timing_numbers("100:04:10"))
 *    -  seq64::extract_timing_numbers("100:04:10.0123"))
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
   xpc::cut_status status
   (
      options, 4, 1, "seq64::calculations", "extract_timing_numbers()"
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

/**
 *    Tests the helper function seq64::timestring_to_pulses().
 *
 * \group
 *    4. seq64::calculations (module)
 *
 * \case
 *    2. seq64::timestring_to_pulses()
 *
 * \tests
 *    -  BPM = 120, PPQN = 192
 *       -  seq64::timestring_to_pulses("0:0:0"))
 *       -  seq64::timestring_to_pulses("0:0:0.0"))
 *       -  seq64::timestring_to_pulses("100:04:10"))
 *       -  seq64::timestring_to_pulses("100:04:10.0123"))
 *
 * \param options
 *    Provides the command-line options for the unit-test application.
 *
 * \return
 *    Returns the unit-test status object needed by the protocol.
 */

xpc::cut_status
calculations_unit_test_04_02 (const xpc::cut_options & options)
{
   xpc::cut_status status
   (
      options, 4, 2, "seq64::calculations", "timestring_to_pulses()"
   );
   bool ok = status.valid();                       /* invalidity not an error */
   if (ok)
   {
      const int BPM = 120;
      const int PPQN = 192;
      if (! status.can_proceed())                  /* is test allowed to run? */
      {
         status.pass();                            /* no, force it to pass    */
      }
      else
      {
         if (status.next_subtest("0:0:0"))
         {
            std::string test = "0:0:0";            /* kind of a smoke test    */
            seq64::midipulse p = seq64::timestring_to_pulses(test, BPM, PPQN);
            if (options.is_verbose())
            {
               std::cout
                  << "Source = '" << test << "' --> " << p << " pulses"
                  << std::endl
                  ;
            }
            status.pass(p == 0);
         }
         if (status.next_subtest("0:0:0.0"))
         {
            std::string test = "0:0:0.0";          /* kind of a smoke test    */
            seq64::midipulse p = seq64::timestring_to_pulses(test, BPM, PPQN);
            if (options.is_verbose())
            {
               std::cout
                  << "Source = '" << test << "' --> " << p << " pulses"
                  << std::endl
                  ;
            }
            status.pass(p == 0);
         }
         if (status.next_subtest("100:04:10"))
         {
            /*
             * Result should be (100 * 3600 + 4 * 60 + 10) * 1000000
             * microseconds, which is then multiplied by (120 * 192) and
             * divided by (60 * 1000000).
             */

            std::string test = "100:04:10";
            seq64::midipulse p = seq64::timestring_to_pulses(test, BPM, PPQN);
            if (options.is_verbose())
            {
               std::cout
                  << "Source = '" << test << "' --> " << p << " pulses"
                  << std::endl
                  ;
            }
            status.pass(p == 138336000);
         }
         if (status.next_subtest("100:04:10.0123"))
         {
            std::string test = "100:04:10.0123";
            status.pass();
         }
      }
   }
   return status;
}

/**
 *    Tests the helper function seq64::pulses_to_timestring().
 *
 * \group
 *    4. seq64::calculations (module)
 *
 * \case
 *    3. seq64::pulses_to_timestring()
 *
 * \tests
 *    -  BPM = 120, PPQN = 192
 *       -  seq64::pulses_to_timestring(0")
 *       -  seq64::pulses_to_timestring(1")
 *
 * \param options
 *    Provides the command-line options for the unit-test application.
 *
 * \return
 *    Returns the unit-test status object needed by the protocol.
 */

xpc::cut_status
calculations_unit_test_04_03 (const xpc::cut_options & options)
{
   xpc::cut_status status
   (
      options, 4, 3, "seq64::calculations", "pulses_to_timestring()"
   );
   bool ok = status.valid();                       /* invalidity not an error */
   if (ok)
   {
      const int BPM = 120;
      const int PPQN = 192;
      if (! status.can_proceed())                  /* is test allowed to run? */
      {
         status.pass();                            /* no, force it to pass    */
      }
      else
      {
         if (options.is_verbose())
            std::cout << "BPM = " << BPM << "; PPQN = " << PPQN << std::endl;

         if (status.next_subtest("0"))
         {
            std::string t = seq64::pulses_to_timestring(0, BPM, PPQN);
            if (options.is_verbose())
            {
               std::cout
                  << "Source = 0 pulses --> '" << t << "' time string"
                  << std::endl
                  ;
            }
            status.pass(t == "0:0:0");
         }
         if (status.next_subtest("1"))
         {
            std::string t = seq64::pulses_to_timestring(1, BPM, PPQN);
            if (options.is_verbose())
            {
               std::cout
                  << "Source = 1 pulse --> '" << t << "' time string"
                  << std::endl
                  ;
            }
            status.pass(t == "0:0:0.002604");
         }
         if (status.next_subtest("PPQN"))
         {
            std::string t = seq64::pulses_to_timestring(PPQN, BPM, PPQN);
            if (options.is_verbose())
            {
               std::cout
                  << "Source = " << PPQN
                  << " pulses --> '" << t << "' time string" << std::endl
                  ;
            }
            status.pass(t == "0:0:0.500000");
         }
         if (status.next_subtest("2*PPQN"))
         {
            std::string t = seq64::pulses_to_timestring(2*PPQN, BPM, PPQN);
            if (options.is_verbose())
            {
               std::cout
                  << "Source = " << (2*PPQN)
                  << " pulses --> '" << t << "' time string" << std::endl
                  ;
            }
            status.pass(t == "0:0:1");
         }
         if (status.next_subtest("3*PPQN"))
         {
            std::string t = seq64::pulses_to_timestring(3*PPQN, BPM, PPQN);
            if (options.is_verbose())
            {
               std::cout
                  << "Source = " << (3*PPQN)
                  << " pulses --> '" << t << "' time string" << std::endl
                  ;
            }
            status.pass(t == "0:0:1.500000");
         }
         if (status.next_subtest("4*PPQN"))
         {
            std::string t = seq64::pulses_to_timestring(4*PPQN, BPM, PPQN);
            if (options.is_verbose())
            {
               std::cout
                  << "Source = " << (4*PPQN)
                  << " pulses --> '" << t << "' time string"
                  << std::endl
                  ;
            }
            status.pass(t == "0:0:2");
         }
         if (status.next_subtest("BPM/2*PPQN"))
         {
            std::string t = seq64::pulses_to_timestring((BPM/2)*PPQN, BPM, PPQN);
            if (options.is_verbose())
            {
               std::cout
                  << "Source = " << ((BPM/2)*PPQN)
                  << " pulses --> '" << t << "' time string" << std::endl
                  ;
            }
            status.pass(t == "0:0:30");
         }
         if (status.next_subtest("BPM*PPQN"))
         {
            std::string t = seq64::pulses_to_timestring(BPM*PPQN, BPM, PPQN);
            if (options.is_verbose())
            {
               std::cout
                  << "Source = " << (BPM*PPQN)
                  << " pulses --> '" << t << "' time string" << std::endl
                  ;
            }
            status.pass(t == "0:1:0");
         }
         if (status.next_subtest("(BPM+1)*PPQN"))
         {
            std::string t = seq64::pulses_to_timestring((BPM+1)*PPQN, BPM, PPQN);
            if (options.is_verbose())
            {
               std::cout
                  << "Source = " << ((BPM+1)*PPQN)
                  << " pulses --> '" << t << "' time string" << std::endl
                  ;
            }
            status.pass(t == "0:1:0.500000");
         }
         if (status.next_subtest("60*BPM*PPQN"))
         {
            std::string t = seq64::pulses_to_timestring(BPM*60*PPQN, BPM, PPQN);
            if (options.is_verbose())
            {
               std::cout
                  << "Source = " << (60*BPM*PPQN)
                  << " pulses --> '" << t << "' time string" << std::endl
                  ;
            }
            status.pass(t == "1:0:0");
         }
#if 0
         if (status.next_subtest("0:0:0.0"))
         {
            std::string test = "0:0:0.0";          /* kind of a smoke test    */
            seq64::midipulse p = seq64::pulses_to_timestring(, BPM, PPQN);
            if (options.is_verbose())
            {
               std::cout
                  << "Source = '" << test << "' --> " << p << " pulses"
                  << std::endl
                  ;
            }
            status.pass(p == 0);
         }
         if (status.next_subtest("100:04:10"))
         {
            /*
             * Result should be (100 * 3600 + 4 * 60 + 10) * 1000000
             * microseconds, which is then multiplied by (120 * 192) and
             * divided by (60 * 1000000).
             */

            std::string test = "100:04:10";
            seq64::midipulse p = seq64::pulses_to_timestring(, BPM, PPQN);
            if (options.is_verbose())
            {
               std::cout
                  << "Source = '" << test << "' --> " << p << " pulses"
                  << std::endl
                  ;
            }
            status.pass(p == 138336000);
         }
         if (status.next_subtest("100:04:10.0123"))
         {
            std::string test = "100:04:10.0123";
            status.pass();
         }
#endif   // 0
      }
   }
   return status;
}

/*
 * calculations_unit_test.cpp
 *
 * vim: ts=3 sw=3 et ft=cpp
 */

