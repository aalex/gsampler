bin_PROGRAMS = sampled

sampled_SOURCES = main.cpp oscReceiver.cpp oscSender.cpp application.cpp samplerServer.cpp Loop.cpp  \
				  Stk.cpp FileWrite.cpp FileRead.cpp FileWvOut.cpp FileWvIn.cpp RtWvIn.cpp \
                  RtAudio.cpp RtWvOut.cpp  Mutex.cpp


sampled_CXXFLAGS = $(LIBLO_CFLAGS) $(BOOST_PROGRAM_OPTIONS_CPPFLAGS) $(BOOST_THREAD_CPPFLAGS) $(audio_apis)
sampled_LDADD = $(LIBLO_LIBS) $(BOOST_PROGRAM_OPTIONS_LIB) $(BOOST_THREAD_LIB) $(frameworks)
