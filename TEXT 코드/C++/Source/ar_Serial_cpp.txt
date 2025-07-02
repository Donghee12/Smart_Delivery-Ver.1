#include "ar_SerialClass.h"

ar_Serial::ar_Serial(const char* ar_port_name)
{
    //We're not yet connected
    this->ar_connected = false;

    //Try to connect to the given port throuh CreateFile
    this->ar_h_serial = CreateFileA(ar_port_name,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    //Check if the connection was successfull
    if (this->ar_h_serial == INVALID_HANDLE_VALUE)
    {
        //If not success full display an Error
        if (GetLastError() == ERROR_FILE_NOT_FOUND) {

            //Print Error if neccessary
            printf("ERROR: Handle was not attached. Reason: %s not available.\n", ar_port_name);

        }
        else
        {
            printf("ERROR!!!");
        }
    }
    else
    {
        //If connected we try to set the comm parameters
        DCB ar_dcb_serial_params = { 0 };

        //Try to get the current
        if (!GetCommState(this->ar_h_serial, &ar_dcb_serial_params))
        {
            //If impossible, show an error
            printf("failed to get current serial parameters!");
        }
        else
        {
            //Define serial connection parameters for the arduino board
            ar_dcb_serial_params.BaudRate = CBR_9600;
            ar_dcb_serial_params.ByteSize = 8;
            ar_dcb_serial_params.StopBits = ONESTOPBIT;
            ar_dcb_serial_params.Parity = NOPARITY;
            //Setting the DTR to Control_Enable ensures that the Arduino is properly
            //reset upon establishing a connection
            ar_dcb_serial_params.fDtrControl = DTR_CONTROL_ENABLE;

            //Set the parameters and check for their proper application
            if (!SetCommState(ar_h_serial, &ar_dcb_serial_params))
            {
                printf("ALERT: Could not set Serial Port parameters");
            }
            else
            {
                //If everything went fine we're connected
                this->ar_connected = true;
                //Flush any remaining characters in the buffers 
                PurgeComm(this->ar_h_serial, PURGE_RXCLEAR | PURGE_TXCLEAR);
                //We wait 2s as the arduino board will be reseting
                Sleep(ARDUINO_WAIT_TIME);
            }
        }
    }

}

ar_Serial::~ar_Serial()
{
    //Check if we are connected before trying to disconnect
    if (this->ar_connected)
    {
        //We're no longer connected
        this->ar_connected = false;
        //Close the serial handler
        CloseHandle(this->ar_h_serial);
    }
}

int ar_Serial::ar_read_data(char* ar_buffer, unsigned int ar_nb_char)
{
    //Number of bytes we'll have read
    DWORD ar_bytes_read;
    //Number of bytes we'll really ask to read
    unsigned int ar_to_read;

    //Use the ClearCommError function to get status info on the Serial port
    ClearCommError(this->ar_h_serial, &this->ar_errors, &this->ar_status);

    //Check if there is something to read
    if (this->ar_status.cbInQue > 0)
    {
        //If there is we check if there is enough data to read the required number
        //of characters, if not we'll read only the available characters to prevent
        //locking of the application.
        if (this->ar_status.cbInQue > ar_nb_char)
        {
            ar_to_read = ar_nb_char;
        }
        else
        {
            ar_to_read = this->ar_status.cbInQue;
        }

        //Try to read the require number of chars, and return the number of read bytes on success
        if (ReadFile(this->ar_h_serial, ar_buffer, ar_to_read, &ar_bytes_read, NULL))
        {
            return ar_bytes_read;
        }
    }

    //If nothing has been read, or that an error was detected return 0
    return 0;

}


bool ar_Serial::ar_write_data(const char* ar_buffer, unsigned int ar_nb_char)
{
    DWORD ar_bytes_send;

    //Try to write the buffer on the Serial port
    if (!WriteFile(this->ar_h_serial, (void*)ar_buffer, ar_nb_char, &ar_bytes_send, 0))
    {
        //In case it don't work get comm error and return false
        ClearCommError(this->ar_h_serial, &this->ar_errors, &this->ar_status);

        return false;
    }
    else
        return true;
}

bool ar_Serial::ar_is_connected()
{
    //Simply return the connection status
    return this->ar_connected;
}