#ifndef _AUDIO_MANAGER_H_
#define _AUDIO_MANAGER_H_

#include <string>
#include <stk/RtAudio.h>
#include <stk/Messager.h>
#include <stk/Thread.h>

class AudioManager
{
    public:
        AudioManager();
        ~AudioManager();
        bool handleMessage(const std::string &msg);
     
    private:
        static void* recordLoop(void *data);
        void start();
        void stop();
        static int process(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
        double /*streamTime*/, RtAudioStreamStatus status, void *data);
        void cleanup();
        RtAudio adac_;
        stk::Messager messager_;
        bool stopped_;
        stk::Thread recorder_;
        bool recorderExit_;
};

#endif // _AUDIO_MANAGER_H_
