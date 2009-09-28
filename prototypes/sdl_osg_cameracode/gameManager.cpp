#include "gameManager.h"
GameManager:: GameManager()
  : scene(new Scene()), 
    sceneView(new osgUtil::SceneView()), 
    globalCamera(NULL) {
  try{
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
    sceneView->setDefaults();
    sceneView->setComputeNearFarMode(
               osgUtil::CullVisitor::DO_NOT_COMPUTE_NEAR_FAR);
    globalCamera = sceneView->getCamera();
    globalCamera->setViewport(0, 0, 640, 480);
    globalCamera->setProjectionMatrixAsPerspective(
       45.0,
       globalCamera->getViewport()->aspectRatio(),
       0.1,
       1000.0
    );
    globalCamera->setClearColor(osg::Vec4(0.2, 0.2, 0.4, 0.0));

    // First vector is where camera is, Second vector is where the
    // camera points, Third is the camera rotation vector (up vector)
    // Magnitude matters for the first two vectors but not for the 3rd.
    // For the 2nd vector, the x, y and z aim the gaze.
    // We're aiming the gaze at the middel object in the second row!
    // For the 3rd vector, the up vector, we use (0,1,0), which means
    // to always point the top of the camera up!
    globalCamera->setViewMatrixAsLookAt(osg::Vec3d(20.0, 0.0, 10.0),
                  osg::Vec3d(0.0, 0.0, -25.0), osg::Vec3d(0.0, 1.0, 0.0));
    sceneView->init();
    scene->attach(*sceneView.get());

  }
  catch(const string &error){
    throw error;
  }
}

GameManager::~GameManager() { delete scene; }

void GameManager:: draw(){
  sceneView->update();
  sceneView->cull();
  sceneView->draw();
}

void GameManager:: startEventLoop(){
  SDL_Event event;
  while(true){
    if (SDL_PollEvent(&event)){
      switch(event.type){
        case SDL_QUIT: return;
        case SDL_KEYDOWN:
          if(event.key.keysym.sym == SDLK_ESCAPE){
            return;
          }
      }
    }
    draw();
    SDL_GL_SwapBuffers();
  }
}
