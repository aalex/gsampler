#ifndef _KEYBOARD_EVENT_HANDLER_H_
#define _KEYBOARD_EVENT_HANDLER_H_

#include <osgGA/GUIEventHandler>
#include <osgGA/GUIActionAdapter>

#include <tr1/memory>

class SpriteState;

class KeyboardEventHandler : public osgGA::GUIEventHandler
{
    public:
        KeyboardEventHandler(std::tr1::shared_ptr<SpriteState> spriteState); 
        virtual bool handle(const osgGA::GUIEventAdapter &eventAdapter, 
                osgGA::GUIActionAdapter &actionAdapter);
        virtual void accept(osgGA::GUIEventHandlerVisitor &visitor);
    private:
        std::tr1::shared_ptr<SpriteState> spriteState_;
};

#endif // _KEYBOARD_EVENT_HANDLER_H_
