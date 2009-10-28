#ifndef _PHYSICS_H_
#define _PHYSICS_H_
#include <btBulletDynamicsCommon.h>
#include <osg/Node>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

class Physics {
    private:
        btDynamicsWorld *dynamicsWorld_;
        osg::Timer_t frame_tick_;
        btRigidBody* createRigidBody(btDynamicsWorld *world,
                             float mass,
                             const btTransform& startTransform,
                             btCollisionShape* shape);
    public:
        void initPhysics();
        void step();
};

#endif // _PHYSICS_H_
