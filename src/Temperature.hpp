/*
 * File:   Temperature.hpp
 * Author: Karl Kangur, ESA/ESTEC
 * Date:   2017-03-16
 */

#ifndef _TEMPERATURE_HPP_
#define _TEMPERATURE_HPP_

#include <iodrivers_base/Driver.hpp>

// Start bytes of message parts
#define TEMPERATURE_HEADER 0
#define TEMPERATURE_SEQUENCE 4
#define TEMPERATURE_MESSAGE 5

namespace temperature
{
    class Temperature: public iodrivers_base::Driver
    {
    public:
        const unsigned int sensors;
        
        Temperature(const unsigned int sensors);
        ~Temperature();
        bool update(float * temperatures);
        int getFileDescriptor();
        int getIndex();
    private:
        static const unsigned int MAX_PACKET_SIZE = 512;
        virtual int extractPacket(uint8_t const* buffer, size_t buffer_size) const;
        int packet_index;
    };
}

#endif

