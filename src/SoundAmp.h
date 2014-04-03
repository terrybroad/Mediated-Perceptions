//
//  SoundAmp.h
//  Oculus_1_0
//
//  Created by Terence Broad on 25/03/2014.
//
//

#ifndef Oculus_1_0_SoundAmp_h
#define Oculus_1_0_SoundAmp_h
#include "Trigger.h"

class SoundAmp : public Trigger
{
    OscilatePacket dataP;
    
    ofSoundPlayer song;
    int nBandsToGet;
    float * fftSmoothed;
    float avgSound[3];
    float centroid;
    
    
    public :
    
    SoundAmp()
    {
        song.loadSound("sounds/Pacific202.mp3");
        
        fftSmoothed = new float[8192];
        for (int i = 0; i < 8192; i++)
        {
            fftSmoothed[i] = 0;
        }
        
        nBandsToGet = 128;
    }
    
    void update()
    {
        ofSoundUpdate();
    }
    
    OscilatePacket returnData()
    {
        float * val = ofSoundGetSpectrum(nBandsToGet);
        for (int i = 0;i < nBandsToGet; i++){
            
            fftSmoothed[i] *= 0.96f;
            
            if (fftSmoothed[i] < val[i])
            {
                fftSmoothed[i] = val[i];
            }
            
        }
        
        for(int i = 0; i<3; i++)
        {
            avgSound[i] = 0;
        }
        

        for (int i = 0;i < nBandsToGet; i++)
        {
            fftSmoothed[i] *= 0.96f;
            
            if (fftSmoothed[i] < val[i])
            {
                fftSmoothed[i] = val[i];
            }
            
            //Divide amplitude into values for low medium and high
            if(i < (nBandsToGet/3))
            {
                avgSound[0] += fftSmoothed[i];
            }
            else if(i < (nBandsToGet/3)*2 && i > (nBandsToGet/2))
            {
                avgSound[1] += fftSmoothed[i];
            }
            else if(i > (nBandsToGet/3)*2)
            {
                avgSound[2] += fftSmoothed[i];
            }
        }
        
        for(int i = 0; i < 3; i++)
        {
            avgSound[i] /= (nBandsToGet/3);
            dataP.values[i] = avgSound[i];
        }
    
        return dataP;
    }
    void toggleSound()
    {
        if(song.getIsPlaying())
        {
            song.stop();
        }
        else
        {
            song.play();
        }
    }
    
    ~SoundAmp()
    {
        song.unloadSound();
    }
    
};

#endif
