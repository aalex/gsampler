#ifndef _SCENE_H_
#define _SCENE_H_

#include <osg/Node>

class Scene {
    public:
        Scene(osg::ref_ptr<osg::Group> root);
};

#endif // _SCENE_H_
