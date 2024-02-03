#include <stdio.h>
#include <stdlib.h>
#include "jaeyeong.h"

string color_format(string msg, string open, string close) {
  string ret = str_intp(4, _MOV((StrIntpData[]){{_SLIT("\033["), 0x10, {.d_s = open}}, {_SLIT("m"), 0x10, {.d_s = msg}}, {_SLIT("\033["), 0x10, {.d_s = close}}, {_SLIT("m"), 0, { .d_c = 0 }}}));
  return ret;
}

string color_format_rgb(int r, int g, int b, string msg, string open, string close) {
  string ret =  str_intp(7, _MOV((StrIntpData[]){{_SLIT("\033["), 0x10, {.d_s = open}}, {_SLIT(";2;"), 0x7, {.d_i32 = r}}, {_SLIT(";"), 0x7, {.d_i32 = g}}, {_SLIT(";"), 0x7, {.d_i32 = b}}, {_SLIT("m"), 0x10, {.d_s = msg}}, {_SLIT("\033["), 0x10, {.d_s = close}}, {_SLIT("m"), 0, { .d_c = 0 }}}));
  return ret;
}

string rgb(int r, int g, int b, string msg) {
  string ret = color_format_rgb(r, g, b, msg, _SLIT("38"), _SLIT("39"));
  return ret;
}

string bg_rgb(int r, int g, int b, string msg) {
  string ret = color_format_rgb(r, g, b, msg, _SLIT("48"), _SLIT("49"));
  return ret;
}

string color_hex(int hex, string msg) {
  string ret = color_format_rgb((hex >> 16), ((hex >> 8) & 0xFF), (hex & 0xFF), msg, _SLIT("38"), _SLIT("39"));
  return ret;
}

string bg_hex(int hex, string msg) {
  string ret = color_format_rgb((hex >> 16), ((hex >> 8) & 0xFF), (hex & 0xFF), msg, _SLIT("48"), _SLIT("49"));
  return ret;
}

string color_reset(string msg) {
  string ret = color_format(msg, _SLIT("0"), _SLIT("0"));
  return ret;
}

string bold(string msg) {
  string ret = color_format(msg, _SLIT("1"), _SLIT("22"));
  return ret;
}

string dim(string msg) {
  string ret = color_format(msg, _SLIT("2"), _SLIT("22"));
  return ret;
}

string italic(string msg) {
  string ret = color_format(msg, _SLIT("3"), _SLIT("23"));
  return ret;
}

string underline(string msg) {
  string ret = color_format(msg, _SLIT("4"), _SLIT("24"));
  return ret;
}

string slow_blink(string msg) {
  string ret = color_format(msg, _SLIT("5"), _SLIT("25"));
  return ret;
}

string rapid_blink(string msg) {
  string ret = color_format(msg, _SLIT("6"), _SLIT("26"));
  return ret;
}

string inverse(string msg) {
  string ret = color_format(msg, _SLIT("7"), _SLIT("27"));
  return ret;
}

string hidden(string msg) {
  string ret = color_format(msg, _SLIT("8"), _SLIT("28"));
  return ret;
}

string strikethrough(string msg) {
  string ret = color_format(msg, _SLIT("9"), _SLIT("29"));
  return ret;
}

string black(string msg) {
  string ret = color_format(msg, _SLIT("30"), _SLIT("39"));
  return ret;
}

string red(string msg) {
  string ret = color_format(msg, _SLIT("31"), _SLIT("39"));
  return ret;
}

string green(string msg) {
  string ret = color_format(msg, _SLIT("32"), _SLIT("39"));
  return ret;
}

string yellow(string msg) {
  string ret = color_format(msg, _SLIT("33"), _SLIT("39"));
  return ret;
}

string blue(string msg) {
  string ret = color_format(msg, _SLIT("34"), _SLIT("39"));
  return ret;
}

string magenta(string msg) {
  string ret = color_format(msg, _SLIT("35"), _SLIT("39"));
  return ret;
}

string cyan(string msg) {
  string ret = color_format(msg, _SLIT("36"), _SLIT("39"));
  return ret;
}

string white(string msg) {
  string ret = color_format(msg, _SLIT("37"), _SLIT("39"));
  return ret;
}

string bg_black(string msg) {
  string ret = color_format(msg, _SLIT("40"), _SLIT("49"));
  return ret;
}

string bg_red(string msg) {
  string ret = color_format(msg, _SLIT("41"), _SLIT("49"));
  return ret;
}

string bg_green(string msg) {
  string ret = color_format(msg, _SLIT("42"), _SLIT("49"));
  return ret;
}

string bg_yellow(string msg) {
  string ret = color_format(msg, _SLIT("43"), _SLIT("49"));
  return ret;
}

string bg_blue(string msg) {
  string ret = color_format(msg, _SLIT("44"), _SLIT("49"));
  return ret;
}

string bg_magenta(string msg) {
  string ret = color_format(msg, _SLIT("45"), _SLIT("49"));
  return ret;
}

string bg_cyan(string msg) {
  string ret = color_format(msg, _SLIT("46"), _SLIT("49"));
  return ret;
}

string bg_white(string msg) {
  string ret = color_format(msg, _SLIT("47"), _SLIT("49"));
  return ret;
}

string gray(string msg) {
  string ret = bright_black(msg);
  return ret;
}

string bright_black(string msg) {
  string ret = color_format(msg, _SLIT("90"), _SLIT("39"));
  return ret;
}

string bright_red(string msg) {
  string ret = color_format(msg, _SLIT("91"), _SLIT("39"));
  return ret;
}

string bright_green(string msg) {
  string ret = color_format(msg, _SLIT("92"), _SLIT("39"));
  return ret;
}

string bright_yellow(string msg) {
  string ret = color_format(msg, _SLIT("93"), _SLIT("39"));
  return ret;
}

string bright_blue(string msg) {
  string ret = color_format(msg, _SLIT("94"), _SLIT("39"));
  return ret;
}

string bright_magenta(string msg) {
  string ret = color_format(msg, _SLIT("95"), _SLIT("39"));
  return ret;
}

string bright_cyan(string msg) {
  string ret = color_format(msg, _SLIT("96"), _SLIT("39"));
  return ret;
}

string bright_white(string msg) {
  string ret = color_format(msg, _SLIT("97"), _SLIT("39"));
  return ret;
}

string bright_bg_black(string msg) {
  string ret = color_format(msg, _SLIT("100"), _SLIT("49"));
  return ret;
}

string bright_bg_red(string msg) {
  string ret = color_format(msg, _SLIT("101"), _SLIT("49"));
  return ret;
}

string bright_bg_green(string msg) {
  string ret = color_format(msg, _SLIT("102"), _SLIT("49"));
  return ret;
}

string bright_bg_yellow(string msg) {
  string ret = color_format(msg, _SLIT("103"), _SLIT("49"));
  return ret;
}

string bright_bg_blue(string msg) {
  string ret = color_format(msg, _SLIT("104"), _SLIT("49"));
  return ret;
}

string bright_bg_magenta(string msg) {
  string ret = color_format(msg, _SLIT("105"), _SLIT("49"));
  return ret;
}

string bright_bg_cyan(string msg) {
  string ret = color_format(msg, _SLIT("106"), _SLIT("49"));
  return ret;
}

string bright_bg_white(string msg) {
  string ret = color_format(msg, _SLIT("107"), _SLIT("49"));
  return ret;
}