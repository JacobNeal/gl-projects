CXX = clang++
CXXFLAGS = -Wall -c
LDFLAGS = -lglfw -lglew -framework OpenGL
EXE = basic_window

all: $(EXE)

$(EXE): main.o
	$(CXX) $(LDFLAGS) main.o -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o && rm $(EXE)
