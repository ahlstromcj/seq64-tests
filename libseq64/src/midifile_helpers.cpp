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

#include "gui_assistant_dummy.hpp"     /* qui_assistant_dummy stubby class    */
#include "midifile.hpp"                /* seq64::midifile class               */
#include "midifile_helpers.hpp"        /* constructor_test_t and functions    */
#include "perform.hpp"                 /* seq64::perform                      */

/**
 *    Opens a MIDI file and commences a parse operation very similar to what
 *    mainwnd::open_file() does.
 */

static bool
parse_midi_file
(
   seq64::perform & perf,
   const std::string & filename,
   int screenset     = 0,
   int ppqn          = SEQ64_USE_DEFAULT_PPQN,
   bool propformat   = true
)
{
   seq64::midifile f(filename, ppqn, propformat);
   perf.clear_all();
   bool result = f.parse(perf, screenset);
   if (result)
      ppqn = f.ppqn();

   return result;
}

/**
 *    Exercises the midifile.  It creates a perform object much like the
 *    sequencer64.cpp's main() function does, then calls
 *    seq64::midifile::parse().
 */

bool
midifile_parse_test (const std::string & filename)
{
   gui_assistant_dummy g;
   seq64::perform p(g);
   bool result = parse_midi_file(p, filename);
   return result;
}

/**
 *    Exercises the midifile, for two MIDI files.  Hopefully, this will
 *    show that a perform object can be safely cleared and re-used, and, when
 *    run under valgrind, will show any memory leaks we should handle.
 */

bool
midifile_dual_parse_test
(
   const std::string & fname1,
   const std::string & fname2
)
{
   gui_assistant_dummy g;
   seq64::perform p(g);
   bool result = parse_midi_file(p, fname1);
   if (result)
      result = parse_midi_file(p, fname2);

   return result;
}

/**
 *    Opens a MIDI file and commences a write operation very similar to what
 *    mainwnd::save_file() does.
 */

static bool
write_midi_file
(
   seq64::perform & perf,
   const std::string & filename,
   int ppqn          = SEQ64_USE_DEFAULT_PPQN,
   bool propformat   = true
)
{
   seq64::midifile f(filename, ppqn, propformat);
   bool result = f.write(perf);
   return result;
}

/**
 *    Exercises the midifile writing.
 */

bool
midifile_write_test (const std::string & filename)
{
   gui_assistant_dummy g;
   seq64::perform p(g);
   bool result = parse_midi_file(p, filename);
   if (result)
   {
      std::string backup_filename = filename;
      backup_filename += "-bak";
      result = write_midi_file(p, backup_filename, 192 /* ppqn */);
   }
   return result;
}

/*
 * midifile_helpers.cpp
 *
 * vim: ts=3 sw=3 et ft=cpp
 */
