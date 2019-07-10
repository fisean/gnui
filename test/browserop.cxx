//
// "$Id$"
//
// Browser operation test program for the Fast Light Tool Kit (FLTK).
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

#include "forms.h"

GNUI_FORM *form;
GNUI_OBJECT *browserobj, *inputobj, *exitobj;

void addit(GNUI_OBJECT *, long)
{
  /* append and show the last line. Don't use this if you just want
   * to add some lines. use gnui_add_browser_line
   */
  gnui_addto_browser(browserobj,gnui_get_input(inputobj));
}

void insertit(GNUI_OBJECT *, long)
{
  int n;
  if (! ( n = gnui_get_browser(browserobj))) return;
  gnui_insert_browser_line(browserobj,n,gnui_get_input(inputobj));
}

void replaceit(GNUI_OBJECT *, long)
{
  int n;
  if (! (n=gnui_get_browser(browserobj))) return;
  gnui_replace_browser_line(browserobj,n,gnui_get_input(inputobj));
}

void deleteit(GNUI_OBJECT *, long)
{
  int n;
  if (! (n = gnui_get_browser(browserobj))) return;
  gnui_delete_browser_line(browserobj,n);
}

void clearit(GNUI_OBJECT *, long)
{
  gnui_clear_browser(browserobj);
}

/*---------------------------------------*/

void create_form(void)
{
  GNUI_OBJECT *obj;

  form = gnui_bgn_form(GNUI_UP_BOX,390,420);
  browserobj = gnui_add_browser(GNUI_HOLD_BROWSER,20,20,210,330,"");
//  gnui_set_object_dblbuffer(browserobj, 1);
  inputobj = obj = gnui_add_input(GNUI_NORMAL_INPUT,20,370,210,30,"");
    gnui_set_object_callback(obj,addit,0);
    obj->when(GNUI_WHEN_ENTER_KEY|GNUI_WHEN_NOT_CHANGED);
  obj = gnui_add_button(GNUI_NORMAL_BUTTON,250,20,120,30,"Add");
    gnui_set_object_callback(obj,addit,0);
  obj = gnui_add_button(GNUI_NORMAL_BUTTON,250,60,120,30,"Insert");
    gnui_set_object_callback(obj,insertit,0);
  obj = gnui_add_button(GNUI_NORMAL_BUTTON,250,100,120,30,"Replace");
    gnui_set_object_callback(obj,replaceit,0);
  obj = gnui_add_button(GNUI_NORMAL_BUTTON,250,160,120,30,"Delete");
    gnui_set_object_callback(obj,deleteit,0);
  obj = gnui_add_button(GNUI_NORMAL_BUTTON,250,200,120,30,"Clear");
    gnui_set_object_callback(obj,clearit,0);
  exitobj = gnui_add_button(GNUI_NORMAL_BUTTON,250,370,120,30,"Exit");
  gnui_end_form();
}

/*---------------------------------------*/

int
main(int argc, char *argv[])
{
  GNUI_OBJECT *obj;

  gnui_initialize(&argc, argv, "FormDemo", 0, 0);
  create_form();
  gnui_show_form(form,GNUI_PLACE_CENTER,GNUI_TRANSIENT,"Browser Op");
  do obj = gnui_do_forms(); while (obj != exitobj);
  gnui_hide_form(form);
  return 0;
}

//
// End of "$Id$".
//
