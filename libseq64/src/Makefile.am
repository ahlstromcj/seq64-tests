#****************************************************************************
# Makefile.am (seq64-tests)
#----------------------------------------------------------------------------
##
# \file       	Makefile.am
# \library    	libseq64 test
# \author     	Chris Ahlstrom
# \date       	2015-10-06
# \update      2015-10-07
# \version    	$Revision$
# \license    	$XPC_SUITE_GPL_LICENSE$
#
#		This is a Makefile for the tests directory for the libseq64 test
#		project.  This module provides an automake makefile for the unit-test,
#		developer tests, or integration test applications.  This makefile
#		provides the items needed to build the test applications using GNU
#		autotools.
#
#----------------------------------------------------------------------------

AUTOMAKE_OPTIONS = foreign dist-zip dist-bzip2
MAINTAINERCLEANFILES = Makefile.in Makefile $(AUX_DIST)
CLEANFILES = *.gc*

#****************************************************************************
# 	EXTRA_DIST
#----------------------------------------------------------------------------
#
#	Add any extra distributable files here, so they are added to the tar
#	package.
#
#----------------------------------------------------------------------------

EXTRA_DIST = test_script

#******************************************************************************
# Packaging items from configure.ac
#-------------------------------------------------------------------------------
#
#  XPCCUT_LIBS is defined by the PKG_CHECK_MODULES macro.  The xpccut
#  library must be installed officially in order to be used to build the
#  unit-test application of the xpc library.  2012-06-17:  NO LONGER TRUE.
#
#-------------------------------------------------------------------------------

PACKAGE = @PACKAGE@
VERSION = @VERSION@

# XPCCUTPP_CFLAGS = @XPCCUTPP_CFLAGS@
# XPCCUT_CFLAGS = @XPCCUT_CFLAGS@

XPCCUTPP_LIBS = @XPCCUTPP_LIBS@
XPCCUT_LIBS = @XPCCUT_LIBS@

#******************************************************************************
# Local project directories
#------------------------------------------------------------------------------

top_srcdir = @top_srcdir@
builddir = @abs_top_builddir@

#******************************************************************************
# Locations of the test libraries and header files
#------------------------------------------------------------------------------
#
#		It is assumed that the sequencer64 project and this test project
#		have their roots at the same level (e.g. both are in the "git"
#		directory).  They are related projects, but we don't want to force
#		the user/developer to download and build the unit-test libraries
#		just to be able to build sequencer64.
#
#------------------------------------------------------------------------------

libseq64_incdir = $(top_srcdir)/../sequencer64/libseq64/include
libseq64_libdir = $(top_srcdir)/../sequencer64/libseq64/src/   # .libs/
libseq64_libs = -L$(libseq64_libdir) -lseq64

#*****************************************************************************
# libtool
#-----------------------------------------------------------------------------
#
#     GNU automake assigns, for us: LIBTOOL_DEPS = @LIBTOOL_DEPS@
#
#-----------------------------------------------------------------------------
#
# LIBTOOL_DEPS = @LIBTOOL_DEPS@
#
# libtool: $(LIBTOOL_DEPS)
#    $(SHELL) ./scripts/config.status --recheck
#
#-----------------------------------------------------------------------------

version = $(XPC_API_MAJOR):$(XPC_API_MINOR):$(XPC_API_PATCH)

#****************************************************************************
# AM_CPPFLAGS [formerly "INCLUDES"]
#----------------------------------------------------------------------------
#
#	Specifies the header-file locations for uninstalled libraries in the XPC
#	source tree.
#
#----------------------------------------------------------------------------

AM_CXXFLAGS = \
 -I$(libseq64_incdir) \
 -I../include \
 $(XPCCUTPP_CFLAGS) \
 $(XPCCUT_CFLAGS) \
 $(JACK_CFLAGS) \
 $(LASH_CFLAGS)

#****************************************************************************
# The program(s) to build, but not install
#----------------------------------------------------------------------------

noinst_PROGRAMS = libseq64_unit_test

#****************************************************************************
# libseq64_unittest_SOURCES
#----------------------------------------------------------------------------
#
#  Note that we assume the developer has also downloaded and built, in this
#  same directory tree, the C library, xpccut.  If a bug is found, the
#  developer will need both sets of source code anyway.
#
#     if STANDALONE
#     libseq64_unit_test_DEPENDENCIES = ../src/.libs/libxpccut++.a
#     else
#
# We do not need "-ldl"!
#
# libseq64_unit_test_LDADD = @LIBINTL@ -lpthread $(libraries)
#
#----------------------------------------------------------------------------

libseq64_unit_test_SOURCES = \
 click_unit_test.cpp \
 libseq64_unit_test.cpp

# -lpthread $(libraries)

libseq64_unit_test_LDADD = \
 $(libseq64_libs) \
 $(XPCCUTPP_LIBS) \
 $(XPCCUT_LIBS) \
 $(ALSA_LIBS) \
 $(JACK_LIBS) \
 $(LASH_LIBS)

# libseq64_unit_test_DEPENDENCIES = $(dependencies)

#****************************************************************************
# TESTS
#----------------------------------------------------------------------------
#
#     This variable is used in the "make check" command.  We add a target to
#     implement "make test", also.
#
#----------------------------------------------------------------------------

testsubdir = test-results
TESTS_ENVIRONMENT =
TESTS = test_script

test: check

#****************************************************************************
# distclean
#----------------------------------------------------------------------------

distclean-local:
	-rm -rf $(testsubdir)

#****************************************************************************
# Makefile.am (seq64-tests)
#----------------------------------------------------------------------------
# vim: ts=3 sw=3 wm=8 ft=automake
#----------------------------------------------------------------------------
