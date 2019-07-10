//
// "$Id$"
//
// Copyright 2008 by Bill Spitzak and others.
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

#ifndef gnui_ask_h
#define gnui_ask_h

#include "GNUI_API.h"
#include "Style.h"

namespace gnui {

class Widget;

/// \name gnui/ask.h
//@{

enum {
  BEEP_DEFAULT = 0,
  BEEP_MESSAGE,
  BEEP_ERROR,
  BEEP_QUESTION,
  BEEP_PASSWORD,
  BEEP_NOTIFICATION
};

GNUI_API void message(const char *, ...);
GNUI_API void alert(const char *, ...);
GNUI_API int  ask(const char *, ...);
GNUI_API int  choice(const char *q,
		  const char *b0, const char *b1, const char *b2, ...);
GNUI_API int  choice_alert(const char *q,
		  const char *b0, const char *b1, const char *b2, ...);
GNUI_API const char *input(const char *label, const char *deflt = 0, ...);
GNUI_API const char *password(const char *label, const char *deflt = 0, ...);
GNUI_API void beep(int type = BEEP_DEFAULT);
GNUI_API void beep_on_dialog(bool);
GNUI_API bool beep_on_dialog();

extern GNUI_API NamedStyle* icon_style;
extern GNUI_API NamedStyle* message_style;

extern GNUI_API const char* message_window_label;
extern GNUI_API float message_window_timeout;

extern GNUI_API bool message_window_scrollable;

// pointers you can use to change FLTK to a foreign language:
extern GNUI_API const char* no;
extern GNUI_API const char* yes;
extern GNUI_API const char* ok;
extern GNUI_API const char* cancel;

}

//@}

#endif

//
// End of "$Id$".
//
