#ifndef _DYSTVIEWER_H_
#define _DYSTVIEWER_H_

#include <osg/Group>
#include <tr1/memory>
#include "./spriteState.h"
#include "./scene.h"

class SceneViewer {
    friend class StateClient;
    public:
        SceneViewer();
        void run();
    private:
        osg::ref_ptr<osg::Group> root_;
        std::tr1::shared_ptr<SpriteState> spriteState_;
        std::tr1::shared_ptr<RemoteSpriteState> remoteState_;
        Scene scene_;
};

#endif // _DYSTVIEWER_H_
