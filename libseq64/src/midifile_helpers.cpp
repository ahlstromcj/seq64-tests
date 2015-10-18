/**
 * \file          midifile_helpers.cpp
 * \library       libseq64 (from the Sequencer64 project)
 * \author        Chris Ahlstrom
 * \date          2015-10-17
 * \updates       2015-10-18
 * \version       $Revision$
 * \license       $XPC_SUITE_GPL_LICENSE$
 *
 *    This module provides helper functions for the unit tests of the midifile
 *    module of the libseq64 library.  These tests will perforce also cover
 *    some of the functionality of the sequence and event classes, but without
 *    having to worry about the manipulations and leakages of GUI elements.
 */

#include <string>

#include "midifile.hpp"                /* seq64::midifile class               */
#include "midifile_helpers.hpp"        /* constructor_test_t and functions    */
#include "perform.hpp"                 /* seq64::perform                      */

/**
 *    Opens a MIDI file and commences a parse operation very similar to what
 *    mainwnd::open_file() does.
 */

bool
parse_midi_file
(
   seq64::perform & perf,
   const std::string & filename,
   int screenset,
   int ppqn,
   bool propformat
)
{
   seq64::midifile f(filename, ppqn, propformat);
   perf.clear_all();
   bool result = f.parse(perf, screenset);
   if (result)
      ppqn = f.ppqn();

   return result;
}

/*
 * midifile_helpers.cpp
 *
 * vim: ts=3 sw=3 et ft=cpp
 */
