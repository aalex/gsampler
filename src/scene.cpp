#include <osg/Node>
#include <osg/PositionAttitudeTransform>
#include <osgDB/ReadFile> 
#include <osgUtil/Optimizer>

#include "./scene.h"
#include "./spriteInputDeviceState.h"


using std::tr1::shared_ptr;

class UpdateSpritePositionCallback : public osg::NodeCallback {
    public:
        UpdateSpritePositionCallback(shared_ptr<SpriteInputDeviceState> deviceState) : 
            spriteRotation_(0.0), 
            spritePosition_(0.0, 0., 0.), 
            deviceState_(deviceState)
        {}
            
        virtual void operator()(osg::Node *node, osg::NodeVisitor *visitor)
        {
            osg::PositionAttitudeTransform *pat = 
                dynamic_cast<osg::PositionAttitudeTransform*>(node);
            if (pat)
            {
                if (deviceState_->moveForwardRequest_)
                {
                   spritePosition_.set(spritePosition_.x(), spritePosition_.y() + 0.01, spritePosition_.z());
                   pat->setPosition(spritePosition_);
                }
                if (deviceState_->moveBackwardRequest_)
                {
                   spritePosition_.set(spritePosition_.x(), spritePosition_.y() - 0.01, spritePosition_.z());
                   pat->setPosition(spritePosition_);
                }
                if (deviceState_->moveLeftRequest_)
                {
                   spritePosition_.set(spritePosition_.x() - 0.01, spritePosition_.y(), spritePosition_.z());
                   pat->setPosition(spritePosition_);
                }
                if (deviceState_->moveRightRequest_)
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
        shared_ptr<SpriteInputDeviceState> deviceState_;
};

Scene::Scene(osg::ref_ptr<osg::Group> root, 
        shared_ptr<SpriteInputDeviceState> deviceState)
{
    // load the scene graph here

    // die
    osg::ref_ptr<osg::Node> dieModel = osgDB::readNodeFile("die.osg");
    // Load the model as a child of a transform node so we can reposition the model. 
    osg::ref_ptr<osg::PositionAttitudeTransform> diePat = new osg::PositionAttitudeTransform;
    diePat->addChild(dieModel.get());
    diePat->setUpdateCallback(new UpdateSpritePositionCallback(deviceState));
    root->addChild(diePat.get());
    
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

