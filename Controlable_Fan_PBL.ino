// Name: Desire Gonyora
// Class: Introduction to IOT (Internet of Things)
// Project: Controllable Smart Fan

// Including the libraries
#include <DHT.h>
#include <LiquidCrystal.h>

// Setting up LCD
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Setting up the DHT11 
#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Setting up the Pot and the fan
int potPin = A0;
int fanPin = 5;


// Function #1: Manual fan speed control
int getManualSpeed() {

  int potValue = analogRead(potPin);

  // Convert 0–1023 into 0–255
  int speed = map(potValue, 0, 1023, 0, 255);

  return speed;
}

// Function #2: Automatic temperature-based speed
int autoSpeed(float temp) {

  // Limiting temperature range
  if (temp < 20) temp = 20;
  if (temp > 35) temp = 35;

  // Speed control
  return map(temp, 20, 35, 0, 255);
}

// Setting up
void setup() {

  pinMode(fanPin, OUTPUT);

  lcd.begin(16, 2);

  Serial.begin(9600);

  dht.begin();

  // Startup message
  lcd.setCursor(0, 0);
  lcd.print("Smart Fan");

  lcd.setCursor(0, 1);
  lcd.print("Starting...");

  delay(2000);

  lcd.clear();
}

// THE VOOIIDD
void loop() {

  // Read temperature
  float temperature = dht.readTemperature();

  int speed;

  // If DHT11 fails -> use potentiometer
  if (isnan(temperature)) {

    speed = getManualSpeed();

    lcd.setCursor(0, 0);
    lcd.print("Manual Mode   ");
  }

  // Otherwise -> automatic mode
  else {

    speed = autoSpeed(temperature);

    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print(" C   ");
  }

  // Send PWM signal to fan
  analogWrite(fanPin, speed);

  // Convert speed to percentage
  int percent = map(speed, 0, 255, 0, 100);

  // LCD second row
  lcd.setCursor(0, 1);
  lcd.print("Fan: ");
  lcd.print(percent);
  lcd.print("%   ");

  // Serial Monitor output
  Serial.print("Temperature: ");
  Serial.print(temperature);

  Serial.print(" | Fan Speed: ");
  Serial.print(percent);
  Serial.println("%");

  delay(1000);
}
