//
//  DataPacket.h
//  Oculus_1_0
//
//  Created by Terence Broad on 25/03/2014.
//
//

#ifndef Oculus_1_0_DataPacket_h
#define Oculus_1_0_DataPacket_h

//
//  dataPacket.h
//  Mediated_Perception
//
//  Created by Terence Broad on 19/03/2014.
//
//

#ifndef Mediated_Perception_dataPacket_h
#define Mediated_Perception_dataPacket_h

struct DataPacket
{
    const static int valuesLength = 10;
    const static int truthsLength = 3;
    
    int valuesUsed, truthsUsed;
    
    float values[valuesLength];
    bool truths[truthsLength];
    
    DataPacket()
    {
        for(int i = 0; i < valuesLength; i++)
        {
            values[i] = 0;
            
            if(i < truthsLength)
            {
                truths[i] = false;
            }
        }
    }
};

#endif


#ifndef Mediated_Perception_cartesianPacket_h
#define Mediated_Perception_cartesianPacket_h

struct CartesianPacket : DataPacket
{

};

#endif


#ifndef Mediated_Perception_nullPacket_h
#define Mediated_Perception_nullPacket_h

struct NullPacket : DataPacket
{
    
};


#endif

#ifndef Mediated_Perception_oscilatePacket_h
#define Mediated_Perception_oscilatePacket_h

struct OscilatePacket : DataPacket
{
    OscilatePacket()
    {
        valuesUsed = 3;
        truthsUsed = 0;
    }
};


#endif

#ifndef Mediated_Perception_valuePacket_h
#define Mediated_Perception_valuePacket_h

struct ValuePacket : DataPacket
{
    
};


#endif


#endif
