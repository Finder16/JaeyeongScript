#ifndef __JAEYEONG_COLOR_H__
#define __JAEYEONG_COLOR_H__
#include "apua.h"
#include "jstrings.h"

//! @brief 주어진 메시지에 ANSI escape 코드를 사용하여 색상을 적용합니다.
//! 'open'과 'close' 매개변수는 각각 색상을 시작하고 종료하는데 사용되는 ANSI 코드입니다.
//! @copyright Alexander Medvednikov
//! @param msg 색상이 적용될 메시지입니다.
//! @param open 색상을 시작하는 ANSI 코드입니다.
//! @param close 색상을 종료하는 ANSI 코드입니다.
//! @return 색상이 적용된 메시지를 반환합니다.
string color_format(string msg, string open, string close);

//! @brief RGB 값을 사용하여 메시지에 색상을 적용합니다.
//! 이 함수는 주어진 RGB 값과 ANSI escape 코드를 사용하여 메시지에 색상을 적용합니다.
//! 'open'과 'close' 매개변수는 각각 색상을 시작하고 종료하는데 사용되는 ANSI 코드입니다.
//! @copyright Alexander Medvednikov
//! @param r 빨간색 성분의 값입니다 (`0`-`255`).
//! @param g 초록색 성분의 값입니다 (`0`-`255`).
//! @param b 파란색 성분의 값입니다 (`0`-`255`).
//! @param msg 색상이 적용될 메시지입니다.
//! @param open 색상을 시작하는 ANSI 코드입니다.
//! @param close 색상을 종료하는 ANSI 코드입니다.
//! @return 색상이 적용된 메시지를 반환합니다.
string color_format_rgb(int r, int g, int b, string msg, string open, string close);

//! @brief RGB 값을 사용하여 메시지에 색상을 적용합니다.
//! 이 함수는 주어진 RGB 값과 ANSI escape 코드를 사용하여 메시지에 색상을 적용합니다.
//! 본문 안에서 사용된 '38'과 '39'는 각각 전경색을 설정하고 리셋하는데 사용되는 ANSI 코드입니다.
//! @copyright Alexander Medvednikov
//! @see color_format_rgb
//! @param r 빨간색 성분의 값입니다 (`0`-`255`).
//! @param g 초록색 성분의 값입니다 (`0`-`255`).
//! @param b 파란색 성분의 값입니다 (`0`-`255`).
//! @param msg 색상이 적용될 메시지입니다.
//! @return 색상이 적용된 메시지를 반환합니다.
string rgb(int r, int g, int b, string msg);

//! @brief RGB 값을 사용하여 메시지의 배경색을 설정합니다.
//! 이 함수는 주어진 RGB 값과 ANSI escape 코드를 사용하여 메시지의 배경색을 설정합니다.
//! 함수 본문 안에서 사용된 '48'과 '49'는 각각 배경색을 설정하고 리셋하는데 사용되는 ANSI 코드입니다.
//! @copyright Alexander Medvednikov
//! @see color_format_rgb
//! @param r 빨간색 성분의 값입니다 (`0`-`255`).
//! @param g 초록색 성분의 값입니다 (`0`-`255`).
//! @param b 파란색 성분의 값입니다 (`0`-`255`).
//! @param msg 배경색이 적용될 메시지입니다.
//! @return 배경색이 적용된 메시지를 반환합니다.
string bg_rgb(int r, int g, int b, string msg);

//! @brief 16진수 색상 코드를 사용하여 메시지에 색상을 적용합니다.
//! 이 함수는 주어진 16진수 색상 코드와 ANSI escape 코드를 사용하여 메시지에 색상을 적용합니다.
//! 함수 본문 안에서 사용된 '38'과 '39'는 각각 전경색을 설정하고 리셋하는데 사용되는 ANSI 코드입니다.
//! @copyright Alexander Medvednikov
//! @see color_format_rgb
//! @param hex 16진수 색상 코드입니다 (`0xRRGGBB` 형식).
//! @param msg 색상이 적용될 메시지입니다.
//! @return 색상이 적용된 메시지를 반환합니다.
string color_hex(int hex, string msg);

//! @brief 16진수 색상 코드를 사용하여 메시지의 배경색을 설정합니다.
//! 이 함수는 주어진 16진수 색상 코드와 ANSI escape 코드를 사용하여 메시지의 배경색을 설정합니다.
//! 함수 본문 안에서 사용된 '48'과 '49'는 각각 배경색을 설정하고 리셋하는데 사용되는 ANSI 코드입니다.
//! @copyright Alexander Medvednikov
//! @see color_format_rgb
//! @param hex 16진수 색상 코드입니다 (`0xRRGGBB` 형식).
//! @param msg 배경색이 적용될 메시지입니다.
//! @return 배경색이 적용된 메시지를 반환합니다.
string bg_hex(int hex, string msg);

//! @brief 모든 색상을 리셋합니다.
//! @copyright Alexander Medvednikov
//! @param msg 리셋이 적용될 메시지입니다.
//! @return 색상이 리셋된 메시지를 반환합니다.
string color_reset(string msg);

//! @brief 주어진 메시지를 굵게 만듭니다.
//! @param msg 굵게 만들 메시지입니다.
//! @return 굵게 만들어진 메시지를 반환합니다.
string bold(string msg);

//! @brief 주어진 메시지를 밝게 만듭니다.
//! @param msg 밝게 만들 메시지입니다.
//! @return 밝게 만들어진 메시지를 반환합니다.
string dim(string msg);

//! @brief 주어진 메시지에 이탤릭체를 적용합니다
//! @param msg 이탤릭체가 적용될 메시지입니다.
//! @return 이탤릭체가 적용된 메시지를 반환합니다.
string italic(string msg);

//! @brief 주어진 메시지에 언더라인을 적용합니다.
//! @param msg 언더라인이 적용될 메시지입니다.
//! @return 언더라인이 적용된 메시지를 반환합니다.
string underline(string msg);

//! @brief 주어진 메시지에 느린 간격으로 깜빡이는 효과를 적용합니다.
//! @param msg 느린 간격으로 깜빡이는 효과가 적용될 메시지입니다.
//! @return 느린 간격으로 깜빡이는 효과가 적용된 메시지를 반환합니다.
//! @warning 이 기능은 VSCode 내장 터미널을 포함해 일부 터미널에서 지원되지 않을 수 있습니다.
string slow_blink(string msg);

//! @brief 주어진 메시지에 빠른 간격으로 깜빡이는 효과를 적용합니다.
//! @param msg 빠른 간격으로 깜빡이는 효과가 적용될 메시지입니다.
//! @return 빠른 간격으로 깜빡이는 효과가 적용된 메시지를 반환합니다.
//! @warning 이 기능은 VSCode 내장 터미널을 포함해 일부 터미널에서 지원되지 않을 수 있습니다.
string rapid_blink(string msg);

//! @brief 주어진 메시지에 깜빡이는 효과를 적용합니다.
//! @param msg 깜빡이는 효과가 적용될 메시지입니다.
//! @return 깜빡이는 효과가 적용된 메시지를 반환합니다.
//! @warning 이 기능은 VSCode 내장 터미널을 포함해 일부 터미널에서 지원되지 않을 수 있습니다.
string inverse(string msg);

//! @brief 주어진 메시지에 숨김 효과를 적용합니다.
//! @param msg 숨김 효과가 적용될 메시지입니다.
//! @return 숨김 효과가 적용된 메시지를 반환합니다.
string hidden(string msg);

//! @brief 주어진 메시지에 취소선을 적용합니다.
//! @param msg 취소선이 적용될 메시지입니다.
//! @return 취소선이 적용된 메시지를 반환합니다.
string strikethrough(string msg);

//! @brief 주어진 메시지에 검은 색상을 적용합니다.
//! @param msg 검은 색상이 적용될 메시지입니다.
//! @return 검은 색상이 적용된 메시지를 반환합니다.
string black(string msg);

//! @brief 주어진 메시지에 빨간 색상을 적용합니다.
//! @param msg 빨간 색상이 적용될 메시지입니다.
//! @return 빨간 색상이 적용된 메시지를 반환합니다.
string red(string msg);

//! @brief 주어진 메시지에 초록 색상을 적용합니다.
//! @param msg 초록 색상이 적용될 메시지입니다.
//! @return 초록 색상이 적용된 메시지를 반환합니다.
string green(string msg);

//! @brief 주어진 메시지에 노란 색상을 적용합니다.
//! @param msg 노란 색상이 적용될 메시지입니다.
//! @return 노란 색상이 적용된 메시지를 반환합니다.
string yellow(string msg);

//! @brief 주어진 메시지에 파란 색상을 적용합니다.
//! @param msg 파란 색상이 적용될 메시지입니다.
//! @return 파란 색상이 적용된 메시지를 반환합니다.
string blue(string msg);

//! @brief 주어진 메시지에 자홍색 색상을 적용합니다.
//! @param msg 자홍색 색상이 적용될 메시지입니다.
//! @return 자홍색 색상이 적용된 메시지를 반환합니다.
string magenta(string msg);

//! @brief 주어진 메시지에 청록색 색상을 적용합니다.
//! @param msg 청록색 색상이 적용될 메시지입니다.
//! @return 청록색 색상이 적용된 메시지를 반환합니다.
string cyan(string msg);

//! @brief 주어진 메시지에 흰색 색상을 적용합니다.
//! @param msg 흰색 색상이 적용될 메시지입니다.
//! @return 흰색 색상이 적용된 메시지를 반환합니다.
string white(string msg);

//! @brief 주어진 메시지의 배경색을 검은색으로 설정합니다.
//! @param msg 배경색이 적용될 메시지입니다.
//! @return 배경색이 검은색으로 설정된 메시지를 반환합니다.
string bg_black(string msg);

//! @brief 주어진 메시지의 배경색을 빨간색으로 설정합니다.
//! @param msg 배경색이 적용될 메시지입니다.
//! @return 배경색이 빨간색으로 설정된 메시지를 반환합니다.
string bg_red(string msg);

//! @brief 주어진 메시지의 배경색을 초록색으로 설정합니다.
//! @param msg 배경색이 적용될 메시지입니다.
//! @return 배경색이 초록색으로 설정된 메시지를 반환합니다.
string bg_green(string msg);

//! @brief 주어진 메시지의 배경색을 노란색으로 설정합니다.
//! @param msg 배경색이 적용될 메시지입니다.
//! @return 배경색이 노란색으로 설정된 메시지를 반환합니다.
string bg_yellow(string msg);

//! @brief 주어진 메시지의 배경색을 파란색으로 설정합니다.
//! @param msg 배경색이 적용될 메시지입니다.
//! @return 배경색이 파란색으로 설정된 메시지를 반환합니다.
string bg_blue(string msg);

//! @brief 주어진 메시지의 배경색을 자홍색으로 설정합니다.
//! @param msg 배경색이 적용될 메시지입니다.
//! @return 배경색이 자홍색으로 설정된 메시지를 반환합니다.
string bg_magenta(string msg);

//! @brief 주어진 메시지의 배경색을 청록색으로 설정합니다.
//! @param msg 배경색이 적용될 메시지입니다.
//! @return 배경색이 청록색으로 설정된 메시지를 반환합니다.
string bg_cyan(string msg);

//! @brief 주어진 메시지의 배경색을 흰색으로 설정합니다.
//! @param msg 배경색이 적용될 메시지입니다.
//! @return 배경색이 흰색으로 설정된 메시지를 반환합니다.
string bg_white(string msg);

//! @brief 주어진 메시지에 회색 색상을 적용합니다.
//! @param msg 회색 색상이 적용될 메시지입니다.
//! @return 회색 색상이 적용된 메시지를 반환합니다.
string gray(string msg);

//! @brief 주어진 메시지에 밝은 검정 색상을 적용합니다.
//! @param msg 밝은 검정 색상이 적용될 메시지입니다.
//! @return 밝은 검정 색상이 적용된 메시지를 반환합니다.
string bright_black(string msg);

//! @brief 주어진 메시지에 밝은 빨간 색상을 적용합니다.
//! @param msg 밝은 빨간 색상이 적용될 메시지입니다.
//! @return 밝은 빨간 색상이 적용된 메시지를 반환합니다.
string bright_red(string msg);

//! @brief 주어진 메시지에 밝은 초록 색상을 적용합니다.
//! @param msg 밝은 초록 색상이 적용될 메시지입니다.
//! @return 밝은 초록 색상이 적용된 메시지를 반환합니다.
string bright_green(string msg);

//! @brief 주어진 메시지에 밝은 노란 색상을 적용합니다.
//! @param msg 밝은 노란 색상이 적용될 메시지입니다.
//! @return 밝은 노란 색상이 적용된 메시지를 반환합니다.
string bright_yellow(string msg);

//! @brief 주어진 메시지에 밝은 파란 색상을 적용합니다.
//! @param msg 밝은 파란 색상이 적용될 메시지입니다.
//! @return 밝은 파란 색상이 적용된 메시지를 반환합니다.
string bright_blue(string msg);

//! @brief 주어진 메시지에 밝은 자홍색 색상을 적용합니다.
//! @param msg 밝은 자홍색 색상이 적용될 메시지입니다.
//! @return 밝은 자홍색 색상이 적용된 메시지를 반환합니다.
string bright_magenta(string msg);

//! @brief 주어진 메시지에 밝은 청록색 색상을 적용합니다.
//! @param msg 밝은 청록색 색상이 적용될 메시지입니다.
//! @return 밝은 청록색 색상이 적용된 메시지를 반환합니다.
string bright_cyan(string msg);

//! @brief 주어진 메시지에 밝은 흰색 색상을 적용합니다.
//! @param msg 밝은 흰색 색상이 적용될 메시지입니다.
//! @return 밝은 흰색 색상이 적용된 메시지를 반환합니다.
string bright_white(string msg);

//! @brief 주어진 메시지의 배경색을 밝은 검정색으로 설정합니다.
//! @param msg 배경색이 적용될 메시지입니다.
//! @return 배경색이 밝은 검정색으로 설정된 메시지를 반환합니다.
string bright_bg_black(string msg);

//! @brief 주어진 메시지의 배경색을 밝은 빨간색으로 설정합니다.
//! @param msg 배경색이 적용될 메시지입니다.
//! @return 배경색이 밝은 빨간색으로 설정된 메시지를 반환합니다.
string bright_bg_red(string msg);

//! @brief 주어진 메시지의 배경색을 밝은 초록색으로 설정합니다.
//! @param msg 배경색이 적용될 메시지입니다.
//! @return 배경색이 밝은 초록색으로 설정된 메시지를 반환합니다.
string bright_bg_green(string msg);

//! @brief 주어진 메시지의 배경색을 밝은 노란색으로 설정합니다.
//! @param msg 배경색이 적용될 메시지입니다.
//! @return 배경색이 밝은 노란색으로 설정된 메시지를 반환합니다.
string bright_bg_yellow(string msg);

//! @brief 주어진 메시지의 배경색을 밝은 파란색으로 설정합니다.
//! @param msg 배경색이 적용될 메시지입니다.
//! @return 배경색이 밝은 파란색으로 설정된 메시지를 반환합니다.
string bright_bg_blue(string msg);

//! @brief 주어진 메시지의 배경색을 밝은 자홍색으로 설정합니다.
//! @param msg 배경색이 적용될 메시지입니다.
//! @return 배경색이 밝은 자홍색으로 설정된 메시지를 반환합니다.
string bright_bg_magenta(string msg);

//! @brief 주어진 메시지의 배경색을 밝은 청록색으로 설정합니다.
//! @param msg 배경색이 적용될 메시지입니다.
//! @return 배경색이 밝은 청록색으로 설정된 메시지를 반환합니다.
string bright_bg_cyan(string msg);

//! @brief 주어진 메시지의 배경색을 밝은 흰색으로 설정합니다.
//! @param msg 배경색이 적용될 메시지입니다.
//! @return 배경색이 밝은 흰색으로 설정된 메시지를 반환합니다.
string bright_bg_white(string msg);
#endif /* __JAEYEONG_COLOR_H__ */