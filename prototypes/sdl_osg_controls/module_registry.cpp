#include "module_registry.h"
////////////////////////////////////////////////////////////////////////////////
Module_Registry::
Module_Registry():
    _window(NULL),
    _scene(NULL),
    _input_manager(NULL)        //Set pointer to null initially
{
    //Do nothing
}
////////////////////////////////////////////////////////////////////////////////
Module_Registry::
~Module_Registry(){
    if(_window)
        delete _window;
    if(_scene)
        delete _scene;
        
    //Delete the input manager if it exists        
    if(_input_manager)
        delete _input_manager;
}
////////////////////////////////////////////////////////////////////////////////
void Module_Registry::
register_window(Window& window){
    if(_window)
        delete _window;
    _window = &window;
    _window->set_module_registry(*this);
}
////////////////////////////////////////////////////////////////////////////////
Window * Module_Registry::
get_window(){
    return _window;
}
////////////////////////////////////////////////////////////////////////////////
void Module_Registry::
register_scene(Scene& scene){
    if(_scene)
        delete _scene;
    _scene = &scene;
    _scene->set_module_registry(*this);
}
////////////////////////////////////////////////////////////////////////////////
Scene * Module_Registry::
get_scene(){
    return _scene;
}
////////////////////////////////////////////////////////////////////////////////
void Module_Registry::
register_input_manager(Input_Manager& input_manager){
    if(_input_manager)
        delete _input_manager;
    _input_manager = &input_manager;
    _input_manager->set_module_registry(*this);
}
////////////////////////////////////////////////////////////////////////////////
Input_Manager * Module_Registry::
get_input_manager(){
    return _input_manager;
}
////////////////////////////////////////////////////////////////////////////////
