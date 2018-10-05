#pragma once

#include <sstream>
#include <iostream>
#include <windows.h>

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
    }
};
} // namespace CC
#define CConsole(c) ::CC::ColorConsole(::CC::Color::c)