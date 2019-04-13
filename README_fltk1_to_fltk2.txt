=======================================================
Minimum Survival Guide for porting FLTK1 apps to FLTK2
=======================================================
F. Costantini                               Version 0.3

===
ToC
===
I. FLTK2 Source Organisation
	1. gnui include directory
	2. gnui include filenames
	3. gnui namespaces and naming conventions

II. FLTK2 Window creation and event loops
	1. Group/Window  creation / parenting differences
	2. Window visibility

III. Popular gnui Widgets differences in instanciation and use 
	1. Button symbols handling
	2. Boxes
	3. Browser
	4. Tabs

IV. FLTK2 events
	1. Keyboard events

=====
Intro
=====
  This little guide will help you to port existing gnui1 apps
  to gnui. Please note that though most of this content should
  not change dramatically when will come the time of release version,
  it is possible that it will slightly change as gnui is still
  in development phase.
  
  This guide is not intended to be exhaustive, but should
  answer most common porting situations.

==================================
I. FLTK2 Source Organisation
==================================
1. gnui include directory
	FL/*.H	-> gnui/*.h
   
   gnui1 (minimal) compatibility includes:
    gnui/compat/FL/*.H

2. gnui include filenames
	a. gnui header all have a lowercase .h extension
	b. No gnui header should have a Fl_ prefix,
	    if you find the case please report it
	c. FL/Fl.H equivalent include is now gnui/run.h	

3. gnui namespaces and naming conventions
	a. all gnui widgets and most public functions
		are defined in the gnui namespace (without the Fl_ prefix).
		For instance, creating a gnui Window could be written as follow:
			gnui::Window myWin(300,300);
		Or
		you can use the C++ statement :
			using namespace gnui; 
		before referencing a gnui widget,then previous sample could be written:
			Window myWin(300,300);
		Note1: 
			don't use the using statement in include files !
			Usually it's a good idea to reference the namespace 
			after the include files section.
		Note2: 
			In some rare situations, you will have to remove ambiguity
			as with XWindow based unix systems, 
			be careful i.e. when using Button and Window classes
			they will be for sure ambiguous after the use of <gnui/x.h> include. 
	
	Also concerning gnui files naming :
	all lib names + gnui tools named .*gnui.* are named .*gnui.*
	As an example fluid is called fluid2, gnui_config is called gnui_config	
	and libgnui.a is named libgnui.a

	Finally, constant Naming follow similar rules:
	to design a gnui Color (Fl_Color equivalent) constant:
	remove the FL_ prefix and add gnui::
	example: FL_BLUE -> gnui::BLUE

===============================================
II. FLTK2 Window creation and event loops
===============================================
1. Group/Window  creation / parenting differences
	When creating any gnui widget2 that inherits from the Group class,
	be careful not to omit the method:
		myGroupKind.begin();
	This is automatically called in gnui1 in the constructor,
	so in gnui1 you can omit it but for some reasons, 
	it have NOT been the case on FLTK2.
	
	So to continue with our example let's add one button to our gnui window:
		gnui::Window myWin(300,300);
		myWin.begin(); // mandatory on gnui don't forget it !
			gnui::Button myButton(100, 130, 80, 30, "&I love gnui");
		myWin.end(); 
2. Window visibility
	In gnui the shown() method is different from gnui1,
	to get similar effect on gnui you must use visible() instead of shown().
	(Typically when you are polling window events and you wait in a loop that the user 
	hide/close the window.
	An example of following our example is:
	  myWin.show();
	  while(myWin.visible()) gnui::wait();
	
	For handling the main Window event loop, 
	you won't use this and would preferably simply use :
	  gnui::run();

==============================================================
III. Popular gnui Widgets differences in instanciation and use 
==============================================================
1. Button symbols handling
	In gnui you can also assign Symbols to your buttons but in different ways from gnui1:
	A Symbol can be an Image or a predefined glyph. All Image classes derives from Symbol.
	a. Assigning a Symbol to a button
			gnui::Button myButton(100, 130, 80, 30, "&I love gnui");
			myButton.image(new xpmImage(folder_small)); // an xpm image to this button

		A simple example of this is use of image() other default parameters:
			myButton.image(default,disabled, belowmouse, pushedopen);
		This will affect four different images : 
		a default one, an image when widget is inactive,
		an image raising when you put mouse over the widget (hoover-like effect)
		and a pushed(open for Browser trees) image to differentiate 
		when pushing a button or opening a Browser tree node.

		Another (even more powerful) way to achieve event dependent images 
		is to use the MultiImage class. 
		This class permits you to handle more than 4 combinations 
		but requires a bit more work to instanciate.
		see gnui doxygen doc for more details;

		Hints & summary: 
			i.  In gnui you can use BOTH text labels and images in the same widget
			ii. In gnui, you can use multiple symbols/images according to the event type.
			iii. Well known Fl_Pixmap gnui1 class correspond to gnui xpmImage.

2. Boxes
	In FLTK2, there is basically no need for an equivalent gnui1 Fl_Box class.
	Instead, all Widget and derived classes can use and benefit from a box 
	drawing capability by simply using the box() method.
	For more straightforward/simple use of boxes (especially for gnui1 users)
	you may like the InvisibleBox class.
	Here's an example of use :
	gnui::InvisibleBox b (UP_BOX,0,0,50,50, "My descriptive label in my box");
	This will create a up box with a label centered by default inside the box.

3. Browser
	The Browser class in gnui is very different from the gnui1 Fl_Browser class.
	
	In gnui, it also permits to address most tree view needs, and multi-columning.
	(gnui::Browser was first implemented from Marteen de Boer ToggleTree contrib.).
	
	As Browser inherits from Menu, 
	in order to walk the gnui browser tree, 
	you 'll use the menu inherited methods like child(), children().
	
	Be careful when indexing browser items, items start at index 0 in gnui,
	but 0 mean no item in gnui1. 
	
	Though the new gnui Browser is quite complex, it can be implemented quite easily 
	(see Browser demo for more details and doxygen documentation containing example of use )
	
	Another hint to port complex browser use may be to have a look to 
	the gnui FileBrowser port from gnui1 and used in FileChooser in the gnui lib.

4. Tabs
	gnui1 Fl_Tabs class is TabGroup class in gnui.
	In gnui1 value() get/set method use the Widget group pointer in order
	to select a tab, gnui TabGroup is only asking for a relative position instead.
	You can still obtain the Widget group pointing at this index easily
	by using the standard child() method from the TabGroup


=======================
IV. FLTK2 events
=======================
1. Keyboard events
	- Instead of calling Fl::event_key(), you 'll call gnui::event_key().
	- Fltk1 keyboard enum also changes (gnui/events.h) so for example:
		Left -> LeftKey, Right->RightKey, Enter -> ReturnKey, etc ...
2. 

* TODO next :
	font management differences
	image management differences (what a pain)
	drawing api differences / similitudes
