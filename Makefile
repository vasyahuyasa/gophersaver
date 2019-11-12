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
RESOURCS=\
	assets/astro-gopher-1.png \
	assets/astro-gopher-2.png \
	assets/astro-gopher-3.png \
	assets/astro-gopher-4.png


EXECUTABLE=gophersaver

.PHONY: all clean assets clean-assets

all: $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CXX) $(LDFLAGS) $(OBJECTS) $(CXXFLAGS) -o $@

.cpp.o:
	$(CXX) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	rm src/*.o

assets: 
	for img in $(RESOURCS); do xxd -i $$img > $$img.c; done

clean-assets:
	for img in $(RESOURCS); do rm $$img.c; done