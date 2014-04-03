#pragma once

#include "ofMain.h"
#include "Posterize.h"
#include "PosterizeRGB.h"
#include "DataPacket.h"
#include "Trigger.h"
#include "SoundAmp.h"
#include "Abberation.h"
#include "PerlinXYZ.h"
#include "PerlinRGB.h"

class testApp : public ofBaseApp
{
public:
    
    void setup();
    void update();
    void draw();
    void keyReleased(int key);
    int camWidth,camHeight,switchInt;
    
    float K0,K1,K2,K3,_x,_y,_w,_h,as,DistortionXCenterOffset;
    
    //images and textures
    ofVideoGrabber vidGrabber[2];
    ofImage tbIm[2];
    vector< ofTexture > tex;
    vector< ofFbo > fbo;
    
    //effects
    Effect effect;
    Posterize posterize;
    PosterizeRGB posterizergb;
    Abberation abberation;
    PerlinXYZ perlinxyz;
    PerlinRGB perlinrgb;
    
    //triggers
    SoundAmp trigger;
    
    ofShader hmdWarpShader, wobbleShader, testShader, empty,chromaShader,RGBPoster,chromaWobble, liquify, liquifyS, brightness,perlinLAB, perlinXYZ, perlinHSV, LABFluctuate;

    
};
