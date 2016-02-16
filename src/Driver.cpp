#include <flasher/Driver.hpp>
#include <iostream>
#include <cmath>

using namespace flasher;

Driver::Driver()
    : iodrivers_base::Driver(20)
{
    buffer.resize(20);
}


int Driver::extractPacket(uint8_t const *buffer, size_t buffer_size) const
{
//     for (unsigned i = 0; i < buffer_size; i++)
//     {
//         if (buffer[i] == START_SIGN)
//         {
//             if (i > 0)
//                 return -i;  //Startbyte is not in the first Byte
//             
//             if (buffer_size < 8)
//                 return 0; //It's not posible that a full package is in the buffer
// 
//             uint8_t temp_crc = 0;
// 
//             uint8_t j;
//             for (j = 0; j < 6; j++)
//             {
//                 temp_crc = this->calculateCRC(temp_crc, buffer[j+1]);
//             }
//             if (temp_crc == buffer[7])
//                 return (j+1); //Size of the Packet that was found
// 
//         }
// 
//     }
    return -buffer_size;
}

bool Driver::read(Status &status, base::Time timeout)
{
    int packet_size = readPacket(&buffer[0], buffer.size(), timeout);
    //std::cout << packet_size << std::endl;
    
    if (packet_size)
    {
        /*std::cout << "[0]" << (int)buffer[0] << std::endl;
        std::cout << "[1]" << (int)buffer[1] << std::endl;
        std::cout << "[2]" << (int)buffer[2] << std::endl;
        std::cout << "[3]" << (int)buffer[3] << std::endl;
        std::cout << "[4]" << (int)buffer[4] << std::endl;
        std::cout << "[5]" << (int)buffer[5] << std::endl;
        std::cout << "[6]" << (int)buffer[6] << std::endl;
        */
        //std::cout << "Maxon als Int: " << (((unsigned)(buffer[2] & 0x3f) << 4) | (buffer[3] >> 4)) << std::endl; 

//         status.clearence = (bool)(buffer[2]>>7);
//         status.direction = (DIRECTION)((buffer[2]>>6) & 0x01);
//         status.setpoint = ((float)(((unsigned)(buffer[2] & 0x3f) << 4) | (buffer[3] >> 4))/255);
//         status.current = std::abs((((float)(((unsigned)(buffer[3] & 0x0f) << 6) | (buffer[4] >> 2)))-103)/26.0);
//         status.speed = -1*(((float)(((unsigned)(buffer[4] & 0x03) << 8) | (buffer[5])))-103)/(7.6);
//         status.humidity = (float)((unsigned)(buffer[6]));
        
        return true;
    } 
    return false;
}

void Driver::write(Command command, base::Time timeout)
{
     uint8_t command_packet[18];
     
     //light 1
     command_packet[0] = 'A';
     command_packet[1] = '1';
     command_packet[2] = ',';
     if(command.light1 == true) {
	command_packet[3] = '1';
     } else {
	command_packet[3] = '0';
     }
     command_packet[4] = 0x0D;
     command_packet[5] = 0x0A;
     
     //light 2
     command_packet[6] = 'A';
     command_packet[7] = '2';
     command_packet[8] = ',';
     if(command.light2 == true) {
	command_packet[9] = '1';
     } else {
	command_packet[9] = '0';
     }
     command_packet[10] = 0x0D;
     command_packet[11] = 0x0A;
     
     //light 3
     command_packet[12] = 'A';
     command_packet[13] = '3';
     command_packet[14] = ',';
     if(command.light3 == true) {
	command_packet[15] = '1';
     } else {
	command_packet[15] = '0';
     }
     command_packet[16] = 0x0D;
     command_packet[17] = 0x0A;
     
     
     writePacket(command_packet, 18, timeout);
     
     
//     command_packet[0] = START_SIGN;
//     command_packet[1] = (command.type << 7) | (command.direction << 6);
//     command_packet[2] = (uint8_t)(command.setpoint*255);
// 
//     command_packet[COMMAND_BYTES+1] = 0; //INIT CRC
//     for (uint8_t i = 0; i < COMMAND_BYTES; i++)
//     {
//         command_packet[COMMAND_BYTES+1] = this->calculateCRC(command_packet[COMMAND_BYTES+1], command_packet[i+1]);
//     }

   /* //print the command package 
    std::cout << "CMD[0]: " << (int)command_packet[0] << std::endl;
    std::cout << "CMD[1]: " << (int)command_packet[1] << std::endl;
    std::cout << "CMD[2]: " << (int)command_packet[2] << std::endl;
    std::cout << "CMD[3]: " << (int)command_packet[3] << std::endl;
    */
    
//     writePacket(command_packet, COMMAND_BYTES+2, timeout);

}

uint8_t Driver::calculateCRC(uint8_t crc, uint8_t data) const
{
    uint8_t i;

    crc = crc ^ data;

    for (i = 0; i < 8; i++)
    {
        if (crc & 0x01)
        {
            crc = (crc >> 1) ^ 0x8C;
        }
        else
        {
            crc >>= 1;
        }
    }

    return crc;
}

