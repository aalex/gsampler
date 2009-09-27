/*##############################################################################
    File:       input_manager.h
    Purpose:    Class designed to handle all of the input events from keyboard/mouse. 
    This specific instance of the class is tied to a Movable * _target object, 
    as the input will manipulate the target in some way. This class uses SDL 
    Events to handle input interception.
                
    Returns:    Input_Manager::SIGNAL enumeration:
                    NORMAL - on normal loop returns
                    QUIT   - on request for program termination
##############################################################################*/
#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H
#include <iostream>
using std::endl; using std::cout;
#include <SDL/SDL.h>
#include "movable.h"
#include "module_registry.h"

//##############################################################################

class Module_Registry;
class Input_Manager{
public:

    /*
        Here we define the signals we need to let our parent know the status
        of the program.
    */
    enum SIGNAL{
        NORMAL,     //handle_input() processed input correctly
        QUIT        //handle_input() says the user wants to exit the program
    };
    
/*//////////////////////////////////////////////////////////////////////////////
    Default Constructor - Initialize pointers to NULL
/////////////////////////////////////////////////////////////////////////////*/
    Input_Manager();

/*//////////////////////////////////////////////////////////////////////////////
    Default Destructor - Empty
/////////////////////////////////////////////////////////////////////////////*/
    ~Input_Manager();
    
/*//////////////////////////////////////////////////////////////////////////////
    Sets the module registry reference
/////////////////////////////////////////////////////////////////////////////*/
    void set_module_registry(Module_Registry& registry);
    
/*//////////////////////////////////////////////////////////////////////////////
    Sets the target Movable object of this class as this parameter.
/////////////////////////////////////////////////////////////////////////////*/
    void set_target(Movable& target);
    
/*//////////////////////////////////////////////////////////////////////////////
    General function called to interpret all user input. 
    Returns Input_Manager::NORMAL on normal loop returns
            Input_Manager::QUIT when user requests to quit.
/////////////////////////////////////////////////////////////////////////////*/
    SIGNAL handle_input();
    
private:
    Module_Registry * _registry;
    
    /*
        SDL Event that contains the input device data from the last query
    */
    SDL_Event _event;
    
    /*
        Our target object we are going to control through input
    */
    Movable * _target;

/*  PRIVATE FUNCTIONS */
    //Handle mouse x/y motion
    SIGNAL handle_mouse_motion();
    
    //Handle single mouse clicks (max 1 event per click)
    SIGNAL handle_mouse_single();
    
    //Handle pressed mouse events (triggers as long as button is held)
    SIGNAL handle_mouse_repeating();    
    
    //Handle all single key strokes (max 1 event per key)
    SIGNAL handle_keyboard_single();
    
    //Handle pressed key strokes (triggers as long as key is held)
    SIGNAL handle_keyboard_repeating();    
};
#endif
