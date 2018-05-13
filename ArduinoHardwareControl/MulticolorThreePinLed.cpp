// need to include application.h in .cpp files
#include "application.h"


#include "MulticolorThreePinLed.h"


MulticolorThreePinLed::MulticolorThreePinLed(int pin_red, int pin_green, int pin_blue) :
  m_pin_red(pin_red),
  m_pin_green(pin_green),
  m_pin_blue(pin_blue)
{
}

void MulticolorThreePinLed::Initialize()
{
  pinMode(m_pin_red, OUTPUT);
  pinMode(m_pin_green, OUTPUT);
  pinMode(m_pin_blue, OUTPUT);
  Off();
}

void MulticolorThreePinLed::SetColor(color c, shade s)
{
  byte r, g, b;
  ColorShade(r, g, b, c, s);
  SetColor(r, g, b);
}

void MulticolorThreePinLed::SetColor(byte red, byte green, byte blue)
{
  // assume that LED is a cathode
  m_output_red = red;
  m_output_green = green;
  m_output_blue = blue;

  if (m_on)
  {
    On();
  }
}

void MulticolorThreePinLed::On()
{
  m_on = true;
  Serial.println("on");
  WriteCathodeLed(m_output_red, m_output_green, m_output_blue);
}

void MulticolorThreePinLed::Off()
{
  m_on = false;
  Serial.println("off");
  WriteCathodeLed(0, 0, 0);
}


void MulticolorThreePinLed::WriteCathodeLed(byte red, byte green, byte blue)
{
    analogWrite(m_pin_red, 255 - red);
    analogWrite(m_pin_green, 255 - green);
    analogWrite(m_pin_blue, 255 - blue);
}
