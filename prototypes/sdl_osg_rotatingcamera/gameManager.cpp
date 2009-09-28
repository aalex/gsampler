#include <iostream>
#include "gameManager.h"

GameManager:: GameManager()
  : scene(new Scene()), 
    sceneView(new osgUtil::SceneView()) {
    if(SDL_Init(SDL_INIT_VIDEO)){
       string error("Error: SDL Could not be initialized: ");
       error += SDL_GetError();
       throw error;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    if(!SDL_SetVideoMode(WIDTH, HEIGHT, 0, SDL_OPENGL)){
       string error("Error: SDL Could not create Video Surface.");
       error += SDL_GetError();
       throw error;
    }
    SDL_WM_SetCaption("A Rotating Camera -- the objects don't move", 
		      "Camera");
    sceneView->setDefaults();
    sceneView->setComputeNearFarMode(
               osgUtil::CullVisitor::DO_NOT_COMPUTE_NEAR_FAR);

    sceneView->init();
    globalCamera = new MyCamera(WIDTH, HEIGHT, sceneView->getCamera());
    scene->attach(*sceneView.get());
}

GameManager::~GameManager() { 
  delete scene; 
  delete globalCamera; 
}

void GameManager:: draw(){
  sceneView->update();
  sceneView->cull();
  sceneView->draw();
}

void GameManager:: runEventLoop(){
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
    globalCamera->move();
    SDL_Delay(30);
  }
}
