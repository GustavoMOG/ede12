#
# $Id: Makefile 2124 2007-11-16 09:43:03Z karijes $
#
# Part of Equinox Desktop Environment (EDE).
# Copyright (c) 2000-2006 EDE Authors.
#
# This program is licenced under terms of the 
# GNU General Public Licence version 2 or newer.
# See COPYING for details.

CPPFILES = ecolorconf.cpp ecolorutils.cpp efontdialog.cpp
TARGET   = ecolorconf

POFILES = locale/ru.po\
			locale/sr.po\
			locale/sk.po\
			locale/hu.po\
			locale/de.po\
			locale/fr.po

include ../makeinclude

install:
	$(INSTALL_PROGRAM) $(TARGET) $(bindir)
	$(INSTALL_LOCALE)

uninstall:
	$(RM) $(bindir)/$(TARGET)

clean:
	$(RM) $(TARGET)
	$(RM) *.o
