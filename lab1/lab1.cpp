// lab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "modbus.h"

template <typename T>

T GetCorrectNumber(T least = 0, T great = 1000000) {
    T val = 0;
    while (true) {
        if (std::cin >> val && (std::cin.peek() == EOF || std::cin.peek() == '\n') && (val >= least) && (val < great)) return val;
        else {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Попробуйте ещё раз: ";
        }
    }
}

void cout_menu()
{
    //setlocale(LC_ALL, "");
    std::cout << "Введите соответствующее значение:" << std::endl
        << "1. COIL STATUS.\n" 
        << "2. INPUT STATUS.\n" 
        << "3. HOLDING REGISTER. \n" 
        << "4. INPUT REGISTER.\n" 
        << "0. Выход." << std::endl;
    
    
}

void second_menu_r(int& first, int& n)
{
    std::cout << "Введите адрес первого регистра: " << std::endl;
    first = GetCorrectNumber(1)-1;
    std::cout << "Введите кол-во регистров: " << std::endl;
    n = GetCorrectNumber(1);

}
template<typename data>
void second_menu_w(int& first, data& n)
{
    std::cout << "Введите адреc регистра: " << std::endl;
    first = GetCorrectNumber(1,32)-1;
    std::cout << "Введите Dанное: " << std::endl;
    n = GetCorrectNumber(0,65536);

}

int input_menu()
{
    while (true)
    {
        int a = GetCorrectNumber(0, 5);
        return a;
    }
}

int start()
{
    setlocale(LC_ALL, "");

    std::string ip;
    int port;
    int slave;

    std::cout << "Введите адрес устройства (IP): ";
    std::cin >> ip;
    std::cout << "Введите номер порта: ";
    std::cin >> port;
    std::cout << "Введите Id устройства(slave): ";
    std::cin >> slave;

    modbus_t* mb = modbus_new_tcp(ip.c_str(), port);
    if (modbus_connect(mb) == -1) {
        std::cerr << "Ошибка соединения." << std::endl;
        modbus_free(mb);
        return -1;
    }

    modbus_set_slave(mb, slave);

    int first = 0;
    int n = 1;

    int menu = 0;
    while (true)
    {
        cout_menu();
        menu = input_menu();

        switch (menu)
        {
        case 1:
        {
            std::cout << "Введите соответствующее значение:" << std::endl
                << "1. Прочитать бит.\n"
                << "2. Записать бит.\n"
                << "0. Назад." << std::endl;
            int rw = GetCorrectNumber(0, 3);
            switch (rw)
            {
            case 1:
            {
                uint8_t tab_reg_bit[32];
                second_menu_r(first, n);
                int k = modbus_read_bits(mb, first, n, tab_reg_bit);
                if (k < 0)
                {
                    std::cout << "Ошибка..." << std::endl;
                    break;
                }

                std::cout << "Результат:" << std::endl;
                for (int i = first; i < first + k; i++)
                {
                    std::cout.width(3);
                    std::cout << i+1 << ".  " << int(tab_reg_bit[i]) << std::endl;
                }
                break;
            }
            case 2:
            {
                int addr = 0;
                uint8_t data = 0;
                second_menu_w(addr, data);
                int k = modbus_write_bit(mb, addr, data);
                if (k < 0)
                {
                    std::cout << "Ошибка..." << std::endl;
                    break;
                }
            }
            default:
                break;
            }

            break;
            
        }

        case 2:
        {
            uint8_t tab_reg_bit[32];
            second_menu_r(first, n);
            int k = modbus_read_input_bits(mb, first, n, tab_reg_bit);
            if (k < 0)
            {
                std::cout << "Ошибка..." << std::endl;
                break;
            }

            std::cout << "Результат:" << std::endl;
            for (int i = first; i < first + k; i++)
            {
                std::cout.width(3);
                std::cout << i+1 << ".  " << int(tab_reg_bit[i]) << std::endl;
            }
            break;
        }

        case 3:
        {
            std::cout << "Введите соответствующее значение:" << std::endl
                << "1. Прочитать регистр.\n"
                << "2. Записать регистр.\n" 
                << "0. Назад." << std::endl;
            int rw = GetCorrectNumber(0,3);
            switch (rw)
            {
            case 1:
            {
                second_menu_r(first, n);
                uint16_t tab_reg[32];
                int k = modbus_read_registers(mb, first, n, tab_reg);
                if (k < 0)
                {
                    std::cout << "Ошибка..." << std::endl;
                    break;
                }

                std::cout << "Результат:" << std::endl;
                for (int i = first; i < first + k; i++)
                {
                    std::cout.width(5);
                    std::cout << i+1 << ".  " << int(tab_reg[i]) << std::endl;
                }
                break;
            }
            case 2:
            {
                int addr = 0;
                uint16_t data = 0;
                second_menu_w(addr, data);
                int k = modbus_write_register(mb, addr, data);
                if (k < 0)
                {
                    std::cout << "Ошибка..." << std::endl;
                    break;
                }
            }
            default:
                break;
            }
            
            break;
        }

        case 4:
        {
            second_menu_r(first, n);
            uint16_t tab_reg[32];
            int k = modbus_read_input_registers(mb, first, n, tab_reg);
            if (k < 0)
            {
                std::cout << "Ошибка..." << std::endl;
                break;
            }

            std::cout << "Результат:" << std::endl;
            for (int i = first; i < first + k; i++)
            {
                std::cout.width(5);
                std::cout << i+1 << ".  " << int(tab_reg[i]) << std::endl;
            }
            break;
        }
        default:
            modbus_close(mb);
            modbus_free(mb);
            return 0;
        }
    }
    
    //uint16_t tab_reg[32];

    //uint8_t tab_reg_bit[32];
    //mb = modbus_new_tcp("127.0.0.1", 502);
    ////std::cout << modbus_connect(mb) << std::endl;
    //if (modbus_connect(mb) == -1) {
    //    std::cerr << "Ошибка соединения: " << modbus_strerror(errno) << std::endl;
    //    modbus_free(mb);
    //    return -1;
    //}
    //int r = modbus_connect(mb);
    ////int kkk = modbus_get_slave(mb);
    ////std::cout <<"server slaves:" << kkk << std::endl;
    //modbus_set_slave(mb, 17);
    ///* Read 5 registers fromythe address 0 */
    ////int m = modbus_read_bits(mb,0, 5, tab_reg);
    //int m = 0;
    ////for (int i = 0; i < 15; ++i)
    ////{
    //m = modbus_read_input_registers(mb, 0, 10, tab_reg);
    //int n = modbus_read_input_bits(mb, 0, 10, tab_reg_bit);

    ////std::cout << m <<"  " << n << std::endl;
    ////}



    //modbus_close(mb);
    //modbus_free(mb);

    //std::cout << "start list" << std::endl;
    //for (int i = 0; i < 10; i++)
    //{

    //    //std::cout << tab_reg[i] << "   ";
    //    std::cout << i + 1 << "   " << int(tab_reg_bit[i]) << std::endl;
    //}
}


int main() 
{
    int a = start();
    return a;
}



