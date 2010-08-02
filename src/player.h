#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <stk/RtAudio.h>
#include <stk/FileWvIn.h>

using namespace stk;

class SoundPlayer {
    public:
        //SoundPlayer();
        void start(const std::string &fileName);
        void stop();
    private:
        bool done_;
        FileWvIn input_;
        StkFrames frames_;
        void finish(int ignore);
};

static int soundplayer_tick(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
    double streamTime, RtAudioStreamStatus status, void *userData);
#endif // _PLAYER_H_
