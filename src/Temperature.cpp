/*
 * File:   Temperature.cpp
 * Author: Karl Kangur, ESA/ESTEC
 * Date:   2017-03-16
 */
 
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "Temperature.hpp"

using namespace std;
using namespace temperature;

Temperature::Temperature(const unsigned int sensors):
    Driver(MAX_PACKET_SIZE),
    sensors(sensors)
{

}

Temperature::~Temperature()
{
    // Close the serial connection if it is still valid
    if(isValid())
    {
        close();
    }
}

int Temperature::getFileDescriptor()
{
    return Driver::getFileDescriptor();
}

bool Temperature::update(float * temp)
{
    uint8_t buffer[MAX_PACKET_SIZE];
    static uint8_t sequence = 0xff;
    
    try
    {
        // Read the packet in the local buffer. Timeout and first byte timeout is 1s
        readPacket(buffer, MAX_PACKET_SIZE, 1000, 1000);
        
        // Count sequence to check for missing packets, loops back to 0 at 127
        packet_index = buffer[TEMPERATURE_SEQUENCE];
        if(sequence != 0xff && ((packet_index != 0 && sequence + 1 != packet_index) || (packet_index == 0 && sequence != 127)))
        {
            cout << "TemperatureDriver: Value out of sequence" << endl;
            sequence = 0xff;
            return false;
        }
        // Update the sequence number
        sequence = packet_index;
        
        // Populate the data array, expect floats
        uint8_t temperatures[sensors * sizeof(float)];
        for(unsigned int i = 0; i < sensors * sizeof(float); i++)
        {
            temperatures[i] = buffer[TEMPERATURE_MESSAGE + i];
        }
        
        // Copy the data to the provided address
        memcpy(temp, &temperatures, sizeof(temperatures));
        
        return true;
    }
    catch(int timeout_error)
    {
        cout << "TemperatureDriver: Timeout error" << endl;
        return false;
    }
}

int Temperature::getIndex()
{
    return packet_index;
}

// Virtual method, must be redefined to process custom packet
int Temperature::extractPacket(uint8_t const* buffer, size_t buffer_size) const
{   
    // One packet must be at least (5+sensors*sizeof(float)) chars long, return if buffer is shorter
    if(buffer_size < TEMPERATURE_MESSAGE + sensors * sizeof(float))
    {
        return 0;
    }
    
    // Every packet of 36 bytes starts with 0xFE81FF55 for the Temperature device
    if(buffer[0] == 0xFE && buffer[1] == 0x81 && buffer[2] == 0xFF && buffer[3] == 0x55)
    {
        // Return the number of bytes for one packet
        return TEMPERATURE_MESSAGE + sensors * sizeof(float);
    }
    
    // Remove one byte at the beginning of the device buffer
    return -1;
}

