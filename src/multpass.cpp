#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <osgDB/ReadFile>
#include <osgFX/Technique>
#include <osgFX/Effect>
#include <osg/Material>
#include <osg/Depth>
#include <osg/BlendFunc>
#include "app.h"

class TransparencyTechnique : public osgFX::Technique
{
public:
    TransparencyTechnique() : osgFX::Technique() {}
    virtual bool validate( osg::State& ss ) const
        {
            return true;
        }
protected:
    virtual void define_passes()
        {
            osg::ref_ptr<osg::StateSet> ss = new osg::StateSet;
            ss->setAttributeAndModes( new osg::ColorMask(
                                          false, false, false, false) );
            ss->setAttributeAndModes( new osg::Depth(osg::Depth::LESS) );
            addPass( ss.get() );
            ss = new osg::StateSet;
            ss->setAttributeAndModes( new osg::ColorMask(
                                          true, true, true, true) );
            ss->setAttributeAndModes( new osg::Depth(osg::Depth::EQUAL) );
            addPass( ss.get() );
        }
};


class TransparentcyEffect : public osgFX::Effect
{
public:
    TransparentcyEffect() : osgFX::Effect() {}
    TransparentcyEffect( const TransparentcyEffect& copy,
                      const osg::CopyOp op=osg::CopyOp::SHALLOW_COPY )
        : osgFX::Effect(copy, op) {}
    META_Effect( osgFX, TransparentcyEffect, "TransparentcyEffect",
                 "", "" );
protected:
    virtual bool define_techniques()
        {
            addTechnique(new TransparencyTechnique);
            return true;
        }
};


class MultpassApp : public Common::App
{
protected:
    ~MultpassApp(){

    }
public:
    virtual void init( int argc, char *argv[] )
        {
            osg::Group *lpGroup = new osg::Group;
            if ( argc >= 2 )
            {
                for ( int i = 1; i < argc; i ++ )
                {
                    if ( i == 1 )
                    {
                        lpGroup->addChild( osgDB::readNodeFile(argv[i]) );
                    }else
                    {
                        _root->addChild(osgDB::readNodeFile(argv[i]));
                    }
                }
            }else
            {
                lpGroup->addChild( osgDB::readNodeFile("cow.osg") );
            }

            TransparentcyEffect *lpEffect = new TransparentcyEffect;
            //osg::Group *lpEffect = new osg::Group;
            lpEffect->addChild( lpGroup );
            _root->addChild( lpEffect );
            osg::ref_ptr<osg::Material> material = new osg::Material;
            material->setAmbient( osg::Material::FRONT_AND_BACK, osg::Vec4(0.0f, 0.0f, 0.0f, 0.3f) );
            material->setDiffuse( osg::Material::FRONT_AND_BACK, osg::Vec4(1.0f, 1.0f, 1.0f, 0.3f) );
            lpGroup->getOrCreateStateSet()->setAttributeAndModes(material.get(), osg::StateAttribute::ON|osg::StateAttribute::OVERRIDE );
            lpGroup->getOrCreateStateSet()->setAttributeAndModes(new osg::BlendFunc );
            lpGroup->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN );
        }

};


int main( int argc, char *argv[] )
{
    Common::App *lpApp = new MultpassApp;

    lpApp->init( argc, argv );
    lpApp->run();

    return 0;
}
