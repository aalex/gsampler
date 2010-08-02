
#include <stk/Stk.h>
#include <stk/RtWvIn.h>
#include <stk/FileWvOut.h>
#include <stdexcept>
#include "./Sampler.h"

#if 0
// this is meant to run in a separate thread
void Loop::recordLoop(void *data)
{
    using namespace stk;
    recording_ = true;
    const double SAMPLE_RATE = 44100.0;
    // TODO:2010-08-02: the only thing we should look at/touch from outside
    // is a threadsafe queue that will pass messages to this thread
    // TODO:2010-08-02: this should be done callback style.
    Loop *context = static_cast<Loop*>(data);

    Stk::setSampleRate(SAMPLE_RATE);

    RtWvIn adc; // realtime input from ADC

    FileWvOut output;
    output.openFile(context->name_.c_str(), 1, FileWrite::FILE_WAV, Stk::STK_SINT16);

    register StkFloat sample;
    while (!stopped_)
    {
        sample = adc.tick();
        output.tick(sample);
    }

    output.closeFile();
    std::cout << "Finished recording " << *context << std::endl;    
    delete context;
    recording_ = false;
    stopped_ = false;
}
#endif

// dsp callback, passthrough for now
int Sampler::process(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
        double /*streamTime*/, RtAudioStreamStatus status, void *data)
{
    using namespace stk;
    register StkFloat *out = static_cast<StkFloat*>(outputBuffer);
    register StkFloat *in = static_cast<StkFloat*>(inputBuffer);
    // the number of input and output channels is equal 

    // FIXME:02/08/2010:tmatth Don't use cerr, this will block. 
    // Should set a flag or something that our main thread can print out.
    if (status)
        std::cerr << "Stream over/underflow detected." << std::endl;

    // stereo, interleaved channels
    while (nBufferFrames--)
    {
        *out++ = *in++;
        *out++ = *in++;
    }

    return 0;
}

std::ostream& operator<<( std::ostream& o, const Sampler& s )
{
    return o << s.name_;
}

void Sampler::cleanup()
{
    if (adac_.isStreamOpen())
        adac_.closeStream();
}

Sampler::Sampler(const std::string &name) : name_(name)
{
    using namespace stk;
    
    if (adac_.getDeviceCount() < 1) {
        cleanup();
        throw std::runtime_error("\nNo audio devices found!\n");
    }
}

void Sampler::start()
{
    using namespace stk;
    // set the same number of channels for both input and output
    unsigned int bufferFrames = RT_BUFFER_SIZE;
    RtAudioFormat format = (sizeof(StkFloat) == 8) ? RTAUDIO_FLOAT64 : 
        RTAUDIO_FLOAT32;
    RtAudio::StreamParameters iParams, oParams;
    iParams.deviceId = 0; // first available device
    iParams.nChannels = 2;
    oParams.deviceId = 0; // first available device
    oParams.nChannels = 2;
    try {
        adac_.openStream(&oParams, &iParams, format, Stk::sampleRate(), 
                &bufferFrames, &process, static_cast<void *>(this));
    }
    catch (RtError& e) {
        e.printMessage();
        cleanup();
        throw;
    }

    try { 
        char c;
        adac_.startStream();
        std::cout << "Hit a key..." << std::endl;
        std::cin >> c;
        stop();
    }
    catch (RtError &e)
    {
        e.printMessage();
        cleanup();
        throw; 
    }
}


void Sampler::stop()
{
    try { 
        // stop the stream
        if (adac_.isStreamRunning())
            adac_.stopStream();
    }
    catch (RtError &e)
    {
        e.printMessage();
        cleanup();
        throw;
    }
}

Sampler::~Sampler()
{
    stop();
    cleanup();
}

