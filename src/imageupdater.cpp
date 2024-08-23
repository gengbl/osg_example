#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <osg/Texture2D>
#include <osg/Image>
#include <osg/Geode>
#include <osg/Geometry>
#include <osgDB/ReadFile>
#include "app.h"

class UpdateImageApp : public Common::App
{
protected:
    ~UpdateImageApp(){
        
    }

    virtual void preFrame()
    {
		updateImage();
		_viewer->frame();
    }

public:
	UpdateImageApp()
	{
        _frameCount = 0;
        _width = 400;
        _height = 400;
	}
	virtual void init(int argc, char* argv[])
	{
        osg::Geode* lpGeode = new osg::Geode;
        osg::Geometry* lpGeometry = osg::createTexturedQuadGeometry(osg::Vec3(), osg::Vec3(10, 0.0, 0.0), osg::Vec3(0.0, 10.0, 0.0));
        lpGeode->addDrawable(lpGeometry);

        _texture = new osg::Texture2D;
        _image = new osg::Image;
        _image->allocateImage( _width, _height, 1, GL_RGBA, GL_UNSIGNED_BYTE, 1);
        _texture->setImage(_image);
        //_texture->setUnRefImageDataAfterApply(false);
        lpGeometry->getOrCreateStateSet()->setTextureAttributeAndModes(0, _texture);
        //lpGeometry->setUseDisplayList(false);
        updateImage();
        _root->addChild(lpGeode);
	}

protected:
    void updateImage()
    {
        std::vector<unsigned char> colorBuf;
        colorBuf.resize( _width * _height * 4 );

		for (int r = 0; r < _height; r++)
		{
			for (int c = 0; c < _width; c++)
			{
                colorBuf[(r * _width + c ) * 4 + 0 ] = ( r + _frameCount ) % 255;
                colorBuf[(r * _width + c ) * 4 + 1 ] = ( c + _frameCount ) % 255;
                colorBuf[(r * _width + c ) * 4 + 2 ] = (r + c + _frameCount) % 255;
                colorBuf[(r * _width + c ) * 4 + 3 ] = 255;
            }
        }


        memcpy(_image->data(), &colorBuf[0], _width * _height * 4);
        _image->dirty();

        //_texture->setImage(_image);
        //_texture->dirtyTextureParameters();


        _frameCount++;
    }


protected:
    osg::ref_ptr<osg::Texture2D> _texture;
    osg::ref_ptr<osg::Image> _image;

    int _width;
    int _height;
    int _frameCount;

};


int main( int argc, char *argv[] )
{
    Common::App *lpApp = new UpdateImageApp;

    lpApp->init( argc, argv );
    lpApp->run();

    return 0;
}
