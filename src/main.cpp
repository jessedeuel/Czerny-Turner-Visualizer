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
        std::cout << "Successfully setup COM4." << std::endl;
    else if (ret == 1)
        std::cout << "Error getting state." << std::endl;
    else if (ret == 2)
        std::cout << "Error setting state." << std::endl;
    else if (ret == 3)
        std::cout << "Error setting timeouts." << std::endl;

    const int bytes_to_read = 12;
    char buff[bytes_to_read + 1] = {0};
    ret = serial.read_bytes(buff, bytes_to_read);

    if (ret == 0)
    {
        std::cout << "Read " << bytes_to_read << " bytes: ";

        for (char i : buff)
        {
            std::cout << i;
        }
        std::cout << std::endl;
    }
    else
        std::cout << "Error reading data." << std::endl;

    return 0;
}
