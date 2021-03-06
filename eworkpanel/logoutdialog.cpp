// generated by Fast Light User Interface Designer (fluid) version 2,0003

// Work Panel for EDE is (C) Copyright 2000-2002 by Martin Pekar,
// this program is provided under the terms of GNU GPL v.2, see file COPYING for more information.
// Improvements by Vedran Ljubovic (c) 2005.

#include "logoutdialog.h"
#include <stdlib.h>
#include <efltk/Fl_Util.h>
#include <efltk/fl_ask.h>

#include <efltk/x.h>							  // X stuff
#include <signal.h>
#include <efltk/Fl_Image.h>						  // icons

// widgets
Fl_Window* windowLogoutDialog;
Fl_Round_Button* logoutRadioItemLogoutDialog;
Fl_Round_Button* restartRadioItemLogoutDialog;
Fl_Round_Button* shutdownRadioItemLogoutDialog;

// graphics
static Fl_Image penguin_pix((const char **)penguin_xpm);

// globals
bool dmAvailable;
char *xdm_fifo;
bool canShutdown;
bool sdForceNow;
bool sdTryNow;

void SendLogoutMsg(Fl_Window* win)
{
	Atom _XA_EDE_WM_ACTION = XInternAtom(fl_display, "_EDE_WM_ACTION", False);
	Atom _XA_EDE_WM_LOGOUT = XInternAtom(fl_display, "_EDE_WM_LOGOUT", False);
	XClientMessageEvent evt;
	memset(&evt, 0, sizeof(evt));
	evt.type = ClientMessage;
	evt.window = fl_xid(win);
	evt.format = 32;
	evt.message_type = _XA_EDE_WM_ACTION;
	evt.data.l[0] = _XA_EDE_WM_LOGOUT;
	XSendEvent(fl_display, RootWindow(fl_display, DefaultScreen(fl_display)), False,
			SubstructureNotifyMask, (XEvent*)&evt);
}

// This function looks what a user can do and sets other
// global variables
void checkPermissions()
{
	Fl_String xdm_env = Fl_String(getenv("XDM_MANAGED"));
	if (xdm_env == "")
		dmAvailable = false;
	else
		dmAvailable = true;

	// shutting down via XDM fifo
	if (dmAvailable)
	{
		Fl_String_List xdm_env_list = Fl_String_List(xdm_env,",");
		xdm_fifo = xdm_env_list.item(0);
		if (xdm_fifo[0] != '/')					  // broken config
		{
			dmAvailable = false;
			xdm_fifo = "";
		}

		// can a user shutdown?
		if (xdm_env_list.index_of("maysd")>-1)
			canShutdown = true;
		else
			canShutdown = false;

		// we will use fn/tn only if XDM suggests to do it
		if (xdm_env_list.index_of("fn")>-1)
			sdForceNow = true;
		else
			sdForceNow = false;

		if (xdm_env_list.index_of("tn")>-1)
			sdTryNow = true;
		else
			sdTryNow = false;
	}

	// the old way
	if (!dmAvailable)
	{
		// shutdown cmd with no params shouldn't do anything...
		if (fl_start_child_process("shutdown") == 127)
			canShutdown = false;
	}
}

// Logout using XDM messaging
void newLogoutFunction(Fl_Window* win)
{

	if ((logoutRadioItemLogoutDialog->value()==0) &&
		(restartRadioItemLogoutDialog->value()==0) &&
		(shutdownRadioItemLogoutDialog->value() == 0))
		// this shoudn't happen...
		return;

	if (restartRadioItemLogoutDialog->value()==1)
	{
		if (!canShutdown)
		{
			fl_alert (_("You are not allowed to restart !"));
			return;
		}

		FILE *fd = fopen(xdm_fifo, "w");
		Fl_String method;
		if (sdForceNow)
			method = "shutdown\treboot\tforcenow\n";
		else if (sdTryNow)
			method = "shutdown\treboot\ttrynow\n";
		else
			method = "shutdown\treboot\tschedule\n";
		fputs ((char *)method, fd);
		fclose (fd);
	}

	if (shutdownRadioItemLogoutDialog->value() == 1)
	{
		if (!canShutdown)
		{
			fl_alert (_("You are not allowed to shutdown !"));
			return;
		}

		FILE *fd = fopen(xdm_fifo, "w");
		Fl_String method;
		if (sdForceNow)
			method = "shutdown\thalt\tforcenow\n";
		else if (sdTryNow)
			method = "shutdown\thalt\ttrynow\n";
		else
			method = "shutdown\thalt\tschedule\n";
		fputs ((char *)method, fd);
		fclose (fd);
	}

	SendLogoutMsg(win);
	XCloseDisplay(fl_display);
	exit(0);

	//XCloseDisplay(fl_display);
	//XSetCloseDownMode(fl_display, DestroyAll);
	//XKillClient(fl_display, AllTemporary);
	//XUngrabServer(fl_display);
	//fl_close_display();
	//exit(0);
}

// "brute force" logout function
// (in case XDM is not available)
void oldLogoutFunction(Fl_Window* win)
{
	if (logoutRadioItemLogoutDialog->value()==1)
	{
		SendLogoutMsg(win);
		XCloseDisplay(fl_display);
		exit(0);
		//XKillClient(fl_display, AllTemporary);
		//XUngrabServer(fl_display);
		//fl_close_display();
		//XCloseDisplay(fl_display);
		//exit(0);
	}

	if (restartRadioItemLogoutDialog->value()==1)
	{
		if(fl_start_child_process( "shutdown -r now" ) != 0)
			fl_alert("You are not alowed to reboot !");
	}

	if (shutdownRadioItemLogoutDialog->value() == 1)
	{
		if(fl_start_child_process( "shutdown -h now" ) != 0)
			fl_alert("You are not alowed to shutdown !");
	}
}

// Determine logout type
void LogoutFunction(Fl_Widget *, void* w)
{
	Fl_Window* win = (Fl_Window*)w;
	if (dmAvailable)
		newLogoutFunction(win);
	else
		oldLogoutFunction(win);
}

// Main logout UI and control
static void cb_Cancel(Fl_Button*, void*)
{
	windowLogoutDialog->hide();
}

void LogoutDialog(Fl_Widget*, void *)
{
	// first see what options are available
	checkPermissions();

	// draw GUI
	Fl_Window* w;
	{
		Fl_Window* o = windowLogoutDialog = new Fl_Window(171, 160, 330, 190, _("Logout"));
		w = o;
		{
			Fl_Group* o = new Fl_Group(5, 12, 55, 45);
			o->image(penguin_pix);
			o->align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
			o->end();
		}
		{
			Fl_Round_Button* o = logoutRadioItemLogoutDialog = new Fl_Round_Button(80, 67, 225, 20, _("&logout from the current session"));
			o->type(Fl_Round_Button::RADIO);
			o->value(1);
			o->tooltip(_("Logout from the current session."));
		}
		{
			Fl_Round_Button* o = restartRadioItemLogoutDialog = new Fl_Round_Button(80, 88, 225, 20, _("&restart the computer"));
			o->type(Fl_Round_Button::RADIO);
			if (canShutdown)
				o->tooltip(_("Restart the computer."));
			else
			{
				o->tooltip(_("Restart the computer. You do not have privileges to do that."));
				o->deactivate();
			}
		}
		{
			Fl_Round_Button* o = shutdownRadioItemLogoutDialog = new Fl_Round_Button(80, 110, 225, 20, _("&shut down the computer"));
			o->type(Fl_Round_Button::RADIO);
			if (canShutdown)
				o->tooltip(_("Shut down the computer."));
			else
			{
				o->tooltip(_("Shut down the computer. You do not have privileges to do that."));
				o->deactivate();
			}
		}
		{
			Fl_Button* o = new Fl_Button(85, 157, 80, 25, _("&OK"));
			o->callback((Fl_Callback*)LogoutFunction, w);
		}
		{
			Fl_Button* o = new Fl_Button(170, 157, 80, 25, _("&Cancel"));
			o->callback((Fl_Callback*)cb_Cancel);
		}
		{
			Fl_Box* o = new Fl_Box(65, 7, 260, 63, _("Logout, restart or shut down the computer?"));
			o->label_size(18);
			o->align(132|FL_ALIGN_INSIDE);
		}

		new Fl_Divider(60, 130, 210, 20, "");
		o->x( Fl::info().w/2 - (o->w()/2) );
		o->y( (Fl::info().h/2) - (o->h()/2) );
		o->set_modal();
		o->end();
	}
	windowLogoutDialog->end();
	windowLogoutDialog->show();
}
