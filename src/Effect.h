//
//  Effect.h
//  Oculus_1_0
//
//  Created by Terence Broad on 25/03/2014.
//
//

#ifndef __Oculus_1_0__Effect__
#define __Oculus_1_0__Effect__

#include <iostream>
#include "ofMain.h"
#include "DataPacket.h"

class Effect
{
    protected :
    vector< ofFbo > framebuf;
    ofShader effectShader;
    
    public :
    
    Effect()
    {
        framebuf.resize(2);
        for(int i = 0; i < 2; i++)
        {
            framebuf.at(i).allocate(640,800);
        }
    }
    
    vector< ofFbo >& renderEffect(vector< ofTexture > &tex, DataPacket dataP)
    {
        for(int i = 0; i < 2; i++)
        {
            framebuf.at(i).begin();
            tex.at(i).bind();
            
            glBegin(GL_QUADS);
            glTexCoord2f(0,0); glVertex3f(0,0,0);
            glTexCoord2f(1,0); glVertex3f(640,0,0);
            glTexCoord2f(1,1); glVertex3f(640,800,0);
            glTexCoord2f(0,1); glVertex3f(0,800,0);
            glEnd();
            
            tex.at(i).unbind();
            framebuf.at(i).end();
        }
        
        return framebuf;
    }
    
    ~Effect(){ }
};
#endif /* defined(__Oculus_1_0__Effect__) */
