#ifndef GNUI_File_Chooser_H
#define GNUI_File_Chooser_H

#include "GNUI_Widget.H"

#include <gnui/FileChooser.h>
typedef gnui::FileChooser GNUI_File_Chooser;

#include <gnui/file_chooser.h>

//char *gnui_dir_chooser(const char *message,const char *fname,int relative=0);
inline const char *gnui_file_chooser(const char *message,const char *pat,const char *fname,int /*relative*/ = 0) {
  return gnui::file_chooser(message, pat, fname);
}

#endif
