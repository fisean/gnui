//
// "$Id: Preferences.H 4458 2005-07-26 07:59:01Z matt $"
//
// Preferences definitions for the Fast Light Tool Kit (FLTK).
//
// Copyright 2002-2005 by Matthias Melcher.
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
//     http://www.fltk.org/str.php
//

#ifndef Preferences_H
#  define Preferences_H

#  ifdef WIN32
#    include <windows.h>
#  endif // WIN32

#  include <stdio.h>
#  include <fltk/FL_API.h>


namespace fltk {

/**
 * Preferences are a data tree containing a root, branches and leafs
 */
class FL_API Preferences 
{

public:

  enum Root { SYSTEM=0, USER };
  // enum Type { win32, macos, fltk };

  Preferences( Root root, const char *vendor, const char *application );
  Preferences( const char *path, const char *vendor, const char *application );
  Preferences( Preferences&, const char *group );
  Preferences( Preferences*, const char *group );
  ~Preferences();

  int groups();
  const char *group( int );
  char groupExists( const char *group );
  char deleteGroup( const char *group );

  int entries();
  const char *entry( int );
  char entryExists( const char *entry );
  char deleteEntry( const char *entry );

  char set( const char *entry, int value );
  char set( const char *entry, float value );
  char set( const char *entry, double value );
  char set( const char *entry, const char *value );
  char set( const char *entry, const void *value, int size ); 

  char get( const char *entry, int &value,    int defaultValue );
  char get( const char *entry, float &value,  float defaultValue );
  char get( const char *entry, double &value, double defaultValue );
  char get( const char *entry, char *&value,  const char *defaultValue );
  char get( const char *entry, char *value,   const char *defaultValue, int maxSize );
  char get( const char *entry, void *&value,  const void *defaultValue, int defaultSize );
  char get( const char *entry, void *value,   const void *defaultValue, int defaultSize, int maxSize );
  int size( const char *entry );

  char getUserdataPath( char *path, int pathlen );

  void flush();

  // char export( const char *filename, Type fileFormat );
  // char import( const char *filename );

  class FL_API Name {
    char *data_;
  public:
    Name( unsigned int n );
    Name( const char *format, ... );
    operator const char *() { return data_; }
    ~Name();
  };

  struct Entry
  {
    char *name, *value;
  };

private:

  // make the following functions unavailable
  Preferences(); 
  Preferences(const Preferences&); 
  Preferences &operator=(const Preferences&);

  static char nameBuffer[128];

  class FL_API Node // a node contains a list to all its entries 
  {          // and all means to manage the tree structure
    Node *child_, *next_, *parent_;
    char *path_;
    char dirty_;
  public:
    Node( const char *path );
    ~Node();
    // node methods
    int write( FILE *f );
    Node *find( const char *path );
    Node *search( const char *path, int offset=0 );
    Node *addChild( const char *path );
    void setParent( Node *parent );
    Node *parent() { return parent_; }
    char remove();
    char dirty();
    // entry methods
    int nChildren();
    const char *child( int ix );
    void set( const char *name, const char *value );
    void set( const char *line );
    void add( const char *line );
    const char *get( const char *name );
    int getEntry( const char *name );
    char deleteEntry( const char *name );
    // public values
    Entry *entry;
    int nEntry, NEntry;
    static int lastEntrySet;
  };
  friend class Node;

  class FL_API RootNode  // the root node manages file paths and basic reading and writing
  {
    Preferences *prefs_;
    char *filename_;
    char *vendor_, *application_;
  public:
    RootNode( Preferences *, Root root, const char *vendor, const char *application );
    RootNode( Preferences *, const char *path, const char *vendor, const char *application );
    ~RootNode();
    int read();
    int write();
    char getPath( char *path, int pathlen );
  };
  friend class RootNode;

  Node *node;
  RootNode *rootNode;
  
};

}

#endif // !Preferences_H

//
// End of "$Id: Preferences.H 4458 2005-07-26 07:59:01Z matt $".
//
