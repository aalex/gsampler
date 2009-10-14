#include <osg/Node>
#include <osg/PositionAttitudeTransform>
#include <osgDB/ReadFile> 
#include <osgUtil/Optimizer>

#include "./scene.h"
#include "./spriteState.h"


using std::tr1::shared_ptr;

class UpdatePositionCallback : public osg::NodeCallback {
    public:
        UpdatePositionCallback(shared_ptr<SpriteState> spriteState, 
                const osg::Vec3d &position) : 
            spriteRotation_(0.0), 
            spritePosition_(position), 
            spriteState_(spriteState)
        {}
            
        virtual void operator()(osg::Node *node, osg::NodeVisitor *visitor)
        {
            osg::PositionAttitudeTransform *pat = 
                dynamic_cast<osg::PositionAttitudeTransform*>(node);
            if (pat)
            {
                if (spriteState_->moveForwardRequest_)
                {
                   spritePosition_.set(spritePosition_.x(), spritePosition_.y() + 0.01, spritePosition_.z());
                   pat->setPosition(spritePosition_);
                }
                if (spriteState_->moveBackwardRequest_)
                {
                   spritePosition_.set(spritePosition_.x(), spritePosition_.y() - 0.01, spritePosition_.z());
                   pat->setPosition(spritePosition_);
                }
                if (spriteState_->moveLeftRequest_)
                {
                   spritePosition_.set(spritePosition_.x() - 0.01, spritePosition_.y(), spritePosition_.z());
                   pat->setPosition(spritePosition_);
                }
                if (spriteState_->moveRightRequest_)
                {
                   spritePosition_.set(spritePosition_.x() + 0.01, spritePosition_.y(), spritePosition_.z());
                   pat->setPosition(spritePosition_);
                }
            }
            traverse(node, visitor);
        }
    private:
        double spriteRotation_;
        osg::Vec3d spritePosition_;
        shared_ptr<SpriteState> spriteState_;
};

Scene::Scene(osg::ref_ptr<osg::Group> root, 
        shared_ptr<SpriteState> spriteState)
{
    // load the scene graph here

    // die
    osg::ref_ptr<osg::Node> dieModel = osgDB::readNodeFile("die.osg");
    // Load the model as a child of a transform node so we can reposition the model. 
    osg::ref_ptr<osg::PositionAttitudeTransform> diePat = new osg::PositionAttitudeTransform;
    diePat->addChild(dieModel.get());
    diePat->setUpdateCallback(new UpdatePositionCallback(spriteState, 
                osg::Vec3d(0.0, 5.0, 0.0)));
    diePat->setPosition(osg::Vec3d(0.0, 5.0, 0.0));
    root->addChild(diePat.get());


    // opponent die
    osg::ref_ptr<osg::Node> opponentModel = osgDB::readNodeFile("die.osg"); // FIXME: do we have to read this twice?
    // Load the model as a child of a transform node so we can reposition the model. 
    osg::ref_ptr<osg::PositionAttitudeTransform> opponentPat = new osg::PositionAttitudeTransform;
    opponentPat->addChild(opponentModel.get());
    opponentPat->setUpdateCallback(new UpdatePositionCallback(spriteState, 
                osg::Vec3d(0.0, 0.0, 0.0)));    // FIXME: should be remote state
    root->addChild(opponentPat.get());
    
    // ground
    osg::ref_ptr<osg::Node> groundModel = osgDB::readNodeFile("ground-plane.osg");
    osg::ref_ptr<osg::PositionAttitudeTransform> groundPat = new osg::PositionAttitudeTransform;
    groundPat->addChild(groundModel.get());
    groundPat->setScale(osg::Vec3(50.0, 50.0, 0.1));
    root->addChild(groundPat.get());

    // optimize the scene graph, remove redundant nodes and state etc.
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());

    // switch off lighting as we haven't assigned any normals.
    //root->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
}

