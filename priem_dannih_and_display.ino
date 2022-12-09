#include "DHT.h"  // Объявление библиотек
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define DHTPIN 2

LiquidCrystal_I2C lcd(0x3F,16,2); // Задаем параметры дисплея

DHT dht(DHTPIN, DHT11); // Задаем параметры датчика dht11
void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();                      // Инициализация дисплея  
  lcd.backlight();                 // Подключение подсветки
}
void loop() {
  float h = dht.readHumidity(); //Измеряем влажность
  float t = dht.readTemperature(); //Измеряем температуру
  if (isnan(h) || isnan(t)) {  // Проверка. Если не удается считать показания, выводится «Ошибка считывания», и программа завершает работу
    Serial.println("Error");
    lcd.setCursor(0,0);
    lcd.print("Error");
    lcd.setCursor(0,1);
    lcd.print("Check DHT11");
    return;
  }
  lcd.setCursor(0,0); // Выводим данные сначала на дисплей, потом в монитор порта
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print("*C");
  Serial.print("Влажность: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Температура: ");
  Serial.print(t);
  Serial.println(" *C ");
  delay(4000); // Задержка 4 секунды
}
