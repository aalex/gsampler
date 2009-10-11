bin_PROGRAMS = boomers

boomers_SOURCES = main.cpp application.cpp stateServer.cpp stateClient.cpp oscSender.cpp oscReceiver.cpp sceneViewer.cpp scene.cpp keyboardEventHandler.cpp
boomers_CXXFLAGS = $(LIBLO_CFLAGS) $(BOOST_PROGRAM_OPTIONS_CPPFLAGS)
boomers_LDADD = $(LIBLO_LIBS) $(BOOST_PROGRAM_OPTIONS_LIB) $(OSG_LIBS)
