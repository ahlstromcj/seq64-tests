/**
 * \file          calculations_helpers.cpp
 * \library       libseq64 (from the Sequencer64 project)
 * \author        Chris Ahlstrom
 * \date          2015-12-01
 * \updates       2015-12-02
 * \version       $Revision$
 * \license       $XPC_SUITE_GPL_LICENSE$
 *
 *    This application provides helper functions for the calculations module of
 *    the libseq64 library.
 *
 *    We could leverage these tests better by making the complementary test at
 *    the same time.  Save a lot of code.  Also need super-tests that
 *    comprehensively survey the BPM, PPQN, W (beat-width), B (beats/measure)
 *    parameter space.
 */

#include <iostream>                    /* std::cout, std::endl             */

#include "calculations_helpers.hpp"    /* declares these helper functions  */

/*
 * Helper function to run a test of seq64::extract_timing_numbers()
 */

bool
extract_timing_numbers_test
(
   const xpc::cut_options & options,
   const std::string & test
)
{
   std::string s1, s2, s3, s4;
   bool result = seq64::extract_timing_numbers(test, s1, s2, s3, s4);
   if (options.is_verbose())
   {
      std::cout
         << "Source = '" << test << "' --> "
         << "'" << s1 << "'; "
         << "'" << s2 << "'; "
         << "'" << s3 << "'; "
         << "'" << s4 << "'"
         << std::endl
         ;
   }
   if (result)
   {
      std::string target = s1;
      target += ":";
      target += s2;
      target += ":";
      target += s3;
      target += s4;
      result = target == test;
   }
   return result;
}

/**
 * Helper function to run a test of seq64::timestring_to_pulses().
 */

bool
timestring_to_pulses_test
(
   const xpc::cut_options & options,
   const std::string & test,
   seq64::midipulse target,
   int BPM,
   int PPQN
)
{
   bool result = false;
   seq64::midipulse p = seq64::timestring_to_pulses(test, BPM, PPQN);
   if (options.is_verbose())
   {
      std::cout
         << "Source = '" << test << "' --> " << p << " pulses"
         << std::endl
         ;
   }
   result = p == target;
   return result;
}

/**
 * Helper function to run a test of seq64::pulses_to_timestring().
 */

bool
pulses_to_timestring_test
(
   const xpc::cut_options & options,
   seq64::midipulse test,
   const std::string & target,
   int BPM,
   int PPQN,
   bool show_settings
)
{
   bool result = false;
   std::string t = seq64::pulses_to_timestring(test, BPM, PPQN);
   if (options.is_verbose())
   {
      if (show_settings)
         std::cout << "BPM = " << BPM << "; PPQN = " << PPQN << std::endl;

      std::cout
         << "Source = " << test << " pulses --> '"
         << t << "' time string" << std::endl
         ;
   }
   result = t == target;
   return result;
}

/**
 * Helper function to run a test of seq64::pulses_to_midi_measures().
 */

bool
pulses_to_midi_measures_test
(
   const xpc::cut_options & options,
   seq64::midipulse test,
   const seq64::midi_measures & target,
   const seq64::midi_timing & mtt,
   bool show_settings
)
{
   seq64::midi_measures results;
   bool result = seq64::pulses_to_midi_measures(test, mtt, results);
   if (options.is_verbose())
   {
      if (show_settings)
      {
         std::cout
            << "PPQN = " << mtt.ppqn()
            << "; beats/minute = " << mtt.beats_per_minute()
            << "; beats/measure = " << mtt.beats_per_measure()
            << "; beat width = " << mtt.beat_width()
            << std::endl
            ;
      }
      std::cout
         << "Source = " << test << " pulses --> '"
         << results.measures() << ":"
         << results.beats() << ":"
         << results.divisions() << "' MIDI measures:beats:divisions"
         << std::endl
         ;
   }
   if (result)
      result = results.measures() == target.measures();

   if (result)
      result = results.beats() == target.beats();

   if (result)
      result = results.divisions() == target.divisions();

   return result;
}

/**
 * Helper function to run a test of seq64::pulses_to_measurestring().
 */

bool
pulses_to_measurestring_test
(
   const xpc::cut_options & options,
   seq64::midipulse test,
   const std::string & target,
   const seq64::midi_timing & mtt,
   bool show_setting
)
{
   std::string ms = seq64::pulses_to_measurestring(test, mtt);
   bool result = ! ms.empty();
   if (options.is_verbose())
   {
      if (show_setting)
      {
         std::cout
            << "PPQN = " << mtt.ppqn()
            << "; beats/minute = " << mtt.beats_per_minute()
            << "; beats/measure = " << mtt.beats_per_measure()
            << "; beat width = " << mtt.beat_width()
            << std::endl
            ;
      }
      std::cout
         << "Source = " << test << " pulses --> '"
         << ms << "' MIDI measures:beats:divisions"
         << std::endl
         ;
   }
   if (result)
      result = ms == target;

   return result;
}

/**
 * Helper function to run a test of seq64::midi_measures_to_pulses().
 */

bool
midi_measures_to_pulses_test
(
   const xpc::cut_options & options,
   const seq64::midi_measures & test,
   seq64::midipulse target,
   const seq64::midi_timing & mtt,
   bool show_settings
)
{
   seq64::midipulse p = seq64::midi_measures_to_pulses(test, mtt);
   bool result = p == target;
   if (options.is_verbose())
   {
      if (show_settings)
      {
         std::cout
            << "PPQN = " << mtt.ppqn()
            << "; beats/minute = " << mtt.beats_per_minute()
            << "; beats/measure = " << mtt.beats_per_measure()
            << "; beat width = " << mtt.beat_width()
            << std::endl
            ;
      }
      std::cout
         << "Source = "
         << test.measures() << ":"
         << test.beats() << ":"
         << test.divisions() << " MIDI measures:beats:divisions -->"
         << p << " pulses"
         << std::endl
         ;
   }
   return result;
}

/**
 * Helper function to run a test of seq64::measurestring_to_pulses().
 */

bool
measurestring_to_pulses_test
(
   const xpc::cut_options & options,
   const std::string & test,
   seq64::midipulse target,
   const seq64::midi_timing & mtt,
   bool show_settings
)
{
   seq64::midipulse p = seq64::measurestring_to_pulses(test, mtt);
   bool result = p == target;
   if (options.is_verbose())
   {
      if (show_settings)
      {
         std::cout
            << "PPQN = " << mtt.ppqn()
            << "; beats/minute = " << mtt.beats_per_minute()
            << "; beats/measure = " << mtt.beats_per_measure()
            << "; beat width = " << mtt.beat_width()
            << std::endl
            ;
      }
      std::cout
         << "Source = '" << test << "' MIDI measures:beats:divisions -->"
         << p << " pulses"
         << std::endl
         ;
   }
   return result;
}

/*
 * calculations_helpers.cpp
 *
 * vim: ts=3 sw=3 et ft=cpp
 */

