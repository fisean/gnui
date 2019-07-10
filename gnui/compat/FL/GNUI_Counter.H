#ifndef GNUI_Counter_H
#define GNUI_Counter_H

#include <gnui/ValueInput.h>
class GNUI_Counter : public gnui::ValueInput {
public:
  GNUI_Counter(int x, int y, int w, int h, const char* l = 0)
    : gnui::ValueInput(x,y,w,h,l) {align(gnui::ALIGN_BOTTOM);}
};

// these don't do anything:
#define GNUI_NORMAL_COUNTER	0
#define GNUI_SIMPLE_COUNTER	1

#endif
