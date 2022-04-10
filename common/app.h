#ifndef __COMMON_H_FILE__
#define __COMMON_H_FILE__
#include <osgViewer/Viewer>
#include <osg/Camera>
#include <osg/Group>
#include <osg/ref_ptr>

namespace Common
{
    class App : public osg::Referenced
    {
    protected:
        ~App();
    public:
        App();

        virtual void init( int argc, char *argv[] );

        virtual void run();

    protected:
        osg::ref_ptr<osgViewer::Viewer> _viewer;

        osg::ref_ptr<osg::Group> _root;
    };
}


#endif // __COMMON_H_FILE__
