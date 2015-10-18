/**
 * \file          libseq64_unit_test.cpp
 * \library       libseq64 (from the Sequencer64 project)
 * \author        Chris Ahlstrom
 * \date          2015-10-06
 * \updates       2015-10-18
 * \version       $Revision$
 * \license       $XPC_SUITE_GPL_LICENSE$
 *
 *    This application provides a few unit tests of the libseq64
 *    library module.
 */

#include "click_unit_test.hpp"
#include "keystroke_unit_test.hpp"
#include "midifile_unit_test.hpp"

/**
 *    This is the main routine for the libseq64_unit_test application.
 *
 * \note
 *    Parse for any additional (non-unittest) arguments.  Don't try to find
 *    erroneous options in this loop.  If a valid option is found, then turn
 *    off the complaint flag to avoid error messages.  Note that a better
 *    way to do this work is to derive a class from unit-test and extend it
 *    to support the additional variables.  (In this case, it is likely that
 *    one would also want to extend the TestOptions class.
 *
 * \return
 *    Returns POSIX_SUCCESS (0) if the function succeeds.  Other values,
 *    including possible error-codes, are returned otherwise.
 *
 */

#define SEQ64_APP_NAME           "Sequencer64 libseq64"
#define SEQ64_TEST_NAME          "libseq64_unit_test 2015-10-18"
#define SEQ64_TEST_VERSION       1.1.2
#define DEFAULT_AUTHOR           "Chris Ahlstrom"

int
main
(
   int argc,               /**< Number of command-line arguments.             */
   char * argv []          /**< The actual array of command-line arguments.   */
)
{
   static const char * const additional_help =

"\n"
SEQ64_TEST_NAME "-specific options:\n"
"\n"
" --none             No options for this unit-test, at present ....\n"

   ;

   xpc::cut testbattery
   (
      argc, argv,
      std::string(SEQ64_TEST_NAME),
      std::string(XPCCUT_VERSION_STRING(SEQ64_TEST_VERSION)),
      std::string(additional_help)
   );
   bool ok = testbattery.valid();
   if (ok)
   {
      int argcount = argc;
      char ** arglist = argv;
      cbool_t load_the_tests = true;
      if (argcount > 1)
      {
         int currentarg = 1;
         while (currentarg < argcount)
         {
            std::string arg = arglist[currentarg];
            if (arg == "--none")
            {
               // currentarg++;
               // if ((currentarg < argcount) && (arglist[currentarg] != 0))
               //    strcpy(gsBasename, arglist[currentarg]);
            }
            currentarg++;
         }
      }
      if (load_the_tests)
      {
         /*
          * Unit tests for the click module/group/class:
          */

         ok = testbattery.load(click_unit_test_01_01);
         if (ok) ok = testbattery.load(click_unit_test_01_02);
         if (ok) ok = testbattery.load(click_unit_test_01_03);
         if (ok) ok = testbattery.load(click_unit_test_01_04);

         /*
          * Unit tests for the keystroke module/group/class:
          */

         if (ok) ok = testbattery.load(keystroke_unit_test_01_01);
         if (ok) ok = testbattery.load(keystroke_unit_test_01_02);
         if (ok) ok = testbattery.load(keystroke_unit_test_01_03);
         if (ok) ok = testbattery.load(keystroke_unit_test_01_04);

         /*
          * Unit tests for the midifile module/group/class:
          */

         if (ok) ok = testbattery.load(midifile_unit_test_01_01);
      }
      if (ok)
         ok = testbattery.run();
      else
         xpccut_errprint(_("load of the unit-test functions failed"));
   }
   return ok ? EXIT_SUCCESS : EXIT_FAILURE ;
}

/*
 * libseq64_unit_test.cpp
 *
 * vim: ts=3 sw=3 et ft=cpp
 */
