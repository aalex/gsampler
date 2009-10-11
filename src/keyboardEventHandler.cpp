#include "./keyboardEventHandler.h"
#include <iostream>

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
                        std::cout << " w key pressed " << std::endl;
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

