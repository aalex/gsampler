#include "scene.h"
////////////////////////////////////////////////////////////////////////////////
Scene::
Scene():
    _module_registry(NULL),
    _root(new osg::Group()),
    _movable(NULL)              //Movable should initially be null
{
    create_scene();
}
////////////////////////////////////////////////////////////////////////////////
Scene::
~Scene(){
    /*
        If the movable object exists, delete it
    */
    if(_movable) 
        delete _movable;
}
////////////////////////////////////////////////////////////////////////////////
void Scene::
attach(osgUtil::SceneView& sceneview){
    sceneview.setSceneData(_root);
}
////////////////////////////////////////////////////////////////////////////////
void Scene::
create_scene(){

    osg::Node *  model = osgDB::readNodeFile("data/starthing.obj");
    if(!model){
        throw string("Error! Could not load node file.");
    }
    osg::PositionAttitudeTransform * _model_pat = new osg::PositionAttitudeTransform();
    _model_pat->setPosition(osg::Vec3d(0, 0, -20));
    _model_pat->addChild(model);
    _root->addChild(_model_pat);
    
    /*
        Create the Movable as this PAT containing the model we wish to control.
    */
    _movable = new Movable(*_model_pat);
}
////////////////////////////////////////////////////////////////////////////////
void Scene::
set_module_registry(Module_Registry& registry){
    _module_registry = &registry;
}
////////////////////////////////////////////////////////////////////////////////
Movable& Scene::
get_movable() const{
    /*
        Return a reference to the movable object.
    */
    return *_movable;
}
////////////////////////////////////////////////////////////////////////////////
