#include <stdio.h>
#include <tchar.h>
#include "ar_SerialClass.h"	// Library described above
#include <string>
#include <iostream>

using namespace std;

string ar_g_converyor_stop = {};
extern ar_Serial* ar_sp;

// application reads from the specified serial port and reports the collected data
void ar_serial_Communication(char* ar_input_data, int direction) // direction: 1 = ar -> PC  2 = PC -> ar
{
	//printf("Welcome to the serial test app!\n\n");


	if (ar_sp->ar_is_connected())
		printf("ARDUINO connected\n");

	char ar_incoming_data[256] = "";// don't forget to pre-allocate memory
	int ar_data_length = 255;
	int ar_read_result = 0;

	while (ar_sp->ar_is_connected()) 
	{
		Sleep(500);
		//아래 코드는 테스트용 코드
		// 실시간 데이터 입력을 시리얼 모니터에서 보는 코드

		if (direction == 1)
		{
			// 아두이노 -> C++
			ar_read_result = ar_sp->ar_read_data(ar_incoming_data, ar_data_length);
			ar_incoming_data[ar_read_result] = 0;
		
			cout << ar_incoming_data;
			if ( strcmp(ar_incoming_data, "Conveyor stop\0") == 0)
			{
				
				ar_g_converyor_stop = ar_incoming_data;
				break;
			}		
		
		}
		else if (direction == 2)
		{
			//C++ -> 아두이노
			
			bool check = ar_sp->ar_write_data(ar_input_data, ar_data_length);
			cout << "\nEND OF WRITE ------------" << endl;
			Sleep(500);
			break;
		}

		else
		{
			cout << "ERROR IN SERIAL COMM" << endl;
		}
	
	}

}