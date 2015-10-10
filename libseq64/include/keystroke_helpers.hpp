#ifndef XPCCUTPP_KEYSTROKE_HELPERS
#define XPCCUTPP_KEYSTROKE_HELPERS

/**
 * \file          keystroke_helpers.hpp
 * \library       libseq64 (from the Sequencer64 project)
 * \author        Chris Ahlstrom
 * \date          2015-10-10
 * \updates       2015-10-10
 * \version       $Revision$
 * \license       $XPC_SUITE_GPL_LICENSE$
 *
 *    This module provides helper functions for the unit tests of
 *    the keystroke module of the libseq64 library.
 */

#include "common_helpers.hpp"          /* CTOR_PRINCIPAL_CONSTRUCTOR          */

namespace seq64
{
   class keystroke;
}

/*
 * Global functions.
 */

extern bool check_keystroke
(
   const seq64::keystroke & k,
   unsigned int key = SEQ64_KEYSTROKE_MIN,
   bool press = SEQ64_KEYSTROKE_RELEASE,            /* false */
   int modkey = int(seq64::SEQ64_NO_MASK)
);
extern bool compare_keystrokes
(
   const seq64::keystroke & k1,
   const seq64::keystroke & k2,
   unsigned int key = SEQ64_KEYSTROKE_MIN,
   bool press = SEQ64_KEYSTROKE_RELEASE,            /* false */
   int modkey = int(seq64::SEQ64_NO_MASK)
);
extern bool keystroke_ctor_tests
(
   constructor_test_t testitem = CTOR_PRINCIPAL_CONSTRUCTOR
);

#endif         // XPCCUTPP_KEYSTROKE_HELPERS

/*
 * keystroke_helpers.hpp
 *
 * vim: ts=3 sw=3 et ft=cpp
 */
