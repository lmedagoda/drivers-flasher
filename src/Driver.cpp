#include <flasher/Driver.hpp>
#include <iostream>
#include <cmath>
#include <sstream>


using namespace flasher;

Driver::Driver()
    : iodrivers_base::Driver(200)
{
    buffer.resize(200);
}


int Driver::extractPacket(uint8_t const *buffer, size_t buffer_size) const
{
     for (unsigned i = 0; i < buffer_size; i++)
     {
	std::cout << buffer[i] << std::flush;
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
     }
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
     std::string string;
    /*
     if(command.light1 == true) {
	string = "A0,1\r\n";
     } else {
	string = "A0,0\r\n";
     }

     std::cout << string << std::endl;	
    
     writePacket((uint8_t*)string.c_str(), string.size(), timeout);
     
     if(command.light2 == true) {
	string = "A1,1\r\n";
     } else {
	string = "A1,0\r\n";
     }

     std::cout << string << std::endl;	
    
     writePacket((uint8_t*)string.c_str(), string.size(), timeout);*/

     if(command.light3 == true) {
	string = "A2,1\r\n";
     } else {
	string = "A2,0\r\n";
     }

     std::cout << "Length: " << string.size() << std::endl;	
     std::cout << string << std::endl;	
    
     writePacket((uint8_t*)string.c_str(), 6, timeout);
     
     
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

void Driver::writeConfig(base::Time timeout)
{
  uint8_t config_packet[59];
  
     //light 1 mode
     config_packet[0] = 'M';
     config_packet[1] = '0';
     config_packet[2] = ',';
     config_packet[3] = '1';
     config_packet[4] = 0x0D;
     config_packet[5] = 0x0A;
     
     //light 2 mode
     config_packet[6] = 'M';
     config_packet[7] = '1';
     config_packet[8] = ',';
     config_packet[9] = '1';
     config_packet[10] = 0x0D;
     config_packet[11] = 0x0A;
     
     //light 3 mode
     config_packet[12] = 'M';
     config_packet[13] = '2';
     config_packet[14] = ',';
     config_packet[15] = '1';
     config_packet[16] = 0x0D;
     config_packet[17] = 0x0A;
     
     //light 1 voltage (x * 0.1 V)
     config_packet[18] = 'U';
     config_packet[19] = '0';
     config_packet[20] = ',';
     config_packet[21] = '3';
     config_packet[22] = '6';
     config_packet[23] = '0';
     config_packet[24] = 0x0D;
     config_packet[25] = 0x0A;
     
     //light 2 voltage
     config_packet[26] = 'U';
     config_packet[27] = '1';
     config_packet[28] = ',';
     config_packet[29] = '3';
     config_packet[30] = '6';
     config_packet[31] = '0';
     config_packet[32] = 0x0D;
     config_packet[33] = 0x0A;
     
     //light 3 voltage
     config_packet[34] = 'U';
     config_packet[35] = '2';
     config_packet[36] = ',';
     config_packet[37] = '2';
     config_packet[38] = '5';
     config_packet[39] = 0x0D;
     config_packet[40] = 0x0A;
     
     //light 1 current
     config_packet[41] = 'I';
     config_packet[42] = '0';
     config_packet[43] = ',';
     config_packet[44] = '1';
     config_packet[45] = 0x0D;
     config_packet[46] = 0x0A;
     
     //light 2 current
     config_packet[47] = 'I';
     config_packet[48] = '1';
     config_packet[49] = ',';
     config_packet[50] = '1';
     config_packet[51] = 0x0D;
     config_packet[52] = 0x0A;
     
     //light 3 current
     config_packet[53] = 'I';
     config_packet[54] = '2';
     config_packet[55] = ',';
     config_packet[56] = '1';
     config_packet[57] = 0x0D;
     config_packet[58] = 0x0A;
  
  writePacket(config_packet, 59, timeout);
  
}


