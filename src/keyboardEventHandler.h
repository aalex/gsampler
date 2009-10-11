#ifndef _KEYBOARD_EVENT_HANDLER_H_
#define _KEYBOARD_EVENT_HANDLER_H_

#include <osgGA/GUIEventHandler>
#include <osgGA/GUIActionAdapter>

class KeyboardEventHandler : public osgGA::GUIEventHandler
{
    public:
        virtual bool handle(const osgGA::GUIEventAdapter &eventAdapter, 
                osgGA::GUIActionAdapter &actionAdapter);
        virtual void accept(osgGA::GUIEventHandlerVisitor &visitor);
};

#endif // _KEYBOARD_EVENT_HANDLER_H_
