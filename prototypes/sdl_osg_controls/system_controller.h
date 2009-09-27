#ifndef SYSTEM_CONTROLLER_H
#define SYSTEM_CONTROLLER_H
#include <string>
using std::string;
#include <SDL/SDL.h>
#include "module_registry.h"
#include "scene.h"

/*
    Input manager class to handle all of our input events
*/
#include "input_manager.h"
/*
    Now we include the movable class to handle model transformations
*/
#include "movable.h"


class System_Controller{
public:
    System_Controller();
    ~System_Controller();
    void start_event_loop();
    
private:
    Module_Registry _module_registry;
    Window * _window;
    
    //Don't want to instantiate these guys
    System_Controller(const System_Controller& controller);
    const System_Controller& operator=(const System_Controller& controller);
};
#endif
