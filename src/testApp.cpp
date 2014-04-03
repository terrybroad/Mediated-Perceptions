#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    ofSetFrameRate(60);
    
    camWidth = 800;
    camHeight = 640;
    switchInt = 0;
    
    tex.resize(2);
    fbo.resize(2);
    
    vidGrabber[0].setDeviceID(0);
    vidGrabber[1].setDeviceID(1);
    for(int i = 0; i < 2; i++)
    {
        vidGrabber[i].setDesiredFrameRate(60);
        vidGrabber[i].initGrabber(camWidth, camHeight);
        
        tex.at(i).setTextureWrap(GL_REPEAT, GL_REPEAT);
        tex.at(i).allocate(camHeight,camWidth,GL_RGB,GL_RGBA);
        tbIm[i].allocate(camHeight,camWidth,OF_IMAGE_COLOR_ALPHA);
        fbo.at(i).allocate(640,800);
    }

    
    //There are the parameters for the polynomial warp function to correct for the Oculus Rift and Webcam Lenses
    K0 = 1.0;
    K1 = 5.74;
    K2 = 0.27;
    K3 = 0.0;
    _x = 0.0f;
    _y = 0.0f;
    _w = 1.0f;
    _h = 1.0f;
    as = 640.0f/800.0f;
	DistortionXCenterOffset = 90;
    
    ofEnableNormalizedTexCoords();
    
    hmdWarpShader.load("Shaders/HmdWarpExp");
}

//--------------------------------------------------------------
void testApp::update(){
    
    trigger.update();
    
    for(int i = 0; i < 2; i++)
    {
        vidGrabber[i].update();
        
        if (vidGrabber[i].isFrameNew())
        {
            for(int j = 0; j < camHeight; j++)
            {
                for(int k = 0; k < camWidth; k++)
                {
                    tbIm[i].setColor(j,k,vidGrabber[i].getPixelsRef().getColor(k, j));
                }
            }
        }
        tbIm[i].reloadTexture();
        tex.at(i) = tbIm[i].getTextureReference();
        
    }
}

//--------------------------------------------------------------
void testApp::draw()
{
    switch(switchInt)
    {
        case 0:
        fbo = effect.renderEffect(tex,trigger.returnData());
        break;
        
        case 1:
            fbo = posterize.renderEffect(tex,trigger.returnData());
        break;
        
        case 2:
            fbo = posterizergb.renderEffect(tex,trigger.returnData());
        break;
        
        case 3:
            fbo = abberation.renderEffect(tex,trigger.returnData());
        break;
        
        case 4:
            fbo = perlinxyz.renderEffect(tex,trigger.returnData());
        break;
        
        case 5:
        fbo = perlinrgb.renderEffect(tex,trigger.returnData());
        break;
        
        default:
            fbo = effect.renderEffect(tex,trigger.returnData());
        break;
    }

    fbo.at(0).getTextureReference().bind();

    hmdWarpShader.begin();
    hmdWarpShader.setUniformTexture("tex", fbo.at(0).getTextureReference(), 0);
    hmdWarpShader.setUniform2f("LensCenter", DistortionXCenterOffset, 0 );
    hmdWarpShader.setUniform2f("ScreenCenter", _x + _w*1.0f, _y + _h*1.0f );
    hmdWarpShader.setUniform2f("Scale", (_w/1.0f) * 1.0f, (_h/1.0f) * 1.0f * as );
    hmdWarpShader.setUniform2f("ScaleIn", (1.0f/_w), (1.0f/_h) / as );
    hmdWarpShader.setUniform4f("HmdWarpParam", K0, K1, K2, K3 );

    glBegin(GL_QUADS);
    glTexCoord2f(1,0); glVertex3f(0,0,0);
    glTexCoord2f(0,0); glVertex3f(640,0,0);
    glTexCoord2f(0,1); glVertex3f(640,800,0);
    glTexCoord2f(1,1); glVertex3f(0,800,0);
    glEnd();
    
    hmdWarpShader.end();
    
    fbo.at(0).getTextureReference().unbind();

    // -----------

    fbo.at(1).getTextureReference().bind();

    hmdWarpShader.begin();
    hmdWarpShader.setUniformTexture("tex", fbo.at(1).getTextureReference(), 0);
    hmdWarpShader.setUniform2f("LensCenter", DistortionXCenterOffset , 1);
    hmdWarpShader.setUniform2f("ScreenCenter", _x + _w*1.0f, _y + _h*1.0f );
    hmdWarpShader.setUniform2f("Scale", (_w/1.0f) * 1.0f, (_h/1.0f) * 1.0f * as );
    hmdWarpShader.setUniform2f("ScaleIn", (1.0f/_w), (1.0f/_h) / as );
    hmdWarpShader.setUniform4f("HmdWarpParam", K0, K1, K2, K3 );
     
    ofPushMatrix();
    ofTranslate(640,0);
    glBegin(GL_QUADS);
    glTexCoord2f(1,0); glVertex3f(0,0,0);
    glTexCoord2f(0,0); glVertex3f(640,0,0);
    glTexCoord2f(0,1); glVertex3f(640,800,0);
    glTexCoord2f(1,1); glVertex3f(0,800,0);
    glEnd();
    ofPopMatrix();
    hmdWarpShader.end();
    fbo.at(1).getTextureReference().unbind();

}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{
    if(key == '0')
    {
        switchInt = 0;
    }
    if(key == '1')
    {
        switchInt = 1;
    }
    if(key == '2')
    {
        switchInt = 2;
    }
    if(key == '3')
    {
        switchInt = 3;
    }
    if(key == '4')
    {
        switchInt = 4;
    }
    if(key == '5')
    {
        switchInt = 5;
    }
    if(key == '6')
    {
        switchInt = 6;
    }
    if(key == '7')
    {
        switchInt = 7;
    }
    if(key == '8')
    {
        switchInt = 8;
    }
    if(key == 'f')
    {
        ofToggleFullscreen();
    }
    if(key == 'p')
    {
        trigger.toggleSound();
    }
}
