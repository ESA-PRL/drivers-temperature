/*
 * File:   main.cpp
 * Author: Karl Kangur, ESA/ESTEC
 * Date:   2017-03-14
 */

#include <iostream>
#include "Temperature.hpp"

int main(int argc, char** argv)
{   
	if(argc < 2)
	{
		fprintf(stderr,"Use \n./temperature_test <device>\n");
		return -1;
	}

    const unsigned int sensor_number = 4;
    temperature::Temperature device(sensor_number);
    
    if(!device.openSerial(argv[1], 9600))
    {
        std::cout << "Could not open device on port " << argv[1] << std::endl;    
    }
    
    // Read all the temperature sensors
    float temperatures[device.sensors];
    while(true)
    {
		if(device.update(temperatures))
		{
			for(int i = 0; i < device.sensors; i++)
			{
                printf("%f\t", temperatures[i]);
            }
            printf("\n");
		}
	}

    return 0;
}
