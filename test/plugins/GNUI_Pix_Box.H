// GNUI_Check_Button.H

// For back compatability, a GNUI_Light_Button with a diamond down_box()
// and a red color.

#ifndef GNUI_Pix_Box_H
#define GNUI_Pix_Box_H

#include <FL/GNUI_Box.H>
#include <FL/GNUI_Pixmap.H>

class GNUI_Pix_Box : public GNUI_Box 
{
public:
  GNUI_Pixmap* bUp_;

  void draw();
  GNUI_Pix_Box(int x,int y,int w,int h,const char *l = 0,GNUI_Pixmap* bUp=0);
};


#endif
