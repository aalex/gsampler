bin_PROGRAMS = sampled

sampled_SOURCES = main.cpp oscReceiver.cpp oscSender.cpp application.cpp samplerServer.cpp
sampled_CXXFLAGS = $(LIBLO_CFLAGS) $(BOOST_PROGRAM_OPTIONS_CPPFLAGS) $(BOOST_THREAD_CPPFLAGS) -Wall
sampled_LDADD = $(LIBLO_LIBS) $(BOOST_PROGRAM_OPTIONS_LIB) $(BOOST_THREAD_LIB) 
