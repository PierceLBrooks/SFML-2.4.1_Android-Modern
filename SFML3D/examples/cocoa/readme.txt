SFML3D IN COCOA APPLICATION
=========================

This is a small example of the integration of SFML3D in a Cocoa application.

Features
--------

 * This example shows how basic UI elements can interact with SFML3D 
   render areas such as sf3d::RenderWindow (you can use sf3d::Window and 
   OpenGL code too, of course).
 * It also provides tools for converting NSString to and from 
   std::[w]string in an Objective-C Category of NSString.
 * Moreover, it shows how you can prevent annoying the system alerts
   produced when the SFML3D view has focus and the user press a key
   (see SilentWindow interface in CocoaAppDelegate.[h|mm]).

Special Considerations
----------------------

While mixing SFML3D into a Cocoa application you have to deal with mixing
C++ and Objective-C. In order to proceed you should use .mm extension for
Objective-C++ files.

Be aware of the limitations of Objective-C++. Please refer to the official
documentation provided by Apple for more information.

You can also work around these limitations by using CSFML3D.
