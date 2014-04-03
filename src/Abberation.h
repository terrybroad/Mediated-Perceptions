//
//  Abberation.h
//  Oculus_1_0
//
//  Created by Terence Broad on 25/03/2014.
//
//

#ifndef Oculus_1_0_Abberation_h
#define Oculus_1_0_Abberation_h

#include "Effect.h"

class Abberation : public Effect
{
    public :
    
    Abberation()
    {
        effectShader.load("shaders/ChromaAb_GLSL");
    }
    
    vector< ofFbo >& renderEffect(vector< ofTexture > &tex, OscilatePacket dataP)
    {
        for(int i = 0; i < 2; i++)
        {
            framebuf.at(i).begin();
            tex.at(i).bind();
            
            effectShader.begin();
            effectShader.setUniformTexture("tex", tex.at(i), 0);
            effectShader.setUniform2f("windowSize", 640, 800);
            effectShader.setUniform1f("offsetALL", /*1*dataP.values[1]*/ 0);
            effectShader.setUniform2f("offsetVecR", 50*dataP.values[0]*sin(ofGetElapsedTimeMillis()), 50*dataP.values[0]*cos(ofGetElapsedTimeMillis()));
            effectShader.setUniform2f("offsetVecG", 500*dataP.values[1]*cos(ofGetElapsedTimeMillis()), 700*dataP.values[1]*sin(ofGetElapsedTimeMillis()));
            effectShader.setUniform2f("offsetVecB", 1000*dataP.values[2]*sin(ofGetElapsedTimeMillis()+(pi/2)), 1000*dataP.values[2]*cos(ofGetElapsedTimeMillis())+(pi/2));
            
            glBegin(GL_QUADS);
            glTexCoord2f(0,0); glVertex3f(0,0,0);
            glTexCoord2f(1,0); glVertex3f(640,0,0);
            glTexCoord2f(1,1); glVertex3f(640,800,0);
            glTexCoord2f(0,1); glVertex3f(0,800,0);
            glEnd();
            ofPopMatrix();
            
            effectShader.end();
            
            tex.at(i).unbind();
            framebuf.at(i).end();
        }
        
        return framebuf;
    }
    
    ~Abberation()
    {
        effectShader.unload();
    }
};

#endif
