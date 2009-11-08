bin_PROGRAMS = player

player_SOURCES = main.cpp \
				  Stk.cpp FileWrite.cpp FileRead.cpp FileWvOut.cpp FileWvIn.cpp RtWvIn.cpp \
                  RtAudio.cpp RtWvOut.cpp  Mutex.cpp
# player.cpp

player_CXXFLAGS = $(audio_apis)
player_LDADD = $(frameworks)

