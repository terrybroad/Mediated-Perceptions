//
//  PosterizeRGB.h
//  Oculus_1_0
//
//  Created by Terence Broad on 25/03/2014.
//
//

#ifndef Oculus_1_0_PosterizeRGB_h
#define Oculus_1_0_PosterizeRGB_h

#include "Effect.h"

class PosterizeRGB : public Effect
{
    public :
    
    PosterizeRGB()
    {
        effectShader.load("shaders/RGBPost");
    }
    
    vector< ofFbo >& renderEffect(vector< ofTexture > &tex, OscilatePacket dataP)
    {
        for(int i = 0; i < 2; i++)
        {
            framebuf.at(i).begin();
            tex.at(i).bind();
            
            effectShader.begin();
            effectShader.setUniformTexture("tex", tex.at(i), 0);
            effectShader.setUniform1f("threshG", 2.5*dataP.values[0]);
            effectShader.setUniform1f("threshB", 60*dataP.values[1]);
            effectShader.setUniform1f("threshR", 80*dataP.values[2]);
            
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
    
    ~PosterizeRGB()
    {
        effectShader.unload();
    }
};

#endif
