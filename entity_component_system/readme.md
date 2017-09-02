## entity_component_system (work in progress)

The purpose of this project is to implement the entity component system pattern. This pattern allows entities to posses properties and functionality through composition, rather than inheritance.

Benefits of using this pattern are stronger decoupling of logic, easier serialization of entities, and better reusability of code.

To build this project there is an included Makefile within the src folder, though you'll probably have to update the compilation and linking flags (CXX, CXXFLAGS, LDFLAGS) to reference the dependencies on OpenGL, GLFW and GLM.
