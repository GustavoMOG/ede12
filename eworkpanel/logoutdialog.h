// generated by Fast Light User Interface Designer (fluid) version 2,0003

#ifndef logoutdialog_h
#define logoutdialog_h


#include <efltk/Fl.h>
#include <efltk/Fl_Locale.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Group.h>
#include <efltk/Fl_Round_Button.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_Box.h>
#include <efltk/Fl_Divider.h>

#include "icons/penguin.xpm"


// which of these can be safely removed? what should be extern and
// what shouldn't?

extern Fl_Window* windowLogoutDialog;
extern Fl_Round_Button* logoutRadioItemLogoutDialog;
extern Fl_Round_Button* restartRadioItemLogoutDialog;
extern Fl_Round_Button* shutdownRadioItemLogoutDialog;
void LogoutFunction(Fl_Widget *, void *);
extern void LogoutFunction(Fl_Button*, void*);
void LogoutDialog(Fl_Widget*, void *);


#endif
