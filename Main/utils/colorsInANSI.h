#pragma once
#ifndef CALCULATOR__UTILS__COLORSINANSI_H__
#define CALCULATOR__UTILS__COLORSINANSI_H__

#include "header.h"

#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

_CALCULATOR_UTILS_BEGIN

#ifdef _WIN32
inline int enableTheColorfulInANSI(bool enableValue)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hConsole, &mode);
    if (enableValue) mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    else             mode &= ~ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hConsole, mode);
    return 0;
}
#else
inline int enableTheColorfulInANSI(bool /*enableValue*/)
{
    return 0;
}
#endif

_CALCULATOR_UTILS_END

#define _GRAY   "\033[90m"
#define _RED    "\033[91m"
#define _GREEN  "\033[92m"
#define _YELLOW "\033[93m"
#define _BLUE   "\033[94m"
#define _PURPLE "\033[95m"
#define _CYAN   "\033[96m"
#define _WHITE  "\033[97m"

#define _RESET  "\033[0m"
#define _DEFAULT "\033[0m"

#define _GRAY_(m)   (_GRAY   m _RESET)
#define _RED_(m)    (_RED    m _RESET)
#define _GREEN_(m)  (_GREEN  m _RESET)
#define _YELLOW_(m) (_YELLOW m _RESET)
#define _BLUE_(m)   (_BLUE   m _RESET)
#define _PURPLE_(m) (_PURPLE m _RESET)
#define _CYAN_(m)   (_CYAN   m _RESET)
#define _WHITE_(m)  (_WHITE  m _RESET)


#endif // !CALCULATOR__UTILS__COLORSINANSI_H__
