CXX = g++
CXXFLAGS = -I/Users/SrirachaAnt/Documents/glm -Wall -c -std=c++14
LDFLAGS = -lglfw -lglew -framework OpenGL
EXE = test

all: $(EXE)

$(EXE): test.o Window.o Camera.o ModelLoader.o Model.o Shader.o
	$(CXX) $(LDFLAGS) test.o Window.o Camera.o ModelLoader.o Model.o Shader.o -o $@

test.o: test.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

Window.o: ../Window.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

Camera.o: ../Camera.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

ModelLoader.o: ../ModelLoader.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

Model.o: ../Model.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

Shader.o: ../Shader.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o && rm $(EXE)
