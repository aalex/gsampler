#include "scene.h"
using namespace osg;

Scene::Scene() : root(new Group()) {
  createScene();
}

Scene::~Scene(){ }

void Scene::attach(osgUtil::SceneView& sceneview) const{
  sceneview.setSceneData(root.get());
}

void Scene::createScene(){
  Geode * scene_geode= new Geode();

  //20 units into the screen
  scene_geode->addDrawable(new ShapeDrawable(new Box(Vec3(-6,5,-20), 2.0)));
  scene_geode->addDrawable(new ShapeDrawable(new Sphere(Vec3(-3,5,-20), 1.0)));
  scene_geode->addDrawable(new ShapeDrawable(new Cone(Vec3(0, 5,-20), 1.0, 1.0)));
  scene_geode->addDrawable(new ShapeDrawable(new Cylinder(Vec3(3, 5,-20), 1.0, 1.0)));
  scene_geode->addDrawable(new ShapeDrawable(new Capsule(Vec3(6, 5,-20), 1.0, 1.0)));

  //25 units into the screen
  scene_geode->addDrawable(new ShapeDrawable(new Box(Vec3(-6,0,-25), 1.0)));
  scene_geode->addDrawable(new ShapeDrawable(new Sphere(Vec3(-3,0,-25), 1.0)));
  scene_geode->addDrawable(new ShapeDrawable(new Cone(Vec3(0, 0,-25), 1.0, 1.0)));
  scene_geode->addDrawable(new ShapeDrawable(new Cylinder(Vec3(3, 0,-25), 1.0, 1.0)));
  scene_geode->addDrawable(new ShapeDrawable(new Capsule(Vec3(6, 0,-25), 1.0, 1.0)));

  //30 units into the screen
  scene_geode->addDrawable(new ShapeDrawable(new Box(Vec3(-6,-5,-30), 1.0)));
  scene_geode->addDrawable(new ShapeDrawable(new Sphere(Vec3(-3,-5,-30), 1.0)));
  scene_geode->addDrawable(new ShapeDrawable(new Cone(Vec3(0, -5,-30), 1.0, 1.0)));
  scene_geode->addDrawable(new ShapeDrawable(new Cylinder(Vec3(3, -5,-30), 1.0, 1.0)));
  scene_geode->addDrawable(new ShapeDrawable(new Capsule(Vec3(6, -5,-30), 1.0, 1.0)));

  //35 units into the screen
  scene_geode->addDrawable(new ShapeDrawable(new Box(Vec3(-6,-10,-35), 1.0)));
  scene_geode->addDrawable(new ShapeDrawable(new Sphere(Vec3(-3,-10,-35), 1.0)));
  scene_geode->addDrawable(new ShapeDrawable(new Cone(Vec3(0, -10,-35), 1.0, 1.0)));
  scene_geode->addDrawable(new ShapeDrawable(new Cylinder(Vec3(3, -10,-35), 1.0, 1.0)));
  scene_geode->addDrawable(new ShapeDrawable(new Capsule(Vec3(6, -10,-35), 1.0, 1.0)));

  root->addChild(scene_geode);
}
