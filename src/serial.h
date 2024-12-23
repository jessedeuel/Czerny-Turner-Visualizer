#ifndef SERIAL_H
#define SERIAL_H

class serial_port
{
public:
    serial_port(const char* prt) : port(prt) {}

    int open_serial();
    int setup_serial();
    int read_bytes(char* buf, int num_bytes);

    void set_port(const char * port);

private:
    const char* port;
    void* hSerial;
};

#endif