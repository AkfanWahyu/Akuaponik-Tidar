#include <EEPROM.h>
#include "GravityTDS.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Alamat I2C, kolom, baris

#define TdsSensorPin A1
GravityTDS gravityTds;

float temperature = 25, tdsValue = 0;

void setup()
{
  lcd.init();
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ppm ");
  Serial.begin(115200);
  gravityTds.setPin(TdsSensorPin);
  gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
  gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
  gravityTds.begin();  //initialization
  lcd.backlight();
}

void loop()
{
  //temperature = readTemperature();  //add your temperature sensor and read it
  gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
  gravityTds.update();  //sample and calculate
  tdsValue = gravityTds.getTdsValue();  // then get the value
  Serial.print(tdsValue, 0);
  Serial.println("ppm");
  lcd.setCursor(0,4);
  lcd.print(tdsValue);
  delay(1000);
}
