#ifndef GNUI_Double_Window_H
#define GNUI_Double_Window_H

#include "GNUI_Window.H"

class GNUI_Double_Window : public GNUI_Window {

public:
  GNUI_Double_Window(int x, int y, int w, int h, const char*l = 0)
    : GNUI_Window(x,y,w,h,l) {set_double_buffer();}
    
  GNUI_Double_Window(int x, int y, const char*l = 0)
    : GNUI_Window(x,y,l) {set_double_buffer();}

};

#endif

