#include "application.h"

#include "UltrasonicRangeFinder.h"


UltrasonicRangeFinder::UltrasonicRangeFinder(int pin_trigger, int pin_echo) :
  m_pin_trigger(pin_trigger),
  m_pin_echo(pin_echo)
{
  
}

void UltrasonicRangeFinder::Setup()
{
  pinMode(m_pin_trigger, OUTPUT);
  digitalWrite(m_pin_trigger, LOW);
  pinMode(m_pin_echo, INPUT);
}

float UltrasonicRangeFinder::RangeCentimeters()
{
  unsigned long t1;
  unsigned long t2;
  unsigned long pulse_width;
  float cm;
  float inches;

  // Hold the trigger pin high for at least 10 us
  digitalWrite(m_pin_trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(m_pin_trigger, LOW);

  // Wait for pulse on echo pin
  while ( digitalRead(m_pin_echo) == 0 );

  // Measure how long the echo pin was held high (pulse width)
  // Note: the micros() counter will overflow after ~70 min
  t1 = micros();
  while ( digitalRead(m_pin_echo) == 1);
  t2 = micros();
  pulse_width = t2 - t1;

  // Calculate distance in centimeters and inches. The constants
  // are found in the datasheet, and calculated from the assumed speed 
  // of sound in air at sea level (~340 m/s).
  // Datasheet: https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf
  cm = pulse_width / 58.0;
  inches = pulse_width / 148.0;
  
  // The HC-SR04 datasheet recommends waiting at least 60ms before next measurement
  // in order to prevent accidentally noise between trigger and echo
  // See: https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf
  delay(60);

  return cm;
}

