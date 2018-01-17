#include <Wire.h>
#include <LiquidCrystal_I2C.h>


int redLed = 12;
int greenLed = 11;
int buzzer = 10;
int smokeA0 = A0;
// threshold value
int sensorThres = 600;

// init LCD
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
  //setup LEDS, Buzzer and Gas Sensor
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  // setup LCD and Serial
  lcd.begin(16,2); // sixteen characters across - 2 lines
  // clear any trash values on the LCD
  lcd.clear();
  // set constant lcd text on first line
//  lcd.setCursor(0, 0);
//  lcd.print("Poziom gazu:");
  Serial.begin(9600);
}

void loop() {
  int analogSensor = analogRead(smokeA0);

  Serial.print("Pin A0: ");
  Serial.println(analogSensor);

//   set LCD text on second line, that will refresh frequently and check gas safety level
//  lcd.setCursor(0, 1);

  
  // check if gas is on a dangerous level and notify the user
  if (analogSensor > sensorThres + 200)
  {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    tone(buzzer, 1000, 200);
    // print info on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Poziom gazu:");
    lcd.print(analogSensor);
    // display text explanation of gas level
    lcd.setCursor(0, 1);
    lcd.print("NIEBEZPIECZNY!!!");
    delay(200);
  }
  // Checks if it has reached non-dangerous threshold value
  else if (analogSensor > sensorThres)
  {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    // print info on LCD
    lcd.clear();
    // print current gas level
    lcd.setCursor(0, 0);
    lcd.print("Poziom gazu:");
    lcd.print(analogSensor);
    // display text explanation of gas level
    lcd.setCursor(0, 1);
    lcd.print("UWAGA");
    delay(500);
  }
  else
  {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    noTone(buzzer);

    // write info on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Poziom gazu:");
    lcd.print(analogSensor);
    // display text explanation of gas level
    lcd.setCursor(0, 1);
    lcd.print("BEZPIECZNY");
    delay(1000);
  }
}

