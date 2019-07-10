//
// "$Id$"
//
// Forms file selection routines for the Fast Light Tool Kit (FLTK).
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
//    http://www.fltk.org/str.php
//

// Emulate the Forms file chooser using the fltk file chooser.

#include <fltk/forms.h>
#include <string.h>

static char gnui_directory[1024];
static const char *gnui_pattern;  // assummed passed value is static
static char gnui_filename[256];

char* gnui_show_file_selector(const char *message,const char *dir,
			    const char *pat,const char *fname) {
  if (dir && dir[0]) strncpy(gnui_directory,dir,1023);
  if (pat && pat[0]) gnui_pattern = pat;
  if (fname && fname[0]) strncpy(gnui_filename,fname,255);
  char *p = gnui_directory+strlen(gnui_directory);
  if (p > gnui_directory && *(p-1)!='/'
#ifdef _WIN32
      && *(p-1)!='\\' && *(p-1)!=':'
#endif
      ) *p++ = '/';
  strcpy(p,gnui_filename);
  const char *q = gnui_file_chooser(message,gnui_pattern,gnui_directory);
  if (!q) return 0;
  strcpy(gnui_directory, q);
  p = (char *)filename_name(gnui_directory);
  strcpy(gnui_filename, p);
  if (p > gnui_directory+1) p--;
  *p = 0;
  return (char *)q;
}

char*	gnui_get_directory() {return gnui_directory;}

char*	gnui_get_pattern() {return (char *)gnui_pattern;}

char*	gnui_get_filename() {return gnui_filename;}

//
// End of "$Id$".
//
