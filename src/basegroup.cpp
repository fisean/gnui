#include <gnui/basegroup.h>


using namespace gnui;


BaseGroup * BaseGroup::current{nullptr};


BaseGroup::BaseGroup(
  const int &x,
  const int &y,
  const int &w,
  const int &h,
  const std::string &label
)
  : Widget(x, y, w, h, label)
  , _previousGroup{nullptr}
{
  _type = "group";
}


void
BaseGroup::begin()
{
  _previousGroup = current;
  current = this;
}


void
BaseGroup::add(Widget *widget)
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
BaseGroup::remove(Widget *widget)
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
BaseGroup::end()
{
  if (current == this) { current = _previousGroup; }
}


Widget *
BaseGroup::children() { return _children; }


void
BaseGroup::draw() const
{}
