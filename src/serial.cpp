#include <windows.h>
#include "serial.h"

void serial_port::set_port(const char * port)
{
    this->port = port;
}

int serial_port::open_serial()
{
    hSerial = CreateFile(reinterpret_cast<LPCSTR>(port), GENERIC_READ | GENERIC_WRITE, 0,
                        0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (hSerial == INVALID_HANDLE_VALUE)
    {
        if(GetLastError()==ERROR_FILE_NOT_FOUND)
        {
            // Serial port doesn't exist
            return 1;
        }
    }

    return 0;
}

int serial_port::setup_serial()
{
    DCB dcbSerialParams = {0};

    dcbSerialParams.DCBlength=sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams)) {
        // Error getting state
        return 1;
    }

    dcbSerialParams.BaudRate = CBR_115200;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams))
    {
        // Error setting serial port state
        return 2;
    }

    COMMTIMEOUTS timeouts = {0};

    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(hSerial, &timeouts))
    {
        // Error occured
        return 3;
    }

    return 0;
}

int serial_port::read_bytes(char* buf, int num_bytes)
{
    DWORD dwBytesRead = 0;
    
    if (!ReadFile(hSerial, buf, num_bytes, &dwBytesRead, NULL))
    {
        // Couldn't read
        return 1;
    }

    return 0;
}