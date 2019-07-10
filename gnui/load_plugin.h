/*! \file
  This is a convienence function for portable loading of a plugin
  and possibly returing a symbol in that plugin. The function is
  \e not in the gnui namespace!
*/

#ifndef gnui_load_plugin_h
#define gnui_load_plugin_h

#include "GNUI_API.h"

GNUI_API void* load_plugin(const char* name, const char* symbol);

#endif
