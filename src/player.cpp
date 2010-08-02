/******************************************/
/*
  Example program to play an N channel
  soundfile.

  This program will load WAV, SND, AIF, and
  MAT-file formatted files of various data
  types.  If the audio system does not support
  the number of channels or sample rate of
  the soundfile, the program will stop.

  By Gary P. Scavone, 2000 - 2004.
*/
/******************************************/

#include <stk/FileWvIn.h>
#include <stk/RtAudio.h>

#include "player.h"

#include <signal.h>
#include <iostream>

using namespace stk;

//static 
/*
TODO: handle ctrl-c signal
void SoundPlayer::finish(int ignore)
{ 
    done_ = true; 
}
*/
// This tick() function handles sample computation only.  It will be
// called automatically when the system needs a new buffer of audio
// samples.
// // FIXME
static int soundplayer_tick(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *userData)
{
    //FileWvIn *input = (FileWvIn *) userData;
    SoundPlayer *context = static_cast<SoundPlayer *>(userData);
    register StkFloat *samples = (StkFloat *) outputBuffer;

    context->input_.tick(context->frames_);
    for (unsigned int i = 0; i < context->frames_.size(); i++) 
    {
        *samples++ = context->frames_[i];
    }
    if (context->input_.isFinished()) 
    {
        context->done_ = true;
        return 1;
    }
    else
    {
        return 0;
    }
}

SoundPlayer::SoundPlayer() :
    done_(false),
    input_()
{
    // pass
}

void SoundPlayer::stop()
{
    std::cout << "Stop : Not implemented." << std::endl;
}

void SoundPlayer::start(const std::string &fileName)
{
    std::cout << "Playing " << fileName << std::endl;

    // Set the global sample rate before creating class instances.
    Stk::setSampleRate((StkFloat) 48000.0); // FIXME
    // Initialize our WvIn and RtAudio pointers.
    RtAudio dac;

    // Try to load the soundfile.
    try 
    {
        input_.openFile(fileName);
    }
    catch (StkError &) 
    {
        std::cout << "Error trying to open file " << fileName << std::endl;
        exit(1); // FIXME
    }
    // Set input read rate based on the default STK sample rate.
    double rate = 1.0;
    rate = input_.getFileRate() / Stk::sampleRate();
    //if ( argc == 4 ) rate *= atof( argv[3] );
    input_.setRate(rate);
    input_.ignoreSampleRateChange();
    // Find out how many channels we have.
    int channels = input_.channelsOut();
    // Figure out how many bytes in an StkFloat and setup the RtAudio stream.
    RtAudio::StreamParameters parameters;
    parameters.deviceId = dac.getDefaultOutputDevice();
    parameters.nChannels = channels;
    RtAudioFormat format = (sizeof(StkFloat) == 8) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
    unsigned int bufferFrames = RT_BUFFER_SIZE;
    try 
    {
        //dac.openStream(&parameters, NULL, format, (unsigned int)Stk::sampleRate(), &bufferFrames, &tick, (void *)&input); // FIXME
        dac.openStream(&parameters, NULL, format, (unsigned int)Stk::sampleRate(), &bufferFrames, &soundplayer_tick, (void *)this); // FIXME
    }
    catch (RtError &error) 
    {
      error.printMessage();
      goto cleanup; // FIXME
    }
    // Install an interrupt handler function.
	// TODO: (void) signal(SIGINT, finish); // FIXME
    // Resize the StkFrames object appropriately.
    frames_.resize(bufferFrames, channels);
    try 
    {
        dac.startStream();
    }
    catch (RtError &error) 
    {
        error.printMessage();
        goto cleanup; // FIXME
    }

    // Block waiting until callback signals done.
    while (!done_)
    {
        Stk::sleep(100);
    }
    // By returning a non-zero value in the callback above, the stream
    // is automatically stopped.  But we should still close it.
    try 
    {
        dac.closeStream();
    }
    catch (RtError &error) 
    {
        error.printMessage();
    }
    cleanup: // FIXME
        //return 0;
        std::cout << "cleaning up..." << std::endl;
}

