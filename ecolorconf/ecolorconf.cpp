/*
 * $Id: ecolorconf.cpp 1653 2006-06-09 13:08:58Z karijes $
 *
 * EControl applet for colors and fonts
 * Part of Equinox Desktop Environment (EDE).
 * Copyright (c) 2000-2006 EDE Authors.
 *
 * This program is licenced under terms of the 
 * GNU General Public Licence version 2 or newer.
 * See COPYING for details.
 */

#include "ecolorconf.h"
#include <edeconf.h>
#include <efltk/Fl_Color_Chooser.h>
#include "ecolorutils.h"
Fl_Window* windowColorSettings;

static void cb_windowColorSettings(Fl_Window*, void*) {
	exit(0);
}
Fl_Button* colorBox;
Fl_Button* labelColorBox;
Fl_Button* selectionColorBox;
Fl_Button* selectionTextColorBox;
Fl_Button* highlightColorBox;
Fl_Button* highlightLabelColorBox;
Fl_Button* textColorBox;
Fl_Button* backgroundBox;
Fl_Button* textBackgroundBox;
Fl_Button* tooltipBox;
Fl_Button* tooltipTextColorButton;
Fl_Check_Button* tooltipsEnableEffects;
Fl_Check_Button* tooltipsEnable;
Fl_Choice* tooltipsEffectType;
Fl_Value_Input* tooltipsDelay;
Fl_Button* setLabelFont;

static void cb_setLabelFont(Fl_Button*, void*) {
	labelfont_cb();
}
Fl_Button* setTextFont;

static void cb_setTextFont(Fl_Button*, void*) {
	textfont_cb();
}
Fl_Box* labelFontInput;
Fl_Box* textFontInput;
Fl_Check_Button* menusEnableEffects;
Fl_Check_Button* menusEnableSubwindowEffects;
Fl_Choice* menusEffectType;
Fl_Value_Input* menusSpeed;
Fl_Value_Input* menusDelay;
Fl_Check_Button* mdiAnimation;
Fl_Check_Button* mdiOpaqueAnimation;
Fl_Check_Button* imagesStateEffect;

static void cb_Save(Fl_Button*, void*) {
	saveSchemeAs();
}
Fl_Check_Button* allApplyRadioButton;
Fl_Input_Browser* schemeListBox;

static void cb_schemeListBox(Fl_Input_Browser*, void*) {
	getSchemeColors();
}

static void cb_OK(Fl_Button*, void*) {
	//windowColorSettings->hide();
	saveActiveScheme();
	applyColors();
	saveEfltkConfig();
	exit(0);
}

static void cb_Apply(Fl_Button*, void*) {
	saveActiveScheme();
	applyColors();
	saveEfltkConfig();
}

static void cb_Cancel(Fl_Button*, void*) {
	exit(0);
}

int main (int argc, char **argv) {

	Fl_Window* w;
	fl_init_locale_support("ecolorconf", PREFIX"/share/locale");
	 {Fl_Window* o = windowColorSettings = new Fl_Window(330, 360, _("Colors and fonts settings"));
		w = o;
		o->shortcut(0xff1b);
		o->callback((Fl_Callback*)cb_windowColorSettings);
		 {Fl_Tabs* o = new Fl_Tabs(3, 5, 320, 195);
			o->color((Fl_Color)0xfffffffe);
			 {Fl_Group* o = new Fl_Group(1, 24, 318, 170, _("Default colors"));
				o->align(FL_ALIGN_TOP|FL_ALIGN_LEFT);
				o->hide();
				 {Fl_Button* o = colorBox = new Fl_Button(91, 31, 65, 20, _("Widgets"));
					o->box(FL_DOWN_BOX);
					o->callback((Fl_Callback*)ChangeBoxColor);
					o->align(FL_ALIGN_TOP|FL_ALIGN_LEFT|FL_ALIGN_WRAP);
				}
				 {Fl_Button* o = labelColorBox = new Fl_Button(16, 76, 65, 20, _("Label"));
					o->box(FL_DOWN_BOX);
					o->callback((Fl_Callback*)ChangeBoxColor);
					o->align(FL_ALIGN_TOP|FL_ALIGN_LEFT|FL_ALIGN_WRAP);
				}
				 {Fl_Button* o = selectionColorBox = new Fl_Button(241, 121, 65, 20, _("Sel. back."));
					o->box(FL_DOWN_BOX);
					o->callback((Fl_Callback*)ChangeBoxColor);
					o->align(FL_ALIGN_TOP|FL_ALIGN_LEFT|FL_ALIGN_WRAP);
				}
				 {Fl_Button* o = selectionTextColorBox = new Fl_Button(166, 121, 65, 20, _("Selection"));
					o->box(FL_DOWN_BOX);
					o->callback((Fl_Callback*)ChangeBoxColor);
					o->align(FL_ALIGN_TOP|FL_ALIGN_LEFT|FL_ALIGN_WRAP);
				}
				 {Fl_Button* o = highlightColorBox = new Fl_Button(166, 31, 65, 20, _("Highlight"));
					o->box(FL_DOWN_BOX);
					o->callback((Fl_Callback*)ChangeBoxColor);
					o->align(FL_ALIGN_TOP|FL_ALIGN_LEFT|FL_ALIGN_WRAP);
				}
				 {Fl_Button* o = highlightLabelColorBox = new Fl_Button(166, 76, 65, 20, _("Highlight"));
					o->box(FL_DOWN_BOX);
					o->callback((Fl_Callback*)ChangeBoxColor);
					o->align(FL_ALIGN_TOP|FL_ALIGN_LEFT|FL_ALIGN_WRAP);
				}
				 {Fl_Button* o = textColorBox = new Fl_Button(16, 121, 65, 20, _("Text"));
					o->box(FL_DOWN_BOX);
					o->callback((Fl_Callback*)ChangeBoxColor);
					o->align(FL_ALIGN_TOP|FL_ALIGN_LEFT|FL_ALIGN_WRAP);
				}
				 {Fl_Button* o = backgroundBox = new Fl_Button(16, 31, 65, 20, _("Background"));
					o->box(FL_DOWN_BOX);
					o->callback((Fl_Callback*)ChangeBoxColor);
					o->align(FL_ALIGN_TOP|FL_ALIGN_LEFT|FL_ALIGN_WRAP);
				}
				 {Fl_Button* o = textBackgroundBox = new Fl_Button(91, 121, 65, 20, _("Background"));
					o->box(FL_DOWN_BOX);
					o->callback((Fl_Callback*)ChangeBoxColor);
					o->align(FL_ALIGN_TOP|FL_ALIGN_LEFT|FL_ALIGN_WRAP);
				}
				o->end();
			}
			 {Fl_Group* o = new Fl_Group(1, 24, 318, 170, _("Tooltips"));
				o->align(FL_ALIGN_TOP|FL_ALIGN_LEFT);
				o->hide();
				 {Fl_Button* o = tooltipBox = new Fl_Button(157, 45, 65, 20, _("Tooltip color"));
					o->box(FL_DOWN_BOX);
					o->callback((Fl_Callback*)ChangeBoxColor);
					o->align(FL_ALIGN_TOP|FL_ALIGN_LEFT|FL_ALIGN_WRAP);
				}
				 {Fl_Button* o = tooltipTextColorButton = new Fl_Button(237, 45, 65, 20, _("Tooltip text color"));
					o->box(FL_DOWN_BOX);
					o->callback((Fl_Callback*)ChangeBoxColor);
					o->align(FL_ALIGN_TOP|FL_ALIGN_LEFT|FL_ALIGN_WRAP);
				}
				tooltipsEnableEffects = new Fl_Check_Button(7, 45, 145, 25, _("Enable effects"));
				tooltipsEnable = new Fl_Check_Button(7, 15, 145, 25, _("Enabled"));
				 {Fl_Choice* o = tooltipsEffectType = new Fl_Choice(77, 82, 115, 23, _("Effect type:")); o->begin();
					o->align(FL_ALIGN_LEFT|FL_ALIGN_WRAP);
					new Fl_Item(_("None"));
					new Fl_Item(_("Animation"));
					new Fl_Item(_("Fading"));
					o->end();
				}
				tooltipsDelay = new Fl_Value_Input(77, 120, 50, 25, _("Delay:"));
				o->end();
			}
			 {Fl_Group* o = new Fl_Group(1, 24, 318, 170, _("Fonts"));
				o->align(FL_ALIGN_TOP|FL_ALIGN_LEFT);
				 {Fl_Button* o = setLabelFont = new Fl_Button(276, 16, 30, 25, _("..."));
					o->callback((Fl_Callback*)cb_setLabelFont);
				}
				 {Fl_Button* o = setTextFont = new Fl_Button(276, 51, 30, 25, _("..."));
					o->callback((Fl_Callback*)cb_setTextFont);
				}
				 {Fl_Box* o = labelFontInput = new Fl_Box(76, 16, 190, 25, _("label"));
					o->box(FL_DOWN_BOX);
					o->align(FL_ALIGN_TOP|FL_ALIGN_LEFT|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
				}
				 {Fl_Box* o = textFontInput = new Fl_Box(76, 52, 190, 24, _("label"));
					o->box(FL_DOWN_BOX);
					o->align(FL_ALIGN_TOP|FL_ALIGN_LEFT|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
				}
				 {Fl_Box* o = new Fl_Box(11, 16, 65, 25, _("Label font:"));
					o->align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
				}
				 {Fl_Box* o = new Fl_Box(11, 51, 65, 25, _("Text font:"));
					o->align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
				}
				o->label(_(o->label()));
				o->end();
			}
			 {Fl_Group* o = new Fl_Group(1, 24, 318, 170, _("Menus"));
				o->hide();
				menusEnableEffects = new Fl_Check_Button(7, 5, 305, 25, _("Enable effects"));
				menusEnableSubwindowEffects = new Fl_Check_Button(7, 30, 305, 25, _("Enable subwindow effects"));
				 {Fl_Choice* o = menusEffectType = new Fl_Choice(77, 60, 115, 23, _("Effect type:")); o->begin();
					o->align(FL_ALIGN_LEFT|FL_ALIGN_WRAP);
					new Fl_Item(_("None"));
					new Fl_Item(_("Animation"));
					new Fl_Item(_("Fading"));
					o->end();
				}
				menusSpeed = new Fl_Value_Input(77, 95, 45, 25, _("Speed:"));
				menusDelay = new Fl_Value_Input(212, 95, 50, 25, _("Delay:"));
				o->end();
			}
			 {Fl_Group* o = new Fl_Group(1, 24, 318, 170, _("Others"));
				o->hide();
				mdiAnimation = new Fl_Check_Button(12, 10, 300, 25, _("Enable MDI animation"));
				mdiOpaqueAnimation = new Fl_Check_Button(12, 40, 300, 25, _("MDI opaque animation"));
				imagesStateEffect = new Fl_Check_Button(12, 70, 300, 25, _("Enable images state effect"));
				o->end();
			}
			o->end();
		}
		 {Fl_Group* o = new Fl_Group(3, 210, 320, 100);
			o->box(FL_DOWN_BOX);
			 {Fl_Button* o = new Fl_Button(197, 20, 80, 25, _("&Save as..."));
				o->callback((Fl_Callback*)cb_Save);
			}
			 {Fl_Check_Button* o = allApplyRadioButton = new Fl_Check_Button(9, 60, 299, 25, _("Ap&ply colors to all programs"));
				o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
				o->when(FL_WHEN_CHANGED);
			}
			 {Fl_Input_Browser* o = schemeListBox = new Fl_Input_Browser(12, 22, 175, 23, _("Schemes:")); o->begin();
				o->callback((Fl_Callback*)cb_schemeListBox);
				o->align(FL_ALIGN_TOP|FL_ALIGN_LEFT);
				o->when(FL_WHEN_CHANGED);
				o->type(1);
				fillItems();
				o->end();
			}
			o->end();
		}
		 {Fl_Button* o = new Fl_Button(75, 328, 80, 25, _("&OK"));
			o->callback((Fl_Callback*)cb_OK);
		}
		 {Fl_Button* o = new Fl_Button(160, 328, 80, 25, _("&Apply"));
			o->callback((Fl_Callback*)cb_Apply);
		}
		 {Fl_Button* o = new Fl_Button(245, 328, 80, 25, _("&Cancel"));
			o->callback((Fl_Callback*)cb_Cancel);
		}
		o->end();
		o->resizable(o);
	}
	//updateFontAll();
	loadEfltkConfig();
	w->show(argc, argv);
	return  Fl::run();
}

void ChangeBoxColor(Fl_Button *box, void *) {
	Fl_Button *colorBox = box;
	Fl_Color oldColor = colorBox->color();
	Fl_Color defColor = oldColor;
	fl_color_chooser(_("Choose color"), defColor);
	if (defColor != oldColor) 
	{
		colorBox->color(defColor);
		colorBox->highlight_color(defColor);
		colorBox->redraw();
	}
}
