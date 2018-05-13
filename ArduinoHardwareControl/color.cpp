#include "application.h"

#include "color.h"

String color_name[color::COLOR_COUNT] =
{
  "off",
  "red",
  "orange",
  "yellow",
  "chartreuse",
  "green",
  "aquamarine",
  "cyan",
  "azure",
  "blue",
  "violet",
  "magenta",
  "rose",
  "white"
};

byte color_values[color::COLOR_COUNT][3] =
{
  {0, 0, 0}, // off
  {255, 0,  0}, // red
  {255, 127, 0}, // orange
  {255, 255, 0}, // yellow
  {127, 255, 0}, // chartreuse
  {0, 255, 0}, // green
  {0, 255, 127}, // aquamarine
  {0, 255, 255}, // cyan
  {0, 127, 255}, // azure
  {0, 0, 255}, // blue
  {127, 0, 255}, // violet
  {255, 0, 255}, // magenta
  {255, 0, 127}, // rose
  {255, 255, 255} // white
};


String shade_name[shade::SHADE_COUNT] =
{
  "bright",
  "one",
  "two",
  "three",
  "four",
  "five",
  "six",
  "seven",
  "dark"
};

void ColorShade(byte &r, byte &g, byte &b, color c, shade s)
{
  r = color_values[c][0];
  g = color_values[c][1];
  b = color_values[c][2];

  // bitshift to adjust brightness
  r = r >> s;
  g = g >> s;
  b = b >> s;
}
