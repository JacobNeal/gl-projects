CXX = g++
CXXFLAGS = -Wall -c
LDFLAGS = -lglfw -lglew -framework OpenGL
EXE = test

all: $(EXE)

$(EXE): test.o window.o
	$(CXX) $(LDFLAGS) test.o window.o -o $@

test.o: test.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

window.o: ../Window.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o && rm $(EXE)
