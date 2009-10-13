#ifndef _SPRITE_INPUT_DEVICE_STATE_H_
#define _SPRITE_INPUT_DEVICE_STATE_H_

class SpriteInputDeviceState
{
    friend class KeyboardEventHandler;
    friend class UpdatePositionCallback;
    public:
        SpriteInputDeviceState () : 
            moveForwardRequest_(false),
            moveBackwardRequest_(false),
            moveLeftRequest_(false),
            moveRightRequest_(false)
    {}
    private:
        bool moveForwardRequest_;
        bool moveBackwardRequest_;
        bool moveLeftRequest_;
        bool moveRightRequest_;
};

#endif // _SPRITE_INPUT_DEVICE_STATE_H_
