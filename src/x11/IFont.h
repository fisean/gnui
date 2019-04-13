// This is the structure created for each gnui::Font the user sees.
// It is defined here so it can be used by both fl_font_x.cxx and
// by fl_list_fonts_x.cxx.
//
// It contains the crap needed to figure out fonts on X. This is only
// used for the plain X implementation of gnui, not for any other
// system and not for Xft. THIS IS NOT A PUBLIC DATA STRUCTURE!

#include <gnui/Font.h>
struct FontSize;
struct IFont {
  gnui::Font f;
  const char* system_name;
  // pointers to any matched bold or italic versions:
  IFont* bold;
  IFont* italic;
  // pointers to found sizes:
  FontSize* first;
  // XListFonts results:
  char** xlist;
  int n;
};
