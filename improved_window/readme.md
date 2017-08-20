## improved_window

The purpose of this project is to expand on our previous project (basic_window) by wrapping our GLFW window creation into a Window class, and creating a basic structure that can be used to draw OpenGL elements to the screen through using an abstract Drawable class.

In this example a simple triangle is drawn within the rendered window.

To build this project there is an included Makefile within the src folder, though you'll probably have to update the compilation and linking flags (CXX, CXXFLAGS, LDFLAGS) to reference the dependencies on OpenGL, and GLFW.

