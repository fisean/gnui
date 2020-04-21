#include <gnui/group.h>


using namespace gnui;


Group * Group::_current{nullptr};


Group::Group(
  const int &x,
  const int &y,
  const int &w,
  const int &h
)
  : Widget(x, y, w, h)
  , _previous{nullptr}
{}


void
Group::begin()
{
  _previous = _current;
  _current = this;
}


void
Group::add(Widget *widget)
{
  if (_children == nullptr)
  {
    _children = widget;
    _last = widget;
    return;
  }
  widget->next(nullptr);
  widget->previous(_last);
  _last->next(widget);
}


void
Group::remove(Widget *widget)
{
  // TODO: Check if widget is in this group?
  if (widget == nullptr) { return; }
  if (_children == widget) { _children = widget->next(); }
  if (_last == widget)
  {
    _last = widget->previous();
    _last->next(nullptr);
  }
  if (widget->next() != nullptr)
  {
    widget->next()->previous(widget->previous());
  }
  if (widget->previous() != nullptr)
  {
    widget->previous(widget->next());
  }
  widget->next(nullptr);
  widget->previous(nullptr);
}


void
Group::end() { _current = _previous; }


Widget *
Group::children() { return _children; }
