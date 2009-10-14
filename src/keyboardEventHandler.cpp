#include "./keyboardEventHandler.h"
#include "./spriteState.h"
#include <iostream>

using std::tr1::shared_ptr;

KeyboardEventHandler::KeyboardEventHandler(shared_ptr<SpriteState> deviceState) :
    deviceState_(deviceState)
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
                        deviceState_->moveForwardRequest_ = true;
                        return false;
                        break;
                    case 's':
                    case osgGA::GUIEventAdapter::KEY_Down:
                        deviceState_->moveBackwardRequest_ = true;
                        return false;
                        break;
                    case 'a':
                    case osgGA::GUIEventAdapter::KEY_Left:
                        deviceState_->moveLeftRequest_ = true;
                        return false;
                        break;
                    case 'd':
                    case osgGA::GUIEventAdapter::KEY_Right:
                        deviceState_->moveRightRequest_ = true;
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
                        deviceState_->moveForwardRequest_ = false;
                        return false;
                        break;
                    case 's':
                    case osgGA::GUIEventAdapter::KEY_Down:
                        deviceState_->moveBackwardRequest_ = false;
                        return false;
                        break;
                    case 'a':
                    case osgGA::GUIEventAdapter::KEY_Left:
                        deviceState_->moveLeftRequest_ = false;
                        return false;
                        break;
                    case 'd':
                    case osgGA::GUIEventAdapter::KEY_Right:
                        deviceState_->moveRightRequest_ = false;
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

