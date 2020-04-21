#pragma once
#include <string>
#include <gnui/display.h>


namespace gnui
{
class Engine
{
  public:
    static void init();
    static int run(const std::string &displayName = "");
}; // Engine
} // namespace
