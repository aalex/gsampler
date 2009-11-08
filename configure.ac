#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT(SAMPLED, 0.01)
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
    AC_CHECK_HEADER(CoreAudio/CoreAudio.h, [], [AC_MSG_ERROR(CoreAudio header files not found!)] )
    AC_SUBST( frameworks, ["-framework CoreAudio -framework CoreFoundation -framework CoreMidi"] )
    AC_SUBST( audio_apis, ["-D__MACOSX_CORE__"] )
else 
    # assume linux
  case $host in
    *-*-linux*)
    AC_ARG_WITH(jack, [  --with-jack = choose JACK server support (mac and linux only)], [
    api="$api -D__UNIX_JACK__"
    AC_MSG_RESULT(using JACK)
    AC_CHECK_LIB(jack, jack_client_open, , AC_MSG_ERROR(JACK support requires the jack library!))
    AC_CHECK_LIB(asound, snd_pcm_open, , AC_MSG_ERROR(Jack support also requires the asound library!))], )

    # Look for ALSA flag
    AC_ARG_WITH(alsa, [  --with-alsa = choose native ALSA API support (linux only)], [
    api="$api -D__LINUX_ALSA__"
    AC_MSG_RESULT(using ALSA)
    AC_CHECK_LIB(asound, snd_pcm_open, , AC_MSG_ERROR(ALSA support requires the asound library!))], )

    # Look for OSS flag
    AC_ARG_WITH(oss, [  --with-oss = choose OSS API support (linux only)], [
    api="$api -D__LINUX_OSS__"
    AC_MSG_RESULT(using OSS)], )

    # If no audio api flags specified, use ALSA
    if [test "$api" == "";] then
      AC_MSG_RESULT(using ALSA)
      AC_SUBST( api, [-D__LINUX_ALSA__] )
      AC_CHECK_LIB(asound, snd_pcm_open, , AC_MSG_ERROR(ALSA support requires the asound library!))
    fi

    CPPFLAGS="$CPPFLAGS $api"
    #;;
    esac
fi

#Set LIBLO with pkg-config
PKG_CHECK_MODULES(LIBLO, liblo, have_liblo=true, have_liblo=false)
if test "x${have_liblo}" = "xfalse" ; then
    AC_MSG_ERROR([Missing liblo])
fi

AX_BOOST_BASE([1.35])
AX_BOOST_PROGRAM_OPTIONS
AX_BOOST_THREAD

#NOTE: setting relevant flags has to happen before this line
AC_CONFIG_FILES([
        Makefile
        src/Makefile
        py/Makefile
        prototypes/Makefile
        prototypes/playing/Makefile
        ])
AC_OUTPUT

