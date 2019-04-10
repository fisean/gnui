//
// "$Id$"
//
// Theme plugin file for FLTK
//
// Copyright 1999 Bill Spitzak and others.
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

// essai.cxx

// Demonstration of a plugin that replaces the boxes such that a pixmap
// is used to draw everything.

#include <fltk/Widget.h>
#include <fltk/Window.h>
#include <fltk/draw.h>
#include <fltk/Style.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <fltk/Box.h>
#include <fltk/SharedImage.h>
#include <fltk/TiledImage.h>

class gnui::Image_Box : public gnui::Boxtype_ {
  gnui::Flags mask;
public:
  void draw(const int,int,int,int, gnui::Color, gnui::Flags) const;
  gnui::Tiled_Image* normal_img;
  gnui::Tiled_Image* down_img;
  gnui::Tiled_Image* highlight_img;
  gnui::Image_Box(const char*, const char*, const char*, gnui::Flags = 0);
};

void gnui::Image_Box::draw(int x, int y, int w, int h,
			gnui::Color color, gnui::Flags flags) const
{
  gnui::Tiled_Image* img;

  if (flags&gnui::VALUE) img = down_img;
  else if (flags&gnui::HIGHLIGHT) img = highlight_img;
  else img = normal_img;

  gnui::up_box.draw(x,y,w,h,0,(flags|gnui::INACTIVE)&(~mask));
  if (!(flags&gnui::INACTIVE)) {
    gnui::up_box.inset(x,y,w,h);
    img->draw(x,y,w,h);
  }
}

gnui::Image_Box::gnui::Image_Box(const char* normal_b, const char* down_b, const char* highlight_b, gnui::Flags m) :
gnui::Boxtype_(0), mask(m) {
  dx_ = gnui::up_box.dx();
  dy_ = gnui::up_box.dy();
  dw_ = gnui::up_box.dw();
  dh_ = gnui::up_box.dh();
  fills_rectangle_ = true;
  char buffer[256];
  normal_img =
    new gnui::Tiled_Image(gnui::JPEG_Image::get(gnui::find_config_file(buffer,256,normal_b)));
  down_img =
    new gnui::Tiled_Image(gnui::JPEG_Image::get(gnui::find_config_file(buffer,256,down_b)));
  highlight_img =
    new gnui::Tiled_Image(gnui::JPEG_Image::get(gnui::find_config_file(buffer,256,highlight_b)));
}

class gnui::Image_NoBorderBox : public gnui::Image_Box {
  void draw(int,int,int,int, gnui::Color, gnui::Flags) const;
public:
  gnui::Image_NoBorderBox(const char*a, const char*b, const char*c, gnui::Flags m = 0) : gnui::Image_Box(a,b,c,m) {dx_=dy_=dw_=dh_=0;}
};

void gnui::Image_NoBorderBox::draw(int x, int y, int w, int h,
                                gnui::Color color, gnui::Flags flags) const
{
  if (flags&(gnui::SELECTED|gnui::HIGHLIGHT)) {
    gnui::Image_Box::draw(x,y,w,h, color, flags);
    return;
  }
  if (!(flags&gnui::INACTIVE)) {
    normal_img->draw(x, y, w, h);
  }
}

extern "C" bool fltk_theme()
{

  //  gnui::background(0xD0D0E000); // it would be nice to figure out color from image
  gnui::Boxtype flat1 = new gnui::Image_NoBorderBox("bg.jpeg", "bg2.jpeg", "bg3.jpeg");
  gnui::Boxtype flat2 = new gnui::Image_NoBorderBox("bg2.jpeg", "bg3.jpeg", "bg3.jpeg", gnui::VALUE);
  gnui::Boxtype box1 = new gnui::Image_Box("bg2.jpeg", "bg3.jpeg", "bg3.jpeg");
  //gnui::Boxtype box2 = new gnui::Image_Box("bg.jpeg", "bg.jpeg", "bg.jpeg");
  gnui::Boxtype box3 = new gnui::Image_Box("bg2.jpeg", "bg3.jpeg", "bg3.jpeg", gnui::VALUE);
  gnui::Widget::default_style->box = box1;
  gnui::Widget::default_style->button_box = box3;
  gnui::Widget::default_style->highlight_color = gnui::LIGHT2;
  gnui::Style* s;
  if ((s = gnui::Style::find("window"))) {
    s->box = flat1;
  }
  if ((s = gnui::Style::find("group"))) {
    s->box = gnui::NO_BOX;
  }
  if ((s = gnui::Style::find("menu"))) {
    s->selection_text_color = gnui::BLACK;
    s->box = flat1;
    s->button_box = flat2;
  }
  if ((s = gnui::Style::find("menu bar"))) {
    s->highlight_color = gnui::GRAY;
    s->highlight_label_color = gnui::BLACK;
    s->box = flat2;
    s->selection_text_color = gnui::BLACK;
    s->button_box = flat2;
  }
  if ((s = gnui::Style::find("highlight button"))) {
    s->box = flat2;
  }
  if ((s = gnui::Style::find("button"))) {
    s->selection_text_color = gnui::BLACK;
    s->box = box3;
  }
  if ((s = gnui::Style::find("tabs"))) {
    s->box = box1;
  }
  if ((s = gnui::Style::find("light button"))) {
    s->box = box3;
  }
  return true;
}

//
// End of "$Id$".
//
