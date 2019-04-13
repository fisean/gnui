#
# "$Id$"
#
# Library makefile for the Fast Light Tool Kit (FLTK).
#
# Copyright 1998-2003 by Bill Spitzak and others.
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
# USA.
#
# Please report all bugs and problems to the following page:
#
#    http://www.gnui.org/str.php
#

#
# Include common definitions...
#

include ../makeinclude

#
# Files for this directory...
#

# The following should be added but they don't work as long as the images
# library is seperated:
#	HelpDialog.cxx \

CPPFILES = \
	add_idle.cxx \
	addarc.cxx \
	addcurve.cxx \
	Adjuster.cxx \
	AlignGroup.cxx \
	AnsiWidget.cxx \
	args.cxx \
	BarGroup.cxx \
	bmpImage.cxx \
	Browser.cxx \
	Browser_load.cxx \
	Button.cxx \
	CheckButton.cxx \
	Choice.cxx \
	clip.cxx \
	Clock.cxx \
	Color.cxx \
	color_chooser.cxx \
	ComboBox.cxx \
	compose.cxx \
	Cursor.cxx \
	CycleButton.cxx \
	default_glyph.cxx \
	Dial.cxx \
	DiamondBox.cxx \
	dnd.cxx \
	drawtext.cxx \
	EngravedLabel.cxx \
	error.cxx \
	event_key_state.cxx \
	file_chooser.cxx \
	FileBrowser.cxx \
	FileChooser.cxx \
	FileChooser2.cxx \
	FileIcon.cxx \
	FileInput.cxx \
	filename_absolute.cxx \
	filename_ext.cxx \
	filename_isdir.cxx \
	filename_list.cxx \
	filename_match.cxx \
	filename_name.cxx \
	fillrect.cxx \
	Fl_Menu_Item.cxx \
	FloatInput.cxx \
	gnui_theme.cxx \
	Font.cxx \
	gifImage.cxx \
	Group.cxx \
	GSave.cxx \
	HelpView.cxx \
	HighlightButton.cxx \
	Image.cxx \
	Input.cxx \
	InputBrowser.cxx \
	InvisibleWidget.cxx \
	Item.cxx \
	key_name.cxx \
	LightButton.cxx \
	list_fonts.cxx \
	load_plugin.cxx \
	lock.cxx \
	Menu.cxx \
	Menu_add.cxx \
	Menu_global.cxx \
	Menu_popup.cxx \
	MenuBar.cxx \
	MenuWindow.cxx \
	message.cxx \
	MultiImage.cxx \
	NumericInput.cxx \
	numericsort.cxx \
	Output.cxx \
	OvalBox.cxx \
	overlay_rect.cxx \
	own_colormap.cxx \
	PackedGroup.cxx \
	path.cxx \
	PlasticBox.cxx \
	PopupMenu.cxx \
	Preferences.cxx \
	ProgressBar.cxx \
	RadioButton.cxx \
	readimage.cxx \
	RepeatButton.cxx \
	ReturnButton.cxx \
	RoundBox.cxx \
	RoundedBox.cxx \
	run.cxx \
	Scrollbar.cxx \
	ScrollGroup.cxx \
	scrollrect.cxx \
	setcolor.cxx \
	setdisplay.cxx \
	setvisual.cxx \
	ShadowBox.cxx \
	ShapedWindow.cxx \
	SharedImage.cxx \
	ShortcutAssignment.cxx \
	show_colormap.cxx \
	Slider.cxx \
	StatusBarGroup.cxx \
	StringList.cxx \
	Style.cxx \
	StyleSet.cxx \
	Symbol.cxx \
	SystemMenuBar.cxx \
	TabGroup.cxx \
	TabGroup2.cxx \
	TextBuffer.cxx \
	TextDisplay.cxx \
	TextEditor.cxx \
	ThumbWheel.cxx \
	TiledGroup.cxx \
	TiledImage.cxx \
	Tooltip.cxx \
	UpBox.cxx \
	Valuator.cxx \
	ValueInput.cxx \
	ValueOutput.cxx \
	ValueSlider.cxx \
	Widget.cxx \
	Widget_draw.cxx \
	WidgetAssociation.cxx \
	Window.cxx \
	Window_fullscreen.cxx \
	Window_hotspot.cxx \
	Window_iconize.cxx \
	WizardGroup.cxx \
	xbmImage.cxx \
	xpmImage.cxx

CFILES	= scandir.c \
	string.c \
	utf.c \
	vsnprintf.c

LIBNAME	=	$(LIBPREFIX)gnui$(LIBSUFFIX)
DSONAME	=	$(DSOPREFIX)gnui$(DSOSUFFIX)
DSOLINK = 	$(DSOPREFIX)gnui$(DSOSYMLINK)
OBJECTS =	$(CPPFILES:.cxx=.o) $(CFILES:.c=.o)


#
# Make everything...
#

all:		$(LIBTARGET) $(DSOTARGET)

static:		../lib/$(LIBNAME)

shared:		../lib/$(DSONAME)


#
# Clean old files...
#

clean:
	$(RM) *.bck
	$(RM) *.o
	$(RM) core*
	$(RM) ../lib/$(LIBNAME)
	$(RM) ../lib/$(DSONAME)
        ifeq ($(DSONAME), gnui.dll)
	$(RM) lib$(DSONAME).a $(DSONAME)
        endif


#
# Make dependencies, excluding standard include directories...
#

depend:
	$(MAKEDEPEND) -I.. $(CPPFILES) $(CFILES) > makedepend


#
# Include automatically generated dependencies...
#
makedepend:
	touch makedepend
include makedepend


#
# Make static libraries...
#

../lib/$(LIBNAME): $(OBJECTS)
	$(RM) $@
	echo $(LIBCOMMAND) $@ ...
	$(LIBCOMMAND) $@ $(OBJECTS)
	$(RANLIB) $@

../lib/$(DSONAME): $(OBJECTS)
	echo $(DSOCOMMAND) $@ $(OBJECTS) -L../lib $(IMAGELIBS)
	$(DSOCOMMAND) $@ $(OBJECTS) $(LDLIBS)
	$(RM) ../lib/$(DSOLINK)
	$(LN) ../lib/$(DSONAME) ../lib/$(DSOLINK)

#
# Install everything...
# DESTDIR can be used as root directory (default empty, assuming '/')
# 

install:
	echo "Installing include files in $(includedir)/gnui..."
	if [ ! -z $(DESTDIR) ]; then                            \
		if [ -d $(DESTDIR) ]; then                          \
	    	echo "$(DESTDIR) exists - will be overwritten"; \
		else                                                \
			mkdir $(DESTDIR);                               \
		fi                                                  \
	fi

	$(RMDIR) $(DESTDIR)$(includedir)/gnui
	$(MKDIR) $(DESTDIR)$(includedir)/gnui
	$(CP) ../gnui/*.h ../gnui/*.r  $(DESTDIR)$(includedir)/gnui
	$(CHMOD) 755 $(DESTDIR)$(includedir)/gnui
	$(CHMOD) 644 $(DESTDIR)$(includedir)/gnui/*
	echo "Installing FLTK1.1 emulation include files in $(includedir)/gnui..."
	$(RMDIR) $(DESTDIR)$(includedir)/gnui/compat/FL
	$(MKDIR) $(DESTDIR)$(includedir)/gnui/compat/FL
	$(CP) ../gnui/compat/FL/*.H ../gnui/compat/FL/*.h  $(DESTDIR)$(includedir)/gnui/compat/FL
	$(CHMOD) 755 $(DESTDIR)$(includedir)/gnui/compat/FL
	$(CHMOD) 644 $(DESTDIR)$(includedir)/gnui/compat/FL/*
        ifneq (,$(wildcard ../gnui-config))
	echo "Installing gnui-config in $(bindir)..."
	$(MKDIR) $(DESTDIR)$(bindir)
	$(CP) ../gnui-config $(DESTDIR)$(bindir)
	$(CHMOD) 755 $(DESTDIR)$(bindir)/gnui-config
        endif
        ifneq (,$(wildcard ../lib/$(LIBNAME)))
	echo "Installing static core library in $(libdir)"
	$(MKDIR) $(DESTDIR)$(libdir)
	$(RM) $(DESTDIR)$(libdir)/$(LIBNAME)
	$(CP) ../lib/$(LIBNAME) $(DESTDIR)$(libdir)
	$(RANLIB) $(DESTDIR)$(libdir)/$(LIBNAME)
        endif
        ifneq (,$(wildcard ../lib/$(DSONAME)))
	echo "Installing shared core library in $(libdir)"
	$(MKDIR) $(DESTDIR)$(libdir)
	$(RM) $(DESTDIR)$(libdir)/$(DSONAME)
	$(RM) $(DESTDIR)$(libdir)/$(DSOLINK)
	$(CP) ../lib/$(DSONAME) $(DESTDIR)$(libdir)
	$(LN) $(DSONAME) $(DESTDIR)$(libdir)/$(DSOLINK)
        endif
        ifeq ($(DSONAME), gnui.dll)
	$(CP) lib$(DSONAME).a $(DESTDIR)$(libdir)
        endif

#
# Uninstall the libraries...
#

uninstall:
	echo "Removing FLTK1.1 emulation include files from $(includedir)/FL..."
	$(RMDIR) $(includedir)/gnui/compat/FL
	echo "Removing include files from $(includedir)/gnui..."
	$(RMDIR) $(includedir)/gnui
	echo "Removing gnui-config from $(bindir)..."
	$(RM) $(bindir)/gnui-config
	echo "Removing static core library from $(libdir)"
	$(RM) $(libdir)/$(LIBPREFIX)gnui$(LIBSUFFIX)
	echo "Removing shared core library from $(libdir)"
	$(RM) $(libdir)/$(DSONAME)
	$(RM) $(libdir)/$(DSOLINK)
        ifeq ($(DSONAME), gnui.dll)
	$(RM) $(libdir)/lib$(DSONAME).a
        endif


#
# End of "$Id$".
#
# DO NOT DELETE
