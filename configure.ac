#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT(BOOMERS, 0.01)
AC_CONFIG_HEADER([config.h])
AC_PROG_LIBTOOL
AM_INIT_AUTOMAKE()

# Extract host information.
AC_CANONICAL_HOST

# Check for C and C++ compilers
AC_PROG_CXX
AC_PROG_CC

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([arpa/inet.h stdlib.h string.h sys/ioctl.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
PKG_PROG_PKG_CONFIG

AC_PROG_GCC_TRADITIONAL
AC_CHECK_FUNCS([inet_ntoa memset socket])

# check if we are running OS X
if test "x$build_vendor" = "xapple" ; then
    AC_DEFINE([PLATFORM_OSX], 1, [Define whether we are running on Mac OS X.])
fi

#Set BULLET with pkg-config
PKG_CHECK_MODULES(BULLET, bullet >= 2.73, have_bullet=true, have_bullet=false)
if test "x${have_bullet}" = "xfalse" ; then
    AC_MSG_ERROR([Missing bullet])
fi

#Set OSG with pkg-config
PKG_CHECK_MODULES(OSG, openscenegraph, have_osg=true, have_osg=false)
if test "x${have_osg}" = "xfalse" ; then
    AC_MSG_ERROR([Missing openscenegraph])
fi


#Set LIBLO with pkg-config
PKG_CHECK_MODULES(LIBLO, liblo, have_liblo=true, have_liblo=false)
if test "x${have_liblo}" = "xfalse" ; then
    AC_MSG_ERROR([Missing liblo])
fi

AX_BOOST_BASE([1.35])
AX_BOOST_PROGRAM_OPTIONS

#NOTE: setting relevant flags has to happen before this line
AC_CONFIG_FILES([
        Makefile
        src/Makefile
        prototypes/Makefile
        prototypes/osgbullet/Makefile
        ])
AC_OUTPUT
