#ifndef _AUDIO_MANAGER_H_
#define _AUDIO_MANAGER_H_

#include <string>

class AudioManager
{
    public:
        AudioManager();
        ~AudioManager();
        
    private:
        void start();
        void stop();
        static int process(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
        double /*streamTime*/, RtAudioStreamStatus status, void *data);
        void cleanup();
        RtAudio adac_;
};

#endif // _AUDIO_MANAGER_H_
