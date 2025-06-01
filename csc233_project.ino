// project code
// how to indicate pain level? Better way to represent scale rather
// than just integers? keypad? another potentiometer?
// Output: led lights?, display?, lcd?, or smth better?
// maybe a buzzer when high temp is detected? not very Baymax-y
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 4, 3, 2, 10);
int sensorValue = 0;
int outputValue = 0;
int switchValGood = 0;
int switchValMild = 0;
int switchValBad = 0;
int painLevel;
int answer = 0;
const int sensorPin = A1;

void setup()
{
  pinMode(A0, INPUT);
  pinMode(sensorPin, INPUT);
  pinMode(9, OUTPUT);
  pinMode(7, INPUT);
  pinMode(6, INPUT);
  pinMode(5, INPUT);
  Serial.begin(9600);
  
  // lcd
  lcd.begin(16, 2);
  lcd.print("Hello I'm Baymax");
  lcd.setCursor(0, 1);
  lcd.print("your companion!");
  delay(6000);
}

void loop()
{
  Serial.begin(9600); //open serial port
  // read the value from the sensor for DC motor
  sensorValue = analogRead(A0);
  outputValue = map(sensorValue, 0, 1023, 0, 255);

  // read pain level
  switchValGood = digitalRead(7);
  switchValMild = digitalRead(6);
  switchValBad = digitalRead(5);

  if(switchValGood == HIGH){
    painLevel = 1;
  }
  else if(switchValMild == HIGH){
    painLevel = 0;
  }
  else if(switchValBad == HIGH){
    painLevel = -1;
  }
  else{
  	painLevel = -2;
  }
  
  // write out potentiometer values
  analogWrite(9, outputValue);
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("     output = ");
  Serial.println(outputValue);
  
  // Temp sensor
  int sensorVal = analogRead(sensorPin); // convert ADC reading to voltage
  float voltage = (sensorVal/1024.0) *5.0;  // convert voltage to temp
  float temp = (voltage -.5) *100;
  
  switch(painLevel){
  case 1:
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("You're healthy!!");
    lcd.setCursor(0, 1);
    lcd.print("Body temp: ");
    lcd.print(temp);
    break;
  case 0:
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Looking good!");
    lcd.setCursor(0, 1);
    lcd.print("Body temp: ");
    lcd.print(temp);
    break;
  case -1:
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("I can help you!");
    lcd.setCursor(0, 1);
    lcd.print("Body temp: ");
    lcd.print(temp);
    break;
  default:
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Rate pain level");
    lcd.setCursor(0, 1);
    lcd.print("Good, Mild, Bad");
    break;
  }

  delay(1000); // Wait for 100 millisecond(s)
}
