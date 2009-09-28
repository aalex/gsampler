#ifndef WINDOW_H
#define WINDOW_H
#include <string>
using std::string;
#include <SDL/SDL.h>
#include <osg/CameraNode>
#include <osgUtil/SceneView>
#include "scene.h"
class Scene;
#include "module_registry.h"
class Module_Registry;

class Window{
public:
    Window();
    ~Window();
    
    void set_module_registry(Module_Registry& registry);
    void draw();
    void attach(Scene& scene);
    
private:
    Module_Registry * _module_registry;

    osg::ref_ptr<osgUtil::SceneView>             _scene_view;
    osg::ref_ptr<osg::CameraNode>                _global_camera;

    //Don't want to instantiate these guys
    Window(const Window& window);
    const Window& operator=(const Window& window);
};
#endif
