#include <osg/CameraNode>

class MyCamera {
public:
  MyCamera(int, int, osg::CameraNode *);
  void  move();
  osg::Vec3d getEye() { return eye; }
  osg::Vec3d getDir() { return dir; }
  osg::Vec3d getUp()  { return up;  }
  void  setClearColor() {
    camera->setClearColor(osg::Vec4(0.2, 0.2, 0.4, 0.0));
  }
private:
  MyCamera();
  osg::ref_ptr<osg::CameraNode> camera;
  osg::Vec3d eye;
  osg::Vec3d dir;
  osg::Vec3d up;
};
