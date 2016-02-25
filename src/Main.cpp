#include <iostream>
#include <flasher/Driver.hpp>

int main(int argc, char** argv)
{
    std::string device;
//     double setpoint;
    if (argc == 2){
        device = argv[1];
    } else {
        std::cout << "Usage: " << argv[0] << " <device>" << std::endl;
        return -1;
    }
    flasher::Driver driver;
    int fd;
    fd = driver.openSerialIO(device, 57600);
    driver.setFileDescriptor(fd);
    flasher::Status status;
    base::Time timeout = base::Time().fromSeconds(10);
    
    flasher::Command cmd;
    cmd.light1 = false;
    cmd.light2 = false;
    cmd.light3 = false;

    while(driver.read(status, timeout)){
        std::cout << "Light states: " << status.light1 << " "<< status.light2 << " "<< status.light3 << std::endl;
        
        driver.write(cmd, timeout);
    }
    
    return 0;
}