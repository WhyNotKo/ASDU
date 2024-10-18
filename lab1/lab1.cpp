// lab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "modbus.h"
int main()
{
    modbus_t* mb;
    uint16_t tab_reg[32];

    //uint8_t tab_reg[32];
    mb = modbus_new_tcp("127.0.0.1", 502);
    int r = modbus_connect(mb);
    modbus_set_slave(mb, 1);
    /* Read 5 registers fromythe address 0 */
    //int m = modbus read _bits(mb,0, 3, tab_reg);
    int m = modbus_read_registers(mb, 0, 3, tab_reg); 
    
    modbus_close(mb);
    modbus_free(mb);
    for (int i = 0; i < 3; i++)
    {

        std::cout << tab_reg[i]<<std::endl;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
