#include <osg/Node>
#include <osg/PositionAttitudeTransform>
#include <osgDB/ReadFile> 
#include <osgUtil/Optimizer>

#include "./scene.h"

Scene::Scene(osg::ref_ptr<osg::Group> root)
{
    // load the scene graph here

    // die
    osg::ref_ptr<osg::Node> dieModel = osgDB::readNodeFile("die.osg");
    // Load the model as a child of a transform node so we can reposition the model. 
    osg::ref_ptr<osg::PositionAttitudeTransform> diePat = new osg::PositionAttitudeTransform;
    diePat->addChild(dieModel.get());
    root->addChild(diePat.get());
    
    // ground
    osg::ref_ptr<osg::Node> groundModel = osgDB::readNodeFile("ground-plane.osg");
    osg::ref_ptr<osg::PositionAttitudeTransform> groundPat = new osg::PositionAttitudeTransform;
    groundPat->addChild(groundModel.get());
    groundPat->setScale(osg::Vec3(100.0, 100.0, 0.1));
    root->addChild(groundPat.get());

    // optimize the scene graph, remove redundant nodes and state etc.
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());

    // switch off lighting as we haven't assigned any normals.
    //root->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
}

