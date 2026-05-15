// Name: Desire Gonyora
// Class: Introduction to IOT (Internet of things)
// Project: Controlable fan

//Library 
#include <DHT.h>
#include <LiquidCrystal.h>

// LCD Pins
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// DHT11 setup
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// potentiometer + fan setup 
int potPin = A0; 
int fanPin = 5;

// Function #1: Potntiometer controle speed
int getManualSpeed() {
  int potValue = analogRead(potPin);
  return map(potValue, 0, 1023, 0, 255);
}

// Funtion #2: Automatically setting the speed
int autoSpeed(float temp) {
  if (temp < 22) {
    return 0;
  }
  else if (temp < 26) {
    return 120;
  }
  else {
    return 255;
  }
}

  void setup() {
  
    pinMode(fanPin, OUTPUT);

    lcd.begin(16, 2);

    Serial.begin(9600);

    dht.begin();
  }

  void loop() {

    float temperature = dht.readTemperature(); 

    int speed;

    // If sensor fails -> manual mode
    if (isnan(temperature)) {
      speed = getManualSpeed(); 
    }

    analogWrite(fanPin, speed);

    int percent = map(speed, 0, 255, 0, 100);

    // LCD display
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print(" C");

    lcd.setCursor(0, 1);
    lcd.print("fan: ");
    lcd.print(percent);
    lcd.print("%"); 

     // Serial monitor
  Serial.print("Temp: ");
  Serial.print(temperature);

  Serial.print(" | Fan: ");
  Serial.print(percent);
  Serial.println("%");

  delay(1000);
}

