#include "system_controller.h"
////////////////////////////////////////////////////////////////////////////////
System_Controller::
System_Controller():
    _window(NULL)
{   
    try{
        _window = new Window();
        _module_registry.register_window(*_window);
    }
    catch(string error){
        throw error;
    }
    
    Scene * scene = new Scene();
    _module_registry.register_scene(*scene);
    _window->attach(*scene);
    
    /*
        Create and register the input manager
    */
    Input_Manager * input_manager = new Input_Manager();
    _module_registry.register_input_manager(*input_manager);
    
    /*
        Now set the input manager's target to be the movable object of the
        scene.
    */
    input_manager->set_target(scene->get_movable());
        
    /*
        The following must be in the same file as SDL_INIT() for some reason
        Ensures that SDL intercepts all mouse/keyboard input
    */
    SDL_WM_GrabInput(SDL_GRAB_ON);
    
    /*
        Ensures that SDL does not display the mouse cursor
    */
    SDL_ShowCursor(SDL_DISABLE);
}
////////////////////////////////////////////////////////////////////////////////
System_Controller::
~System_Controller(){}
////////////////////////////////////////////////////////////////////////////////
void System_Controller::
start_event_loop(){

    /*
        Grab a reference to the scene that has been created.
    */
    Input_Manager * input_manager = _module_registry.get_input_manager();
    
    while(true){
        /*
            WARNING! IF we have SDL to grab the input and not show a cursor,
            we MUST ensure that we have some mechanism for quitting the program,
            otherwise we will lose control of the entire OS as SDL intercepts
            ALL input!
        
            Use the input manager to handle the keyboard/mouse input. Check to
            see if the user has chosen to quit.
        */
        if(input_manager->handle_input() == Input_Manager::QUIT){
            break;
        }
        
        _window->draw();
        SDL_GL_SwapBuffers();
    }
}
////////////////////////////////////////////////////////////////////////////////
