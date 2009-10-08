#include <osgViewer/View>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>
#include <osgGA/TrackballManipulator>
#include <osg/PositionAttitudeTransform>
#include <osgUtil/Optimizer>

#include "./dystViewer.h"

DystViewer::DystViewer()
{}

void initializeScene(osg::ref_ptr<osg::Group> root)
{
    // load the scene graph here
    osg::ref_ptr<osg::Geode> pyramidGeode = new osg::Geode;
    osg::ref_ptr<osg::Geometry> pyramidGeometry = new osg::Geometry;

    // Associate the pyramid geometry with the pyramid geode
    // Add the pyramid geode to the root node of the scene graph.

    pyramidGeode->addDrawable(pyramidGeometry);
    root->addChild(pyramidGeode);

    //Declare an array of vertices. Each vertex will be represented by
    //a triple -- an instances of the vec3 class. An instance of
    //osg::Vec3Array can be used to store these triples. Since
    //osg::Vec3Array is derived from the STL vector class, we can use the
    //push_back method to add array elements. Push back adds elements to
    //the end of the vector, thus the index of first element entered is
    //zero, the second entries index is 1, etc.
    //Using a right-handed coordinate system with 'z' up, array
    //elements zero..four below represent the 5 points required to create
    //a simple pyramid.
    osg::ref_ptr<osg::Vec3Array> pyramidVertices = new osg::Vec3Array;
    pyramidVertices->push_back( osg::Vec3( 0, 0, 0) ); // front left
    pyramidVertices->push_back( osg::Vec3(10, 0, 0) ); // front right
    pyramidVertices->push_back( osg::Vec3(10,10, 0) ); // back right
    pyramidVertices->push_back( osg::Vec3( 0,10, 0) ); // back left
    pyramidVertices->push_back( osg::Vec3( 5, 5,10) ); // peak

    // associate this set of vertices with the geometry associated with the geode
    // we added to the scene
    pyramidGeometry->setVertexArray(pyramidVertices);

    //Next, create a primitive set and add it to the pyramid geometry.
    //Use the first four points of the pyramid to define the base using an
    //instance of the DrawElementsUint class. Again this class is derived
    //from the STL vector, so the push_back method will add elements in
    //sequential order. To ensure proper backface cullling, vertices
    //should be specified in counterclockwise order. The arguments for the
    //constructor are the enumerated type for the primitive
    //(same as the OpenGL primitive enumerated types), and the index in
    //the vertex array to start from.
    osg::ref_ptr<osg::DrawElementsUInt> pyramidBase =
        new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
    pyramidBase->push_back(3);
    pyramidBase->push_back(2);
    pyramidBase->push_back(1);
    pyramidBase->push_back(0);
    pyramidGeometry->addPrimitiveSet(pyramidBase);

    //Repeat the same for each of the four sides. Again, vertices are
    //specified in counter-clockwise order.

    osg::ref_ptr<osg::DrawElementsUInt> pyramidFaceOne =
        new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
    pyramidFaceOne->push_back(0);
    pyramidFaceOne->push_back(1);
    pyramidFaceOne->push_back(4);
    pyramidGeometry->addPrimitiveSet(pyramidFaceOne);

    osg::ref_ptr<osg::DrawElementsUInt> pyramidFaceTwo =
        new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
    pyramidFaceTwo->push_back(1);
    pyramidFaceTwo->push_back(2);
    pyramidFaceTwo->push_back(4);
    pyramidGeometry->addPrimitiveSet(pyramidFaceTwo);

    osg::ref_ptr<osg::DrawElementsUInt> pyramidFaceThree =
        new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
    pyramidFaceThree->push_back(2);
    pyramidFaceThree->push_back(3);
    pyramidFaceThree->push_back(4);
    pyramidGeometry->addPrimitiveSet(pyramidFaceThree);

    osg::ref_ptr<osg::DrawElementsUInt> pyramidFaceFour =
        new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
    pyramidFaceFour->push_back(3);
    pyramidFaceFour->push_back(0);
    pyramidFaceFour->push_back(4);
    pyramidGeometry->addPrimitiveSet(pyramidFaceFour);

    //Declare and load an array of Vec4 elements to store colors.

    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
    colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f) ); //index 0 red
    colors->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f) ); //index 1 green
    colors->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f) ); //index 2 blue
    colors->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f) ); //index 3 white
    colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f) ); //index 4 red

    //The next step is to associate the array of colors with the geometry,
    //assign the color indices created above to the geometry and set the
    //binding mode to _PER_VERTEX.

    pyramidGeometry->setColorArray(colors);
    pyramidGeometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);


    //Now that we have created a geometry node and added it to the scene
    //we can reuse this geometry. For example, if we wanted to put a
    //second pyramid 15 units to the right of the first one, we could add
    //this geode as the child of a transform node in our scene graph.


    // Declare and initialize a transform node.
    osg::ref_ptr<osg::PositionAttitudeTransform> pyramidTwoXForm =
        new osg::PositionAttitudeTransform();

    // Use the 'addChild' method of the osg::Group class to
    // add the transform as a child of the root node and the
    // pyramid node as a child of the transform.

    root->addChild(pyramidTwoXForm);
    pyramidTwoXForm->addChild(pyramidGeode);

    // Declare and initialize a Vec3 instance to change the
    // position of the model in the scene

    osg::Vec3 pyramidTwoPosition(15,0,0);
    pyramidTwoXForm->setPosition( pyramidTwoPosition );

    // optimize the scene graph, remove redundant nodes and state etc.
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());

    // switch off lighting as we haven't assigned any normals.
    root->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
}


void initializeViewer(osgViewer::Viewer &viewer)
{
    // add the state manipulator
    viewer.addEventHandler(new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()));

    // add the thread model handler
    viewer.addEventHandler(new osgViewer::ThreadingHandler);

    // add the window size toggle handler
    viewer.addEventHandler(new osgViewer::WindowSizeHandler);

    // add the stats handler
    viewer.addEventHandler(new osgViewer::StatsHandler);

    // create the windows and run the threads.
    viewer.setCameraManipulator(new osgGA::TrackballManipulator());
    viewer.realize();

}

void DystViewer::run()
{
    // construct the viewer.
    osgViewer::Viewer viewer;

    // scenegraph root
    osg::ref_ptr<osg::Group> root = new osg::Group;

    initializeScene(root);

    viewer.setSceneData(root.get());

    initializeViewer(viewer);

    osg::Timer_t frame_tick = osg::Timer::instance()->tick();
    while (!viewer.done())
    {
        // Physics update would happen here
        osg::Timer_t now_tick = osg::Timer::instance()->tick();
        float dt = osg::Timer::instance()->delta_s(frame_tick, now_tick);
        frame_tick = now_tick;

        // render
        viewer.frame();
    }
}
