#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <stk/Sampler.h>

namespace stk {
class SoundPlayer : public Sampler {
    public:
        SoundPlayer();
        ~SoundPlayer();

        //! Set instrument parameters for a particular frequency.
        void setFrequency(StkFloat frequency);
  
        //! Perform the control change specified by \e number and \e value (0.0 - 128.0).
        void controlChange( int number, StkFloat value );
  
        //! Compute and return one output sample.
        StkFloat tick( unsigned int channel = 0 );
};

inline StkFloat SoundPlayer::tick(unsigned int)
{
  // for now just output our loop without any change
  return lastFrame_[0] = loopGain_ * loops_[0]->tick();
}

} // stk namespace

#endif // _PLAYER_H_
