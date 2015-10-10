/**
 * \file          common_helpers.cpp
 * \library       libseq64 (from the Sequencer64 project)
 * \author        Chris Ahlstrom
 * \date          2015-10-10
 * \updates       2015-10-10
 * \version       $Revision$
 * \license       $XPC_SUITE_GPL_LICENSE$
 *
 *    This modules provides helper data for the unit tests of
 *    the various modules of the libseq64 library.
 */

#include <string>

#include "common_helpers.hpp"           /* click_test_t and functions          */

/**
 *    Provides a list of click modifier-values to test; the full range is a
 *    bit much.
 */

static seq64::seq_modifier_t s_mod_list [] =
{
    seq64::SEQ64_NO_MASK,
    seq64::SEQ64_SHIFT_MASK,
    seq64::SEQ64_LOCK_MASK,
    seq64::SEQ64_CONTROL_MASK,
    seq64::seq_modifier_t(seq64::SEQ64_CONTROL_MASK | seq64::SEQ64_SHIFT_MASK),
    seq64::SEQ64_MOD1_MASK,
    seq64::SEQ64_MOD2_MASK,
    seq64::SEQ64_MOD3_MASK,
    seq64::SEQ64_MOD4_MASK,
    seq64::SEQ64_MOD5_MASK,
    seq64::SEQ64_BUTTON1_MASK,
    seq64::SEQ64_BUTTON2_MASK,
    seq64::SEQ64_BUTTON3_MASK,
    seq64::SEQ64_BUTTON4_MASK,
    seq64::SEQ64_BUTTON5_MASK,

   /*
    * Bits 13 and 14 are used by XKB, bits 15 to 25 are unused. Bit 29 is
    * used internally.
    */

    seq64::SEQ64_SUPER_MASK,
    seq64::SEQ64_HYPER_MASK,
    seq64::SEQ64_META_MASK,
    seq64::SEQ64_RELEASE_MASK,
    seq64::SEQ64_MASK_MAX
};
static int s_mod_list_size = sizeof(s_mod_list) / sizeof(seq64::seq_modifier_t);

/**
 *    Provides an accessor to the elements of the static list of seq64 key
 *    modifier values to test.
 */

seq64::seq_modifier_t
key_mod (int index)
{
   seq64::seq_modifier_t result = seq64::SEQ64_MASK_MAX;
   if (index >= 0 && index < s_mod_list_size)
      result = s_mod_list[index];

   return result;
}

/**
 *    Provides an accessor to the size of the static list of seq64 key
 *    modifier values to test.
 */

int
key_mod_list_size ()
{
   return s_mod_list_size;
}

/*
 * common_helpers.cpp
 *
 * vim: ts=3 sw=3 et ft=cpp
 */
