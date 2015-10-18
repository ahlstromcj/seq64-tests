#ifndef XPCCUTPP_MIDIFILE_HELPERS_HPP
#define XPCCUTPP_MIDIFILE_HELPERS_HPP

/**
 * \file          midifile_helpers.hpp
 * \library       libseq64 (from the Sequencer64 project)
 * \author        Chris Ahlstrom
 * \date          2015-10-17
 * \updates       2015-10-17
 * \version       $Revision$
 * \license       $XPC_SUITE_GPL_LICENSE$
 *
 *    This module provides helper functions for the unit tests of
 *    the midifile module of the libseq64 library.
 */

#include "common_helpers.hpp"          /* CTOR_PRINCIPAL_CONSTRUCTOR          */

/*
namespace seq64
{
   class midifile;
}
*/

/*
 * Global functions.
 */

extern bool parse_midi_file
(
   seq64::perform & perf,
   const std::string & filename,
   int screenset     = 0,
   int ppqn          = SEQ64_USE_DEFAULT_PPQN,
   bool propformat   = true
);

#endif         // XPCCUTPP_MIDIFILE_HELPERS_HPP

/*
 * midifile_helpers.hpp
 *
 * vim: ts=3 sw=3 et ft=cpp
 */

