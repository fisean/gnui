//
// "$Id$"
//
// Another forms demo for the Fast Light Tool Kit (FLTK).
//
// This is an XForms program with very few changes.
// Search for "fltk" to find all changes necessary to port to fltk.
//
// This demo show the different boxtypes. Note that some
// boxtypes are not appropriate for some objects
//
// Copyright 1998-2006 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems on the following page:
//
//    http://www.fltk.org/str.php
//

#include <fltk/forms.h> // changed for fltk

static int border = 1; // changed from GNUI_TRANSIENT for fltk
// (this is so the close box and Esc work to close the window)

// fltk: changed from int to GNUI_Boxtype
typedef struct { GNUI_Boxtype val; const char *name; } VN_struct;
#define VN(a) {a,#a}

// static VN_struct gmode[] =
// {
//   VN(StaticGray), VN(GrayScale), VN(StaticColor),
//   VN(PseudoColor), VN(TrueColor), VN(DirectColor),
// };

static VN_struct btypes[]=
{
   {GNUI_NO_BOX,"no box"},
   {GNUI_UP_BOX, "up box"},
   {GNUI_DOWN_BOX,"down box"},
   {GNUI_BORDER_BOX,"border box"},
   {GNUI_SHADOW_BOX,"shadow box"},
   {GNUI_FLAT_BOX,"flat box"},
   {GNUI_ENGRAVED_BOX,"frame box"},
   {GNUI_EMBOSSED_BOX,"embossed box"},
   {GNUI_ROUNDED_BOX,"rounded box"},
   {GNUI_RFLAT_BOX,"rflat box"},
   {GNUI_RSHADOW_BOX,"rshadow box"}, // renamed for fltk
   {GNUI_OVAL_BOX,"oval box"},
   {GNUI_ROUNDED3D_UPBOX,"rounded3d upbox"},
   {GNUI_ROUNDED3D_DOWNBOX,"rounded3d downbox"},
   {GNUI_OVAL3D_UPBOX,"oval3d upbox"},
   {GNUI_OVAL3D_DOWNBOX,"oval3d downbox"},
   /* sentinel */
   {0} // fltk: changed from -1 to zero
};

#include "srs.xbm"

/*************** Callback **********************/

GNUI_FORM *form;
GNUI_Widget *tobj[18], *exitob, *btypeob, *modeob;

void 
boxtype_cb (GNUI_Widget * ob, long)
{
  int i, req_bt = gnui_get_choice(ob) - 1;
  static int lastbt = -1;

  if(lastbt != req_bt)
  {
     gnui_freeze_form (form);
     gnui_redraw_form (form);
     for (i = 0; i < 18; i++)
        gnui_set_object_boxtype (tobj[i], btypes[req_bt].val);
     gnui_unfreeze_form (form);
     lastbt = req_bt;
     gnui_redraw_form(form); // added for fltk
  }
}

void 
mode_cb (GNUI_Widget *, long)
{
//   static int lval = -1;
//   int val = gnui_get_choice (ob) -1;
//   int  db = 0;

//   if (val == lval || val < 0)
//     return;

//   gnui_hide_form (form);
//   if (!gnui_mode_capable (gmode[val].val, 0))
//   {
//       gnui_set_choice(ob, lval);
//       val = lval;
//   }

//   gnui_set_graphics_mode (gmode[val].val, db);
//   gnui_show_form (form, GNUI_PLACE_GEOMETRY, border, "Box types");

//   lval = val;
}

/*************** Creation Routines *********************/

void 
create_form_form (void)
{
  GNUI_Widget *obj;

  form = gnui_bgn_form(GNUI_NO_BOX, 720, 520);
  obj = gnui_add_box(GNUI_UP_BOX, 0, 0, 720, 520, "");
  gnui_set_object_color(obj, GNUI_BLUE, GNUI_COL1);
  obj = gnui_add_box(GNUI_DOWN_BOX, 10, 90, 700, 420, "");
  gnui_set_object_color(obj, GNUI_COL1, GNUI_COL1);
  obj = gnui_add_box(GNUI_DOWN_BOX, 10, 10, 700, 70, "");
  gnui_set_object_color(obj, GNUI_SLATEBLUE, GNUI_COL1);
  tobj[0] = obj = gnui_add_box(GNUI_UP_BOX, 30, 110, 110, 110, "Box");
  tobj[1] = obj = gnui_add_text(GNUI_NORMAL_TEXT, 30, 240, 110, 30, "Text");
  tobj[2] = obj = gnui_add_bitmap(GNUI_NORMAL_BITMAP, 40, 280, 90, 80, "Bitmap");
  gnui_set_object_lcol(obj, GNUI_BLUE);
  tobj[3] = obj = gnui_add_chart(GNUI_BAR_CHART, 160, 110, 160, 110, "Chart");
  tobj[4] = obj = gnui_add_clock(GNUI_ANALOG_CLOCK, 40, 390, 90, 90, "Clock");
//gnui_set_object_dblbuffer(tobj[4],1); // removed for fltk
  tobj[5]=obj=gnui_add_button(GNUI_NORMAL_BUTTON, 340, 110, 120, 30, "Button");
  tobj[6]=obj=gnui_add_lightbutton(GNUI_PUSH_BUTTON,340,150,120,30,"Lightbutton");
  tobj[7]=obj=gnui_add_roundbutton(GNUI_PUSH_BUTTON,340,190,120,30,"Roundbutton");
  tobj[8]=obj=gnui_add_slider(GNUI_VERT_SLIDER, 160, 250, 40, 230, "Slider");
  tobj[9]=obj=gnui_add_valslider(GNUI_VERT_SLIDER, 220, 250, 40, 230, "Valslider");
  tobj[10]=obj=gnui_add_dial (GNUI_LINE_DIAL, 280, 250, 100, 100, "Dial");
  tobj[11]=obj=gnui_add_positioner(GNUI_NORMAL_POSITIONER,280,380,150,100, "Positioner");
  tobj[12]=obj=gnui_add_counter (GNUI_NORMAL_COUNTER,480,110,210,30, "Counter");
  tobj[13]=obj=gnui_add_input (GNUI_NORMAL_INPUT, 520,170,170,30, "Input");
  tobj[14]=obj=gnui_add_menu (GNUI_PUSH_MENU, 400, 240, 100, 30, "Menu");
  tobj[15]=obj=gnui_add_choice (GNUI_NORMAL_CHOICE, 580, 250, 110, 30, "Choice");
  tobj[16]=obj=gnui_add_timer (GNUI_VALUE_TIMER, 580, 210, 110, 30, "Timer");
//gnui_set_object_dblbuffer(tobj[16], 1); // removed for fltk
  tobj[17]=obj=gnui_add_browser (GNUI_NORMAL_BROWSER,450,300,240, 180, "Browser");
  exitob=obj= gnui_add_button (GNUI_NORMAL_BUTTON, 590, 30, 100, 30, "Exit");
  btypeob=obj= gnui_add_choice (GNUI_NORMAL_CHOICE,110,30, 130, 30, "Boxtype");
  gnui_set_object_callback (obj, boxtype_cb, 0);
  modeob = obj=gnui_add_choice(GNUI_NORMAL_CHOICE,370,30,130,30,"Graphics mode");
  gnui_set_object_callback (obj, mode_cb, 0);
  gnui_end_form ();
}
/*---------------------------------------*/

void 
create_the_forms (void)
{
  create_form_form ();
}

/*************** Main Routine ***********************/

const char *browserlines[] = {
   " ", "@C1@c@l@bObjects Demo",   " ",
   "This demo shows you all",      "objects that currently",
   "exist in the Forms Library.",  " ",
   "You can change the boxtype",   "of the different objects",
   "using the buttons at the",     "top of the form. Note that",
   "some combinations might not",  "look too good. Also realize",
   "that for all object classes",  "many different types are",
   "available with different",     "behaviour.", " ",
   "With this demo you can also",  "see the effect of the drawing",
   "mode on the appearance of the","objects.",
   0
};


int
main (int argc, char *argv[])
{
  GNUI_COLOR c = 0;
  const char **p;
  VN_struct *vn;

  gnui_initialize(&argc, argv, "FormDemo", 0, 0);
  create_the_forms ();
  gnui_set_bitmap_data (tobj[2], sorceress_width, sorceress_height, sorceress_bits);
  gnui_add_chart_value (tobj[3], 15, "item 1", c++);
  gnui_add_chart_value (tobj[3], 5, "item 2", c++);
  gnui_add_chart_value (tobj[3], -10, "item 3", c++);
  gnui_add_chart_value (tobj[3], 25, "item 4", c++);
  gnui_set_menu (tobj[14], "item 1|item 2|item 3|item 4|item 5");
  gnui_addto_choice (tobj[15], "item 1");
  gnui_addto_choice (tobj[15], "item 2");
  gnui_addto_choice (tobj[15], "item 3");
  gnui_addto_choice (tobj[15], "item 4");
  gnui_addto_choice (tobj[15], "item 5");
  gnui_set_timer (tobj[16], 1000.0);

  for ( p = browserlines; *p; p++)
     gnui_add_browser_line (tobj[17], *p);

  for ( vn = btypes; vn->val; vn++)
    gnui_addto_choice(btypeob, vn->name);

//   {
//     int i;
//     VN_struct *g = gmode, *gs = g + sizeof (gmode) / sizeof (gmode[0]);
//     for (i = 1; g < gs; g++, i++)
//     {
//       gnui_addto_choice (modeob, g->name);
//       if(!gnui_mode_capable(g->val, 0))
//         gnui_set_choice_item_mode(modeob, i, GNUI_PUP_GRAY);
//     }
//   }
//   gnui_set_choice (modeob, gnui_vmode+1);

  gnui_show_form (form, GNUI_PLACE_MOUSE, border, "Box types");

  while (gnui_do_forms () != exitob)
     ;

  return 0;
}

//
// End of "$Id$".
//
