#ifndef GNUI_Toggle_Button_H
#define GNUI_Toggle_Button_H

#include "GNUI_Button.H"

class GNUI_Toggle_Button : public GNUI_Button {
public:
    GNUI_Toggle_Button(int X,int Y,int W,int H,const char *l=0)
	: GNUI_Button(X,Y,W,H,l) {type(GNUI_TOGGLE_BUTTON);}
};

#endif
