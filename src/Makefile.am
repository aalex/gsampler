bin_PROGRAMS = boomers

boomers_SOURCES = main.cpp application.cpp stateServer.cpp stateClient.cpp oscSender.cpp oscReceiver.cpp sceneViewer.cpp scene.cpp keyboardEventHandler.cpp physics.cpp
boomers_CXXFLAGS = $(LIBLO_CFLAGS) $(BULLET_CFLAGS) $(BOOST_PROGRAM_OPTIONS_CPPFLAGS) $(BOOST_THREAD_CPPFLAGS) -Wall
boomers_LDADD = $(LIBLO_LIBS) $(BOOST_PROGRAM_OPTIONS_LIB) $(BULLET_LIBS) $(BOOST_THREAD_LIB) $(OSG_LIBS) 
