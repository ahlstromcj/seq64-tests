#ifndef CLICK_UNIT_TEST_HPP
#define CLICK_UNIT_TEST_HPP

/**
 * \file          click_unit_test.hpp
 * \library       libseq64 (from the Sequencer64 project)
 * \author        Chris Ahlstrom
 * \date          2015-10-07
 * \updates       2015-10-09
 * \version       $Revision$
 * \license       $XPC_SUITE_GPL_LICENSE$
 *
 *    This application provides unit tests for the click module of the
 *    libseq64 library.
 */

#include <xpc/cut.hpp>                 /* xpc::cut unit-test class            */

extern xpc::cut_status click_unit_test_01_01 (const xpc::cut_options & options);
extern xpc::cut_status click_unit_test_01_02 (const xpc::cut_options & options);
extern xpc::cut_status click_unit_test_01_03 (const xpc::cut_options & options);
extern xpc::cut_status click_unit_test_01_04 (const xpc::cut_options & options);

#endif   // CLICK_UNIT_TEST_HPP

/*
 * click_unit_test.hpp
 *
 * vim: ts=3 sw=3 et ft=cpp
 */
