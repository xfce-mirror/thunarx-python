#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT(thunarx-python, 0.0.1)
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/thunarx-python.h])
AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CC

# Check for Python
AM_CHECK_PYTHON_HEADERS(,[AC_MSG_ERROR(could not find Python headers)])
AM_CHECK_PYTHON_LIBS(,[AC_MSG_ERROR(could not find Python lib)])

# Check for programs
PKG_CHECK_MODULES([THUNARX], [thunarx-1 >= 0.4.0])
PKG_CHECK_PACKAGE([GTK], [gtk+-2.0 >= 2.6.0])
PKG_CHECK_PACKAGE([GLIB], [glib-2.0 >= 2.6.0])
PKG_CHECK_PACKAGE([GOBJECT], [gobject-2.0 >= 2.6.0])
PKG_CHECK_PACKAGE([PYGTK], [pygtk-2.0 >= 2.8.0]

PACKAGE_CFLAGS="-g -Wall $THUNARX_CFLAGS $APR_CFLAGS $GTK_CFLAGS $GLIB_CFLAGS $GOBJECT_CFLAGS"
PACKAGE_LIBS="-g $THUNARX_LIBS $APR_LIBS $GTK_LIBS $GLIB_LIBS $GOBJECT_LIBS"
PACKAGE_LDFLAGS="$THUNARX_LDFLAGS $APR_LDFLAGS $GTK_LDFLAGS $GLIB_LDFLAGS $GOBJECT_LDFLAGS"
PACKAGE_CPPFLAGS="$THUNARX_CPPFLAGS $APR_CPPFLAGS $GTK_CPPFLAGS $GLIB_CPPFLAGS $GOBJECT_CPPFLAGS"

# Make dependency CFLAGS and LIBS available
AC_SUBST(PACKAGE_CFLAGS)
AC_SUBST(PACKAGE_LIBS)
AC_SUBST(PACKAGE_LDFLAGS)
AC_SUBST(PACKAGE_CPPFLAGS)

AC_MSG_CHECKING(for pygtk defs)
PYGTK_DEFSDIR=`$PKG_CONFIG --variable=defsdir pygtk-2.0`
AC_SUBST(PYGTK_DEFSDIR)
AC_MSG_RESULT($PYGTK_DEFSDIR)

AC_MSG_CHECKING(for pygtk codegen)
PYGTK_CODEGEN="$PYTHON `$PKG_CONFIG --variable=codegendir pygtk-2.0`/codegen.py"
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
