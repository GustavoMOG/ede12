//
// "$Id: Shortcut_Button.h 1562 2005-04-03 12:09:07Z vljubovic $"
//
// Shortcut header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-1999 by Bill Spitzak and others.
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
// Please report all bugs and problems to "fltk-bugs@easysw.com".
//

#ifndef Shortcut_Button_H
#define Shortcut_Button_H

#include <efltk/Fl_Button.h>

class Shortcut_Button : public Fl_Button {
public:
  int svalue;
  int handle(int);
  void draw();
  Shortcut_Button(int x, int y, int w, int h, const char* l = 0) :
    Fl_Button(x,y,w,h,l) {svalue = 0;}
};

//
// End of "$Id: Shortcut_Button.h 1562 2005-04-03 12:09:07Z vljubovic $".
//
#endif