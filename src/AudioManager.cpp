
#include <stk/Stk.h>
#include <stk/RtWvIn.h>
#include <stk/FileWvOut.h>
#include <stdexcept>
#include "./AudioManager.h"

// this is meant to run in a separate thread
void* AudioManager::recordLoop(void *data)
{
    AudioManager *context = static_cast<AudioManager*>(data);
    using namespace stk;
    while (not context->recorderExit_)
    {
        if (not context->stopped_)
        {
            //const double SAMPLE_RATE = 44100.0;
            // TODO:2010-08-02: the only thing we should look at/touch from outside
            // is a threadsafe queue that will pass messages to this thread
            // TODO:2010-08-02: this should be done callback style.

            //Stk::setSampleRate(SAMPLE_RATE);

            RtWvIn adc; // realtime input from ADC

            FileWvOut output;
            output.openFile("test.wav", 1, FileWrite::FILE_WAV, Stk::STK_SINT16);

            register StkFloat sample;
            while (!context->stopped_)
            {
                sample = adc.tick();
                output.tick(sample);
            }

            output.closeFile();
            std::cout << "Finished recording test.wav" << std::endl;    
        }
        else
            usleep(1000);
    }
    return data;
}

// dsp callback, passthrough for now
int AudioManager::process(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
        double /*streamTime*/, RtAudioStreamStatus status, void *data)
{
    using namespace stk;
    using std::string;
    register StkFloat *out = static_cast<StkFloat*>(outputBuffer);
    //register StkFloat *in = static_cast<StkFloat*>(inputBuffer);

    Messager *messager = static_cast<Messager*>(data);
    Skini::Message msg;
    messager->popMessage(msg);

    // the number of input and output channels is equal 

    // FIXME:02/08/2010:tmatth Don't use cerr, this will block. 
    // Should set a flag or something that our main thread can print out.
    if (status)
        std::cerr << "Stream over/underflow detected." << std::endl;

    // stereo, interleaved channels
    while (nBufferFrames--)
    {
        *out++ = 0.0; //*in++;
        *out++ = 0.0; //*in++;
    }

    return 0;
}

void AudioManager::cleanup()
{
    if (adac_.isStreamOpen())
        adac_.closeStream();
}

AudioManager::AudioManager() : adac_(), messager_(), stopped_(true), recorder_(), recorderExit_(false)
{
    if (adac_.getDeviceCount() < 1) {
        cleanup();
        throw std::runtime_error("\nNo audio devices found!\n");
    }
}

void AudioManager::start()
{
    using namespace stk;
#if 0
    // set the same number of channels for both input and output
    unsigned int bufferFrames = RT_BUFFER_SIZE;
    RtAudioFormat format = (sizeof(StkFloat) == 8) ? RTAUDIO_FLOAT64 : 
        RTAUDIO_FLOAT32;
    RtAudio::StreamParameters /*iParams,*/ oParams;
    iParams.deviceId = 0; // first available device
    iParams.nChannels = 2;
    oParams.deviceId = 0; // first available device
    oParams.nChannels = 2;
    try {
        adac_.openStream(&oParams, /*&iParams*/ NULL, format, Stk::sampleRate(), 
                &bufferFrames, &process, static_cast<void *>(&messager_));
    }
    catch (RtError& e) {
        e.printMessage();
        cleanup();
        throw;
    }

    try { 
        adac_.startStream();
    }
    catch (RtError &e)
    {
        e.printMessage();
        cleanup();
        throw; 
    }
#endif
    std::cout << "DSP started..." << std::endl;
    recorder_.start(&recordLoop, static_cast<void*>(this));
    std::cout << "Recorder thread started..." << std::endl;
}


bool AudioManager::handleMessage(const std::string &message)
{
    std::cout << "Got message " << message << std::endl;
    if (message == "start dsp")
    {
        start();
        return true;
    }
    else if (message == "start recording")
    {
        // FIXME:08/04/2010:tmatth don't parse these messages twice
        // transform msg into Skini message for use with our thread safe queue.
        stk::Skini::Message msg;
        msg.type = 1;
        msg.remainder = message;
        messager_.pushMessage(msg);
        stopped_ = false;
        return true;
    }
    else if (message == "stop recording")
    {
        // FIXME:08/04/2010:tmatth don't parse these messages twice
        // transform msg into Skini message for use with our thread safe queue.
        stk::Skini::Message msg;
        msg.type = 1;
        msg.remainder = message;
        messager_.pushMessage(msg);
        stopped_ = true;
        return true;
    }
    else
        return false;
}

void AudioManager::stop()
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
        // don't throw since this is called from the destructor
    }
}

AudioManager::~AudioManager()
{
    recorderExit_ = true;
    recorder_.wait();
    stop();
    cleanup();
}

