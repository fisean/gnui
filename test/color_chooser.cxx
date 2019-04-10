// "$Id$"
//
// Color chooser test program for the Fast Light Tool Kit (FLTK).
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
// Please report all bugs and problems to:
//
//     http://www.fltk.org/str.php
//

#include <config.h>
#undef USE_XFT // this breaks the <x.h> header file

#include <fltk/run.h>
#include <fltk/Window.h>
#include <fltk/visual.h>
#include <fltk/Button.h>
#include <fltk/show_colormap.h>
#include <fltk/ColorChooser.h>
#include <fltk/rgbImage.h>
#include <fltk/x.h>
#include <fltk/error.h>
#include <fltk/draw.h>

#include <stdlib.h>
#include <stdio.h>

#if USE_X11
  #include "list_visuals.cxx"
#endif

class GrayLines : public gnui::Widget {
public:
  GrayLines(int X, int Y, int W, int H, const char* L)
    : gnui::Widget(X,Y,W,H,L) { }
  
  void draw() {
    // Use every color in the gray ramp:
    for (int i = 0; i < 3*8; i++) {
      gnui::setcolor((gnui::Color)(gnui::GRAY00+i));
      gnui::drawline(i, 0, i, h());
    }
  }
};

#define freecolor_cell (gnui::FREE_COLOR)

// Callback function for "gnui::show_colormap" button
static void colormap_cb(gnui::Widget *w, void *v) {
  uchar r, g, b;
  gnui::Color c = gnui::show_colormap(w->parent()->color());
  gnui::split_color(c, r,g,b);
  // Set new color to our free color index
  gnui::set_color_index(freecolor_cell, gnui::color(r,g,b));
  // Redraw parent box
  w->parent()->redraw();
}

// Callback function for "gnui::choose_color" button
static void choose_color_cb(gnui::Widget *w, void *v) {
  uchar r,g,b;
  gnui::split_color(w->parent()->color(),r,g,b);
  if (!gnui::color_chooser("New color:", r,g,b)) return;
  // Set new color to our free color index
  gnui::set_color_index(freecolor_cell, gnui::color(r,g,b));
  // Redraw parent box
  w->parent()->redraw();
}

// Main entry point for application
int main(int argc, char **argv) 
{
  // Set default color for our free color index
  gnui::set_color_index(freecolor_cell, gnui::color(145,159,170));
  
  // Create window
  gnui::Window window(200, 170, "color_chooser test");  
  window.begin();

  // Create widget container group
  gnui::Group gbox(10, 10, window.w()-20, window.h()-20);
  gbox.box(gnui::THIN_DOWN_BOX);
  gbox.color(freecolor_cell);
  gbox.begin();

  // Create button
  gnui::Button button1(50,20,120,30, "gnui::show_colormap");
  button1.callback(colormap_cb);

  // Create button
  gnui::Button button2(50,60,120,30, "gnui::choose_color");
  button2.callback(choose_color_cb);

  // Create lines widget
  GrayLines lines(10,20,3*8,120, "Lines");
  lines.align(gnui::ALIGN_TOP);

  // We're done with the group
  gbox.end();

  // Test command line options
  int i = 1;
  if (!gnui::args(argc, argv, i) || i != argc-1) {
    printf("usage: %s <switches> visual-number\n"
	   " - : default visual\n"
	   " r : call gnui::visual(gnui::RGB_COLOR)\n"
	   " c : call gnui::own_colormap()\n",argv[0]);
#if USE_X11
    printf(" # : use this visual with an empty colormap:\n");
    list_visuals();
#endif
    puts("\n Invalid parameter, using with default visual");
  }

  // Parse command line options  
  if (argc > 1 && argv[i][0] == 'r') {
    if (!gnui::visual(gnui::RGB_COLOR)) gnui::fatal("gnui::visual(gnui::RGB_COLOR) returned false.\n");
  } 
  else if (argc > 1 && argv[i][0] == 'c') {
    gnui::own_colormap();
  } 
  else if (argc > 1 && argv[i][0] != '-') {
#if USE_X11
    int visid = atoi(argv[i]);
    gnui::open_display();
    XVisualInfo templt; int num;
    templt.visualid = visid;
    gnui::xvisual= XGetVisualInfo(gnui::xdisplay, VisualIDMask, &templt, &num);
    if (!gnui::xvisual) gnui::fatal("No visual with id %d",visid);
    gnui::xcolormap = XCreateColormap(gnui::xdisplay, RootWindow(gnui::xdisplay,gnui::xscreen),
				  gnui::xvisual->visual, AllocNone);
# if !USE_CAIRO
    gnui::xpixel(gnui::BLACK); // make sure black is allocated
# endif
#else
    gnui::fatal("Visual id's not supported on this platform");
#endif
  }

  // Show window
  window.show(argc, argv);

  // Run FLTK event loop
  return gnui::run();
}

//
// End of "$Id$".
//
