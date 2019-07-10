/* "$Id$"
 *
 * Copyright 1998-2006 by Bill Spitzak and others.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Please report all bugs and problems to the following page:
 *
 *    http://www.gnui.org/str.php
 */
/*! \file
  Functions to manipulate UTF-8 strings and convert from/to legacy
  encodings. These functions are \e not in the gnui namespace.
*/

#ifndef gnui_utf_h
#define gnui_utf_h

#include "GNUI_API.h"
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

GNUI_API int	utf8bytes(unsigned ucs);

GNUI_API unsigned	utf8decode(const char*, const char* end, int* len);
GNUI_API int	utf8encode(unsigned, char*);
GNUI_API const char* utf8fwd(const char*, const char* start, const char* end);
GNUI_API const char* utf8back(const char*, const char* start, const char* end);

GNUI_API unsigned	utf8towc(const char*, unsigned, wchar_t*, unsigned);
GNUI_API unsigned utf8tomb(const char*, unsigned, char*, unsigned);
GNUI_API unsigned utf8toa (const char*, unsigned, char*, unsigned);
GNUI_API unsigned utf8fromwc(char*, unsigned, const wchar_t*, unsigned);
GNUI_API unsigned utf8frommb(char*, unsigned, const char*, unsigned);
GNUI_API unsigned utf8froma (char*, unsigned, const char*, unsigned);
GNUI_API int utf8locale();
GNUI_API int utf8test(const char*, unsigned);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
