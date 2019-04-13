// This class is provided for back compatability only with some gnui.0
// versions. You can turn on double buffering on a normal window if
// you want it.
  
#ifndef gnui_DoubleBufferWindow_h
#define gnui_DoubleBufferWindow_h

#ifndef gnui_Window_h
# include "Window.h"
#endif

namespace gnui {

class DoubleBufferWindow : public Window {

public:
  DoubleBufferWindow(int x, int y, int w, int h, const char*l = 0)
    : Window(x,y,w,h,l) {set_double_buffer();}
    
  DoubleBufferWindow(int w, int h, const char*l = 0)
    : Window(w,h,l) {set_double_buffer();}

};

}

#endif
