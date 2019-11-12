CXX?=c++
CXXFLAGS=-std=c++11 -Wall -pedantic -Werror -Wshadow -Wstrict-aliasing -Wstrict-overflow
CXXFLAGS+=$(shell pkg-config sdl2 --cflags --libs)
LDFLAGS=
SOURCES=\
	src/scene.cpp \
	src/flyobj.cpp \
	src/render.cpp \
	src/physics.cpp \
	src/main.cpp

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=gophersaver

all: $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CXX) $(LDFLAGS) $(OBJECTS) $(CXXFLAGS) -o $@

.cpp.o:
	$(CXX) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	rm src/*.o