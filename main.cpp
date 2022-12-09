#include <serial.h> //Объявление библиотек
#include <fstream>
#include <iostream>
#include <ctime>
using namespace std;

std::string currentDateTime() { // Функция записи даты и времени в момент ее вызова
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    char buffer[128];
    strftime(buffer, sizeof(buffer), "%d-%m-%Y %X", now);
    return buffer;
}

int main() // Основной цикл программы
{
    fstream ardout; // объявляем переменную для записи данных в отдельный документ
    const char *device = "\\\\.\\COM3"; // объявляем различные параметры подключения ардуино к ПК
    uint32_t baud_rate = 9600;
    Serial serial_port;
    if(!serial_port.open(device,baud_rate)) { // Если ардуино не подключено или работает неисправно
        cout<<"Error"<<endl; // выводить Error
        return 1;
    }
    do {
        string received; // Объявление строковых переменных для принимаемых данных
        string hum, temp;
        received = serial_port.read_line(); // Принимаем данные с ардуино
        received.replace(0, 2, ""); // Обрабатываем данные в удобный для отображения вид
        auto pos = received.find("%: ");
        hum = received.substr(0, pos);
        temp = received.substr(pos+1);
        temp.replace(0, 2, "");
        cout<<"Received humidity: "<<hum<<"%, temperature: "<<temp<<endl; // Выводим в консоль программы принятую и обработанную влажность и температуру
        ardout.open("C:/Users/roboschool/Desktop/serialport_read/received.txt", ios_base::app); // Открываем текстовый документ для записи
        if (ardout.is_open()) { // Если документ открыт
            ardout << currentDateTime() << "; Humidity: "<< hum << "%, temperature: " << temp << "\n"; // Записываем в него наши данные
            ardout.close(); // Закрываем документ
            if (ardout.is_open()) // Если документ не закрылся
                            cout << "Stream could not close!" << endl; // Выводим ошибку, что документ не может закрыться
        }
    }
    while(true); // Выполнять пока запущена программа
    return 0;
}
