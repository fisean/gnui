// "$Id$"
//
// The basic gnui runtime. Every program needs to call this somewhere.
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
//    http://www.gnui.org/str.php

#ifndef gnui_run_h
#define gnui_run_h

#include "GNUI_API.h"
#include <stdio.h>
#ifdef check
# undef check
#endif

namespace gnui {

/// \name gnui/run.h
//@{

GNUI_API void display(const char*);
GNUI_API int arg(int, char**, int&);
GNUI_API int args(int, char**, int&, int (*)(int,char**,int&) = 0);
extern GNUI_API const char* const help;
GNUI_API void args(int, char**);
GNUI_API bool enable_tablet_events();

GNUI_API int wait();
GNUI_API int wait(float time);
GNUI_API int check();
GNUI_API int ready();
GNUI_API int run();
GNUI_API void flush();
GNUI_API void redraw();
extern GNUI_API int damage_;
inline void damage(int d) {damage_ = d;}
inline int damage() {return damage_;}

/*! Type of function passed to add_timeout(), add_check(), and add_idle() */
typedef void (*TimeoutHandler)(void*);

GNUI_API double get_time_secs();

GNUI_API void add_timeout(float t, TimeoutHandler, void* v = 0);
GNUI_API void repeat_timeout(float t, TimeoutHandler,void* = 0);
GNUI_API bool has_timeout(TimeoutHandler, void* = 0);
GNUI_API void remove_timeout(TimeoutHandler, void* = 0);

GNUI_API void add_check(TimeoutHandler, void* = 0);
GNUI_API bool has_check(TimeoutHandler, void* = 0);
GNUI_API void remove_check(TimeoutHandler, void* = 0);

GNUI_API void add_idle(TimeoutHandler, void* = 0);
GNUI_API bool has_idle(TimeoutHandler, void* = 0);
GNUI_API void remove_idle(TimeoutHandler, void* = 0);

// For back-compatability only:
extern GNUI_API void (*idle)();
inline void set_idle(void (*cb)()) {idle = cb;}

/*! Type of function passed to add_fd() */
typedef void (*FileHandler)(int fd, void*);
enum {READ = 1, WRITE = 4, EXCEPT = 8};
GNUI_API void add_fd(int fd, int when, FileHandler, void* =0);
GNUI_API void add_fd(int fd, FileHandler, void* = 0);
GNUI_API void remove_fd(int, int when = -1);
GNUI_API FILE* gnui_fopen(const char* name, const char* flags);

GNUI_API void lock();
GNUI_API void unlock();
GNUI_API void awake(void* message = 0);
GNUI_API void* thread_message();
GNUI_API bool in_main_thread();

//@}

}

#endif
