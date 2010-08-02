
#include <stk/Stk.h>
#include <stk/RtWvIn.h>
#include <stk/FileWvOut.h>
#include "Loop.h"

bool Loop::recording_ = false;
bool Loop::stopped_ = false;

// this is meant to run in a separate thread
void Loop::recordLoop(void *data)
{
    using namespace stk;
    recording_ = true;
    const double SAMPLE_RATE = 44100.0;
    // TODO:2010-08-02: the only thing we should look at/touch from outside
    // is a threadsafe queue that will pass messages to this thread
    Loop *context = static_cast<Loop*>(data);

    Stk::setSampleRate(SAMPLE_RATE);

    RtWvIn adc; // RtWvIn: realtime input from ADC

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

std::ostream& operator<<( std::ostream& o, const Loop& s )
{
    /* code to output an X to a stream */
    return o << s.name_;
}

