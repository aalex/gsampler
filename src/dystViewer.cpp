#include <osg/Node>
#include <osgDB/ReadFile> 
#include <osgViewer/View>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>
#include <osgUtil/Optimizer>

#include "./dystViewer.h"

DystViewer::DystViewer()
{}

void initializeScene(osg::ref_ptr<osg::Group> root)
{
    // load the scene graph here
    //osg::ref_ptr<osg::Geode> pyramidGeode = new osg::Geode;
    //osg::ref_ptr<osg::Geometry> pyramidGeometry = new osg::Geometry;

    osg::ref_ptr<osg::Node> ballNode = osgDB::readNodeFile("ball.osg");
    root->addChild(ballNode);

    // optimize the scene graph, remove redundant nodes and state etc.
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());

    // switch off lighting as we haven't assigned any normals.
    root->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
}

void initializeViewer(osgViewer::Viewer &viewer)
{
    // scenegraph root
    osg::ref_ptr<osg::Group> root = new osg::Group;

    initializeScene(root);

    viewer.setSceneData(root.get());

    // add the window size toggle handler
    viewer.addEventHandler(new osgViewer::WindowSizeHandler);
    // attach a trackball manipulator to all user control of the view
    viewer.setCameraManipulator(new osgGA::TrackballManipulator());
    // create the windows and run the threads.
    viewer.realize();
}

void DystViewer::run()
{
    // construct the viewer.
    osgViewer::Viewer viewer;

    initializeViewer(viewer);

   // osg::Timer_t frame_tick = osg::Timer::instance()->tick();
    while (!viewer.done())
    {
        // Physics update would happen here
//        osg::Timer_t now_tick = osg::Timer::instance()->tick();
 //       float dt = osg::Timer::instance()->delta_s(frame_tick, now_tick);
  //      frame_tick = now_tick;

        // render
        viewer.frame();
    }
}
