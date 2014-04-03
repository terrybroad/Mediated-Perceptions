//
//  Trigger.h
//  Oculus_1_0
//
//  Created by Terence Broad on 25/03/2014.
//
//

#ifndef Oculus_1_0_Trigger_h
#define Oculus_1_0_Trigger_h

#include "ofMain.h"
#include "DataPacket.h"

class Trigger
{
    protected :
    
    DataPacket dataP;

    public :
    
    Trigger(){ }
    
    DataPacket returnData()
    {
        return dataP;
    }

    ~Trigger(){ }
};

#endif
