#include "myCamera.h"
#include <iostream>
#include <SDL/SDL.h>
using namespace std;

// eye vector is where camera is placed; 
// dir vector is where the camera points; 
// up vector is the camera rotation vector.
// Magnitude matters for the first two vectors but not for the 3rd.
// For the 2nd vector, the x, y and z indicate where to aim the gaze.
// For the 3rd vector, the up vector, we use (0,1,0), which means
// to always point the top of the camera up!

MyCamera::MyCamera(int width, int height, osg::CameraNode* thisCamera) 
  : camera(thisCamera),
    eye(0.0, 0.0, 40.0), 
    dir(0.0, 0.0, 0.0), 
    up(0.0,1.0,0.0) {
  camera->setViewport(0, 0, width, height);
  camera->setProjectionMatrixAsPerspective(
		  45.0, 
		  camera->getViewport()->aspectRatio(),
		  0.1, 
		  1000.0
  );
  camera->getViewMatrix().makeIdentity();
  setClearColor();
  camera->setViewMatrixAsLookAt(eye, dir, up);
}

void MyCamera::move() {
  static float x;
  static float z;
  static float t = 0;
  t+=.01;
  x = -sin(t) * 40;
  z = cos(t) * 40;
  eye.set(x, eye.y(), z);
  camera->setViewMatrixAsLookAt(eye, dir, up);
}

