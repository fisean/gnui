/*! \file

The FLTK version number. Allows you to write conditionally compiled
code for different versions of FLTK. This file may be included by C
code in case you need it there.

GNUI_VERSION is a macro double that describes the major, minor, and
patch version numbers. The integer value is the major number. One
digit is used for the minor number, and three for the "patch" number
which is increased for each binary differnt release (it can go to 999).

Because double cannot be used in #if statements, the integer
numbers are in the GNUI_MAJOR_VERSION, GNUI_MINOR_VERSION, and
GNUI_PATCH_VERSION macro constants.

*/

#ifndef GNUI_VERSION

# define GNUI_MAJOR_VERSION 2 //!< The major release number, 1 or 2
# define GNUI_MINOR_VERSION 1 //!< The minor release number, 0-9
# define GNUI_PATCH_VERSION 0 //!< The patch number, 0-999
# define GNUI_VERSION	  2.1000

#if defined(__cplusplus) || defined(DOXYGEN) /* Allow this file to be included by C code */
#include "GNUI_API.h"
namespace gnui {

/*!
  Returns the value of GNUI_VERSION that FLTK was compiled with.
  This can be compared to the GNUI_VERSION macro to see if the shared
  library of gnui your program linked with is up to date.
*/
GNUI_API double version();

}
#endif

#endif
