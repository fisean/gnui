#include <gnui/widget.h>


using namespace gnui;


Display * Widget::display;


Widget::Widget(
  const int &x,
  const int &y,
  const int &w,
  const int &h
)
  : _x{x}
  , _y{y}
  , _width{w}
  , _height{h}
  , _next{nullptr}
  , _previous{nullptr}
{
  _handler = new Handler();
}


void
Widget::x(const int &argX) { _x = argX; }


int
Widget::x() { return _x; }


void
Widget::y(const int &argY) { _y = argY; }


int
Widget::y() { return _y; }


void
Widget::width(const int &argWidth) { _width = argWidth; }


int
Widget::width() { return _width; }


void
Widget::height(const int &argHeight) { _height = argHeight; }


int
Widget::height() { return _height; }


void
Widget::next(Widget *widget) { _next = widget; }


Widget *
Widget::next() { return _next; }


void
Widget::previous(Widget *widget) { _previous = widget; }


Widget *
Widget::previous() { return _previous; }

Handler *
Widget::handler() { return _handler; }

void
Widget::label(const std::string &l) { _label = l; }

std::string
Widget::label() { return _label; }
