#ifndef XPCCUTPP_MIDIFILE_HELPERS_HPP
#define XPCCUTPP_MIDIFILE_HELPERS_HPP

/**
 * \file          midifile_helpers.hpp
 * \library       libseq64 (from the Sequencer64 project)
 * \author        Chris Ahlstrom
 * \date          2015-10-17
 * \updates       2015-10-18
 * \version       $Revision$
 * \license       $XPC_SUITE_GPL_LICENSE$
 *
 *    This module provides helper functions for the unit tests of
 *    the midifile module of the libseq64 library.
 */

#include "common_helpers.hpp"          /* CTOR_PRINCIPAL_CONSTRUCTOR          */


/*
 * Global functions.
 */

extern bool midifile_parse_test (const std::string & filename);
extern bool midifile_dual_parse_test
(
   const std::string & fname1,
   const std::string & fname2
);
extern bool midifile_write_test (const std::string & filename);

#endif         // XPCCUTPP_MIDIFILE_HELPERS_HPP

/*
 * midifile_helpers.hpp
 *
 * vim: ts=3 sw=3 et ft=cpp
 */

