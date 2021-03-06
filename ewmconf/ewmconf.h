/*
 * $Id: ewmconf.h 1654 2006-06-09 13:44:34Z karijes $
 *
 * Ewmconf, window manager configuration tool
 * Part of Equinox Desktop Environment (EDE).
 * Copyright (c) 2000-2006 EDE Authors.
 *
 * This program is licenced under terms of the 
 * GNU General Public Licence version 2 or newer.
 * See COPYING for details.
 */

#ifndef ewmconf_h
#define ewmconf_h
#include <efltk/Fl.h>
#include <efltk/Fl_Locale.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Tabs.h>
#include <efltk/Fl_Group.h>
#include <efltk/Fl_Choice.h>
#include <efltk/Fl_Item.h>
#include <efltk/Fl_Value_Input.h>
#include <efltk/Fl_Button.h>
extern Fl_Button* titlebarLabelColorButton;
extern Fl_Button* titlebarColorButton;
extern Fl_Button* titlebarActiveLabelColorButton;
extern Fl_Button* titlebarActiveColorButton;
extern Fl_Choice* titlebarDrawGrad;
#include <efltk/Fl_Check_Button.h>
extern Fl_Check_Button* useThemeButton;
#include <efltk/Fl_Input.h>
extern Fl_Input* themePathInput;
extern Fl_Button* browse_btn;
#include <efltk/Fl_Divider.h>
extern Fl_Check_Button* animateButton;
#include <efltk/Fl_Value_Slider.h>
extern Fl_Value_Slider* animateSlider;
extern Fl_Check_Button* opaqueResize;
void changeBoxColor(Fl_Button *box);
#endif
