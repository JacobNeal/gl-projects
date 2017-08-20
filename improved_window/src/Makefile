CXX = clang++
CXXFLAGS = -I/Users/SrirachaAnt/Documents/glm -Wall -c
LDFLAGS = -lglfw -lglew -framework OpenGL
EXE = improved_window

all: $(EXE)

$(EXE): main.o window.o triangle.o shader.o
	$(CXX) $(LDFLAGS) main.o window.o triangle.o shader.o -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

window.o: Window.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

triangle.o: Triangle.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

shader.o: Shader.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o && rm $(EXE)
