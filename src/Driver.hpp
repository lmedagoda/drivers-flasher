#ifndef FLASHER_DRIVER_HPP
#define FLASHER_DRIVER_HPP

#include <iodrivers_base/Driver.hpp>
namespace flasher
{

    /*
     * Input command to control the flasher lights
     */
    struct Command
    {
        bool light1;
	bool light2;
	bool light3;
    };

    /*
     * The status that is returned by the flasher electronics
     */
    struct Status
    {
        bool light1;
	bool light2;
	bool light3;
    };


    class Driver : public iodrivers_base::Driver
    {
        private:
            std::vector<uint8_t> buffer;
            int extractPacket(uint8_t const *buffer, size_t buffer_size) const;
            uint8_t calculateCRC(uint8_t crc, uint8_t data) const;
        public:
            Driver();
            /*
             * Thist method reads the curret status from the maxon_uc and returned it in the status object
             */
            bool read(Status &staus, base::Time timeout);
            
            /*
             * This mthod writes the data from the command to the maxon_uc
             * */
            void write(Command command, base::Time timeout);

    };
}
#endif
