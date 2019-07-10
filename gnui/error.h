/*! \file
  Functions to report errors and possibly kill the program.
  You can change these pointers from their default values so that
  gnui calls your code instead.
*/

#ifndef gnui_error_h
#define gnui_error_h

#include "GNUI_API.h"

namespace gnui {

/// \name gnui/error.h
//@{

extern GNUI_API void (*warning)(const char*, ...);
extern GNUI_API void (*error)(const char*, ...);
extern GNUI_API void (*fatal)(const char*, ...);

//@}

}
#endif
