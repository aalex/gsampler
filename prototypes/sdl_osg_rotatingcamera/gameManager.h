#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <string>
using std::string;
#include <SDL/SDL.h>

const int WIDTH = 640;
const int HEIGHT = 480;

#include "scene.h"
#include "myCamera.h"

class GameManager{
public:
  GameManager();
  ~GameManager();
  void runEventLoop();
  void draw();
private:
  Scene* scene;
  osg::ref_ptr<osgUtil::SceneView> sceneView;
  MyCamera * globalCamera;

  GameManager(const GameManager&);
  const GameManager& operator=(const GameManager&);
};
#endif
