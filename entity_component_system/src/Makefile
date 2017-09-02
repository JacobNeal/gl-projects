CXX = clang++
CXXFLAGS = -I/Users/SrirachaAnt/Documents/glm -Wall -c -std=c++14
LDFLAGS = -lglfw -lglew -framework OpenGL
EXE = entity_component_system

all: $(EXE)

$(EXE): main.o Window.o SystemManager.o System.o EntityManager.o Component.o Bitmask.o
	$(CXX) $(LDFLAGS) main.o Window.o SystemManager.o System.o EntityManager.o Component.o Bitmask.o -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

Window.o: Window.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

SystemManager.o: SystemManager.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

System.o: System.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

EntityManager.o: EntityManager.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

Component.o: Component.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

Bitmask.o: Bitmask.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o && rm $(EXE)
