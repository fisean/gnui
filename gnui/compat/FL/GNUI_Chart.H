//
// "$Id$"
//
// Forms chart header file for the Fast Light Tool Kit (FLTK).
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
//    http://www.gnui.org/str.php
//

#ifndef GNUI_Chart_H
#define GNUI_Chart_H

#include <gnui/Widget.h>

// values for type()
#define GNUI_BAR_CHART		0
#define GNUI_HORBAR_CHART		1
#define GNUI_LINE_CHART		2
#define GNUI_FILL_CHART		3
#define GNUI_SPIKE_CHART		4
#define GNUI_PIE_CHART		5
#define GNUI_SPECIALPIE_CHART	6

#define GNUI_FILLED_CHART  GNUI_FILL_CHART	// compatibility

#define GNUI_CHART_MAX		128
#define GNUI_CHART_LABEL_MAX	18

struct GNUI_FORMS_API GNUI_CHART_ENTRY {
   float val;
   uchar col;
   char str[GNUI_CHART_LABEL_MAX+1];
};

class GNUI_FORMS_API GNUI_Chart : public gnui::Widget {
public:
  GNUI_Chart(int,int,int,int,const char * = 0);
  ~GNUI_Chart();
  void clear();
  void add(double, const char * =0, uchar=0);
  void insert(int, double, const char * =0, uchar=0);
  void replace(int, double, const char * =0, uchar=0);
  void bounds(double *a,double *b) const {*a = min; *b = max;}
  void bounds(double a,double b);
  int size() const {return numb;}
  int maxsize() const {return maxnumb;}
  void maxsize(int);
  uchar autosize() const {return autosize_;}
  void autosize(uchar n) {autosize_ = n;}

protected:
  void draw();

private:
  uchar autosize_;
  int numb;
  int maxnumb;
  int sizenumb;
  GNUI_CHART_ENTRY *entries;
  double min,max;
};

#endif

//
// End of "$Id$".
//
