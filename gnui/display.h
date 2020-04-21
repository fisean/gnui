#pragma once


namespace gnui
{
class Display
{
  public:
    Display();
    virtual ~Display();

    virtual int run();
    virtual void line(
      const int &x0,
      const int &y0,
      const int &x1,
      const int &y1
    ) = 0;

  protected:
}; // Display
} // namespace
