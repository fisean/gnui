#include <fltk/Fl.h>
#include <fltk/GNUI_Window.h>
#include <fltk/GNUI_Value_Slider.h>
#include <fltk/gnui_draw.h>
#include <fltk/GNUI_Choice.h>

GNUI_Window *form;
GNUI_Slider *sliders[8];
GNUI_Choice *choice[3];

class test_box: public GNUI_Window {
  void draw();
public:
  test_box(int x,int y,int w,int h,const char *l=0)
    : GNUI_Window(x,y,w,h,l) {}
}*test;

void test_box::draw() {
  GNUI_Window::draw();
  gnui_color(gnui_rgb((uchar)(sliders[0]->value()),
		  (uchar)(sliders[1]->value()),
		  (uchar)(sliders[2]->value())));
  char buf[5];
  buf[0] = char(sliders[4]->value());
  buf[1] = char(sliders[5]->value());
  buf[2] = char(sliders[6]->value());
  buf[3] = char(sliders[7]->value());
  buf[4] = 0;
  gnui_line_style(
    (int)(choice[0]->mvalue()->argument()) +
    (int)(choice[1]->mvalue()->argument()) +
    (int)(choice[2]->mvalue()->argument()),
    (int)(sliders[3]->value()),
    buf);
  gnui_rect(10,10,w()-20,h()-20);
  gnui_begin_line();
  gnui_vertex(35, 35);
  gnui_vertex(w()-35, h()-35);
  gnui_vertex(w()-40, 35);
  gnui_vertex(35, h()/2);
  gnui_end_line();
  // you must reset the line type when done:
  gnui_line_style(GNUI_SOLID);
}

GNUI_Menu_Item style_menu[] = {
  {"GNUI_SOLID",	0, 0, (void*)GNUI_SOLID},
  {"GNUI_DASH",	0, 0, (void*)GNUI_DASH},
  {"GNUI_DOT",	0, 0, (void*)GNUI_DOT},
  {"GNUI_DASHDOT",0, 0, (void*)GNUI_DASHDOT},
  {"GNUI_DASHDOTDOT", 0, 0, (void*)GNUI_DASHDOTDOT},
  {0}
};

GNUI_Menu_Item cap_menu[] = {
  {"default",		0, 0, 0},
  {"GNUI_CAP_FLAT",	0, 0, (void*)GNUI_CAP_FLAT},
  {"GNUI_CAP_ROUND",	0, 0, (void*)GNUI_CAP_ROUND},
  {"GNUI_CAP_SQUARE",	0, 0, (void*)GNUI_CAP_SQUARE},
  {0}
};

GNUI_Menu_Item join_menu[] = {
  {"default",		0, 0, 0},
  {"GNUI_JOIN_MITER",	0, 0, (void*)GNUI_JOIN_MITER},
  {"GNUI_JOIN_ROUND",	0, 0, (void*)GNUI_JOIN_ROUND},
  {"GNUI_JOIN_BEVEL",	0, 0, (void*)GNUI_JOIN_BEVEL},
  {0}
};

void do_redraw(GNUI_Widget*,void*)
{
    test->redraw();
}

void makeform(const char *) {
  form = new GNUI_Window(500,210,"line type test");
  sliders[0]= new GNUI_Value_Slider(280,10,180,20,"R");
  sliders[0]->bounds(0,255);
  sliders[1]= new GNUI_Value_Slider(280,30,180,20,"G");
  sliders[1]->bounds(0,255);
  sliders[2]= new GNUI_Value_Slider(280,50,180,20,"B");
  sliders[2]->bounds(0,255);
  choice[0]= new GNUI_Choice(280,70,180,20,"Style");
  choice[0]->menu(style_menu);
  choice[1]= new GNUI_Choice(280,90,180,20,"Cap");
  choice[1]->menu(cap_menu);
  choice[2]= new GNUI_Choice(280,110,180,20,"Join");
  choice[2]->menu(join_menu);
  sliders[3]= new GNUI_Value_Slider(280,130,180,20,"Width");
  sliders[3]->bounds(0,20);
  sliders[4] = new GNUI_Slider(200,170,70,20,"Dash");
  sliders[4]->align(GNUI_ALIGN_TOP_LEFT);
  sliders[4]->bounds(0,40);
  sliders[5] = new GNUI_Slider(270,170,70,20);
  sliders[5]->bounds(0,40);
  sliders[6] = new GNUI_Slider(340,170,70,20);
  sliders[6]->bounds(0,40);
  sliders[7] = new GNUI_Slider(410,170,70,20);
  sliders[7]->bounds(0,40);
  int i;
  for (i=0;i<8;i++) {
    sliders[i]->type(1);
    if (i<4) sliders[i]->align(GNUI_ALIGN_LEFT);
    sliders[i]->callback((GNUI_Callback*)do_redraw);
    sliders[i]->step(1);
  }
  for (i=0;i<3;i++) {
    choice[i]->value(0);
    choice[i]->callback((GNUI_Callback*)do_redraw);
  }
  test=new test_box(10,10,190,190);
  test->end();
  form->resizable(test);
  form->end();
}

main(int argc, char **argv) {
  makeform(argv[0]);
  form->show(argc,argv);
  return Fl::run();
}

