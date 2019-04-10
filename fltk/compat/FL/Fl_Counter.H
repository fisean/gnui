#ifndef Fl_Counter_H
#define Fl_Counter_H

#include <fltk/ValueInput.h>
class Fl_Counter : public gnui::ValueInput {
public:
  Fl_Counter(int x, int y, int w, int h, const char* l = 0)
    : gnui::ValueInput(x,y,w,h,l) {align(gnui::ALIGN_BOTTOM);}
};

// these don't do anything:
#define FL_NORMAL_COUNTER	0
#define FL_SIMPLE_COUNTER	1

#endif
