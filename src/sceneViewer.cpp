#include <iostream>

#include <osgViewer/View>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>

#include "./keyboardEventHandler.h"
#include "./sceneViewer.h"
#include "./scene.h"
#include "./spriteState.h"

using std::tr1::shared_ptr;

SceneViewer::SceneViewer() :
    root_(new osg::Group),
    spriteState_(new SpriteState), 
    remoteState_(new RemoteSpriteState),
    scene_(root_, spriteState_)
{}

void initializeViewer(osgViewer::Viewer &viewer, osg::ref_ptr<osg::Group> root,
        shared_ptr<SpriteState> spriteState)
{
    viewer.setSceneData(root.get());

    viewer.getCamera()->setClearColor(osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f)); // black
    // add keyboard event handler
    viewer.addEventHandler(new KeyboardEventHandler(spriteState));
    // add the window size toggle handler
    viewer.addEventHandler(new osgViewer::WindowSizeHandler);
    // attach a trackball manipulator to all user control of the view
    viewer.setCameraManipulator(new osgGA::TrackballManipulator);
    // create the windows and run the threads.
    viewer.realize();
}

void SceneViewer::run()
{
    scene_.addOpponent(remoteState_);

    // construct the viewer.
    osgViewer::Viewer viewer;

    initializeViewer(viewer, root_, spriteState_);

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
    std::cout << "Finished running viewer\n";
}

