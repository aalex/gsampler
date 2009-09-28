#ifndef MODULE_REGISTRY_H
#define MODULE_REGISTRY_H
#include "window.h"
#include "scene.h"
#include "input_manager.h"
class Window;
class Scene;
class Input_Manager;
class Module_Registry{
public:

    Module_Registry();
    ~Module_Registry();
    
    void register_window(Window& window);
    Window * get_window();
    
    void register_scene(Scene& scene);
    Scene * get_scene();
    
    /*
        Add the ability to register the input manager with this registry
    */
    void register_input_manager(Input_Manager& input_manager);
    Input_Manager * get_input_manager();

private:
    Window * _window;
    Scene * _scene;
    
    /*
        Input manager pointer
    */
    Input_Manager * _input_manager;
    
    //Don't want to instantiate these guys
    Module_Registry(const Module_Registry& registry);
    Module_Registry& operator=(const Module_Registry& registry);
};
#endif
