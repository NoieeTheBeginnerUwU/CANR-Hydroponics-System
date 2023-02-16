
/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-temperature-sensor
 */

#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
#include <SimpleTimer.h>
#include <virtuabotixRTC.h>    
#include <EEPROM.h>
#include <GravityTDS.h>


virtuabotixRTC myRTC(6, 7, 8);

const int SENSOR_PIN = 3; // Arduino pin connected to DS18B20 sensor's DQ pin
LiquidCrystal_I2C lcd(0x27, 16, 2);
OneWire oneWire(SENSOR_PIN);         // setup a oneWire instance
DallasTemperature tempSensor(&oneWire); // pass oneWire to DallasTemperature library

#define TdsSensorPin A1
GravityTDS gravityTds;

float tempCelsius;    // temperature in Celsius
float tempFahrenheit; // temperature in Fahrenheit

int pH_Value;   //the level of PH
float Voltage; //the voltage used to get the ph level

int resval = 0;
int respin = A3;

void setup()
{
  Serial.begin(9600); // initialize serial
  tempSensor.begin();    // initialize the sensor
  pinMode(pH_Value, INPUT); 
 myRTC.setDS1302Time(00, 33, 3, 6, 11, 2, 2023);
  
}

void loop()
{
  lcd.begin();
  tempSensor.requestTemperatures();             // send the command to get temperatures
  tempCelsius = tempSensor.getTempCByIndex(0);  // read temperature in Celsius
  tempFahrenheit = tempCelsius * 9 / 5 + 32; // convert Celsius to Fahrenheit
  myRTC.updateTime();    
  lcd.print("");

    resval = analogRead(respin)*2;
float temperature = resval,tdsValue = 0;
  //Serial.print("Temperature: "); //print the temperature in Celsius
  //Serial.print(tempCelsius);    // print the value

  pH_Value = analogRead(A0); 
  Voltage = pH_Value * (5.0 / 1023.0); 

  //display group name/project name with LCD
  lcd.setCursor(0,0);
  lcd.print("Vertical");
  lcd.setCursor(5,1);
  lcd.print("Hydroponics");

  delay(3000);
  
  //show temperature in Celsius
  lcd.setCursor(0,0);
  lcd.print("temp: ");
  lcd.print(tempCelsius);
  lcd.print(char(223));
  lcd.print("C");

  //show temperature in Fahrenheit
  lcd.setCursor(0,1);
  lcd.print("temp: ");
  lcd.print(tempFahrenheit);
  lcd.print(char(223));
  lcd.print("F   ");

  delay(3000);
  
  //show water level
  lcd.setCursor(0,0);
  lcd.print("water lvl: ");
  lcd.print(resval/100);
  lcd.print("%");

  //show water level
  lcd.setCursor(0,1);
  lcd.print("ph lvl: ");
  lcd.print(Voltage);
  lcd.print("       ");
  delay(3000);

  //show salinity
  lcd.setCursor(0,0);
  lcd.print("salinity lvl: ");
  lcd.print("0");
  lcd.print("      ");

  //humidity humidity
  lcd.setCursor(0,1);
  lcd.print("humidity: ");
  lcd.print("0");
  lcd.print("      ");
  delay(3000);

    //show date
  lcd.setCursor(0,0);
  lcd.print("date: ");
  lcd.print(myRTC.dayofmonth);
  lcd.print("/");
  lcd.print(myRTC.month);
  lcd.print("/");
  lcd.print(myRTC.year);
  lcd.print("  ");
  
  //show time
  lcd.setCursor(0,1);
  lcd.print("time: ");
  lcd.print(myRTC.hours);
  lcd.print(":");
  lcd.print(myRTC.minutes);
  delay(3000);

  Serial.print(myRTC.hours);
  Serial.print(myRTC.minutes);
  
}

