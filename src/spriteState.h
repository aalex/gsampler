#ifndef _SPRITE_STATE_H_
#define _SPRITE_STATE_H_

class SpriteState
{
    friend class KeyboardEventHandler;
    friend class UpdatePositionCallback;
    public:
        SpriteState () : 
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

#endif // _SPRITE_STATE_H_
