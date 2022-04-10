#include "app.h"
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
namespace Common
{
    App::App()
    {
        _viewer = new osgViewer::Viewer;
        _root = new osg::Group;

        _viewer->setCameraManipulator( new osgGA::TrackballManipulator );

        _viewer->setSceneData( _root );
    }
    App::~App()
    {

    }

    void App::init( int argc, char *argv[] )
    {
        osg::Node *lpNode = osgDB::readNodeFile("cow.osg");
        _root->addChild( lpNode );
        //_viewer->setSceneData( lpNode );
    }

    void App::run()
    {
        _viewer->run();
    }
}
