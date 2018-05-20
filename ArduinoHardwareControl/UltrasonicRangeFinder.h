
class UltrasonicRangeFinder
{
public:

  UltrasonicRangeFinder(int pin_trigger, int pin_echo);

  void Setup();

  float RangeCentimeters();
  
private:
  int m_pin_trigger = 0;
  int m_pin_echo = 0;

}
;
