#include "raylib.h"
#include <iostream>
#include "serial.h"

int main() 
{
    serial_port serial("COM4");

    if (serial.open_serial() == 0)
        std::cout << "Found COM4." << std::endl;
    else
        std::cout << "Didn't find COM4." << std::endl;

    int ret = serial.setup_serial();

    if (ret == 0)
        std::cout << "Setup COM4." << std::endl;
    else if (ret == 1)
        std::cout << "Error getting state." << std::endl;
    else if (ret == 2)
        std::cout << "Error setting state." << std::endl;

    return 0;
}
