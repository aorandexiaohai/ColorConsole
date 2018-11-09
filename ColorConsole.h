#pragma once

#include <sstream>
#include <iostream>
#if defined(WIN32) || defined(_WIN32)
#include <windows.h>
#endif

namespace CC
{
enum Color
{
    RED = 0xFF0000,
    GREEN = 0x00FF00,
    BLUE = 0x0000FF,
    WHITE = 0xFFFFFF,
    BLACK = 0x000000
};

// red=     "\e[0;31m"
// RED=     "\e[1;31m"
// blue=    "\e[0;34m"
// BLUE=    "\e[1;34m"
// cyan=    "\e[0;36m"
// CYAN=    "\e[1;36m"
// green=   "\e[0;32m"
// GREEN=   "\e[1;32m"
// yellow=  "\e[0;33m"
// YELLOW=  "\e[1;33m"
// NC=      "\e[0m"

class ColorConsole : public std::stringstream
{
  private:
    Color color;

  public:
    ColorConsole(Color c = WHITE)
    {
        color = c;
    }
    ~ColorConsole()
    {
        #if defined(WIN32) || defined(_WIN32)
        HANDLE handle;
        handle = GetStdHandle(STD_OUTPUT_HANDLE);
        if (color == RED)
        {
            SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
        }
        else if (color == GREEN)
            SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
        else if (color == BLUE)
            SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
        else
            SetConsoleTextAttribute(handle,  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        std::cout << this->rdbuf();
        std::cout.flush();
        //reback to old color
        SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        #else
        //linux
        if (color == RED)
        {
            std::cout << "\e[1;31m";
        }
        else if(color == GREEN)
        {
            std::cout << "\e[0;32m";
        }
        else if(color == BLUE)
        {
            std::cout << "\e[1;34m";
        }
        std::cout << this->rdbuf();
        std::cout.flush();
        
        std::cout << "\e[0m";
        #endif
    }
};
} // namespace CC
#define CConsole(c) ::CC::ColorConsole(::CC::Color::c)

#define CCRED CConsole(RED)
#define CCGREEN CConsole(GREEN)
#define CCBLUE CConsole(BLUE)
#define CCWHITE CConsole(WHITE)
#define CCONSOLE(c) CConsole(c)
