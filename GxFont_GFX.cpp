// class GxFont_GFX : Font Rendering Graphics Switch and Bridge Class
//
// This class allows to connect GxEPD to additional font rendering classes.
//
// Adafruit_ftGFX: a Adafruit_GFX variant with different fonts.
// need to use modified clone from: https://github.com/ZinggJM/Adafruit_ftGFX
//
// GxFont_GFX_TFT_eSPI: fonts and font rendering of TFT_eSPI library (Bodmer)
// available here: https://github.com/ZinggJM/GxFont_GFX_TFT_eSPI
//
// Author : J-M Zingg
//
// Version : see library.properties
//
// License: GNU GENERAL PUBLIC LICENSE V3, see LICENSE
//
// Library: https://github.com/ZinggJM/GxEPD

#include "GxFont_GFX.h"

//#define DIAG(x) x

#ifndef DIAG
#define DIAG(x)
#endif

enum eFont_GFX
{
  Adafruit_GFX_font_gfx, Adafruit_tfGFX_font_gfx, GxFont_GFX_TFT_eSPI_font_gfx
};

GxFont_GFX::GxFont_GFX(int16_t w, int16_t h) : Adafruit_GFX(w, h)
#if defined(_ADAFRUIT_TF_GFX_H_)
  , _GxF_Adafruit_tfGFX(*this, w, h)
#endif
#if defined(_GxFont_GFX_TFT_eSPI_H_)
  , _GxF_GxFont_GFX_TFT_eSPI(*this, w, h)
#endif
{
  _font_gfx = Adafruit_GFX_font_gfx;
}

#if defined(_ADAFRUIT_TF_GFX_H_)

void GxFont_GFX::GxF_Adafruit_tfGFX::drawPixel(int16_t x, int16_t y, uint16_t color)
{
  _container.drawPixel(x, y, color);
}

void GxFont_GFX::setFont(uint8_t f)
{
  _font_gfx = Adafruit_tfGFX_font_gfx;
  _GxF_Adafruit_tfGFX.setFont(f);
}

#endif

#if defined(_GxFont_GFX_TFT_eSPI_H_)

void GxFont_GFX::GxF_GxFont_GFX_TFT_eSPI::drawPixel(uint32_t x, uint32_t y, uint32_t color)
{
  //Serial.print("GxFont_GFX::GxF_GxFont_GFX_TFT_eSPI::drawPixel("); Serial.print(color); Serial.println(")"); yield();
  _container.drawPixel(x, y, color);
}

void GxFont_GFX::GxF_GxFont_GFX_TFT_eSPI::drawFastHLine(int32_t x, int32_t y, int32_t w, uint32_t color)
{
  //Serial.print("GxFont_GFX::GxF_GxFont_GFX_TFT_eSPI::drawFastHLine("); Serial.print(color); Serial.println(")"); yield();
  _container.drawFastHLine(x, y, w, color);
}

void GxFont_GFX::GxF_GxFont_GFX_TFT_eSPI::fillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color)
{
  //Serial.print("GxFont_GFX::GxF_GxFont_GFX_TFT_eSPI::fillRect("); Serial.print(color); Serial.println(")"); yield();
  _container.fillRect(x, y, w, h, color);
}

#ifdef LOAD_GFXFF
void GxFont_GFX::setFreeFont(const GFXfont *f)
{
  _font_gfx = GxFont_GFX_TFT_eSPI_font_gfx;
  _GxF_GxFont_GFX_TFT_eSPI.setFreeFont(f);
}

void GxFont_GFX::setTextFont(uint8_t font)
{
  _font_gfx = GxFont_GFX_TFT_eSPI_font_gfx;
  _GxF_GxFont_GFX_TFT_eSPI.setTextFont(font);
}

#else

void GxFont_GFX::setFreeFont(uint8_t font)
{
  _font_gfx = GxFont_GFX_TFT_eSPI_font_gfx;
  _GxF_GxFont_GFX_TFT_eSPI.setFreeFont(font);
}

void GxFont_GFX::setTextFont(uint8_t font)
{
  _font_gfx = GxFont_GFX_TFT_eSPI_font_gfx;
  _GxF_GxFont_GFX_TFT_eSPI.setTextFont(font);
}

#endif

#endif

void GxFont_GFX::setFont(const GFXfont *f)
{
  Adafruit_GFX::setFont(f);
}

#if defined(_ADAFRUIT_TF_GFX_H_) || defined(_GxFont_GFX_TFT_eSPI_H_)

void GxFont_GFX::drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size)
{
  switch (_font_gfx)
  {
    case Adafruit_GFX_font_gfx:
      Adafruit_GFX::drawChar(x, y, c, color, bg, size);
      break;
#if defined(_ADAFRUIT_TF_GFX_H_)
    case Adafruit_tfGFX_font_gfx:
      _GxF_Adafruit_tfGFX.drawChar(x, y, c, color, bg, size);
      break;
#endif
#if defined(_GxFont_GFX_TFT_eSPI_H_)
    case GxFont_GFX_TFT_eSPI_font_gfx:
      _GxF_GxFont_GFX_TFT_eSPI.drawChar(x, y, c, color, bg, size);
      break;
#endif
  }
}

void GxFont_GFX::setCursor(int16_t x, int16_t y)
{
  Adafruit_GFX::setCursor(x, y);
#if defined(_ADAFRUIT_TF_GFX_H_)
  _GxF_Adafruit_tfGFX.setCursor(x, y);
#endif
#if defined(_GxFont_GFX_TFT_eSPI_H_)
  _GxF_GxFont_GFX_TFT_eSPI.setCursor(x, y);
#endif
}

void GxFont_GFX::setTextColor(uint16_t c)
{
  Adafruit_GFX::setTextColor(c);
#if defined(_ADAFRUIT_TF_GFX_H_)
  _GxF_Adafruit_tfGFX.setTextColor(c);
#endif
#if defined(_GxFont_GFX_TFT_eSPI_H_)
  _GxF_GxFont_GFX_TFT_eSPI.setTextColor(c);
#endif
}

void GxFont_GFX::setTextColor(uint16_t c, uint16_t bg)
{
  Adafruit_GFX::setTextColor(c, bg);
#if defined(_ADAFRUIT_TF_GFX_H_)
  _GxF_Adafruit_tfGFX.setTextColor(c, bg);
#endif
#if defined(_GxFont_GFX_TFT_eSPI_H_)
  _GxF_GxFont_GFX_TFT_eSPI.setTextColor(c, bg);
#endif
}

void GxFont_GFX::setTextSize(uint8_t s)
{
  Adafruit_GFX::setTextSize(s);
#if defined(_ADAFRUIT_TF_GFX_H_)
  _GxF_Adafruit_tfGFX.setTextSize(s);
#endif
#if defined(_GxFont_GFX_TFT_eSPI_H_)
  _GxF_GxFont_GFX_TFT_eSPI.setTextSize(s);
#endif
}

void GxFont_GFX::setTextWrap(boolean w)
{
  Adafruit_GFX::setTextWrap(w);
#if defined(_ADAFRUIT_TF_GFX_H_)
  _GxF_Adafruit_tfGFX.setTextWrap(w);
#endif
#if defined(_GxFont_GFX_TFT_eSPI_H_)
  _GxF_GxFont_GFX_TFT_eSPI.setTextWrap(w);
#endif
}

int16_t GxFont_GFX::getCursorX(void) const
{
  switch (_font_gfx)
  {
    case Adafruit_GFX_font_gfx:
      return Adafruit_GFX::getCursorX();
#if defined(_ADAFRUIT_TF_GFX_H_)
    case Adafruit_tfGFX_font_gfx:
      return 0; // doesn't know
#endif
#if defined(_GxFont_GFX_TFT_eSPI_H_)
    case GxFont_GFX_TFT_eSPI_font_gfx:
      return _GxF_GxFont_GFX_TFT_eSPI.getCursorX();
#endif
  }
}

int16_t GxFont_GFX::getCursorY(void) const
{
  switch (_font_gfx)
  {
    case Adafruit_GFX_font_gfx:
      return Adafruit_GFX::getCursorY();
#if defined(_ADAFRUIT_TF_GFX_H_)
    case Adafruit_tfGFX_font_gfx:
      return 0; // doesn't know
#endif
#if defined(_GxFont_GFX_TFT_eSPI_H_)
    case GxFont_GFX_TFT_eSPI_font_gfx:
      return _GxF_GxFont_GFX_TFT_eSPI.getCursorY();
#endif
  }
}

size_t GxFont_GFX::write(uint8_t v)
{
  DIAG (Serial.write(v); Serial.println();)
  //delay(1);
  switch (_font_gfx)
  {
    case Adafruit_GFX_font_gfx:
      Adafruit_GFX::write(v);
      break;
#if defined(_ADAFRUIT_TF_GFX_H_)
    case Adafruit_tfGFX_font_gfx:
      _GxF_Adafruit_tfGFX.write(v);
      break;
#endif
#if defined(_GxFont_GFX_TFT_eSPI_H_)
    case GxFont_GFX_TFT_eSPI_font_gfx:
      _GxF_GxFont_GFX_TFT_eSPI.write(v);
      break;
#endif
  }
}

#endif

#if defined(_GxFont_GFX_TFT_eSPI_H_)
void GxFont_GFX::setTextDatum(uint8_t datum)
{
  if (_font_gfx == GxFont_GFX_TFT_eSPI_font_gfx) _GxF_GxFont_GFX_TFT_eSPI.setTextDatum(datum);
}
void GxFont_GFX::setTextPadding(uint16_t x_width)
{
  if (_font_gfx == GxFont_GFX_TFT_eSPI_font_gfx) _GxF_GxFont_GFX_TFT_eSPI.setTextPadding(x_width);
}
uint8_t GxFont_GFX::getTextDatum()
{
  return ((_font_gfx == GxFont_GFX_TFT_eSPI_font_gfx) ? _GxF_GxFont_GFX_TFT_eSPI.getTextDatum() : 0);
}
uint8_t GxFont_GFX::color16to8(uint16_t color565) // Convert 16 bit colour to 8 bits
{
  return ((_font_gfx == GxFont_GFX_TFT_eSPI_font_gfx) ? _GxF_GxFont_GFX_TFT_eSPI.color16to8(color565) : 0);
}
uint16_t GxFont_GFX::fontsLoaded(void)
{
  return ((_font_gfx == GxFont_GFX_TFT_eSPI_font_gfx) ? _GxF_GxFont_GFX_TFT_eSPI.fontsLoaded() : 0);
}
uint16_t GxFont_GFX::color565(uint8_t r, uint8_t g, uint8_t b)
{
  return ((_font_gfx == GxFont_GFX_TFT_eSPI_font_gfx) ? _GxF_GxFont_GFX_TFT_eSPI.color565(r, g, b) : 0);
}
uint16_t GxFont_GFX::color8to16(uint8_t color332)  // Convert 8 bit colour to 16 bits
{
  return ((_font_gfx == GxFont_GFX_TFT_eSPI_font_gfx) ? _GxF_GxFont_GFX_TFT_eSPI.color8to16(color332) : 0);
}
int16_t GxFont_GFX::drawNumber(long long_num, int poX, int poY, int font)
{
  return ((_font_gfx == GxFont_GFX_TFT_eSPI_font_gfx) ? _GxF_GxFont_GFX_TFT_eSPI.drawNumber(long_num, poX, poY, font) : 0);
}
int16_t GxFont_GFX::drawNumber(long long_num, int poX, int poY)
{
  return ((_font_gfx == GxFont_GFX_TFT_eSPI_font_gfx) ? _GxF_GxFont_GFX_TFT_eSPI.drawNumber(long_num, poX, poY) : 0);
}
int16_t GxFont_GFX::drawFloat(float floatNumber, int decimal, int poX, int poY, int font)
{
  return ((_font_gfx == GxFont_GFX_TFT_eSPI_font_gfx) ? _GxF_GxFont_GFX_TFT_eSPI.drawFloat(floatNumber, decimal, poX, poY, font) : 0);
}
int16_t GxFont_GFX::drawFloat(float floatNumber, int decimal, int poX, int poY)
{
  return ((_font_gfx == GxFont_GFX_TFT_eSPI_font_gfx) ? _GxF_GxFont_GFX_TFT_eSPI.drawFloat(floatNumber, decimal, poX, poY) : 0);
}
// Handle char arrays
int16_t GxFont_GFX::drawString(const char *string, int poX, int poY, int font)
{
  return ((_font_gfx == GxFont_GFX_TFT_eSPI_font_gfx) ? _GxF_GxFont_GFX_TFT_eSPI.drawString(string, poX, poY, font) : 0);
}
int16_t GxFont_GFX::drawString(const char *string, int poX, int poY)
{
  return ((_font_gfx == GxFont_GFX_TFT_eSPI_font_gfx) ? _GxF_GxFont_GFX_TFT_eSPI.drawString(string, poX, poY) : 0);
}
// Handle String type
int16_t GxFont_GFX::drawString(const String& string, int poX, int poY, int font)
{
  return ((_font_gfx == GxFont_GFX_TFT_eSPI_font_gfx) ? _GxF_GxFont_GFX_TFT_eSPI.drawString(string, poX, poY, font) : 0);
}
int16_t GxFont_GFX::drawString(const String& string, int poX, int poY)
{
  return ((_font_gfx == GxFont_GFX_TFT_eSPI_font_gfx) ? _GxF_GxFont_GFX_TFT_eSPI.drawString(string, poX, poY) : 0);
}
int16_t GxFont_GFX::textWidth(const char *string, int font)
{
  return ((_font_gfx == GxFont_GFX_TFT_eSPI_font_gfx) ? _GxF_GxFont_GFX_TFT_eSPI.textWidth(string, font) : 0);
}
int16_t GxFont_GFX::textWidth(const char *string)
{
  return ((_font_gfx == GxFont_GFX_TFT_eSPI_font_gfx) ? _GxF_GxFont_GFX_TFT_eSPI.textWidth(string) : 0);
}
int16_t GxFont_GFX::textWidth(const String& string, int font)
{
  return ((_font_gfx == GxFont_GFX_TFT_eSPI_font_gfx) ? _GxF_GxFont_GFX_TFT_eSPI.textWidth(string, font) : 0);
}
int16_t GxFont_GFX::textWidth(const String& string)
{
  return ((_font_gfx == GxFont_GFX_TFT_eSPI_font_gfx) ? _GxF_GxFont_GFX_TFT_eSPI.textWidth(string) : 0);
}
int16_t GxFont_GFX::fontHeight(int16_t font)
{
  return ((_font_gfx == GxFont_GFX_TFT_eSPI_font_gfx) ? _GxF_GxFont_GFX_TFT_eSPI.fontHeight(font) : 0);
}
#endif

