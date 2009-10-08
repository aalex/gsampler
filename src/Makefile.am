bin_PROGRAMS = dyst

dyst_SOURCES = main.cpp application.cpp stateServer.cpp stateClient.cpp oscSender.cpp oscReceiver.cpp dystViewer.cpp
dyst_CXXFLAGS = $(LIBLO_CFLAGS) $(BOOST_PROGRAM_OPTIONS_CPPFLAGS)
dyst_LDADD = $(LIBLO_LIBS) $(BOOST_PROGRAM_OPTIONS_LIB) $(OSG_LIBS)
