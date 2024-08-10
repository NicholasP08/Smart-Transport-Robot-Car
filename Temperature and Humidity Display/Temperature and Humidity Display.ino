//Nicholas_Pillay_Code_for_DHT11_Display_On_LCD

//Inclcude Libraries
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal_I2C.h>

//Create objects and variables
DHT dht(2,DHT11);                   //Create dht object to specify data pin and type of DHT sensor
int temp;                           //Create Temperature variable
int humidity;                       //Create Humidity variable
LiquidCrystal_I2C lcd(0x27,16,2);   //Create lcd object. Pass in address parameter, columns parameter, rows parameter.

void setup() {
  dht.begin();                      //Start and initalize dht
  lcd.init();                       //Initalize lcd
  lcd.backlight();                  //Turn on LCD backlight
}

void loop() {
  delay(2000);                      //Delay by 2 seconds for accurate temperature and humidity value
  temp=dht.readTemperature(true);   //Read Temperature and place it in temp. Place true inside () for Fahrenheit reading
  humidity=dht.readHumidity();      //Read Humidity and place it in humidity

  lcd.setCursor(0,0);               //Set the cursor to first column and first row.
  lcd.print("Temp: ");              //Display "Temp: " on LCD
  lcd.print(temp);                  //Display temperature reading on LCD
  lcd.print("F");                   //Display "F" on LCD for abbreviation of Fahrenheit

  lcd.setCursor(0,1);               //Set the cursor to first column and second row.
  lcd.print("Humidity: ");          //Display "Humidity: " on LCD
  lcd.print(humidity);              //Display humidity reading on LCD
  lcd.print("%");                   //Display "%" on LCD for symbol for percent
}