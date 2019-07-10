//
// "$Id"
//
// Mouse cursor support for the Fast Light Tool Kit (FLTK).

// This is likely to change!

#ifndef gnui_Cursor_h
#define gnui_Cursor_h

#include "GNUI_API.h"

namespace gnui {

struct Cursor; // this is not public

class Image;
extern GNUI_API Cursor* cursor(Image*, int x, int y);
extern GNUI_API Cursor* cursor(void *raw);

extern GNUI_API Cursor* const CURSOR_DEFAULT; // == NULL
extern GNUI_API Cursor* const CURSOR_ARROW;
extern GNUI_API Cursor* const CURSOR_CROSS;
extern GNUI_API Cursor* const CURSOR_WAIT;
extern GNUI_API Cursor* const CURSOR_INSERT;
extern GNUI_API Cursor* const CURSOR_HAND;
extern GNUI_API Cursor* const CURSOR_HELP;
extern GNUI_API Cursor* const CURSOR_MOVE;
extern GNUI_API Cursor* const CURSOR_NS;
extern GNUI_API Cursor* const CURSOR_WE;
extern GNUI_API Cursor* const CURSOR_NWSE;
extern GNUI_API Cursor* const CURSOR_NESW;
extern GNUI_API Cursor* const CURSOR_NO;
extern GNUI_API Cursor* const CURSOR_NONE;

}
#endif

// End of "$Id"
