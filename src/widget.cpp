#include <gnui/widget.h>


using namespace gnui;


Display * Widget::display;
Widget * Widget::_begining{nullptr};
Widget * Widget::_end{nullptr};


Widget::Widget(
  const int &x,
  const int &y,
  const int &w,
  const int &h,
  const std::string &label
)
  : _x{x}
  , _y{y}
  , _width{w}
  , _height{h}
  , _next{nullptr}
  , _previous{nullptr}
{
  _label = label;
  if (_begining == nullptr) { _begining = this; }
  else { _end->next(this); }
  _end = this;
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


const std::string
Widget::type() const { return _type; }


Widget *
Widget::begining() { return _begining; }


Widget *
Widget::end() { return _end; }
