//
// "$Id$"
//
// Font demo program for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2003 by Bill Spitzak and others.
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

#include <fltk/run.h>
#include <fltk/Window.h>
#include <fltk/Browser.h>
#include <fltk/CheckButton.h>
#include <fltk/draw.h>
#include <fltk/Font.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

gnui::Window *form;

class FontDisplay : public gnui::Widget {
  void draw();
public:
  gnui::Font* font; float size; const char* encoding;
  FontDisplay(gnui::Box* B, int X, int Y, int W, int H, const char* L = 0) :
    gnui::Widget(X,Y,W,H,L) {box(B); font = 0; size = 14.0f;}
};

gnui::Widget* id_box;

void FontDisplay::draw() {
  draw_box();
  gnui::push_clip(2,2,w()-4,h()-4);
  const char* saved_encoding = gnui::get_encoding();
  gnui::set_encoding(encoding);
  gnui::setfont(font, size);
  id_box->label(gnui::Font::current_name());
  id_box->redraw();
  gnui::setcolor(gnui::BLACK);
  char buffer[32];
  for (int Y = 1; Y < 8; Y++) {
    for (int X = 0; X < 32; X++) buffer[X] = (32*Y+X);
    gnui::drawtext(buffer, 32, 3, 3+(size+leading())*Y);
  }
  gnui::set_encoding(saved_encoding);
  gnui::pop_clip();
}

FontDisplay *textobj;

gnui::Browser *fontobj, *sizeobj, *encobj;

gnui::Font** fonts; // list returned by fltk

gnui::Group *button_group;
gnui::CheckButton* bold_button, *italic_button;

float pickedsize = 14.0f;

void font_cb(gnui::Widget *, long) {
  int fn = fontobj->value();
//printf("font: %d    name: %s   bigname: %s\n", fn, fonts[fn]->name(), fonts[fn]->system_name());

  gnui::Font* f = fonts[fn];
  if (f->bold() == f) bold_button->deactivate();
  else bold_button->activate();
  if (f->italic() == f) italic_button->deactivate();
  else italic_button->activate();
  if (bold_button->value()) f = f->bold();
  if (italic_button->value()) f = f->italic();
  textobj->font = f;

  char saved[30];
  if (textobj->encoding)
    strncpy(saved, textobj->encoding, 29);
  else
    saved[0] = 0;
  encobj->clear();
  const char** encodings; int ne = f->encodings(encodings);
  int picked = -1;
  int iso8859 = 0;
  for (int i = 0; i < ne; i++) {
    encobj->add(encodings[i]);
    if (!strcmp(encodings[i], saved)) picked = i;
    if (!strcmp(encodings[i], gnui::get_encoding())) iso8859 = i;
  }
  if (picked < 0) picked = iso8859;
  textobj->encoding = encodings[picked];
  encobj->value(picked);

  sizeobj->clear();
  int *s; int n = f->sizes(s);
  if (!n) {
    // no sizes (this only happens on X)
    gnui::setfont(f, pickedsize);
    textobj->size = gnui::getsize();
  } else /*if (s[0] == 0)*/ {
    // many sizes;
    int j = 1;
    for (int i = s[0]?0:1; i<64 || i<s[n-1]; i++) {
      char buf[20];
      if (j < n && i==s[j]) {sprintf(buf,"@b;%d",i); j++;}
      else sprintf(buf,"%d",i);
      sizeobj->add(buf);
    }
    sizeobj->value(int(pickedsize-1));
    textobj->size = pickedsize;
    /*  } else {
    // some sizes
    int w = 0;
    for (int i = 0; i < n; i++) {
      if (s[i]<=pickedsize) w = i;
      char buf[20];
      sprintf(buf,"@b;%d",s[i]);
      sizeobj->add(buf);
    }
    sizeobj->value(w);
    textobj->size = s[w]; */
  }
  encobj->redraw();
  sizeobj->redraw();
  textobj->redraw();
  button_group->redraw();
}

void encoding_cb(gnui::Widget *, long) {
  int i = encobj->value();
  if (i < 0)
     return;
  textobj->encoding = encobj->child(i)->label();
  textobj->redraw();
}

void size_cb(gnui::Widget *, long) {
  int i = sizeobj->value();
  if (i < 0) 
     return;
  const char *c = sizeobj->child(i)->label();
  while (*c < '0' || *c > '9') c++;
  pickedsize = (float) atoi(c);
  textobj->size = pickedsize;
  textobj->redraw();
}

void create_the_forms() {
  form = new gnui::Window(550,390);
  form->set_double_buffer();
  form->begin();
  id_box = new gnui::Widget(10, 172, 530, 15);
  id_box->box(gnui::ENGRAVED_BOX);
  id_box->labelsize(10);
  id_box->labelfont(gnui::COURIER);
  id_box->set_flag(gnui::ALIGN_INSIDE|gnui::ALIGN_CLIP|gnui::ALIGN_LEFT);
  textobj = new FontDisplay(gnui::ENGRAVED_BOX,10,10,530,160);
  textobj->clear_flag(gnui::ALIGN_MASK);
  textobj->set_flag(gnui::ALIGN_TOP|gnui::ALIGN_LEFT|gnui::ALIGN_INSIDE|gnui::ALIGN_CLIP);
  button_group = new gnui::Group(10, 190, 140, 20);
  button_group->begin();
  bold_button = new gnui::CheckButton(0, 0, 70, 20, "Bold");
  bold_button->labelfont(bold_button->labelfont()->bold());
  bold_button->callback(font_cb, 1);
  italic_button = new gnui::CheckButton(70, 0, 70, 20, "Italic");
  italic_button->labelfont(italic_button->labelfont()->italic());
  italic_button->callback(font_cb, 1);
  button_group->end();
  fontobj = new gnui::Browser(10, 210, 280, 170);
  fontobj->when(gnui::WHEN_CHANGED);
  fontobj->callback(font_cb);
  form->resizable(fontobj);
  encobj = new gnui::Browser(300, 210, 100, 170);
  encobj->when(gnui::WHEN_CHANGED);
  encobj->callback(encoding_cb, 1);
  sizeobj = new gnui::Browser(410, 210, 130, 170);
  sizeobj->when(gnui::WHEN_CHANGED);
  sizeobj->callback(size_cb);
  form->end();
}

#include <fltk/ask.h>

int main(int argc, char **argv) {
  create_the_forms();
  int numfonts = gnui::list_fonts(fonts);
  for (int i = 0; i < numfonts; i++)
       fontobj->add(fonts[i]->name());

  fontobj->value(0);
  textobj->encoding = gnui::get_encoding();
  font_cb(fontobj,0);
  form->show(argc,argv);
  return gnui::run();
}

//
// End of "$Id$".
//
