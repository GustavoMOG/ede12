/*
 * $Id: ecolorconf.h 1653 2006-06-09 13:08:58Z karijes $
 *
 * EControl applet for colors and fonts
 * Part of Equinox Desktop Environment (EDE).
 * Copyright (c) 2000-2006 EDE Authors.
 *
 * This program is licenced under terms of the 
 * GNU General Public Licence version 2 or newer.
 * See COPYING for details.
 */

#ifndef _ECOLORCONF_H_
#define _ECOLORCONF_H_

#include <efltk/Fl.h>
#include <efltk/Fl_Locale.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Tabs.h>
#include <efltk/Fl_Group.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_Check_Button.h>
#include <efltk/Fl_Choice.h>
#include <efltk/Fl_Item.h>
#include <efltk/Fl_Value_Input.h>
#include <efltk/Fl_Box.h>
#include <efltk/Fl_Input_Browser.h>

extern void ChangeBoxColor(Fl_Button*, void*);

extern Fl_Window* windowColorSettings;
extern Fl_Button* colorBox;
extern Fl_Button* labelColorBox;
extern Fl_Button* selectionColorBox;
extern Fl_Button* selectionTextColorBox;
extern Fl_Button* highlightColorBox;
extern Fl_Button* highlightLabelColorBox;
extern Fl_Button* textColorBox;
extern Fl_Button* backgroundBox;
extern Fl_Button* textBackgroundBox;
extern Fl_Button* tooltipBox;
extern Fl_Button* tooltipTextColorButton;
extern Fl_Check_Button* tooltipsEnableEffects;
extern Fl_Check_Button* tooltipsEnable;
extern Fl_Choice* tooltipsEffectType;
extern Fl_Value_Input* tooltipsDelay;
extern Fl_Button* setLabelFont;
extern Fl_Button* setTextFont;
extern Fl_Box* labelFontInput;
extern Fl_Box* textFontInput;
extern Fl_Check_Button* menusEnableEffects;
extern Fl_Check_Button* menusEnableSubwindowEffects;
extern Fl_Choice* menusEffectType;
extern Fl_Value_Input* menusSpeed;
extern Fl_Value_Input* menusDelay;
extern Fl_Check_Button* mdiAnimation;
extern Fl_Check_Button* mdiOpaqueAnimation;
extern Fl_Check_Button* imagesStateEffect;
extern Fl_Check_Button* allApplyRadioButton;
extern Fl_Input_Browser* schemeListBox;

void ChangeBoxColor(Fl_Button *box, void *);

#endif
