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


class RemoteSpriteState
{
    friend class RemoteUpdatePositionCallback;
    friend class StateClient;
    public:
        RemoteSpriteState () : moveRequest_(false),
        position_(0.0, 0.0, 0.0)
    {}
    private:
        bool moveRequest_;
        osg::Vec3d position_;
};

#endif // _SPRITE_STATE_H_
