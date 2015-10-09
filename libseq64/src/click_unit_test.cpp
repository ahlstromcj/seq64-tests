/**
 * \file          click_unit_test.cpp
 * \library       libseq64 (from the Sequencer64 project)
 * \author        Chris Ahlstrom
 * \date          2015-10-07
 * \updates       2015-10-08
 * \version       $Revision$
 * \license       $XPC_SUITE_GPL_LICENSE$
 *
 *    This application provides unit tests for the click module of the
 *    libseq64 library.
 *
 * Group:   1     "seq64::click"
 * Cases:
 *
 *    -# Default constructor and smoke test.
 *    -# Principal constructor.
 *    -# Copy constructor.
 *    -# Principal assignment operator.
 *    -# is_press()
 *    -# is_left(), is_middle(), is_right()
 *    -# x() and y()
 *    -# modifier(), mod_control(), mod_control_shift(), and mod_super()
 */

#include "click_unit_test.hpp"

/**
 *    Provides a basic "smoke test" for the click module.  A smoke test is a
 *    test of the basic functionality of the object or function.  It is an
 *    easy test that makes sure the code has basic integrity.  This test is
 *    about the simplest unit test function that can be written.
 *
 * \group
 *    1. seq64::click
 *
 * \case
 *    1. Basic smoke test.
 *
 * \note
 *    It all of these unit-tests, it is important to understand that a
 *    status coming up invalid [i.e. status.valid() == false] is \e not a
 *    test failure -- it only indicates that the status object is invalid \e
 *    or that the test is not allowed to run.
 *
 * \tests
 *    -  seq64::click::click()
 *
 * \param options
 *    Provides the command-line options for the unit-test application.
 *
 * \return
 *    Returns the unit-test status object needed by the protocol.
 */

xpc::cut_status
click_unit_test_01_01 (const xpc::cut_options & options)
{
   xpc::cut_status status(options, 1, 1, "seq64::click", _("Smoke Test"));
   bool ok = status.valid();                       /* invalidity not an error */
   if (ok)
   {
      if (! status.can_proceed())                  /* is test allowed to run? */
      {
         status.pass();                            /* no, force it to pass    */
      }
      else
      {
         if (status.next_subtest("click::click()"))
         {
            seq64::click c;
            ok = ! c.is_press();
            if (ok)
               ok = c.x() == 0;

            if (ok)
               ok = c.y() == 0;

            if (ok)
               ok = c.button() == 0;

            if (ok)
               ok = c.modifier() == seq64::SEQ64_NO_MASK;

            status.pass(ok);
         }
      }
   }
   return status;
}

/**
 *    Create a click and test it.
 */

static bool
create_and_check_click (int x, int y, int button, bool press, int modkey)
{
   seq64::click c(x, y, button, press, seq64::seq_modifier_t(modkey));
   bool result;
   if (x < CLICK_X_MIN || x >= CLICK_X_MAX)
      result = c.x() == CLICK_BAD_VALUE;
   else
      result = c.x() == x;

   if (result)
   {
      if (y < CLICK_Y_MIN || y >= CLICK_Y_MAX)
         result = c.y() == CLICK_BAD_VALUE;
      else
         result = c.y() == y;
   }
   if (result)
   {
      if (button < CLICK_BUTTON_MIN || button > CLICK_BUTTON_MAX)
         result = c.button() == CLICK_BAD_VALUE;
      else
         result = c.button() == button;

      if (CLICK_IS_LEFT(button))
      {
         result = c.is_left();
         if (result)
            result = ! c.is_middle();

         if (result)
            result = ! c.is_right();
      }
      else if (CLICK_IS_MIDDLE(button))
      {
         result = ! c.is_left();
         if (result)
            result = c.is_middle();

         if (result)
            result = ! c.is_right();
      }
      else if (CLICK_IS_RIGHT(button))
      {
         result = ! c.is_left();
         if (result)
            result = ! c.is_middle();

         if (result)
            result = c.is_right();
      }
      else
         result = false;
   }
   if (result)
      result = c.is_press() == press;

   if (result)
   {
      bool bad =
      (
         modkey < int(seq64::SEQ64_NO_MASK) ||
         modkey > int(seq64::SEQ64_MASK_MAX)
      );
      if (bad)
         result = c.modifier() == seq64::SEQ64_MASK_MAX;
      else
         result = c.modifier() == seq64::seq_modifier_t(modkey);

      if (result)
      {
         if (seq64::seq_modifier_t(modkey) & seq64::SEQ64_CONTROL_MASK)
         {
            if (seq64::seq_modifier_t(modkey) & seq64::SEQ64_SHIFT_MASK)
               result = c.mod_control_shift();
            else
               result = c.mod_control();
         }
         else if (seq64::seq_modifier_t(modkey) & seq64::SEQ64_MOD4_MASK)
            result = c.mod_super();
      }
   }
   if (! result)
   {
      std::string pb = press ? "true" : "false" ;
      fprintf
      (
         stderr, "? Bad value: click(%d, %d, %d, %s, %d)\n",
         x, y, button, pb.c_str(), modkey
      );
   }
   return result;
}

/**
 *    Provides a list of click x-values to test; the full range is a bit much.
 */

static int s_x_list [] =
{
   -1,
   CLICK_X_MIN,
   1, 2, 3,
   CLICK_X_MAX-2,
   CLICK_X_MAX-1,
   CLICK_X_MAX,
   CLICK_X_MAX+1
};
static int s_x_list_size = sizeof(s_x_list) / sizeof(int);

/**
 *    Provides a list of click y-values to test; the full range is a bit much.
 */

static int s_y_list [] =
{
   -1,
   CLICK_Y_MIN,
   1, 2, 3,
   CLICK_Y_MAX-2,
   CLICK_Y_MAX-1,
   CLICK_Y_MAX,
   CLICK_Y_MAX+1
};
static int s_y_list_size = sizeof(s_y_list) / sizeof(int);

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
 *    Passes a wide range of parameters to the principal constructor
 *    for a complete test.
 */

static bool
click_principal_ctor_tests ()
{
   bool result;
   for (int xcount = 0; xcount < s_x_list_size; ++xcount)
   {
      for (int ycount = 0; ycount < s_y_list_size; ++ycount)
      {
         for
         (
            int button = CLICK_BUTTON_MIN - 1;
            button < CLICK_BUTTON_MAX + 1;
            ++button
         )
         {
            for (int i = 0; i <= 1; ++i)
            {
               bool press = i == 1;
               for (int modcount = 0; modcount < s_mod_list_size; ++modcount)
               {
                  result = create_and_check_click
                  (
                     s_x_list[xcount], s_x_list[ycount], button, press,
                     s_mod_list[modcount]
                  );
                  if (! result)
                     break;
               }
               if (! result)
                  break;
            }
            if (! result)
               break;
         }
         if (! result)
            break;
      }
      if (! result)
         break;
   }
   return result;
}

/**
 * \group
 *    1. seq64::click
 *
 * \case
 *    2. Principal constructor
 *
 * \tests
 *    -  seq64::click::click(int parameters)
 *
 * \param options
 *    Provides the command-line options for the unit-test application.
 *
 * \return
 *    Returns the unit-test status object needed by the protocol.
 */

xpc::cut_status
click_unit_test_01_02 (const xpc::cut_options & options)
{
   xpc::cut_status status
   (
      options, 1, 2, "seq64::click", _("Principal constructor")
   );
   bool ok = status.valid();                       /* invalidity not an error */
   if (ok)
   {
      if (! status.can_proceed())                  /* is test allowed to run? */
      {
         status.pass();                            /* no, force it to pass    */
      }
      else
      {
         if (status.next_subtest("click::click()"))
         {
            ok = click_principal_ctor_tests();
            status.pass(ok);
         }
      }
   }
   return status;
}

/*
 * click_unit_test.cpp
 *
 * vim: ts=3 sw=3 et ft=cpp
 */
