#                                               -*- Autoconf -*- # Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT(GSAMPLER, 0.1.0)
AC_CONFIG_HEADER([config.h])
AC_PROG_LIBTOOL
AM_INIT_AUTOMAKE()
AC_CONFIG_MACRO_DIR([m4])

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

AX_BOOST_BASE([1.38])
AX_BOOST_PROGRAM_OPTIONS
AX_PTHREAD(AC_MSG_NOTICE([Found pthread]), AC_MSG_NOTICE([pthread not found]))

# Check for stk
AC_LANG(C++)
# save original flags
SAVED_LDFLAGS=$LDFLAGS
LDFLAGS="$LDFLAGS -lstk"
AC_LINK_IFELSE(
        [AC_LANG_PROGRAM([ #include <stk/RtAudio.h> ],
        [RtAudio dac])],
        [AC_SUBST(STK_LIBS," -lstk -lrt -lm")],
        [AC_MSG_WARN([libstk is not installed: alsa])])
LDFLAGS=$SAVED_LDFLAGS # restore them
AC_SUBST(STK_CXXFLAGS, "-D__UNIX_JACK__ -D__LITTLE_ENDIAN__")
AC_SUBST(CXXFLAGS, " -O2 -Wall -Wfatal-errors -Werror -pedantic")

# save original flags
#SAVED_LDFLAGS=$LDFLAGS
#LDFLAGS="$LDFLAGS -framework CoreAudio -framework CoreServices -lstk"
#AC_LINK_IFELSE(
#        [AC_LANG_PROGRAM([ #include <stk/RtAudio.h> ],
#       [RtAudio dac])],
#       [AC_SUBST(STK_LIBS," -framework CoreAudio -framework CoreServices -lstk")],
#       [AC_MSG_WARN([libstk is not installed for CoreAudio backend])])
#LDFLAGS=$SAVED_LDFLAGS # restore them

#Set LIBLO with pkg-config
PKG_CHECK_MODULES(LIBLO, liblo, have_liblo=true, have_liblo=false)
if test "x${have_liblo}" = "xfalse" ; then
    AC_MSG_ERROR([Missing liblo-dev])
fi

PKG_CHECK_MODULES(GTKMM, [gtkmm-2.4 >= 0.22], have_gtkmm=true, have_gtkmm=false)
if test "x${have_gtkmm}" = "xfalse" ; then
    AC_MSG_ERROR([Missing libgtkmm-2.4-dev])
fi
AC_SUBST([GTKMM_LIBS])
AC_SUBST([GTKMM_CFLAGS])

#NOTE: setting relevant flags has to happen before this line
AC_CONFIG_FILES([
        Makefile
        src/Makefile
        py/Makefile
        ])
AC_OUTPUT

