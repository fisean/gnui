//
// "$Id: TextBuffer.h,v 1.1 2002/12/09 04:47:59 spitzak Exp $"
//
// Innards of the TextEditor Widget. It's not clear if this header
// file needs to be public.
//
// Copyright Mark Edel.  Permission to distribute under the LGPL for
// the FLTK library granted by Mark Edel.
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

#ifndef fltk_TextBuffer_h
#define fltk_TextBuffer_h

#include "FL_API.h"

namespace fltk {

class FL_API TextSelection {
  friend class TextBuffer;

  public:
    void set(int start, int end);
    void set_rectangular(int start, int end, int rectStart, int rectEnd);
    void update(int pos, int nDeleted, int nInserted);
    char rectangular() { return mRectangular; }
    int start() { return mStart; }
    int end() { return mEnd; }
    int rect_start() { return mRectStart; }
    int rect_end() { return mRectEnd; }
    char selected() { return mSelected; }
    void selected(char b) { mSelected = b; }
    int includes(int pos, int lineStartPos, int dispIndex);
    int position(int* start, int* end);
    int position(int* start, int* end, int* isRect, int* rectStart, int* rectEnd);


  protected:
    char mSelected;
    char mRectangular;
    int mStart;
    int mEnd;
    int mRectStart;
    int mRectEnd;
};

typedef void (*TextModifyCb)(int pos, int nInserted, int nDeleted,
                                  int nRestyled, const char* deletedText,
                                  void* cbArg);

class FL_API TextBuffer {
  public:
    TextBuffer(int requestedSize = 0);
    ~TextBuffer();

    enum {MAX_EXP_CHAR_LEN = 20};

    int length() { return mLength; }
    const char* text();
    void text(const char* text);
    const char* text_range(int start, int end);
    char character(int pos);
    const char* text_in_rectangle(int start, int end, int rectStart, int rectEnd);
    void insert(int pos, const char* text);
    void append(const char* text) { insert(length(), text); }
    void remove(int start, int end);
    void replace(int start, int end, const char *text);
    void copy(TextBuffer* fromBuf, int fromStart, int fromEnd, int toPos);
    int insertfile(const char *file, int pos, int buflen = 128*1024);
    int appendfile(const char *file, int buflen = 128*1024)
      { return insertfile(file, length(), buflen); }
    int loadfile(const char *file, int buflen = 128*1024)
      { select(0, length()); remove_selection(); return appendfile(file, buflen); }
    int outputfile(const char *file, int start, int end, int buflen = 128*1024);
    int savefile(const char *file, int buflen = 128*1024)
      { return outputfile(file, 0, length(), buflen); }

    void insert_column(int column, int startPos, const char* text,
                       int* charsInserted, int* charsDeleted);

    void replace_rectangular(int start, int end, int rectStart, int rectEnd,
                             const char* text);

    void overlay_rectangular(int startPos, int rectStart, int rectEnd,
                             const char* text, int* charsInserted,
                             int* charsDeleted);

    void remove_rectangular(int start, int end, int rectStart, int rectEnd);
    void clear_rectangular(int start, int end, int rectStart, int rectEnd);
    int tab_distance() { return mTabDist; }
    void tab_distance(int tabDist);
    void select(int start, int end);
    int selected() { return mPrimary.selected(); }
    void unselect();
    void select_rectangular(int start, int end, int rectStart, int rectEnd);
    int selection_position(int* start, int* end);

    int selection_position(int* start, int* end, int* isRect, int* rectStart,
                           int* rectEnd);

    const char* selection_text();
    void remove_selection();
    void replace_selection(const char* text);
    void secondary_select(int start, int end);
    void secondary_unselect();

    void secondary_select_rectangular(int start, int end, int rectStart,
                                      int rectEnd);

    int secondary_selection_position(int* start, int* end, int* isRect,
                                     int* rectStart, int* rectEnd);

    const char* secondary_selection_text();
    void remove_secondary_selection();
    void replace_secondary_selection(const char* text);
    void highlight(int start, int end);
    void unhighlight();
    void highlight_rectangular(int start, int end, int rectStart, int rectEnd);

    int highlight_position(int* start, int* end, int* isRect, int* rectStart,
                           int* rectEnd);

    const char* highlight_text();
    void add_modify_callback(TextModifyCb bufModifiedCB, void* cbArg);
    void remove_modify_callback(TextModifyCb bufModifiedCB, void* cbArg);

    void call_modify_callbacks() { call_modify_callbacks(0, 0, 0, 0, 0); }

    const char* line_text(int pos);
    int line_start(int pos);
    int line_end(int pos);
    int word_start(int pos);
    int word_end(int pos);
    int expand_character(int pos, int indent, char *outStr);

    static int expand_character(char c, int indent, char* outStr, int tabDist,
                                char nullSubsChar);

    static int character_width(char c, int indent, int tabDist, char nullSubsChar);
    int count_displayed_characters(int lineStartPos, int targetPos);
    int skip_displayed_characters(int lineStartPos, int nChars);
    int count_lines(int startPos, int endPos);
    int skip_lines(int startPos, int nLines);
    int rewind_lines(int startPos, int nLines);
    int findchar_forward(int startPos, char searchChar, int* foundPos);
    int findchar_backward(int startPos, char searchChar, int* foundPos);
    int findchars_forward(int startPos, const char* searchChars, int* foundPos);
    int findchars_backward(int startPos, const char* searchChars, int* foundPos);

    int search_forward(int startPos, const char* searchString, int* foundPos,
                       int matchCase = 0);

    int search_backward(int startPos, const char* searchString, int* foundPos,
                        int matchCase = 0);

    int substitute_null_characters(char* string, int length);
    void unsubstitute_null_characters(char* string);
    char null_substitution_character() { return mNullSubsChar; }
    TextSelection* primary_selection() { return &mPrimary; }
    TextSelection* secondary_selection() { return &mSecondary; }
    TextSelection* highlight_selection() { return &mHighlight; }

  protected:
    void call_modify_callbacks(int pos, int nDeleted, int nInserted,
                               int nRestyled, const char* deletedText);

    int insert_(int pos, const char* text);
    void remove_(int start, int end);

    void remove_rectangular_(int start, int end, int rectStart, int rectEnd,
                             int* replaceLen, int* endPos);

    void insert_column_(int column, int startPos, const char* insText,
                        int* nDeleted, int* nInserted, int* endPos);

    void overlay_rectangular_(int startPos, int rectStart, int rectEnd,
                              const char* insText, int* nDeleted,
                              int* nInserted, int* endPos);

    void redisplay_selection(TextSelection* oldSelection,
                             TextSelection* newSelection);

    void move_gap(int pos);
    void reallocate_with_gap(int newGapStart, int newGapLen);
    const char* selection_text(TextSelection* sel);
    void remove_selection_(TextSelection* sel);
    void replace_selection_(TextSelection* sel, const char* text);

    void rectangular_selection_boundaries(int lineStartPos, int rectStart,
                                          int rectEnd, int* selStart,
                                          int* selEnd);

    void update_selections(int pos, int nDeleted, int nInserted);

    TextSelection mPrimary; /* highlighted areas */
    TextSelection mSecondary;
    TextSelection mHighlight;
    int mLength;                /* length of the text in the buffer (the length
                                   of the buffer itself must be calculated:
                                   gapEnd - gapStart + length) */
    char* mBuf;                 /* allocated memory where the text is stored */
    int mGapStart;              /* points to the first character of the gap */
    int mGapEnd;                /* points to the first char after the gap */
    // The hardware tab distance used by all displays for this buffer,
    // and used in computing offsets for rectangular selection operations.
    int mTabDist;               /* equiv. number of characters in a tab */
    int mUseTabs;               /* True if buffer routines are allowed to use
                                   tabs for padding in rectangular operations */
    int mNModifyProcs;          /* number of modify-redisplay procs attached */
    TextModifyCb*          /* procedures to call when buffer is */
    mNodifyProcs;               /* modified to redisplay contents */
    void** mCbArgs;             /* caller arguments for modifyProcs above */
    int mCursorPosHint;         /* hint for reasonable cursor position after
                                   a buffer modification operation */
    char mNullSubsChar;         /* NEdit is based on C null-terminated strings,
                                   so ascii-nul characters must be substituted
                                   with something else.  This is the else, but
                                   of course, things get quite messy when you
                                   use it */
};

}

#endif

//
// End of "$Id: TextBuffer.h,v 1.1 2002/12/09 04:47:59 spitzak Exp $".
//