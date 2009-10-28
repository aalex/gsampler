/// btBulletDynamicsCommon.h is the main Bullet include file, contains most common include files.
//#include "btBulletDynamicsCommon.h"
#include <btBulletDynamicsCommon.h>

// TODO: remove some of those deps:
//#include <osgDB/ReadFile>
//#include <osg/CoordinateSystemNode>
//#include <osg/PositionAttitudeTransform>
//#include <osgUtil/Optimizer>
#include <osgViewer/Viewer>
//#include <osgViewer/ViewerEventHandlers>
//#include <osgGA/TrackballManipulator>
//#include <osgGA/FlightManipulator>
//#include <osgGA/DriveManipulator>
//#include <osgGA/KeySwitchMatrixManipulator>
//#include <osgGA/StateSetManipulator>
//#include <osgGA/AnimationPathManipulator>
//#include <osgGA/TerrainManipulator>

#include "./physics.h"

/**
 * Helper function to create a rigid body
 */
btRigidBody* Physics::createRigidBody(btDynamicsWorld *world,
                             float mass,
                             const btTransform& startTransform,
                             btCollisionShape* shape)
{
    //rigidbody is dynamic if and only if mass is non zero, otherwise static
    bool isDynamic = (mass != 0.f);
    btVector3 localInertia(0, 0, 0);
    if (isDynamic)
    {
        shape->calculateLocalInertia(mass, localInertia);
    }
    //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
    btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
    btRigidBody* body = new btRigidBody(mass, myMotionState, shape, localInertia);
    world->addRigidBody(body);
    return body;
}

void Physics::initPhysics()
{
    /*
     * Physics World
     */
    // dimensions of the world
    btVector3 worldAabbMin(-1000, -1000, -1000);
    btVector3 worldAabbMax(1000, 1000, 1000);
    const int maxProxies = 32766;
    btSequentialImpulseConstraintSolver *solver = new btSequentialImpulseConstraintSolver;
    btAxisSweep3 *broadphase = new btAxisSweep3(worldAabbMin, worldAabbMax, maxProxies);
    btDefaultCollisionConfiguration *collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
    dynamicsWorld_ = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
    dynamicsWorld_->setGravity(btVector3(0, 0, -9.8)); // 9.8 m/s/s
    // That means we use the metric system
    // ....
    //
    // ground plane
    {
        btCollisionShape *gnd_shape = new btStaticPlaneShape(btVector3(0, 0, 1), 0.5); // FIXME: check dimensions
        btVector4 pos;
        pos.setValue(0, 0, -0.5, 0); // FIXME: check position
        btTransform trans;
        trans.setIdentity();
        trans.setOrigin(pos);
        btScalar mass = 0.f; // FIXME: no need for a mass?
        btRigidBody* gnd = createRigidBody(dynamicsWorld_, mass, trans, gnd_shape);
        //gnd->setUserPointer(loadedModel2.get());
        gnd->setCollisionFlags(gnd->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
        gnd->setActivationState(DISABLE_DEACTIVATION);
    }

    // timer to calculate positions.
    frame_tick_ = osg::Timer::instance()->tick();
}
/**
 * Call this prior to render a frame.
 * Calculates the position of every rigid body in the scene
 * using the delta time since previous frame.
 */
void Physics::step()
{
    osg::Timer_t now_tick = osg::Timer::instance()->tick();
    float dt = osg::Timer::instance()->delta_s(frame_tick_, now_tick);
    frame_tick_ = now_tick;
    /* int numSimSteps = */
    dynamicsWorld_->stepSimulation(dt); //, 10, 0.01);
    dynamicsWorld_->updateAabbs();
    // ready to render
}
