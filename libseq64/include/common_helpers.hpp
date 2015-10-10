#ifndef XPCCUTPP_COMMON_HELPERS
#define XPCCUTPP_COMMON_HELPERS

/**
 * \file          common_helpers.hpp
 * \library       libseq64 (from the Sequencer64 project)
 * \author        Chris Ahlstrom
 * \date          2015-10-10
 * \updates       2015-10-10
 * \version       $Revision$
 * \license       $XPC_SUITE_GPL_LICENSE$
 *
 *    This modules provides helper data and types for the unit tests of
 *    the various modules of the libseq64 library.
 */

#include "gdk_basic_keys.h"            /* seq64::seq_modifier_t               */

/**
 *    Indicates which constructor is to be tested.  We could test them all
 *    at once, but would like to be able to pinpoint which one, if any,
 *    failed during a test.
 */

enum constructor_test_t
{
   CTOR_PRINCIPAL_CONSTRUCTOR,
   CTOR_COPY_CONSTRUCTOR,
   CTOR_PRINCIPAL_ASSIGNMENT_OPERATOR
};

/*
 *    Provides a list of modifier-values to test.
 */

extern seq64::seq_modifier_t key_mod (int index);
extern int key_mod_list_size ();

#endif         // XPCCUTPP_COMMON_HELPERS

/*
 * common_helpers.hpp
 *
 * vim: ts=3 sw=3 et ft=cpp
 */
