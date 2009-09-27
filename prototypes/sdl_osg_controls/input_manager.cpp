#include "input_manager.h"
////////////////////////////////////////////////////////////////////////////////
Input_Manager::
Input_Manager():
    _registry(NULL),
    _target(NULL)
    {}
////////////////////////////////////////////////////////////////////////////////
Input_Manager::
~Input_Manager(){}
////////////////////////////////////////////////////////////////////////////////
void Input_Manager::
set_module_registry(Module_Registry& registry){
    _registry = &registry;
}
////////////////////////////////////////////////////////////////////////////////
void Input_Manager::
set_target(Movable& target){
    _target = &target;
}
////////////////////////////////////////////////////////////////////////////////
Input_Manager::SIGNAL Input_Manager::
handle_input(){

    /*
        Here we have moved our event loop processing out of System_Controller
        and into Input_Manager.
        
        We have done this to keep System_Controller clean, and abstract all
        input handling to another class.
    */
    //Poll to see if we have any SDL Events
    if (SDL_PollEvent(&_event)){
    
        //Determine the type of the event
        switch(_event.type){
        
            //User has clicked the close button
            case SDL_QUIT:
                return Input_Manager::QUIT;

            //User has pressed a keyboard key - single stroke
            case SDL_KEYDOWN:
            
                /*
                    Check to see if the user has chosen to quit the program.
                    If so, return QUIT
                */
                if(handle_keyboard_single() == Input_Manager::QUIT){
                    return Input_Manager::QUIT;
                }
                break;

            //User has moved the mouse
            case SDL_MOUSEMOTION:
                handle_mouse_motion();
                break;
                
            //User has pressed one of the buttons (single click register)
            case SDL_MOUSEBUTTONDOWN:
                handle_mouse_single();
                break;
                
            /*
                None of the above types have happened, so we break to process
                continuous input.
            */
            default: 
                break;
        }
    }
    
    /*
        Handle keys being pressed down continuously
    */
    handle_keyboard_repeating();
    
    /*
        Handle mouse button held down continuously
    */
    handle_mouse_repeating();
    
    /*
        Return a normal signal if the user did not choose to quit the program
    */
    return Input_Manager::NORMAL;
}
////////////////////////////////////////////////////////////////////////////////
Input_Manager::SIGNAL Input_Manager::
handle_mouse_motion(){
    /*
        Relative Mouse Motion: This floating point number represents the distance
        covered by the mouse since the last update of the event. We use this to
        determine if the mouse moved along the x/y axis, in which case the
        respective floats will be !0.
    */
    
    /*
        Rotation on the x axis
    */
    //If the mouse was moved to the right
    if(_event.motion.xrel > 0.0){
        _target->rotate_x(_event.motion.xrel);
    }
    //If the mouse was moved to the left
    else if(_event.motion.xrel < 0.0){
        _target->rotate_x(_event.motion.xrel);
    }

    /*
        What's up with yrel > 0 being down? Well, SDL has the (0,0) coordinate
        as the upper left hand corner of the window. Therefore, positive y
        direction moves down the screen, unlike OSG.
    */
    /*
        Rotation on the y axis
    */
    //If the mouse was moved down
    if(_event.motion.yrel > 0.0){
        _target->rotate_y(_event.motion.yrel);
    }
    //if the mouse was moved up
    else if(_event.motion.yrel < 0.0){
        _target->rotate_y(_event.motion.yrel);
    }

    /*
        Always return a normal signal, as the user cannot quit with mouse motion.
    */
    return Input_Manager::NORMAL;
}
////////////////////////////////////////////////////////////////////////////////
Input_Manager::SIGNAL Input_Manager::
handle_mouse_single(){
    /*
        Here we check for one time registration of the left and right mouse
        buttons. This means that even though we may hold the button down, we're
        only going to register the first instance of the button, thus these
        messages will only be printed once per click.
    */
    
    /*
        User has clicked the left mouse button
    */
    if(_event.button.button == SDL_BUTTON_LEFT){
        cout << "Left mouse button clicked" << endl;
    }
    /*
        User has clicked the right mouse button
    */
    else if(_event.button.button == SDL_BUTTON_RIGHT){
        cout << "Right mouse button clicked" << endl;
    }

    //Return normal signal
    return Input_Manager::NORMAL;
}
////////////////////////////////////////////////////////////////////////////////
Input_Manager::SIGNAL Input_Manager::
handle_keyboard_single(){
    /*
        Here, like the above mouse single function, we check for single instances
        of keystrokes. If the buttons are held down, this function will only
        register the first instance of it.
        
        This is done checking the key.keysym.sym mapping.
    */

    /*
        User has pressed the escape key - return QUIT signal
        This is the only function that will ever produce a QUIT signal
    */
    if(_event.key.keysym.sym == SDLK_ESCAPE){
        return Input_Manager::QUIT;
    }
    //w - move up 1 unit per stroke
    else if(_event.key.keysym.sym == SDLK_w){
        _target->translate_y(1.0);
    }
    //s - move down 1 unit per stroke
    else if(_event.key.keysym.sym == SDLK_s){
        _target->translate_y(-1.0);
    }
    //a - move left 1 unit per stroke
    else if(_event.key.keysym.sym == SDLK_a){
        _target->translate_x(-1.0);
    }
    //d - move right 1 unit per stroke
    else if(_event.key.keysym.sym == SDLK_d){
        _target->translate_x(1.0);
    }
    //q - move out 1 unit per stroke
    else if(_event.key.keysym.sym == SDLK_q){
        _target->translate_z(1.0);
    }
    //e - move in 1 unit per stroke
    else if(_event.key.keysym.sym == SDLK_e){
        _target->translate_z(-1.0);
    }
    
    //Return normal signal
    return Input_Manager::NORMAL;
}
////////////////////////////////////////////////////////////////////////////////
Input_Manager::SIGNAL Input_Manager::
handle_keyboard_repeating(){
    /*
        Now we must check for keys being held down - get the keyboard snapshot
        to show the keys currently pressed. As the keystate is an array of
        key data [pressed|not pressed], more than one key may be pressed at a time.
        Thus we have all if's without any else. Also note that this method of key
        inspection will take into account keys that are being held down, so
        any functionality associated with these keys will trigger for EACH time
        through our event loop.
        
        Here we grab the keystate mapping snapshot. For each key, we want to
        translate our movable object.
    */
    Uint8 * keystate = SDL_GetKeyState(NULL);
    
    //Y Movement - up or down arrow keys being pressed
    if(keystate[SDLK_UP]){
        _target->translate_y(0.01);
    }
    if(keystate[SDLK_DOWN]){
        _target->translate_y(-0.01);
    }
    
    //X Movement - left or right arrow keys being pressed
    if(keystate[SDLK_LEFT]){
        _target->translate_x(-0.01);
    }
    if(keystate[SDLK_RIGHT]){
        _target->translate_x(0.01);
    }
    
    //Z Movement - pageup or pagedown arrow keys being pressed
    if(keystate[SDLK_PAGEUP]){
        _target->translate_z(0.01);
    }
    if(keystate[SDLK_PAGEDOWN]){
        _target->translate_z(-0.01);
    }
    
    //Return normal signal
    return Input_Manager::NORMAL;
}
////////////////////////////////////////////////////////////////////////////////
Input_Manager::SIGNAL Input_Manager::
handle_mouse_repeating(){
    /*
        Now we must check for mouse buttons being held down. This works similarly
        to the function above with the keys, but the data map is different. This
        one is not vector, but instead an integer representing a bitmap of the
        buttons. When operated with a boolean '&' with the SDL_BUTTON(x) mask,
        the button being pressed can be determined. SDL_BUTTON takes in an integer
        representing the button.
        
        Here we rotate around the z axis depending on which button is pressed
    */
    Uint8 keystate = SDL_GetMouseState(NULL, NULL);
    
    //Left mouse button
    if(keystate & SDL_BUTTON(1)){
        _target->rotate_z(0.05);
    }
    //Middle mouse button
    if(keystate & SDL_BUTTON(2)){
        //DO NOTHING - change me if you like
    }
    //Right mouse button
    if(keystate & SDL_BUTTON(3)){
        _target->rotate_z(-0.05);
    }
    
    //Return normal signal
    return Input_Manager::NORMAL;
}
////////////////////////////////////////////////////////////////////////////////
