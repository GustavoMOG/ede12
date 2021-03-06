/*
 * $Id: escrsaverconf.h 1654 2006-06-09 13:44:34Z karijes $
 *
 * Esvrconf, screensaver configuration tool
 * Part of Equinox Desktop Environment (EDE).
 * Copyright (c) 2000-2006 EDE Authors.
 *
 * This program is licenced under terms of the 
 * GNU General Public Licence version 2 or newer.
 * See COPYING for details.
 */

#ifndef escrsaverconf_h
#define escrsaverconf_h
#include <efltk/Fl.h>
#include <efltk/Fl_Window.h>
extern Fl_Window* mainWindow;
#include <efltk/Fl_Group.h>
#include <efltk/Fl_Input_Browser.h>
extern Fl_Input_Browser* saversList;
#include <efltk/Fl_Value_Input.h>
extern Fl_Value_Input* timeoutSlider;
#include <efltk/Fl_Button.h>
extern Fl_Group* dpmsGroup;
extern Fl_Value_Input* standbySlider;
extern Fl_Value_Input* suspendSlider;
extern Fl_Value_Input* offSlider;
#include <efltk/Fl_Check_Button.h>
extern Fl_Check_Button* enableDPMSCheck;
#include <efltk/Fl_Box.h>
extern Fl_Window* saverWindow;
int main(int argc, char **argv);
#endif
