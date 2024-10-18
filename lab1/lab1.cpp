// lab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "modbus.h"
int start()
{
    setlocale(LC_ALL, "");
    modbus_t* mb;
    uint16_t tab_reg[32];

    //uint8_t tab_reg[32];
    mb = modbus_new_tcp("127.0.0.1", 502);
    //std::cout << modbus_connect(mb) << std::endl;
    if (modbus_connect(mb) == -1) {
        std::cerr << "Ошибка соединения: " << modbus_strerror(errno) << std::endl;
        modbus_free(mb);
        return -1;
    }
    int r = modbus_connect(mb);
    //int kkk = modbus_get_slave(mb);
    //std::cout <<"server slaves:" << kkk << std::endl;
    modbus_set_slave(mb, 17);
    /* Read 5 registers fromythe address 0 */
    //int m = modbus_read_bits(mb,0, 5, tab_reg);
    int m = 0;
    //for (int i = 0; i < 15; ++i)
    //{
    m = modbus_read_registers(mb, 0, 10, tab_reg);

    std::cout << m << std::endl;
    //}
    

    
    modbus_close(mb);
    modbus_free(mb);

    std::cout << "start list" << std::endl;
    for (int i = 0; i < 10; i++)
    {

        std::cout << tab_reg[i]<<std::endl;
    }
}

int main() 
{
    int a = start();
    return a;
}


//#include <iostream>
//#include <vector>
//
//#include "modbus.h"
//
//int main() {
//
//    setlocale(LC_ALL, "");
//
//    std::string ip;
//    int port;
//
//    std::cout << "Введите адрес устройства (IP): ";
//    std::cin >> ip;
//    std::cout << "Введите номер порта: ";
//    std::cin >> port;
//
//    modbus_t* mb = modbus_new_tcp(ip.c_str(), port);
//    if (modbus_connect(mb) == -1) {
//        std::cerr << "Ошибка соединения: " << modbus_strerror(errno) << std::endl;
//        modbus_free(mb);
//        return -1;
//    }
//
//    modbus_set_slave(mb, 1);
//
//    std::vector<uint16_t> tab_reg;
//    uint16_t temp_reg[256]; // Максимальное количество регистров для чтения за один раз
//
//    int read_count;
//    int offset = 0;
//
//    while (true) {
//        read_count = modbus_read_registers(mb, offset, 256, temp_reg);
//        if (read_count < 0) {
//        //    if (errno == MODBUS_ERR_ILLEGAL_DATA_ADDRESS) {
//        //        break; // Достигнут конец доступных регистров
//        //    }
//            std::cerr << "Ошибка чтения регистров: " << modbus_strerror(errno) << std::endl;
//            break;
//        }
//
//        // Сохраняем прочитанные регистры в массив
//        for (int i = 0; i < read_count; ++i) {
//            tab_reg.push_back(temp_reg[i]);
//        }
//
//        offset += read_count;
//    }
//
//    std::cout << "Всего прочитанных регистров: " << tab_reg.size() << std::endl;
//    std::cout << "Значения регистров: ";
//    for (const auto& reg : tab_reg) {
//        std::cout << reg << " ";
//    }
//    std::cout << std::endl;
//
//    modbus_close(mb);
//    modbus_free(mb);
//    return 0;
//}
