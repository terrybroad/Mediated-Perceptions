//
//  PerlinXYZ.h
//  Oculus_1_0
//
//  Created by Terence Broad on 25/03/2014.
//
//

#ifndef Oculus_1_0_PerlinXYZ_h
#define Oculus_1_0_PerlinXYZ_h

#include "Effect.h"

class PerlinXYZ : public Effect
{
    public :
    
    PerlinXYZ()
    {
        effectShader.load("shaders/perlinXYZ");
    }
    
    vector< ofFbo >& renderEffect(vector< ofTexture > &tex, OscilatePacket dataP)
    {
        for(int i = 0; i < 2; i++)
        {
            framebuf.at(i).begin();
            tex.at(i).bind();
            
            effectShader.begin();
            effectShader.setUniformTexture("tex", tex.at(i), 0);
            effectShader.setUniform1f("changingA", dataP.values[0]*0.2);
            effectShader.setUniform1f("changingL", dataP.values[1]*0.5);
            effectShader.setUniform1f("changingB", dataP.values[2]*5);
            effectShader.setUniform1f("time", ofGetElapsedTimeMillis());
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
    
    ~PerlinXYZ()
    {
        effectShader.unload();
    }
};

#endif
