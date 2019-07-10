//
// "$Id$"
//
// Forms test program for the Fast Light Tool Kit (FLTK).
//
// This is an XForms program from the 0.86 distribution of XForms.
// It has been modified as little as possible to work under fltk by
// using fltk's Forms emulation.  Search for "fltk" to find all the
// changes
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

#include <fltk/forms.h>	// changed for fltk
#include <stdlib.h>
#include <stdio.h>	// added for fltk
#include <string.h>	// added for fltk

#define MAX_RGB 3000

static GNUI_FORM *cl;
static GNUI_Widget *rescol, *dbobj, *colbr, *rs, *gs, *bs;
char dbname[GNUI_PATH_MAX];
static void create_form_cl(void);
static int load_browser(char *);

/* the RGB data file does not have a standard location on unix. */

#ifdef __VMS
  static const char *rgbfile = "SYS$MANAGER:DECW$RGB.DAT";
#else
#ifdef __EMX__   /* OS2 */
#include <X11/XlibInt.h>
  static const char *rgbfile = "/XFree86/lib/X11/rgb.txt";
#else
#ifdef __FreeBSD__
  static const char *rgbfile = "/usr/X11R6/lib/X11/rgb.txt";
#else
   static const char *rgbfile = "/usr/lib/X11/rgb.txt";
#endif
#endif
#endif

typedef struct { int r, g, b; } RGBdb;

static RGBdb rgbdb[MAX_RGB];

int
main(int argc, char *argv[])
{

    gnui_initialize(&argc, argv, "FormDemo", 0, 0);

    create_form_cl();
    strcpy(dbname, rgbfile);

    if (load_browser(dbname))
	gnui_set_object_label(dbobj, dbname);
    else
	gnui_set_object_label(dbobj, "None");

//    gnui_set_form_minsize(cl, cl->w , cl->h); // removed for fltk
//    gnui_set_form_maxsize(cl, 2*cl->w , 2*cl->h); // removed for fltk
    cl->size_range(cl->w(),cl->h(),2*cl->w(),2*cl->h()); // added for fltk
    // border changed from GNUI_TRANSIENT for fltk:
    // This is so Esc & the close box will close the window.
    // (on transient windows attempting to close it just calls the callback)
    gnui_show_form(cl, GNUI_PLACE_FREE, 1/*GNUI_TRANSIENT*/, "RGB Browser");


    while (gnui_do_forms())
	;
    return 0;
}

static void
set_entry(int i)
{
    RGBdb *db = rgbdb + i;

    gnui_freeze_form(cl);
// unclear why demo is doing this.  This messes up FL:
//    gnui_mapcolor(GNUI_FREE_COL4+i, db->r, db->g, db->b);
    gnui_mapcolor(GNUI_FREE_COL4, db->r, db->g, db->b);
    gnui_set_slider_value(rs, db->r);
    gnui_set_slider_value(gs, db->g);
    gnui_set_slider_value(bs, db->b);
    gnui_redraw_object(rescol);
    gnui_unfreeze_form(cl);
}

static void
br_cb(GNUI_Widget * ob, long)
{
    int r = gnui_get_browser(ob);

    if (r <= 0)
	return;
    set_entry(r - 1);
}

static int
read_entry(FILE * fp, int *r, int *g, int *b, char *name)
{
    int  n;
    char buf[512], *p;

    if (!fgets(buf, sizeof(buf) - 1, fp))
      return 0;

    if(buf[0] == '!')
      fgets(buf,sizeof(buf)-1,fp);

    if(sscanf(buf, " %d %d %d %n", r, g, b, &n) < 3)
	return 0;

    p = buf + n;

    /* squeeze out all spaces */
    while (*p)
    {
	if (*p != ' ' && *p != '\n')
	    *name++ = *p;
	p++;
    }
    *name = 0;

    return (feof(fp) || ferror(fp)) ? 0 : 1;
}


static int
load_browser(char *fname)
{
    FILE *fp;
    RGBdb *db = rgbdb, *dbs = db + MAX_RGB;
    int r, g, b,  lr  = -1 , lg = -1, lb = -1;
    char name[256], buf[256];
#ifdef __EMX__
    if (!(fp = fopen(__XOS2RedirRoot(fname), "r")))
#else
    if (!(fp = fopen(fname, "r")))
#endif
    {
	gnui_show_alert("Load", fname, "Can't open", 0);
	return 0;
    }

    /* read the items */

    gnui_freeze_form(cl);

    for (; db < dbs && read_entry(fp, &r, &g, &b, name);)
    {
	db->r = r;
	db->g = g;
	db->b = b;

	/* unique the entries on the fly */
	if (lr != r || lg != g || lb != b)
	{
	    db++;
	    lr = r;
	    lg = g;
	    lb = b;
	    sprintf(buf, "(%3d %3d %3d) %s", r, g, b, name);
	    gnui_addto_browser(colbr, buf);
	}
    }
    fclose(fp);

    if (db < dbs)
	db->r = 1000;		/* sentinel */
    else
    {
	db--;
	db->r = 1000;
    }

    gnui_set_browser_topline(colbr, 1);
    gnui_select_browser_line(colbr, 1);
    set_entry(0);
    gnui_unfreeze_form(cl);
    return 1;
}

static int
search_entry(int r, int g, int b)
{
    register RGBdb *db = rgbdb;
    int i, j, diffr, diffg, diffb;
    unsigned int diff, mindiff;

    mindiff = ~0;
    for (i = j = 0; db->r < 256; db++, i++)
    {
       diffr = r - db->r;
       diffg = g - db->g;
       diffb = b - db->b;

#ifdef GNUI_LINEAR
	diff = unsigned(3.0 * (GNUI_abs(r - db->r)) +
			(5.9 * GNUI_abs(g - db->g)) +
			(1.1 * (GNUI_abs(b - db->b)));
#else
        diff = unsigned(3.0 * (diffr *diffr) +
			5.9 * (diffg *diffg) +
			1.1 * (diffb *diffb));
#endif

	if (mindiff > diff)
	{
	    mindiff = diff;
	    j = i;
	}
    }

    return j;
}

static void
search_rgb(GNUI_Widget *, long)
{
    int r, g, b, i;
    int top  = gnui_get_browser_topline(colbr);

    r = int(gnui_get_slider_value(rs));
    g = int(gnui_get_slider_value(gs));
    b = int(gnui_get_slider_value(bs));

    gnui_freeze_form(cl);
    gnui_mapcolor(GNUI_FREE_COL4, r, g, b);
    gnui_redraw_object(rescol);
    i = search_entry(r, g, b);
    /* change topline only if necessary */
    if(i < top || i > (top+15))
       gnui_set_browser_topline(colbr, i-8);
    gnui_select_browser_line(colbr, i + 1);
    gnui_unfreeze_form(cl);
}

/* change database */
static void
db_cb(GNUI_Widget * ob, long)
{
    const char *p = gnui_show_input("Enter New Database Name", dbname);
    char buf[512];

    if (!p || strcmp(p, dbname) == 0)
	return;

    strcpy(buf, p);
    if (load_browser(buf))
	strcpy(dbname, buf);
    else
	gnui_set_object_label(ob, dbname);
}

static void
done_cb(GNUI_Widget *, long)
{
    exit(0);
}

static void
create_form_cl(void)
{
    GNUI_Widget *obj;

    if (cl)
	return;

    cl = gnui_bgn_form(GNUI_NO_BOX, 330, 385);
    obj = gnui_add_box(GNUI_UP_BOX, 0, 0, 330, 385, "");
    gnui_set_object_color(obj, GNUI_INDIANRED, GNUI_COL1);

    obj = gnui_add_box(GNUI_NO_BOX, 40, 10, 250, 30, "Color Browser");
    gnui_set_object_lcol(obj, GNUI_RED);
    gnui_set_object_lsize(obj, GNUI_HUGE_SIZE);
    gnui_set_object_lstyle(obj, GNUI_BOLD_STYLE + GNUI_SHADOW_STYLE);

    dbobj = obj = gnui_add_button(GNUI_NORMAL_BUTTON, 40, 50, 250, 25, "");
    gnui_set_object_boxtype(obj, GNUI_BORDER_BOX);
    gnui_set_object_color(obj, /*gnui_get_visual_depth()==1 ? GNUI_WHITE:*/ GNUI_INDIANRED,
                        GNUI_INDIANRED);
    gnui_set_object_callback(obj, db_cb, 0);
    rs = obj = gnui_add_valslider(GNUI_VERT_FILL_SLIDER, 225, 130, 30, 200, "");
    gnui_set_object_color(obj, GNUI_INDIANRED, GNUI_RED);
    gnui_set_slider_bounds(obj, 0, 255);
    gnui_set_slider_precision(obj, 0);
    gnui_set_object_callback(obj, search_rgb, 0);
    gnui_set_slider_return(obj, 0);

    gs = obj = gnui_add_valslider(GNUI_VERT_FILL_SLIDER, 255, 130, 30, 200, "");
    gnui_set_object_color(obj, GNUI_INDIANRED, GNUI_GREEN);
    gnui_set_slider_bounds(obj, 0, 255);
    gnui_set_slider_precision(obj, 0);
    gnui_set_object_callback(obj, search_rgb, 1);
    gnui_set_slider_return(obj, 0);

    bs = obj = gnui_add_valslider(GNUI_VERT_FILL_SLIDER, 285, 130, 30, 200, "");
    gnui_set_object_color(obj, GNUI_INDIANRED, GNUI_BLUE);
    gnui_set_slider_bounds(obj, 0, 255);
    gnui_set_slider_precision(obj, 0);
    gnui_set_object_callback(obj, search_rgb, 2);
    gnui_set_slider_return(obj, 0);


    colbr = obj = gnui_add_browser(GNUI_HOLD_BROWSER, 10, 90, 205, 240, "");
    gnui_set_browser_fontstyle(obj, GNUI_FIXED_STYLE); 
    gnui_set_object_callback(obj, br_cb, 0);


    obj = gnui_add_button(GNUI_NORMAL_BUTTON, 135, 345, 80, 30, "Done");
    gnui_set_object_callback(obj, done_cb, 0);

    rescol = obj = gnui_add_box(GNUI_FLAT_BOX, 225, 90, 90, 35, "");
    gnui_set_object_color(obj, GNUI_FREE_COL4, GNUI_FREE_COL4);
    gnui_set_object_boxtype(obj, GNUI_BORDER_BOX);


    gnui_end_form();
    gnui_scale_form(cl, 1.1, 1.0);
}

//
// End of "$Id$".
//
