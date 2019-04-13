#ifndef Fl_Window_H
#define Fl_Window_H

#include "Fl_Group.H"
#include <gnui/Window.h>

class Fl_Window : public gnui::Window {

public:
  Fl_Window(int x, int y, int w, int h, const char*l = 0)
    : gnui::Window(x,y,w,h,l) {begin();}
    
  Fl_Window(int x, int y, const char*l = 0)
    : gnui::Window(x,y,l) {begin();}

  void border(bool v) {
    if (!v) clear_border(); // set_border does not work
  }
};

#endif

