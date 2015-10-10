#ifndef XPCCUTPP_CLICK_HELPERS
#define XPCCUTPP_CLICK_HELPERS

/**
 * \file          click_helpers.cpp
 * \library       libseq64 (from the Sequencer64 project)
 * \author        Chris Ahlstrom
 * \date          2015-10-09
 * \updates       2015-10-09
 * \version       $Revision$
 * \license       $XPC_SUITE_GPL_LICENSE$
 *
 *    This application provides helper functions for the unit tests of
 *    the click module of the libseq64 library.
 */

namespace seq64
{
   class click;
}

/**
 *    Indicates which constructor is to be tested.  We could test them all
 *    at once, but would like to be able to pinpoint which one, if any,
 *    failed during a test.
 */

enum click_test_t
{
   CT_PRINCIPAL_CONSTRUCTOR,
   CT_COPY_CONSTRUCTOR,
   CT_PRINCIPAL_ASSIGNMENT_OPERATOR
};

/*
 * Global functions.
 */

extern bool check_click
(
   const seq64::click & c,
   int x = SEQ64_CLICK_X_MIN,
   int y = SEQ64_CLICK_Y_MIN,
   int button = SEQ64_CLICK_BUTTON_LEFT,
   bool press = SEQ64_CLICK_RELEASE,            /* false */
   int modkey = int(seq64::SEQ64_NO_MASK)
);
extern bool compare_clicks
(
   const seq64::click & c1,
   const seq64::click & c2,
   int x = SEQ64_CLICK_X_MIN,
   int y = SEQ64_CLICK_Y_MIN,
   int button = SEQ64_CLICK_BUTTON_LEFT,
   bool press = SEQ64_CLICK_RELEASE,            /* false */
   int modkey = int(seq64::SEQ64_NO_MASK)
);
extern bool click_ctor_tests (click_test_t testitem = CT_PRINCIPAL_CONSTRUCTOR);

#endif         // XPCCUTPP_CLICK_HELPERS

/*
 * click_helpers.cpp
 *
 * vim: ts=3 sw=3 et ft=cpp
 */
