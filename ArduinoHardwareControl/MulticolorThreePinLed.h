#include "color.h"

// Class to control a three pin multi color cathode LED
// One pin is connected to each leg of the cathode each through a resistor
class MulticolorThreePinLed
{
public:
  MulticolorThreePinLed(int pin_out_red, int pin_out_green, int pin_out_blue);
  void Initialize();

  void SetColor(byte red, byte green, byte blue);

  void SetColor(color c, shade s = shade::BRIGHT);

  void On();
  void Off();

  void WriteCathodeLed(byte red, byte green, byte blue);

  
private:
  int m_pin_red = 0;
  int m_pin_green = 0;
  int m_pin_blue = 0;

  byte m_output_red = 0;
  byte m_output_green = 0;
  byte m_output_blue = 0;

  bool m_on = false;
};


