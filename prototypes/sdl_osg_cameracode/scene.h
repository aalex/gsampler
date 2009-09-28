#ifndef SCENE
#define SCENE
#include <osg/ShapeDrawable>
#include <osgUtil/SceneView>
#include <osg/Geode>

class Scene{
public:
  Scene();
  ~Scene();
    
  void attach(osgUtil::SceneView &) const;
private:
  void createScene();
  osg::ref_ptr<osg::Group> root;
};
#endif
