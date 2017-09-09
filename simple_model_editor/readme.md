## simple_model_editor

The purpose of this project is to create a simple 3D model editor that will allow you to place / remove voxels and save the vertex and element data to our custom file type (.MODEL).

This project is expanding on the simple_model_loader project.

To build this project there is an included Makefile within the src folder, though you'll probably have to update the compilation and linking flags (CXX, CXXFLAGS, LDFLAGS) to reference the dependencies on OpenGL, GLFW and GLM.

