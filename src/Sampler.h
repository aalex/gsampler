#ifndef _SAMPLER_H_
#define _SAMPLER_H_

#include <string>

class Sampler
{
    public:
        Sampler(const std::string &name);
        ~Sampler();
        friend std::ostream& operator<<( std::ostream& o, const Sampler& s );
        std::string name() const { return name_; }
        void start();
        void stop();
        
    private:
        static int process(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
        double /*streamTime*/, RtAudioStreamStatus status, void *data);
        const std::string name_;
        void cleanup();
        RtAudio adac_;
};

#endif // _SAMPLER_H_