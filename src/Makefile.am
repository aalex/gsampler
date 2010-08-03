bin_PROGRAMS = gsampler

gsampler_SOURCES = main.cpp oscReceiver.cpp oscSender.cpp application.cpp samplerServer.cpp AudioManager.cpp \
                   oscReceiver.h oscSender.h player.h AudioManager.h samplerServer.h application.h

gsampler_CXXFLAGS = $(LIBLO_CFLAGS) $(BOOST_PROGRAM_OPTIONS_CPPFLAGS) $(PTHREAD_CFLAGS) $(STK_CXXFLAGS)
gsampler_LDADD = $(LIBLO_LIBS) $(BOOST_PROGRAM_OPTIONS_LIB) $(PTHREAD_LIBS) $(STK_LIBS)
