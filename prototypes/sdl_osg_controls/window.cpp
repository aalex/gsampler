#include "window.h"
////////////////////////////////////////////////////////////////////////////////
Window::
Window():
    _module_registry(NULL),
	_scene_view(NULL),
	_global_camera(NULL)
{
////////////////////////////////////////////////////////////////////////////////
//SDL Initialization

    if(SDL_Init(SDL_INIT_VIDEO)){
        string error("Error: SDL Could not be initialized: ");
        error += SDL_GetError();
        throw error;
    }
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    if(!SDL_SetVideoMode(640, 480, 0, SDL_OPENGL)){
        string error("Error: SDL Could not create Video Surface.");
        error += SDL_GetError();
        throw error;
    }
////////////////////////////////////////////////////////////////////////////////
//OSG Initialization

	_scene_view = new osgUtil::SceneView();
	_scene_view->setDefaults();
	_scene_view->setComputeNearFarMode(osgUtil::CullVisitor::DO_NOT_COMPUTE_NEAR_FAR);
	
    _global_camera = _scene_view->getCamera();
	_global_camera->setViewport(0, 0, 640, 480);
	_global_camera->setProjectionMatrixAsPerspective(
	   45.0,
	   _global_camera->getViewport()->aspectRatio(),
	   0.1,
	   1000.0
	   );
	_global_camera->setClearColor(osg::Vec4(0.2, 0.2, 0.4, 0.0));
	_scene_view->init();
}
////////////////////////////////////////////////////////////////////////////////
Window::
~Window(){
    SDL_Quit();
}
////////////////////////////////////////////////////////////////////////////////
void Window::
set_module_registry(Module_Registry& registry){
    _module_registry = &registry;
}
////////////////////////////////////////////////////////////////////////////////
void Window::
draw(){
	_scene_view->update(); 
	_scene_view->cull(); 
	_scene_view->draw();
}
////////////////////////////////////////////////////////////////////////////////
void Window::
attach(Scene& scene){
    scene.attach(*_scene_view.get());
}
////////////////////////////////////////////////////////////////////////////////
