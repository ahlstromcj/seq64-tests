#*****************************************************************************
# Makefile.am (seq64-tests)
#-----------------------------------------------------------------------------
##
# \file        Makefile.am
# \library     seq64-tests
# \author      Chris Ahlstrom
# \date        2015-09-11
# \updates     2015-10-07
# \version     $Revision$
# \license     $XPC_SUITE_GPL_LICENSE$
#
#     This is the project makefile for the seq64-tests project.
#     This makefile provides the skeleton needed to build the library
#     and application directories using GNU autotools.
#
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Packing targets
#-----------------------------------------------------------------------------

AUTOMAKE_OPTIONS = foreign dist-zip dist-bzip2
MAINTAINERCLEANFILES = Makefile.in Makefile $(AUX_DIST)
MOSTLYCLEANFILES = *~

#*****************************************************************************
# Extra files in the top-level directory
#-----------------------------------------------------------------------------

EXTRA_DIST = bootstrap pack README VERSION COPYING AUTHORS INSTALL NEWS ChangeLog

#*****************************************************************************
# Packaging
#-----------------------------------------------------------------------------
#
#     This section is recommended for the top-level Makefile.am by the
#     reference.
#
#-----------------------------------------------------------------------------

PACKAGE = @PACKAGE@
VERSION = @VERSION@

SEQ64_TESTS_API_MAJOR = @SEQ64_TESTS_API_MAJOR@
SEQ64_TESTS_API_MINOR = @SEQ64_TESTS_API_MINOR@
SEQ64_TESTS_API_PATCH = @SEQ64_TESTS_API_PATCH@
SEQ64_TESTS_API_VERSION = @SEQ64_TESTS_API_VERSION@

SEQ64_TESTS_LT_CURRENT = @SEQ64_TESTS_LT_CURRENT@
SEQ64_TESTS_LT_REVISION = @SEQ64_TESTS_LT_REVISION@
SEQ64_TESTS_LT_AGE = @SEQ64_TESTS_LT_AGE@

#*****************************************************************************
# Installed directories
#-----------------------------------------------------------------------------
#
# The 'libdir' define is necessary to cause the proper subdirectory to
# be made during installation.  'seq64_testslibdir' is defined in the
# configure.ac script.  The 'libdir' define is needed for work with
# libtool.  Not sure about 'pkglibdr'.
#
#     pkglibdir=$(seq64_testslibdir)
#
#	Directories and macros:
#
#		prefix                = /usr/local
#		libdir                = /usr/local/lib/seq64-tests
#		datadir               = /usr/local/share
#		datarootdir           = /usr/local/share
#		seq64-testslibdir     = /usr/local/lib/seq64-tests
#		seq64-testsincludedir = /usr/local/include/seq64-tests.1
#		localedir     = /usr/local/share/locale
#
#  'localedir' is the normal system directory for installed localization
#  files.
#
#-----------------------------------------------------------------------------

prefix = @prefix@
libdir = @seq64_testslibdir@
datadir = @datadir@
datarootdir = @datarootdir@
seq64_testsincludedir = @seq64_testsincludedir@
seq64_testslibdir = @seq64_testslibdir@
localedir = $(datadir)/locale
DEFS = -DLOCALEDIR=\"$(localedir)\" @DEFS@

#******************************************************************************
# Local project directories
#------------------------------------------------------------------------------
#
#		top_srcdir    = ../../.. [XPC Basic directory]
#		builddir      = /home/ahlstrom/ca/mls/git/XPC Basic-1.1/debug
#
#------------------------------------------------------------------------------

top_srcdir = @top_srcdir@
builddir = @abs_top_builddir@

#******************************************************************************
# aclocal support
#------------------------------------------------------------------------------

ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

#*****************************************************************************
# libtool
#-----------------------------------------------------------------------------
#	${SHELL} $(top_srcdir)/config.status --recheck
#-----------------------------------------------------------------------------

LIBTOOL_DEPS = @LIBTOOL_DEPS@

libtool: $(LIBTOOL_DEPS)
	$(top_srcdir)/config.status --recheck

#*****************************************************************************
# SUBDIRS
#-----------------------------------------------------------------------------

SUBDIRS = libseq64

#*****************************************************************************
# DIST_SUBDIRS
#-----------------------------------------------------------------------------

DIST_SUBDIRS = $(SUBDIRS)

#*****************************************************************************
# all-local
#-----------------------------------------------------------------------------

all-local:
	@echo "Top source-directory 'top_srcdir' is $(top_srcdir)"
	@echo "* * * * * All build items completed * * * * *"

#******************************************************************************
# Debugging targets
#------------------------------------------------------------------------------

show:
	@echo "Install directories:"
	@echo
	@echo "prefix                 = $(prefix)"
	@echo "datadir                = $(datadir)"
	@echo "datarootdir            = $(datarootdir)"
	@echo "libdir                 = $(libdir)"
	@echo "seq64_testslibdir      = $(seq64_testslibdir)"
	@echo "seq64_testsincludedir  = $(seq64_testsincludedir)"
	@echo "localedir              = $(localedir)"
	@echo
	@echo "Local directories:"
	@echo
	@echo "top_srcdir             = $(top_srcdir) [project root directory]"
	@echo "srcdir                 = $(srcdir)"
	@echo "top_builddir           = $(top_builddir)"
	@echo "builddir               = $(builddir)"

showver:
	@echo "PACKAGE                = $(PACKAGE)"
	@echo "VERSION                = $(VERSION)"
	@echo "SEQ64_TESTS_API_MAJOR    = $(SEQ64_TESTS_API_MAJOR)"
	@echo "SEQ64_TESTS_API_MINOR    = $(SEQ64_TESTS_API_MINOR)"
	@echo "SEQ64_TESTS_API_PATCH    = $(SEQ64_TESTS_API_PATCH)"
	@echo "SEQ64_TESTS_API_VERSION  = $(SEQ64_TESTS_API_VERSION)"
	@echo "SEQ64_TESTS_LT_CURRENT   = $(SEQ64_TESTS_LT_CURRENT)"
	@echo "SEQ64_TESTS_LT_REVISION  = $(SEQ64_TESTS_LT_REVISION)"
	@echo "SEQ64_TESTS_LT_AGE       = $(SEQ64_TESTS_LT_AGE)"

#****************************************************************************
# Makefile.am (seq64-tests)
#----------------------------------------------------------------------------
# vim: ts=3 sw=3 ft=automake
#----------------------------------------------------------------------------
