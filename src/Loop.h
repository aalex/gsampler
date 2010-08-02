#ifndef _LOOP_H_
#define _LOOP_H_

#include <string>

class Sampler
{
    public:
        Sampler(const std::string &name) : name_(name) {}
        friend std::ostream& operator<<( std::ostream& o, const Sampler& s );
        std::string name() const { return name_; }
        static bool isRecording() { return recording_; }
        static void stopRecording() { stopped_ = true; }
        int start();
        
    private:
        static int process(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
        double /*streamTime*/, RtAudioStreamStatus status, void *data);
        static bool recording_;
        static bool stopped_;
        const std::string name_;
        void cleanup();
        RtAudio adac_;
};

#endif // _LOOP_H_
