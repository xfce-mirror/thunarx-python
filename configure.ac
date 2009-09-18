#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.61])
AC_INIT(thunarx-python, 0.0.1)
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/thunarx-python.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LIBTOOL

# Check for programs
PKG_CHECK_MODULES([THUNARX], [thunarx-1 >= 0.4.0])
PKG_CHECK_MODULES([GTK], [gtk+-2.0 >= 2.6.0])
PKG_CHECK_MODULES([GLIB], [glib-2.0 >= 2.6.0])
PKG_CHECK_MODULES([GOBJECT], [gobject-2.0 >= 2.6.0])
PKG_CHECK_MODULES([PYGTK], [pygtk-2.0 >= 2.8.0])
PKG_CHECK_MODULES([PYTHON_GNOME], [gnome-python-2.0])

PACKAGE_CFLAGS="-g -Wall $THUNARX_CFLAGS $PYGTK_CFLAGS $GTK_CFLAGS $GLIB_CFLAGS $GOBJECT_CFLAGS $PYTHON_GNOME_CFLAGS"
PACKAGE_LIBS="-g $THUNARX_LIBS $PYGTK_LIBS $GTK_LIBS $GLIB_LIBS $GOBJECT_LIBS $PYTHON_GNOME_LIBS"
PACKAGE_LDFLAGS="$THUNARX_LDFLAGS $PYGTK_LDFLAGS $GTK_LDFLAGS $GLIB_LDFLAGS $GOBJECT_LDFLAGS $PYTHON_GNOME_LDFLAGS"
PACKAGE_CPPFLAGS="$THUNARX_CPPFLAGS $PYGTK_CPPFLAGS $GTK_CPPFLAGS $GLIB_CPPFLAGS $GOBJECT_CPPFLAGS $PYTHON_GNOME_CPPFLAGS"

# Make dependency CFLAGS and LIBS available
AC_SUBST(PACKAGE_CFLAGS)
AC_SUBST(PACKAGE_LIBS)
AC_SUBST(PACKAGE_LDFLAGS)
AC_SUBST(PACKAGE_CPPFLAGS)

PYTHON_CFLAGS="`python-config --includes`"
PYTHON_LIBS="`python-config --ldflags`"

AC_MSG_CHECKING(for pygtk defs)
PYGTK_DEFSDIR=`pkg-config --variable=defsdir pygtk-2.0`
AC_SUBST(PYGTK_DEFSDIR)
AC_MSG_RESULT($PYGTK_DEFSDIR)

AC_MSG_CHECKING(for pygtk codegen)
PYGTK_CODEGEN="/usr/bin/python `pkg-config --variable=codegendir pygtk-2.0`/codegen.py"
AC_SUBST(PYGTK_CODEGEN)
AC_MSG_RESULT($PYGTK_CODEGEN)

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE

# Checks for library functions.
AC_CHECK_FUNCS([setenv])

AC_CONFIG_FILES([
Makefile
src/Makefile
])
AC_OUTPUT
