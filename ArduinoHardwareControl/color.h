/*
enum color : unsigned int;
enum shade : unsigned int;

void ColorShade(byte &r, byte &g, byte &b, color c, shade s);
*/

//
// Color and shade constants
//

enum color
{
  OFF = 0,
  RED,
  ORANGE,
  YELLOW,
  CHARTREUSE,
  GREEN,
  AQUAMARINE,
  CYAN,
  AZURE,
  BLUE,
  VIOLET,
  MAGENTA,
  ROSE,
  WHITE,
  COLOR_COUNT // not an actual color just used to keep count
};

extern String color_name[color::COLOR_COUNT];

// array of colors that can be output
extern byte color_values[color::COLOR_COUNT][3];

// change brightness
// goes from brightest to dimmest
enum shade
{
  BRIGHT = 0,
  ONE,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  DARK, // 8, bitshifts to 0
  SHADE_COUNT // not an actual shade just used to keep count
};

extern String shade_name[shade::SHADE_COUNT];

void ColorShade(byte &r, byte &g, byte &b, color c, shade s);
