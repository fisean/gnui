#include <iostream>
#include <xcb/xcb.h>
#include <X11/Xlib-xcb.h>
#include <xkbcommon/xkbcommon.h>
#include <xkbcommon/xkbcommon-x11.h>
#include <fontconfig/fontconfig.h>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <xcb/render.h>
#include <xcb/xcb_renderutil.h>


xcb_render_picture_t
xcbft_create_pen(xcb_connection_t *c, xcb_render_color_t color)
{
  xcb_render_pictforminfo_t *fmt;
  const xcb_render_query_pict_formats_reply_t *fmt_rep =
    xcb_render_util_query_formats(c);
  // alpha can only be used with a picture containing a pixmap
  fmt = xcb_render_util_find_standard_format(
    fmt_rep,
    XCB_PICT_STANDARD_ARGB_32
  );

  xcb_drawable_t root = xcb_setup_roots_iterator(
      xcb_get_setup(c)
    ).data->root;

  xcb_pixmap_t pm = xcb_generate_id(c);
  xcb_create_pixmap(c, 32, pm, root, 1, 1);

  uint32_t values[1];
  values[0] = XCB_RENDER_REPEAT_NORMAL;

  xcb_render_picture_t picture = xcb_generate_id(c);

  xcb_render_create_picture(c,
    picture,
    pm,
    fmt->id,
    XCB_RENDER_CP_REPEAT,
    values);

  xcb_rectangle_t rect = {
    .x = 0,
    .y = 0,
    .width = 1,
    .height = 1
  };

  xcb_render_fill_rectangles(c,
    XCB_RENDER_PICT_OP_OVER,
    picture,
    color, 1, &rect);

  xcb_free_pixmap(c, pm);
  return picture;
}


int
main()
{
  Display *display = XOpenDisplay(nullptr);
  if (display == nullptr)
  {
    std::cerr << "Could not open X display!\n";
    return 1;
  }
  xcb_connection_t *c = XGetXCBConnection(display);

  // initialize the fontconfig library
  FcInit();
  FcChar8 *fontquery = (FcChar8 *)"times:pixelsize=20";
  FcPattern *fc_finding_pattern = FcNameParse(fontquery);
  FcBool status;
  FcDefaultSubstitute(fc_finding_pattern);
  status = FcConfigSubstitute(NULL, fc_finding_pattern, FcMatchPattern);
  if (status == FcFalse)
  {
    std::cerr << "could not perform config font substitution\n";
  }
  FcPatternPrint(fc_finding_pattern);
  FcResult result;
  FcPattern *pat_output = FcFontMatch(NULL, fc_finding_pattern, &result);

  FcPatternDestroy(fc_finding_pattern);
  if (result == FcResultMatch)
  {
    FcValue fc_file;
    FcPatternGet(pat_output, FC_FILE, 0, &fc_file);
    std::cout << "found the font in the file: ";
    std::cout << (const char *)fc_file.u.s << '\n';
  }
  else if (result == FcResultNoMatch)
  {
    std::cerr << "there wasn't a match\n";
  }
  else { std::cerr << "the match wasn't as good as it should be\n"; }

  // (1)
  FT_Library library;
  FT_Init_FreeType(&library);

  // (2)
  FcValue fc_file, fc_index;
  result = FcPatternGet(pat_output, FC_FILE, 0, &fc_file);
  if (result != FcResultMatch)
  {
    std::cerr << "font has not file location\n";
  }
  result = FcPatternGet(pat_output, FC_INDEX, 0, &fc_index);
  if (result != FcResultMatch)
  {
    std::cerr << "font has no index, using 0 by default\n";
    fc_index.type = FcTypeInteger;
    fc_index.u.i = 0;
  }

  // (3)
  FT_Face face;
  FT_New_Face(
    library,
    (const char *)fc_file.u.s,
    fc_index.u.i,
    &face
  );

  std::string text = "hello world";
  int glyph_index = FT_Get_Char_Index(face, text[0]);
  if (glyph_index == 0)
  {
    std::cerr << "The character 'h' doesn't have a glyph in this face\n";
  }
  FT_Select_Charmap(face, ft_encoding_unicode);
  FT_Load_Glyph(face, glyph_index, FT_LOAD_RENDER | FT_LOAD_FORCE_AUTOHINT);
  FT_Bitmap *bitmap = &face->glyph->bitmap;
  FT_Vector glyph_advance;
  glyph_advance.x = face->glyph->advance.x / 64;
  glyph_advance.y = face->glyph->advance.y / 64;

  xcb_connection_t *connection = xcb_connect(nullptr, nullptr);
  xcb_screen_t *screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;
  xcb_render_picture_t picture = xcb_generate_id(connection);

  // (1)
  uint32_t values[2];
  values[0] = XCB_RENDER_POLY_MODE_IMPRECISE;
  values[1] = XCB_RENDER_POLY_EDGE_SMOOTH;


  // (2)
  xcb_render_pictforminfo_t *fmt;
  const xcb_render_query_pict_formats_reply_t *fmt_rep =
  xcb_render_util_query_formats(connection);

  fmt = xcb_render_util_find_standard_format(
    fmt_rep,
    XCB_PICT_STANDARD_RGB_24
  );


  // (3)
  xcb_drawable_t pmap = screen->root;
  auto cookie = xcb_render_create_picture_checked(
    connection,
    picture, // pid
    pmap, // drawable
    fmt->id, // format
    XCB_RENDER_CP_POLY_MODE|XCB_RENDER_CP_POLY_EDGE,
    values
  ); // make it smooth

  xcb_render_pictforminfo_t *fmt_a8 = xcb_render_util_find_standard_format(
    fmt_rep,
    XCB_PICT_STANDARD_A_8
  );

  xcb_render_glyphset_t gs = xcb_generate_id(connection);
  xcb_render_create_glyph_set(connection, gs, fmt_a8->id);

  // the glyphinfo we want to convert from FreeType to XCB
  xcb_render_glyphinfo_t ginfo;

  // the basic information
  ginfo.x = -face->glyph->bitmap_left;
  ginfo.y = face->glyph->bitmap_top;
  ginfo.width = bitmap->width;
  ginfo.height = bitmap->rows;
  ginfo.x_off = glyph_advance.x;
  ginfo.y_off = glyph_advance.y;


  // the charcode that will be associated with that glyph in the set
  uint32_t gid = 0;

  // copying the pixels from the FreeType glyph
  int stride = (ginfo.width+3)&~3;
  uint8_t *tmpbitmap = (uint8_t *)calloc(sizeof(uint8_t),stride*ginfo.height);
  int y;
  for (y = 0; y < ginfo.height; y++)
    memcpy(tmpbitmap+y*stride, bitmap->buffer+y*ginfo.width, ginfo.width);

  // finally adding it to the xcb_render_glyphset_t gs
  xcb_render_add_glyphs_checked(
    connection,
    gs,
    1,
    &gid,
    &ginfo,
    stride*ginfo.height,
    tmpbitmap
  );


  // we now have a text stream - a bunch of glyphs basically
  xcb_render_util_composite_text_stream_t *ts = xcb_render_util_composite_text_stream(
    gs, // the glyphset
    text.length(),
    0
  );

  // prepare the text at a certain positions in the stream
  xcb_render_util_glyphs_32(ts, 0, 0, text.size(), (const uint32_t *)text.data());

  xcb_render_color_t color;
  color.red =  0x4242;
  color.green = 0x4242;
  color.blue = 0x4242;
  color.alpha = 0xFFFF;
  xcb_render_picture_t fg_pen = xcbft_create_pen(c, color);

  // finally render using the repeated pen color on the picture
  // (which is related to the pixmap)
  xcb_render_util_composite_text(
    connection, // connection
    XCB_RENDER_PICT_OP_OVER, //op
    fg_pen, // src
    picture, // dst
    0, // fmt
    0, // src x
    0, // src y
    ts
  ); // txt stream
  return 0;
}
