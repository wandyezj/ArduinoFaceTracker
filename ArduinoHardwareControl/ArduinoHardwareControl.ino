#include "RedBearDuoRequiredManual.h"
#include "MulticolorThreePinLed.h"

//#include "pitches.h"
#include "pins.h"


MulticolorThreePinLed output_led(pin_led_red, pin_led_green, pin_led_blue);
//Servo servo;

//
// Board LED
//
/*
void SetRGB(byte r, byte g, byte b)
{
  RGB.color(r, g, b);
}
*/

void setup() {
  Serial.begin(9600);
  //RGB.control(true);
  // put your setup code here, to run once:
  output_led.Initialize();
  
  //pinMode(pin_piezo, OUTPUT);

/*
  pinMode(pin_led_red, OUTPUT);
  pinMode(pin_led_green, OUTPUT);
  pinMode(pin_led_blue, OUTPUT);
*/
  //servo.attach(pin_servo); 
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("loop");
/*
    analogWrite(pin_led_red, 255);
    analogWrite(pin_led_green, 255);
    analogWrite(pin_led_blue, 255);
  delay(5000);
  //output_led.On();
  //delay(2000);
*/
  // LED
/*
    analogWrite(pin_led_red, 0);
    analogWrite(pin_led_green, 0);
    analogWrite(pin_led_blue, 0);
    delay(5000);
  //*/
  
  output_led.On();
  output_led.SetColor(color::RED);
  //output_led.On();
  delay(1000);
  output_led.SetColor(color::GREEN);
  //output_led.On();
  delay(1000);
  output_led.SetColor(color::BLUE);
  delay(1000);
  output_led.Off();
  delay(1000);

  // Sound
  /*
  tone(pin_piezo, NOTE_A6, 1000);
  delay(1000);
  //*/
  
  // Servo
  /*
  servo.write(0);
  delay(10000);
  servo.write(90);
  delay(10000);
  servo.write(180);
  delay(10000);
  //*/







/*
  for (int i = 0; i < 256; i++)
  {
    Serial.println(i);
    analogWrite(pin_piezo, i);
    delay(100);
    analogWrite(pin_piezo, 0);
    delay(100);
  }
*/

/*
  // notes_length
  for (int i = 0; i < 1; i++)
  {
    Serial.println(notes[i]);
    
  }
  noTone(pin_piezo);
  */
  
  //analogWrite(pin_led_red,128);
  //output_led.On();
  //RGB.color(0, 0, 0);
  //delay(500);
  //output_led.Off();
  //delay(500);
}
