#ifndef SERIALCLASS_H_INCLUDED
#define SERIALCLASS_H_INCLUDED

#define ARDUINO_WAIT_TIME 2000

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

class ar_Serial
{
private:
    //Serial comm handler
    HANDLE ar_h_serial;
    //Connection status
    bool ar_connected;
    //Get various information about the connection
    COMSTAT ar_status;
    //Keep track of last error
    DWORD ar_errors;

public:
    //Initialize Serial communication with the given COM port
    ar_Serial(const char* ar_port_name);
    //Close the connection
    ~ar_Serial();
    //Read data in a buffer, if nbChar is greater than the
    //maximum number of bytes available, it will return only the
    //bytes available. The function return -1 when nothing could
    //be read, the number of bytes actually read.
    int ar_read_data(char* ar_buffer, unsigned int ar_nb_char);
    //Writes data from a buffer through the Serial connection
    //return true on success.
    bool ar_write_data(const char* ar_buffer, unsigned int ar_nb_char);
    //Check if we are actually connected
    bool ar_is_connected();


};

#endif // SERIALCLASS_H_INCLUDED