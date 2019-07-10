#ifndef gnui_filename_H
#define gnui_filename_H

#include <gnui/filename.h>
#include <string.h>

#define gnui_filename_name	gnui::filename_name
#define gnui_filename_ext		gnui::filename_ext
#define gnui_filename_match	gnui::filename_match
#define gnui_filename_isdir	gnui::filename_isdir
#define gnui_filename_list	gnui::filename_list

inline char *gnui_filename_setext(char * name, const char *ext) {
  strcpy(gnui::filename_ext(name), ext ? ext : "");
  return name;
}
#define GNUI_PATH_MAX PATH_MAX // all buffers are assummed to be at least this long
GNUI_API bool gnui_filename_expand(char *, const char *from);
GNUI_API bool gnui_filename_absolute(char *, const char *from, const char* pwd=0);

#endif
