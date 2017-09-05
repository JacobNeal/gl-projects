CXX = clang++
CXXFLAGS = -I/Users/SrirachaAnt/Documents/glm -Wall -c -std=c++14
LDFLAGS = -lglfw -lglew -framework OpenGL
EXE = simple_model_loader

all: $(EXE)

$(EXE): main.o Window.o ModelLoader.o Model.o Shader.o
	$(CXX) $(LDFLAGS) main.o Window.o ModelLoader.o Model.o Shader.o -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

Window.o: Window.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

ModelLoader.o: ModelLoader.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

Model.o: Model.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

Shader.o: Shader.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o && rm $(EXE)
