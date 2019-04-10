//
// "$Id$"
//
// Keyboard/event test program for the Fast Light Tool Kit (FLTK).
//
// Continuously display FLTK's event state.
//
// Known bugs:
//
// X insists on reporting the state *before* the shift key was
// pressed, rather than after, on shift key events.  I fixed this for
// the mouse buttons, but it did not seem worth it for shift.
//
// X servers do not agree about any shift flags except shift, ctrl,
// lock, and alt.  They may also not agree about the symbols for the extra
// keys Micro$oft put on the keyboard.
//
// Windows has a number of keys that do not report that they are held down.
// On IRIX the backslash key does not report it is held down.
//
// Copyright 2001 by Bill Spitzak and others.
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

#include "keyboard_ui.cxx"
#include <stdio.h>
#include <ctype.h>
#include <fltk/run.h>

// these are used to identify which buttons are which:
void key_cb(gnui::Button*, void*) {}
void shift_cb(gnui::Button*, void*) {}

static struct {int n; const char* text;} table[] = {
  {gnui::EscapeKey, "gnui::EscapeKey"},
  {gnui::BackSpaceKey, "gnui::BackSpaceKey"},
  {gnui::TabKey, "gnui::TabKey"},
  {gnui::ReturnKey, "gnui::ReturnKey"},
  {gnui::PrintKey, "gnui::PrintKey"},
  {gnui::ScrollLockKey, "gnui::ScrollLockKey"},
  {gnui::PauseKey, "gnui::PauseKey"},
  {gnui::InsertKey, "gnui::InsertKey"},
  {gnui::HomeKey, "gnui::HomeKey"},
  {gnui::PageUpKey, "gnui::PageUpKey"},
  {gnui::DeleteKey, "gnui::DeleteKey"},
  {gnui::EndKey, "gnui::EndKey"},
  {gnui::PageDownKey, "gnui::PageDownKey"},
  {gnui::LeftKey, "gnui::LeftKey"},
  {gnui::UpKey, "gnui::UpKey"},
  {gnui::RightKey, "gnui::RightKey"},
  {gnui::DownKey, "gnui::DownKey"},
  {gnui::LeftShiftKey, "gnui::LeftShiftKey"},
  {gnui::RightShiftKey, "gnui::RightShiftKey"},
  {gnui::LeftCtrlKey, "gnui::LeftCtrlKey"},
  {gnui::RightCtrlKey, "gnui::RightCtrlKey"},
  {gnui::CapsLockKey, "gnui::CapsLockKey"},
  {gnui::LeftAltKey, "gnui::LeftAltKey"},
  {gnui::RightAltKey, "gnui::RightAltKey"},
  {gnui::LeftMetaKey, "gnui::LeftMetaKey"},
  {gnui::RightMetaKey, "gnui::RightMetaKey"},
  {gnui::MenuKey, "gnui::MenuKey"},
  {gnui::NumLockKey, "gnui::NumLockKey"},
  {gnui::KeypadEnter, "gnui::KeypadEnter"},
  {gnui::MultiplyKey, "gnui::MultiplyKey"},
  {gnui::AddKey, "gnui::AddKey"},
  {gnui::SubtractKey, "gnui::SubtractKey"},
  {gnui::DecimalKey, "gnui::DecimalKey"},
  {gnui::DivideKey, "gnui::DivideKey"},
  {gnui::Keypad0, "gnui::Keypad0"},
  {gnui::Keypad1, "gnui::Keypad1"},
  {gnui::Keypad2, "gnui::Keypad2"},
  {gnui::Keypad3, "gnui::Keypad3"},
  {gnui::Keypad4, "gnui::Keypad4"},
  {gnui::Keypad5, "gnui::Keypad5"},
  {gnui::Keypad6, "gnui::Keypad6"},
  {gnui::Keypad7, "gnui::Keypad7"},
  {gnui::Keypad8, "gnui::Keypad8"},
  {gnui::Keypad9, "gnui::Keypad9"},
  {gnui::SpaceKey,"gnui::SpaceKey (' ')"}
};

int main(int argc, char** argv) {
  gnui::Window *window = make_window();
  window->show(argc,argv);
  for (;;) {
    gnui::wait();
    if (!window->visible()) break;

    // update all the buttons with the current key and shift state:
    for (int i = 0; i < window->children(); i++) {
      gnui::Widget* b = window->child(i);
      if (b->callback() == (gnui::Callback*)key_cb) {
	unsigned i = (unsigned)b->argument();
	if (!i) i = tolower(b->label()[0]);
	((gnui::Button*)b)->value(gnui::event_key_state(i));
	if (i == gnui::event_key()) ((gnui::Button*)b)->take_focus();
      } else if (b->callback() == (gnui::Callback*)shift_cb) {
	unsigned i = (unsigned)b->argument();
	((gnui::Button*)b)->value(gnui::event_state(i));
      }
    }

    // figure out the keyname:
    char buffer[100];
    const char *keyname = buffer;
    int k = gnui::event_key();
    if (!k) {
      keyname = "0";
    } else if (k <= 7) {
      sprintf(buffer, "(mouse button %d)", k);
    } else if (k < 256 && k != 32) {
      sprintf(buffer, "'%c'", k);
    } else if (k >= gnui::F0Key && k <= gnui::LastFunctionKey) {
      sprintf(buffer, "gnui::F%dKey", k - gnui::F0Key);
    } else {
      sprintf(buffer, "0x%04x", k);
      for (int i = 0; i < int(sizeof(table)/sizeof(*table)); i++)
	if (table[i].n == k) {keyname = table[i].text; break;}
    }
    key_output->value(keyname);

    if (gnui::event_text()[0] == 32)
      text_output->value("\" \"");
    else if (gnui::event_text()[0])
      text_output->value(gnui::event_text());
    else
      text_output->value("\"\"");
  }
  return 0;
}

//
// End of "$Id$".
//
