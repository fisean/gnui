#ifndef GNUI_Window_H
#define GNUI_Window_H

#include "GNUI_Group.H"
#include <gnui/Window.h>

class GNUI_Window : public gnui::Window {

public:
  GNUI_Window(int x, int y, int w, int h, const char*l = 0)
    : gnui::Window(x,y,w,h,l) {begin();}
    
  GNUI_Window(int x, int y, const char*l = 0)
    : gnui::Window(x,y,l) {begin();}

  void border(bool v) {
    if (!v) clear_border(); // set_border does not work
  }
};

#endif

