#******************************************************************************
# Makefile.am (seq64-tests)
#------------------------------------------------------------------------------
##
# \file       	Makefile.am
# \library    	libseq64 library
# \author     	Chris Ahlstrom
# \date       	2015-10-06
# \update      2015-12-01
# \version    	$Revision$
# \license    	$XPC_SUITE_GPL_LICENSE$
#
# 		This module provides an Automake makefile for the sequencer26 C/C++
# 		tests.
#
#------------------------------------------------------------------------------

#*****************************************************************************
# Packing/cleaning targets
#-----------------------------------------------------------------------------

AUTOMAKE_OPTIONS = foreign dist-zip dist-bzip2
MAINTAINERCLEANFILES = Makefile.in Makefile $(AUX_DIST)
CLEANFILES = *.gc*
MOSTLYCLEANFILES = *~

#******************************************************************************
#  EXTRA_DIST
#------------------------------------------------------------------------------

EXTRA_DIST = *.h

#******************************************************************************
# Items from configure.ac
#-------------------------------------------------------------------------------

PACKAGE = @PACKAGE@
VERSION = @VERSION@

#******************************************************************************
# Source files
#----------------------------------------------------------------------------

pkginclude_HEADERS = \
 calculations_helpers.hpp \
 calculations_unit_test.hpp \
 click_helpers.hpp \
 click_unit_test.hpp \
 common_helpers.hpp \
 gui_assistant_dummy.hpp \
 keystroke_helpers.hpp \
 keystroke_unit_test.hpp \
 midifile_helpers.hpp \
 midifile_unit_test.hpp

#******************************************************************************
# uninstall-hook
#------------------------------------------------------------------------------

uninstall-hook:
	@echo "Note:  you may want to remove $(pkgincludedir) manually"

#******************************************************************************
# Makefile.am (seq64-tests)
#------------------------------------------------------------------------------
# 	vim: ts=3 sw=3 ft=automake
#------------------------------------------------------------------------------
