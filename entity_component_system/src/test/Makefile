CXX = g++
CXXFLAGS = -Wall -c
LDFLAGS = -lglfw -lglew -framework OpenGL
EXE = test

all: $(EXE)

$(EXE): test.o Bitmask.o
	$(CXX) $(LDFLAGS) test.o Bitmask.o -o $@

test.o: test.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

Bitmask.o: ../Bitmask.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o && rm $(EXE)
