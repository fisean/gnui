//
// "$Id$"
//
// MacOS image drawing code for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2003 by Bill Spitzak and others.
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
// Please report all bugs and problems to "fltk-bugs@fltk.org".
//

////////////////////////////////////////////////////////////////

#include <fltk/events.h>
#include <fltk/draw.h>
#include <fltk/x.h>
using namespace fltk;

#define MAXBUFFER 0x40000 // 256k

extern bool fl_drawing_offscreen;
extern CGImageRef* fl_put_image_here;

static void innards(const uchar *buf,
		    fltk::PixelType pixeltype,
		    const fltk::Rectangle &r1,
		    int delta, int linedelta,
		    DrawImageCallback cb, void* userdata)
{
  fltk::Rectangle r(r1); transform(r);
  fltk::Rectangle cr(r); if (!intersect_with_clip(cr)) return;


  int dx = cr.x()-r.x();
  int dy = cr.y()-r.y();
  int x = cr.x();
  int y = cr.y();
  int w = cr.w();
  int h = cr.h();
  if (buf) buf += dx*delta + dy*linedelta;

  const uchar *array = buf;
  U32* tmpBuf = 0;
  if (cb) {
    linedelta = (w*delta+3)&-4;
    int n = (linedelta*h+(r1.w()*delta-linedelta)+3)/4;
    tmpBuf = new U32[n];
    array = (uchar*)tmpBuf;
    for (int i=0; i<h; i++) {
      uchar* dest = (uchar*)array+i*linedelta;
      const uchar* ret = cb(userdata, dx, dy+i, w, dest);
      if (ret != dest) memcpy(dest, ret, w*delta);
    }
  }

  // create an image context
  static CGColorSpaceRef lut = 0;
  if (!lut) lut = CGColorSpaceCreateDeviceRGB();
  CGDataProviderRef src = CGDataProviderCreateWithData( 0L, array, linedelta*h, 0L);
  CGImageAlphaInfo cgtype = kCGImageAlphaNone;
  switch (pixeltype) {
  case MASK: cgtype = kCGImageAlphaOnly; break;
  case RGBA: cgtype = kCGImageAlphaPremultipliedLast; break;
//   case ARGB: cgtype = kCGImageAlphaPremultipliedFirst; break;
//   case RGBM: cgtype = kCGImageAlphaLast; break;
//   case MRGB: cgtype = kCGImageAlphaFirst; break;
  }
  CGImageRef        img = CGImageCreate( w, h, 8, 8*delta, linedelta,
					 lut, cgtype,
					 src, 0L, false,
					 kCGRenderingIntentDefault);
  // draw the image into the destination context
  if (fl_drawing_offscreen && fl_put_image_here) {
    // If we are making an Image, we have to remember the CGImage so we
    // can use it to draw the Image later. If there is a way to update
    // an existing CGImage this would be less of a kludge.
    if (*fl_put_image_here) CGImageRelease(*fl_put_image_here);
    *fl_put_image_here = img;
  } else if (img) {
    CGRect rect = { x, y, w, h };
    fltk::begin_quartz_image(rect, Rectangle(0, 0, w, h));
    CGContextDrawImage(quartz_gc, rect, img);
    fltk::end_quartz_image();
    // release all allocated resources
    CGImageRelease(img);
  } else {
#if 0
    // Otherwise creating the image did not work, just draw all the pixels (!)
    CGContextSetShouldAntialias(quartz_gc, false);
    for ( int i=0; i<h; i++ ) {
      const uchar *src = array+i*linedelta;
      for ( int j=0; j<w; j++ ) {
        if ( pixeltype==LUMINANCE )
          color( src[0], src[0], src[0] );
        else
          color( src[0], src[1], src[2] );
        CGContextMoveToPoint(quartz_gc, x+j, y+i);
        CGContextAddLineToPoint(quartz_gc, x+j, y+i);
        CGContextStrokePath(quartz_gc);
        src += delta;

      }
    }
    CGContextSetShouldAntialias(quartz_gc, true);
#endif
  }
  CGDataProviderRelease(src);
  // ARRGH! Huge memory leak! I need a way to copy the image to the
  // CGImageRef, so this can be deleted at all times!
  if (!(fl_drawing_offscreen && fl_put_image_here)) delete[] tmpBuf;
}

void fltk::begin_quartz_image(CGRect &rect, const Rectangle &c) {
  CGContextSaveGState(quartz_gc);
  CGAffineTransform mx = CGContextGetCTM(quartz_gc);
  CGRect r2 = rect;
  r2.origin.x -= 0.5f;
  r2.origin.y -= 0.5f;
  CGContextClipToRect(quartz_gc, r2);
  mx.d = -1.0; mx.tx = -mx.tx;
  CGContextConcatCTM(quartz_gc, mx);
  rect.origin.x = rect.origin.x - c.x();
  rect.origin.y = (mx.ty+0.5f) - rect.origin.y - c.h() + c.y();
  rect.size.width = c.w();
  rect.size.height = c.h();
}

void fltk::end_quartz_image() {
  CGContextRestoreGState(quartz_gc);
}

//
// End of "$Id$".
//