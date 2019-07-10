// This is an additional header file for "DDForms", which was our internal
// enhancement of Forms.  This defines the precursor of the GNUI_Menu class.
//
// Unfortunately it defined the callbacks as taking a long rather
// than a void* argument, requiring some dubious casts to emulate it:

#include "GNUI_Menu_Bar.h"

struct GNUI_API MenuEntry {
  const char *text;	/*initial character indicates "type", 0 = end of menu*/
  ulong bind;	/* key binding in forms format (#x, etc) */
  void (*cb)(GNUI_Widget *,long);	/* callback */
  long data;		/* value for callback */
  int flags;		/* see below for flags */
  uchar labeltype;
  uchar labelfont;
  uchar labelsize;
  uchar labelcolor;
};

#define CHECKED GNUI_MENU_CHECK
#define UNCHECKED GNUI_MENU_BOX
#define DISABLED GNUI_MENU_INACTIVE

/* Turn a box into a menu bar: */
inline void MenuBar(GNUI_Widget *o,MenuEntry *m) {
    GNUI_Menu_Bar *mb = new GNUI_Menu_Bar(o->x(),o->y(),o->w(),o->h());
    mb->menu((GNUI_Menu_Item*)m);
    mb->box(0);
    GNUI_Group *g = (GNUI_Group *)(o->parent());
    int i = g->find(*o);
    g->insert(*mb, i<g->children()-1 ? g->child(i+1) : 0);
}

/* advance to the Nth item in menu, skipping submenus: */
inline MenuEntry *MenuGetEntry(MenuEntry *m,int i) {
    return (MenuEntry*)(((GNUI_Menu_Item*)m)->next(i));
}

/* Init the shortcuts for a widget with a popup menu: */
inline void MenuSetShortcuts(GNUI_Widget *, MenuEntry *) {}

inline void MenuAdd(
    MenuEntry m[],
    int, /* number of entries in menutable, ignored here */
    const char *text,
    const char *bind,
    void (*cb)(GNUI_Widget *,long),
    long data,
    int flags) {
    ((GNUI_Menu_Item*)m)->add(text,bind,(GNUI_Callback*)cb,(void *)data,flags);
}

inline MenuEntry *MenuPopup(GNUI_Widget *o,const char *title,MenuEntry *m,
			    int x, int y) {
    const GNUI_Menu_Item* v = ((GNUI_Menu_Item*)m)->popup(x,y,title);
    if (v && v->callback_) v->do_callback(o);
    return (MenuEntry *)v;
}

inline MenuEntry *MenuHandleShortcut(GNUI_Widget *o,MenuEntry *m,char) {
    const GNUI_Menu_Item* v = ((GNUI_Menu_Item*)m)->test_shortcut();
    if (v && v->callback_) v->do_callback(o);
    return (MenuEntry *)v;
}
