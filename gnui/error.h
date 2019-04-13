/*! \file
  Functions to report errors and possibly kill the program.
  You can change these pointers from their default values so that
  gnui calls your code instead.
*/

#ifndef gnui_error_h
#define gnui_error_h

#include "FL_API.h"

namespace gnui {

/// \name gnui/error.h
//@{

extern FL_API void (*warning)(const char*, ...);
extern FL_API void (*error)(const char*, ...);
extern FL_API void (*fatal)(const char*, ...);

//@}

}
#endif
