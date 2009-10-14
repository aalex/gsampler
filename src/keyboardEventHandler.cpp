#include "./keyboardEventHandler.h"
#include "./spriteState.h"
#include <iostream>

using std::tr1::shared_ptr;

KeyboardEventHandler::KeyboardEventHandler(shared_ptr<SpriteState> spriteState) :
    spriteState_(spriteState)
{
}

bool KeyboardEventHandler::handle(const osgGA::GUIEventAdapter &eventAdapter, 
        osgGA::GUIActionAdapter &actionAdapter)
{
    switch (eventAdapter.getEventType())
    {
        case osgGA::GUIEventAdapter::KEYDOWN:
            {
                switch (eventAdapter.getKey())
                {
                    case 'w':
                    case osgGA::GUIEventAdapter::KEY_Up:
                        spriteState_->moveForwardRequest_ = true;
                        return false;
                        break;
                    case 's':
                    case osgGA::GUIEventAdapter::KEY_Down:
                        spriteState_->moveBackwardRequest_ = true;
                        return false;
                        break;
                    case 'a':
                    case osgGA::GUIEventAdapter::KEY_Left:
                        spriteState_->moveLeftRequest_ = true;
                        return false;
                        break;
                    case 'd':
                    case osgGA::GUIEventAdapter::KEY_Right:
                        spriteState_->moveRightRequest_ = true;
                        return false;
                        break;
                    default:
                        return false;
                }
            }
        case osgGA::GUIEventAdapter::KEYUP:
            {
                switch (eventAdapter.getKey())
                {
                    case 'w':
                    case osgGA::GUIEventAdapter::KEY_Up:
                        spriteState_->moveForwardRequest_ = false;
                        return false;
                        break;
                    case 's':
                    case osgGA::GUIEventAdapter::KEY_Down:
                        spriteState_->moveBackwardRequest_ = false;
                        return false;
                        break;
                    case 'a':
                    case osgGA::GUIEventAdapter::KEY_Left:
                        spriteState_->moveLeftRequest_ = false;
                        return false;
                        break;
                    case 'd':
                    case osgGA::GUIEventAdapter::KEY_Right:
                        spriteState_->moveRightRequest_ = false;
                        return false;
                        break;
                    default:
                        return false;
                }
            }
        default:
            return false;
    }
}

void KeyboardEventHandler::accept(osgGA::GUIEventHandlerVisitor &visitor)
{
    visitor.visit(*this);
}

