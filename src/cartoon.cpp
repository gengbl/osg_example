#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <osgDB/ReadFile>
#include <osgFX/Cartoon>
#include "app.h"

class CartoonApp : public Common::App
{
protected:
    ~CartoonApp(){
        
    }
public:
    virtual void init( int argc, char *argv[] )
        {
            osgFX::Cartoon *lpCartoon = new osgFX::Cartoon;
            if ( argc >= 2 )
            {
                for ( int i = 1; i < argc; i ++ )
                {
                    lpCartoon->addChild( osgDB::readNodeFile(argv[i]) );
                }
            }else
            {
                lpCartoon->addChild( osgDB::readNodeFile("cow.osg") );
            }

            _root->addChild( lpCartoon );
            //_viewer->setSceneData( lpCartoon );
        }

};


int main( int argc, char *argv[] )
{
    Common::App *lpApp = new CartoonApp;

    lpApp->init( argc, argv );
    lpApp->run();

    return 0;
}
