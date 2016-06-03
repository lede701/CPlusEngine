--== CPlusEngine ==--

Welcome to the CPlusEngine source code project.  This code is released to the 
public with no warranty or any other strings attached! Please if you find this
code helpful and use it in one of your own project please give me some credit
and let me know you have used it.

--== Compiling and Running ==--

I've included in this release the SDL 2.0.3 library for your convince.  You 
will need to setup an environment variable on your system to the path of the
SDL library called LIBSDL.  You can find many good tutorials for Windows on
how to create one on your system.  Here are the steps you will need to complete
in order to compile this project:

	1.  Download and extract the SDL Library from http://www.libsdl.org
	2.	Setup LIBSDL environment variable to the SDL 2.0 library folder
		a.	Or change the path in the Visual C++ project to the location of the
			SDL library
	3.	Copy all the DLL’s from the system type you’re compiling.  For example 
		if your compiling this for a Win32 based computer copy all the x86 file
		from the SDL lib directory to your project compile directory.  For 
		example if your destination directory is C:\CPlusEngine\Release then 
		you will need to copy all the DLL to this folder from 
		C:\CPlusEngine\CPlusEngine\lib\SDL2-2.0.3\lib\x86\
	4.	Compile the project in Visual Studio 2013
	5.	Run the solution!
	
The reason I create an environment variable is because I work on several different
computers and don’t want to be always changing the path to the SDL library.
Do what feels best for your system.

--== Object System ==--

The old object system no longer exists and has been replaced with a more flexible system.  See
the section about Entities.

--== Entity System ==--

The entity system is designed based on components being added to extend the engine entity system.
As more features are added to the core engine the entity system will then be more expandable and
provide a larger support structure for more complex game objects.

Entities can be parented to any entity.  An entity can only have one parent but a parent can have
multiple entities.  This is boaring so we will move onto what today's programming work will involve.

--== Camera's ==--

Part of the scene object class requires at least one camera to be set in the scene.  Since a camera
is just a subset of the Entity class you can treat the camera exatly how you would treat an entity.
The main difference is that the Camera object will provide the game world with the current world position
based on where the camera is located.

The test camera has been fully implamented into the game engine.  To move the camera around an updater
component will need to be added to the camera unless you want it static.  You can look at the demo scroller
game and see how this was accomplished.

 
Also part of the scene will require a culling routine so we don't try and render objects not sceen by
the camera view.

