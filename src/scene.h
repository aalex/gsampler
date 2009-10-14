#ifndef _SCENE_H_
#define _SCENE_H_

#include <osg/Node>
#include <tr1/memory>

class SpriteState;

class Scene {
    public:
        Scene(osg::ref_ptr<osg::Group> root, 
                std::tr1::shared_ptr<SpriteState> deviceState);
};

#endif // _SCENE_H_
