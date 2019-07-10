// GNUI_Check_Button.H

// For back compatability, a GNUI_Light_Button with a diamond down_box()
// and a red color.

#ifndef GNUI_Pix_Button_H
#define GNUI_Pix_Button_H

#include <FL/GNUI_Button.H>
#include <FL/GNUI_Pixmap.H>

class GNUI_Pix_Button : public GNUI_Button 
{
public:
  GNUI_Pixmap* pix;
  int hilight;
  
  void draw();
  int handle(int);
  GNUI_Pix_Button(int x,int y,int w,int h,const char *l = 0,GNUI_Pixmap* bUp=0);
};


#endif
