#include <fltk/Widget.h>
#include <fltk/Browser.h>
#include <fltk/Button.h>
#include <fltk/CheckButton.h>
#include <fltk/LightButton.h>
#include <fltk/ReturnButton.h>
#include <fltk/Menu.h>
#include <fltk/MenuBar.h>
#include <fltk/PopupMenu.h>
#include <fltk/Choice.h>
#include <fltk/Adjuster.h>
#include <fltk/Clock.h>
#include <fltk/Group.h>
#include <fltk/ColorChooser.h>
#include <fltk/Dial.h>
#include <fltk/Valuator.h>
#include <fltk/ValueInput.h>
#include <fltk/Window.h>
#include <fltk/Input.h>
#include <fltk/Output.h>
#include <fltk/ThumbWheel.h>
#include <fltk/ScrollGroup.h>
#include <fltk/Slider.h>
#include <fltk/Scrollbar.h>
#include <fltk/TabGroup.h>
#include <fltk/Style.h>
#include <fltk/TextBuffer.h>
#include <fltk/TextDisplay.h>
#include <fltk/TextEditor.h>
#include <fltk/Box.h>

#include <stdio.h>

int main() {
  printf("sizeof(gnui::Style) = %lu\n", (unsigned long)sizeof(struct gnui::Style));
  //printf("  sizeof(gnui::Box) = %lu\n", (unsigned long)sizeof(class gnui::Box));
  printf("sizeof(gnui::Widget) = %lu\n", (unsigned long)sizeof(class gnui::Widget));
  printf("  sizeof(gnui::Button) = %lu\n", (unsigned long)sizeof(class gnui::Button));
  printf("    sizeof(gnui::LightButton) = %lu\n", (unsigned long)sizeof(class gnui::LightButton));
  printf("      sizeof(gnui::CheckButton) = %lu\n", (unsigned long)sizeof(class gnui::CheckButton));
  printf("    sizeof(gnui::ReturnButton) = %lu\n", (unsigned long)sizeof(class gnui::ReturnButton));
  printf("  sizeof(gnui::Clock) = %lu\n", (unsigned long)sizeof(class gnui::Clock));
  printf("  sizeof(gnui::Group) = %lu\n", (unsigned long)sizeof(class gnui::Group));
  printf("    sizeof(gnui::Browser) = %lu\n", (unsigned long)sizeof(class gnui::Browser));
  printf("    sizeof(gnui::ColorChooser) = %lu\n", (unsigned long)sizeof(class gnui::ColorChooser));
  printf("    sizeof(gnui::ScrollGroup) = %lu\n", (unsigned long)sizeof(class gnui::ScrollGroup));
  printf("    sizeof(gnui::TabGroup) = %lu\n", (unsigned long)sizeof(class gnui::TabGroup));
  printf("    sizeof(gnui::TextDisplay) = %lu\n", (unsigned long)sizeof(class gnui::TextDisplay));
  printf("      sizeof(gnui::TextEditor) = %lu\n", (unsigned long)sizeof(class gnui::TextEditor));
  printf("    sizeof(gnui::Window) = %lu\n", (unsigned long)sizeof(class gnui::Window));
  printf("  sizeof(gnui::Input) = %lu\n", (unsigned long)sizeof(class gnui::Input));
  printf("  sizeof(gnui::Output) = %lu\n", (unsigned long)sizeof(class gnui::Output));
  printf("  sizeof(gnui::Menu) = %lu\n", (unsigned long)sizeof(class gnui::Menu));
  printf("    sizeof(gnui::Choice) = %lu\n", (unsigned long)sizeof(class gnui::Choice));
  printf("    sizeof(gnui::MenuBar) = %lu\n", (unsigned long)sizeof(class gnui::MenuBar));
  printf("    sizeof(gnui::PopupMenu) = %lu\n", (unsigned long)sizeof(class gnui::PopupMenu));
  printf("  sizeof(gnui::ThumbWheel) = %lu\n", (unsigned long)sizeof(class gnui::ThumbWheel));
  printf("  sizeof(gnui::TextBuffer) = %lu\n", (unsigned long)sizeof(class gnui::TextBuffer));
  printf("  sizeof(gnui::Valuator) = %lu\n", (unsigned long)sizeof(class gnui::Valuator));
  printf("    sizeof(gnui::Adjuster) = %lu\n", (unsigned long)sizeof(class gnui::Adjuster));
  printf("    sizeof(gnui::Dial) = %lu\n", (unsigned long)sizeof(class gnui::Dial));
  printf("    sizeof(gnui::Slider) = %lu\n", (unsigned long)sizeof(class gnui::Slider));
  printf("      sizeof(gnui::Scrollbar) = %lu\n", (unsigned long)sizeof(class gnui::Scrollbar));
  printf("    sizeof(gnui::ValueInput) = %lu\n", (unsigned long)sizeof(class gnui::ValueInput));
  return 0;
}
