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
 *    -# seg64::pulses_to_timestring() [string output]
 *    -# seg64::pulses_to_midi_measures()
 *    -# seg64::pulses_to_measuresstring() [string output]
 *
 *    -# seg64::midi_measures_to_pulses()
 *    -# seg64::measurestring_to_pulses() [string input]
 */

#include <iostream>                    /* std::cout, std::endl             */

#include "calculations_helpers.hpp"
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
         std::string test = "0:0:0";
         if (status.next_subtest(test))
         {
            bool ok = extract_timing_numbers_test(options, test);
            status.pass(ok);
         }
         test = "0:0:0.0";
         if (status.next_subtest(test))
         {
            bool ok = extract_timing_numbers_test(options, test);
            status.pass(ok);
         }
         test = "100:04:10";
         if (status.next_subtest(test))
         {
            bool ok = extract_timing_numbers_test(options, test);
            status.pass(ok);
         }
         test = "100:04:10.0123";
         if (status.next_subtest(test))
         {
            bool ok = extract_timing_numbers_test(options, test);
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
      if (! status.can_proceed())                  /* is test allowed to run? */
      {
         status.pass();                            /* no, force it to pass    */
      }
      else
      {
         int B = 120;
         int P = 192;
         std::string test = "0:0:0";            /* kind of a smoke test    */
         if (status.next_subtest(test))
         {
            bool ok = timestring_to_pulses_test(options, test, 0, B, P);
            status.pass(ok);
         }
         test = "0:0:0.0";
         if (status.next_subtest(test))
         {
            bool ok = timestring_to_pulses_test(options, test, 0, B, P);
            status.pass(ok);
         }
         test = "100:04:10";
         if (status.next_subtest(test))
         {
            /*
             * Result should be (100 * 3600 + 4 * 60 + 10) * 1000000
             * microseconds, which is then multiplied by (120 * 192) and
             * divided by (60 * 1000000).
             */

            bool ok = timestring_to_pulses_test
            (
               options, test, 138336000, B, P
            );
            status.pass(ok);
         }
         test = "100:04:10.0124";
         if (status.next_subtest(test))
         {
            // TODO
            status.pass();
         }

         /*
          * Now up the PPQN by a factor of 5, and re-do the tests.
          */

         P = 192 * 5;                     /* 960 PPQN */
         test = "0:0:0";
         if (status.next_subtest(test))
         {
            bool ok = timestring_to_pulses_test(options, test, 0, B, P);
            status.pass(ok);
         }
         test = "0:0:0.0";
         if (status.next_subtest(test))
         {
            bool ok = timestring_to_pulses_test(options, test, 0, B, P);
            status.pass(ok);
         }
         test = "100:04:10";
         if (status.next_subtest(test))
         {
            /*
             * Result should be (100 * 3600 + 4 * 60 + 10) * 1000000
             * microseconds, which is then multiplied by (120 * 192) and
             * divided by (60 * 1000000).
             */

            bool ok = timestring_to_pulses_test
            (
//             options, test, 138336000, B, P
               options, test, 5 * 138336000, B, P
            );
            status.pass(ok);
         }
         test = "100:04:10.0124";
         if (status.next_subtest(test))
         {
            // TODO
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
      if (! status.can_proceed())                  /* is test allowed to run? */
      {
         status.pass();                            /* no, force it to pass    */
      }
      else
      {
         int B = 120;                              /* BPM                     */
         int P = 192;                              /* PPQN                    */
         if (status.next_subtest("0"))
         {
            /*
             * We pass true in this first test to show the other settings, just
             * once.
             */

            bool ok = pulses_to_timestring_test(options, 0, "0:0:0", B, P, true);
            status.pass(ok);
         }
         if (status.next_subtest("1"))             /* the size of one pulse */
         {
            bool ok = pulses_to_timestring_test(options, 1, "0:0:0.002604", B, P);
            status.pass(ok);
         }
         if (status.next_subtest("PPQN"))
         {
            bool ok = pulses_to_timestring_test(options, P, "0:0:0.500000", B, P);
            status.pass(ok);
         }
         if (status.next_subtest("2*PPQN"))
         {
            bool ok = pulses_to_timestring_test(options, 2*P, "0:0:1", B, P);
            status.pass(ok);
         }
         if (status.next_subtest("3*PPQN"))
         {
            bool ok = pulses_to_timestring_test
            (
               options, 3*P, "0:0:1.500000", B, P
            );
            status.pass(ok);
         }
         if (status.next_subtest("4*PPQN"))
         {
            bool ok = pulses_to_timestring_test(options, 4*P, "0:0:2", B, P);
            status.pass(ok);
         }
         if (status.next_subtest("BPM/2*PPQN"))
         {
            bool ok = pulses_to_timestring_test(options, P*B/2, "0:0:30", B, P);
            status.pass(ok);
         }
         if (status.next_subtest("BPM*PPQN"))
         {
            bool ok = pulses_to_timestring_test(options, B*P, "0:1:0", B, P);
            status.pass(ok);
         }
         if (status.next_subtest("(BPM+1)*PPQN"))
         {
            bool ok = pulses_to_timestring_test
            (
               options, (B+1)*P, "0:1:0.500000", B, P
            );
            status.pass(ok);
         }
         if (status.next_subtest("60*BPM*PPQN"))
         {
            bool ok = pulses_to_timestring_test(options, 60*B*P, "1:0:0", B, P);
            status.pass(ok);
         }

         /*
          * Now up the PPQN by a factor of 5, and re-do the tests.
          */

         P = 192 * 5;                     /* 960 PPQN */
         if (status.next_subtest("0"))
         {
            /*
             * We pass true in this first test to show the other settings, just
             * once.
             */

            bool ok = pulses_to_timestring_test(options, 0, "0:0:0", B, P, true);
            status.pass(ok);
         }
         if (status.next_subtest("1"))             /* the size of one pulse */
         {
            bool ok = pulses_to_timestring_test(options, 1, "0:0:0.000520", B, P);
            status.pass(ok);
         }
         if (status.next_subtest("PPQN"))
         {
            bool ok = pulses_to_timestring_test(options, P, "0:0:0.500000", B, P);
            status.pass(ok);
         }
         if (status.next_subtest("2*PPQN"))
         {
            bool ok = pulses_to_timestring_test(options, 2*P, "0:0:1", B, P);
            status.pass(ok);
         }
         if (status.next_subtest("3*PPQN"))
         {
            bool ok = pulses_to_timestring_test
            (
               options, 3*P, "0:0:1.500000", B, P
            );
            status.pass(ok);
         }
         if (status.next_subtest("4*PPQN"))
         {
            bool ok = pulses_to_timestring_test(options, 4*P, "0:0:2", B, P);
            status.pass(ok);
         }
         if (status.next_subtest("BPM/2*PPQN"))
         {
            bool ok = pulses_to_timestring_test(options, P*B/2, "0:0:30", B, P);
            status.pass(ok);
         }
         if (status.next_subtest("BPM*PPQN"))
         {
            bool ok = pulses_to_timestring_test(options, B*P, "0:1:0", B, P);
            status.pass(ok);
         }
         if (status.next_subtest("(BPM+1)*PPQN"))
         {
            bool ok = pulses_to_timestring_test
            (
               options, (B+1)*P, "0:1:0.500000", B, P
            );
            status.pass(ok);
         }
         if (status.next_subtest("60*BPM*PPQN"))
         {
            bool ok = pulses_to_timestring_test(options, 60*B*P, "1:0:0", B, P);
            status.pass(ok);
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
 *    4. seq64::pulses_to_midi_measures()
 *
 * \tests
 *    -  BPM = 120, PPQN = 192
 *       -  seq64::pulses_to_midi_measures(0)
 *
 * \param options
 *    Provides the command-line options for the unit-test application.
 *
 * \return
 *    Returns the unit-test status object needed by the protocol.
 */

xpc::cut_status
calculations_unit_test_04_04 (const xpc::cut_options & options)
{
   xpc::cut_status status
   (
      options, 4, 4, "seq64::calculations", "pulses_to_midi_measures()"
   );
   bool ok = status.valid();                    /* invalidity not an error */
   if (ok)
   {
      if (! status.can_proceed())               /* is test allowed to run? */
      {
         status.pass();                         /* no, force it to pass    */
      }
      else
      {
         bool ok = true;
         int P = 192;                           /* PPQN                    */
         seq64::midi_timing_t mtt;              /* holds MIDI parameters   */
         mtt.mt_beats_per_minute = 0;           /* BPM is not needed here  */
         mtt.mt_beats_per_measure = 4;
         mtt.mt_beat_width = 4;
         mtt.mt_ppqn = P;

         seq64::midi_measures_t target;         /* tailored for each test  */
         target.mm_measures = 1;                /* it's re 1, not 0        */
         target.mm_beats = 1;                   /* it's re 1, not 0        */
         target.mm_divisions = 0;               /* it's re 0, not 1        */
         if (status.next_subtest("0"))
         {
            /*
             * We pass true in this first test to show the other settings, just
             * once.
             */

            ok = pulses_to_midi_measures_test(options, 0, target, mtt, true);
            status.pass(ok);
         }
         if (status.next_subtest("1"))
         {
            target.mm_divisions = 1;
            ok = pulses_to_midi_measures_test(options, 1, target, mtt);
            status.pass(ok);
         }
         if (status.next_subtest("PPQN-1"))
         {
            target.mm_divisions = P-1;
            ok = pulses_to_midi_measures_test(options, P-1, target, mtt);
            status.pass(ok);
         }
         if (status.next_subtest("PPQN"))
         {
            target.mm_beats = 2;
            target.mm_divisions = 0;
            ok = pulses_to_midi_measures_test(options, P, target, mtt);
            status.pass(ok);
         }
         if (status.next_subtest("PPQN+1"))
         {
            target.mm_beats = 2;
            target.mm_divisions = 1;
            ok = pulses_to_midi_measures_test(options, P+1, target, mtt);
            status.pass(ok);
         }
         if (status.next_subtest("2*PPQN"))
         {
            target.mm_beats = 3;
            target.mm_divisions = 0;
            ok = pulses_to_midi_measures_test(options, 2*P, target, mtt);
            status.pass(ok);
         }
         if (status.next_subtest("3*PPQN"))
         {
            target.mm_beats = 4;
            target.mm_divisions = 0;
            ok = pulses_to_midi_measures_test(options, 3*P, target, mtt);
            status.pass(ok);
         }
         if (status.next_subtest("4*PPQN"))
         {
            target.mm_measures = 2;
            target.mm_beats = 1;
            target.mm_divisions = 0;
            ok = pulses_to_midi_measures_test(options, 4*P, target, mtt);
            status.pass(ok);
         }

         // MORE MORE MORE

         /*
          * Now up the PPQN by a factor of 5, and re-do the tests.  We also
          * have to modify the parameter structure and reset the target
          * structure back to it "first sub-test" settings.
          */

         P = 192 * 5;                     /* 960 PPQN */
         mtt.mt_ppqn = P;
         target.mm_measures = 1;                /* it's re 1, not 0        */
         target.mm_beats = 1;                   /* it's re 1, not 0        */
         target.mm_divisions = 0;               /* it's re 0, not 1        */
         if (status.next_subtest("0"))
         {
            /*
             * We pass true in this first test to show the other settings, just
             * once.
             */

            ok = pulses_to_midi_measures_test(options, 0, target, mtt, true);
            status.pass(ok);
         }
         if (status.next_subtest("1"))
         {
            target.mm_divisions = 1;
            ok = pulses_to_midi_measures_test(options, 1, target, mtt);
            status.pass(ok);
         }
         if (status.next_subtest("PPQN-1"))
         {
            target.mm_divisions = P-1;
            ok = pulses_to_midi_measures_test(options, P-1, target, mtt);
            status.pass(ok);
         }
         if (status.next_subtest("PPQN"))
         {
            target.mm_beats = 2;
            target.mm_divisions = 0;
            ok = pulses_to_midi_measures_test(options, P, target, mtt);
            status.pass(ok);
         }
         if (status.next_subtest("PPQN+1"))
         {
            target.mm_beats = 2;
            target.mm_divisions = 1;
            ok = pulses_to_midi_measures_test(options, P+1, target, mtt);
            status.pass(ok);
         }
         if (status.next_subtest("2*PPQN"))
         {
            target.mm_beats = 3;
            target.mm_divisions = 0;
            ok = pulses_to_midi_measures_test(options, 2*P, target, mtt);
            status.pass(ok);
         }
         if (status.next_subtest("3*PPQN"))
         {
            target.mm_beats = 4;
            target.mm_divisions = 0;
            ok = pulses_to_midi_measures_test(options, 3*P, target, mtt);
            status.pass(ok);
         }
         if (status.next_subtest("4*PPQN"))
         {
            target.mm_measures = 2;
            target.mm_beats = 1;
            target.mm_divisions = 0;
            ok = pulses_to_midi_measures_test(options, 4*P, target, mtt);
            status.pass(ok);
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
 *    5. seq64::pulses_to_measurestring()
 *
 * \tests
 *    -  BPM = 120, PPQN = 192
 *       -  seq64::pulses_to_measurestring(0)
 *
 * \param options
 *    Provides the command-line options for the unit-test application.
 *
 * \return
 *    Returns the unit-test status object needed by the protocol.
 */

xpc::cut_status
calculations_unit_test_04_05 (const xpc::cut_options & options)
{
   xpc::cut_status status
   (
      options, 4, 5, "seq64::calculations", "pulses_to_measurestring()"
   );
   bool ok = status.valid();                    /* invalidity not an error */
   if (ok)
   {
      if (! status.can_proceed())               /* is test allowed to run? */
      {
         status.pass();                         /* no, force it to pass    */
      }
      else
      {
         bool ok = true;
         int P = 192;                           /* PPQN                    */
         seq64::midi_timing_t mtt;              /* holds MIDI parameters   */
         mtt.mt_beats_per_minute = 0;           /* BPM is not needed here  */
         mtt.mt_beats_per_measure = 4;
         mtt.mt_beat_width = 4;
         mtt.mt_ppqn = P;
         if (status.next_subtest("0"))
         {
            /*
             * We pass true in this first test to show the other settings, just
             * once.
             */

            ok = pulses_to_measurestring_test(options, 0, "1:1:0", mtt, true);
            status.pass(ok);
         }
         if (status.next_subtest("1"))
         {
            ok = pulses_to_measurestring_test(options, 1, "1:1:1", mtt);
            status.pass(ok);
         }
         if (status.next_subtest("PPQN-1"))
         {
            ok = pulses_to_measurestring_test(options, P-1, "1:1:191", mtt);
            status.pass(ok);
         }
         if (status.next_subtest("PPQN"))
         {
            ok = pulses_to_measurestring_test(options, P, "1:2:0", mtt);
            status.pass(ok);
         }
         if (status.next_subtest("PPQN+1"))
         {
            ok = pulses_to_measurestring_test(options, P+1, "1:2:1", mtt);
            status.pass(ok);
         }
         if (status.next_subtest("2*PPQN"))
         {
            ok = pulses_to_measurestring_test(options, 2*P, "1:3:0", mtt);
            status.pass(ok);
         }
         if (status.next_subtest("3*PPQN"))
         {
            ok = pulses_to_measurestring_test(options, 3*P, "1:4:0", mtt);
            status.pass(ok);
         }
         if (status.next_subtest("4*PPQN"))
         {
            ok = pulses_to_measurestring_test(options, 4*P, "2:1:0", mtt);
            status.pass(ok);
         }

         // MORE MORE MORE

         /*
          * Now up the PPQN by a factor of 5, and re-do the tests.  We also
          * have to modify the parameter structure.
          */

         P = 5 * 192;
         mtt.mt_ppqn = P;
         if (status.next_subtest("0"))
         {
            /*
             * We pass true in this first test to show the other settings, just
             * once.
             */

            ok = pulses_to_measurestring_test(options, 0, "1:1:0", mtt, true);
            status.pass(ok);
         }
         if (status.next_subtest("1"))
         {
            ok = pulses_to_measurestring_test(options, 1, "1:1:1", mtt);
            status.pass(ok);
         }
         if (status.next_subtest("PPQN-1"))
         {
            ok = pulses_to_measurestring_test(options, P-1, "1:1:959", mtt);
            status.pass(ok);
         }
         if (status.next_subtest("PPQN"))
         {
            ok = pulses_to_measurestring_test(options, P, "1:2:0", mtt);
            status.pass(ok);
         }
         if (status.next_subtest("PPQN+1"))
         {
            ok = pulses_to_measurestring_test(options, P+1, "1:2:1", mtt);
            status.pass(ok);
         }
         if (status.next_subtest("2*PPQN"))
         {
            ok = pulses_to_measurestring_test(options, 2*P, "1:3:0", mtt);
            status.pass(ok);
         }
         if (status.next_subtest("3*PPQN"))
         {
            ok = pulses_to_measurestring_test(options, 3*P, "1:4:0", mtt);
            status.pass(ok);
         }
         if (status.next_subtest("4*PPQN"))
         {
            ok = pulses_to_measurestring_test(options, 4*P, "2:1:0", mtt);
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

