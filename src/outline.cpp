#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <osgDB/ReadFile>
#include <osgFX/Outline>
#include "app.h"

class OutlineApp : public Common::App
{
protected:
    ~OutlineApp(){
        
    }
public:
    virtual void init( int argc, char *argv[] )
        {
            osgFX::Outline *lpOutline = new osgFX::Outline;
            lpOutline->setWidth( 2.0f );
            lpOutline->setColor( osg::Vec4( 1.0, 1.0, 0.0, 1.0 ) );

            if ( argc >= 2 )
            {
                for ( int i = 1; i < argc; i ++ )
                {
                    lpOutline->addChild( osgDB::readNodeFile(argv[i]) );
                }
            }else
            {
                lpOutline->addChild( osgDB::readNodeFile("cow.osg") );
            }

            _root->addChild( lpOutline );
            //_viewer->setSceneData( lpOutline );
        }

};


int main( int argc, char *argv[] )
{
    Common::App *lpApp = new OutlineApp;

    lpApp->init( argc, argv );
    lpApp->run();

    return 0;
}
