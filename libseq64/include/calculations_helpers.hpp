#ifndef XPCCUTPP_CALCULATIONS_HELPERS_HPP
#define XPCCUTPP_CALCULATIONS_HELPERS_HPP

/**
 * \file          calculations_helpers.hpp
 * \library       libseq64 (from the Sequencer64 project)
 * \author        Chris Ahlstrom
 * \date          2015-12-01
 * \updates       2015-12-05
 * \version       $Revision$
 * \license       $XPC_SUITE_GPL_LICENSE$
 *
 *    This application provides unit tests for the calculations module of the
 *    libseq64 library.
 */

#include <xpc/cut.hpp>                 /* xpc::cut_options class           */

#include "calculations.hpp"            /* seq64::calculations functions    */

extern bool extract_timing_numbers_test
(
   const xpc::cut_options & options,
   const std::string & test
);
extern bool timestring_to_pulses_test
(
   const xpc::cut_options & options,
   const std::string & test,
   seq64::midipulse target,
   int BPM,
   int PPQN
);
extern bool pulses_to_timestring_test
(
   const xpc::cut_options & options,
   seq64::midipulse test,
   const std::string & target,
   int BPM,
   int PPQN,
   bool show_settings = false
);
extern bool pulses_to_midi_measures_test
(
   const xpc::cut_options & options,
   seq64::midipulse test,
   const seq64::midi_measures & target,
   const seq64::midi_timing & mtt,
   bool show_settings = false
);
extern bool pulses_to_measurestring_test
(
   const xpc::cut_options & options,
   seq64::midipulse test,
   const std::string & target,
   const seq64::midi_timing & mtt,
   bool show_settings = false
);
extern bool midi_measures_to_pulses_test
(
   const xpc::cut_options & options,
   const seq64::midi_measures & test,
   seq64::midipulse target,
   const seq64::midi_timing & mtt,
   bool show_settings = false
);
extern bool measurestring_to_pulses_test
(
   const xpc::cut_options & options,
   const std::string & test,
   seq64::midipulse target,
   const seq64::midi_timing & mtt,
   bool show_settings = false
);

#endif   // XPCCUTPP_CALCULATIONS_HELPERS_HPP

/*
 * calculations_helpers.hpp
 *
 * vim: ts=3 sw=3 et ft=cpp
 */

