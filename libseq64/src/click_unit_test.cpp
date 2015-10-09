/**
 * \file          click_unit_test.cpp
 * \library       libseq64 (from the Sequencer64 project)
 * \author        Chris Ahlstrom
 * \date          2015-10-07
 * \updates       2015-10-09
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

#include "click.hpp"                   /* seq64::click class                  */
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
 *    Check the given click and test it against the given (and expected)
 *    parameters. Note that the defaults of the expected parameters match
 *    the values assumed by the default click constructor.  This match is
 *    set up for convenience in testing.
 */

static bool
check_click
(
   const seq64::click & c,
   int x = CLICK_X_MIN,
   int y = CLICK_Y_MIN,
   int button = CLICK_BUTTON_LEFT,
   bool press = false,
   int modkey = int(seq64::SEQ64_NO_MASK)
)
{
   bool result = false;
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
      {
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
   }
   if (result)
      result = c.is_press() == press;

   if (result)
   {
      unsigned int um = (unsigned int)(modkey); // we could use static_cast<>
      bool bad = um >= (unsigned int)(seq64::SEQ64_MASK_MAX);
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
 *    Check an existing click against itself and another one.  Use for
 *    checking the copy constructor and principal assignment operator.
 *    Note that the comparison does not use an operator ==(), since there is
 *    none defined for seq64::click -- none is needed.
 */

static bool
compare_clicks
(
   const seq64::click & c1,
   const seq64::click & c2
)
{
   bool result = check_click(c1);
   if (result)
      result = check_click(c2);

   if (result)
   {
      result = c1.is_press() == c2.is_press();
      if (result)
         result = c1.x() == c2.x();

      if (result)
         result = c1.y() == c2.y();

      if (result)
         result = c1.button() == c2.button();

      if (result)
         result = c1.modifier() == c2.modifier();
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

/**
 *    Passes a wide range of parameters to the principal constructor, copy
 *    constructor, and principle assignment operator for a complete-enough
 *    test of these functions.
 */

static bool
click_ctor_tests (click_test_t testitem = CT_PRINCIPAL_CONSTRUCTOR)
{
   bool result;
   for (int xi = 0; xi < s_x_list_size; ++xi)
   {
      for (int yi = 0; yi < s_y_list_size; ++yi)
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
               for (int m = 0; m < s_mod_list_size; ++m)
               {
                  int x = s_x_list[xi];
                  int y = s_y_list[yi];
                  seq64::seq_modifier_t smt = s_mod_list[m];
                  seq64::click c(x, y, button, press, smt);
                  if (testitem == CT_PRINCIPAL_CONSTRUCTOR)
                     result = check_click(c, x, y, button, press, smt);
                  else if (testitem == CT_COPY_CONSTRUCTOR)
                  {
                     seq64::click c2(c);                    /* copy object    */
                     result = compare_clicks(c, c2);
                  }
                  else if (testitem == CT_PRINCIPAL_ASSIGNMENT_OPERATOR)
                  {
                     seq64::click c2;
                     /*
                      * Make sure the compiler doesn't "optimize" assignment
                      * into a copy constructor, unlikely though that may
                      * be.
                      */

                     (void) c2.operator =(c);
                     result = compare_clicks(c, c2);
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
            ok = click_ctor_tests();
            status.pass(ok);
         }
      }
   }
   return status;
}

/**
 * \group
 *    1. seq64::click
 *
 * \case
 *    3. Copy constructor
 *
 * \tests
 *    -  seq64::click::click(click)
 *
 * \param options
 *    Provides the command-line options for the unit-test application.
 *
 * \return
 *    Returns the unit-test status object needed by the protocol.
 */

xpc::cut_status
click_unit_test_01_03 (const xpc::cut_options & options)
{
   xpc::cut_status status
   (
      options, 1, 3, "seq64::click", _("Copy constructor")
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
         if (status.next_subtest("Default"))
         {
            seq64::click c1;
            seq64::click c2;
            ok = compare_clicks(c1, c2);
            status.pass(ok);
         }
         if (status.next_subtest("Copy default"))
         {
            seq64::click c1;
            seq64::click c2(c1);
            ok = compare_clicks(c1, c2);
            status.pass(ok);
         }
         if (status.next_subtest("Assign default"))
         {
            seq64::click c1;
            seq64::click c2;
            c2 = c1;
            ok = compare_clicks(c1, c2);
            status.pass(ok);
         }
         if (status.next_subtest("operator =()"))
         {
            seq64::click c1;
            seq64::click c2;
            (void) c2.operator =(c1);
            ok = compare_clicks(c1, c2);
            status.pass(ok);
         }
         if (status.next_subtest("Copy principal"))
         {
            ok = click_ctor_tests(CT_COPY_CONSTRUCTOR);
            status.pass(ok);
         }
      }
   }
   return status;
}

/**
 * \group
 *    1. seq64::click
 *
 * \case
 *    4. Principal assignment operator
 *
 * \tests
 *    -  seq64::click::operator =(click)
 *
 * \param options
 *    Provides the command-line options for the unit-test application.
 *
 * \return
 *    Returns the unit-test status object needed by the protocol.
 */

xpc::cut_status
click_unit_test_01_04 (const xpc::cut_options & options)
{
   xpc::cut_status status
   (
      options, 1, 4, "seq64::click", _("Principal assignment operator")
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
         if (status.next_subtest("Assign default"))
         {
            seq64::click c1;
            seq64::click c2;
            c2 = c1;
            ok = compare_clicks(c1, c2);
            status.pass(ok);
         }
         if (status.next_subtest("operator =()"))
         {
            seq64::click c1;
            seq64::click c2;
            (void) c2.operator =(c1);
            ok = compare_clicks(c1, c2);
            status.pass(ok);
         }
         if (status.next_subtest("Assign principal"))
         {
            ok = click_ctor_tests(CT_PRINCIPAL_ASSIGNMENT_OPERATOR);
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
