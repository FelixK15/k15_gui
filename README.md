**Note that this library is currently in development. Features are still missing, stuff is still being build.**

# What problem is this library trying to solve? (ELI5)
This library tries to make graphical user interface (GUI) programming a little bit easier than what you might be used to when you've programmed with traditional GUI APIs like GTK+ or wxWidgets.

It does so by using a paradigm called "Immediate Mode Programming" (IM), which is a contrast to "Retained Mode Programming" (RM) (which is being used by most GUI libraries, including the ones mentioned before).

Rather than coming up with my own interpretion of these terms, I'd like to quote the user "Imi" from stackexchange, with whose interpretation I very much agree:
>Retained GUI: In a separate initialization phase, you create "GUI controls" like Labels, Buttons, TextBoxes etc. and use some 
>descriptive (or programmatical) way of placing them on screen - all before anything is rendered. 
>Controls hold most of their own state in memory like X,Y location, size, borders, child controls, label text, images and so on. 
>You can add callbacks and listeners to get informed of events and to update data in the GUI control.
>
>Immediate GUI: The GUI library consists of one-shot "RenderButton", "RenderLabel", "RenderTextBox"... functions 
>(edit: don't get confused by the Render prefix. These functions also do the logic behind the controls like polling user input, 
>Inserting characters, handle character-repeat-speed when user holds down a key and so on...) 
>that you can call to "immediately" render a control (doesn't have to be immediately written to the GPU. 
>Usually its remembered for the current frame and sorted into appropiate batches later). 
>The library does not hold any "state" for these. If you want to hide a button... just don't call the RenderButton function. 
>All RenderXXX functions that have user interaction like a buttons or checkbox have return values that 
>indicate whether e.g. the user clicked into the button.

The original post from where I got this quote can be found here: http://gamedev.stackexchange.com/q/24103

**Note that this library does not intend to replace traditional RM-GUI libraries but rather tries to make it easy to quickly add/change GUIs used for prototyping or inhouse tools.**

# How do I add this library to my project?

This library is a single header library which means that you just have to #include it into your project. 
However, you have to add the implementation of the functions used into one of your C/CPP files. 
To do this you have to add #define K15_GUI_IMPLEMENTATION before the #include.

```c
#define K15_GUI_IMPLEMENTATION
#include "k15_gui.h"
```

# Features
* Tries to make it as easily as possible to create GUIs for rapid prototyping or inhouse tools.
* Minimal memory allocations during runtime (actually non if you use K15_CreateGUIContextWithCustomMemory).
* Automatic layouting and resizing - currently working on that.
* Planned: easy to add user generated controls.
* Designed to work well with 3D APIs.
* Easy to multithread.

# Example
An example build with OpenGL rendering can be found in the example.c file. You can build this file using the build.bat file on windows with an installed visual studio version.

This example is mostly used internally by me to test new features and to have a minimal working application. 
The example will be extended over time. Just don't expect a fully fledged application.

# Customization
You can customize some aspects of the library by adding some #define statements before you include the library.

**Note: You have to add these #define statements in the same header where you place the implementation using #define K15_GUI_IMPLEMENTATION.**

* K15_GUI_STRIP_STANDARD_IO - define this to strip the support for file IO (using stdio.h). 
Defining this will effectively restrict you to load resources like fonts and image only from memory.
* K15_GUI_MALLOC - resolves to malloc (must be defined together with K15_GUI_FREE)
* K15_GUI_FREE - resolves to free (must be defined together with K15_GUI_MALLOC)
* K15_GUI_MEMCPY - resolves to memcpy
* K15_GUI_MEMSET - resolves to memset
* K15_GUI_STRLEN - resolves to strlen
* K15_GUI_STRCMP - resolves to strcmp
* K15_GUI_MIN - resolves to a simple macro that filter the element with the lowest value from a set of two elements.
* K15_GUI_MIN - resolves to a simple macro that filter the element with the highest value from a set of two elements.
* K15_GUI_SWAP - resolves to a simple macro that swaps the content of two elements using XOR.
* K15_GUI_CLAMP - resolves to a simple macro that clamps the value of a given element to min|max.

Just #define your own functions if you don't want to use the standard library functions.
```c
#define K15_GUI_MALLOC CustomMalloc
#define K15_GUI_FREE CustomFree
#define K15_GUI_IMPLEMENTATION
#include "k15_gui.h"
```

# How does this library work?
This paragraph will be added if the library is more mature. Currently I experiment with various things regarding layouting and resource management.


