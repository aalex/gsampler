#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <string>
using std::string;

#include <SDL/SDL.h>

#include "scene.h"
#include <osg/CameraNode>

class GameManager{
public:
  GameManager();
  ~GameManager();
  void startEventLoop();
  void draw();
private:
  Scene* scene;
  osg::ref_ptr<osgUtil::SceneView> sceneView;
  osg::ref_ptr<osg::CameraNode>    globalCamera;

  GameManager(const GameManager&);
  const GameManager& operator=(const GameManager&);
};
#endif
