#ifndef SCENE
#define SCENE
#include <osgUtil/SceneView>
#include <osgDB/ReadFile>
#include <osg/PositionAttitudeTransform>
#include "module_registry.h"
class Module_Registry;
#include "movable.h"
class Scene{
public:
    Scene();
    ~Scene();
    
    void attach(osgUtil::SceneView& sceneview);
    void set_module_registry(Module_Registry& registry);
    
/*//////////////////////////////////////////////////////////////////////////////
    Function to return the movable object created by this class.
//////////////////////////////////////////////////////////////////////////////*/
    Movable& get_movable() const;
    

private:
    Module_Registry * _module_registry;
    void create_scene();
    osg::Group *                     _root;
    
    /*
        Movable object of this scene.
    */
    Movable * _movable;
};
#endif
