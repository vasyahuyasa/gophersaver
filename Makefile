CXX?=c++
CXXFLAGS=-std=c++11 -Wall -pedantic -Werror -Wshadow -Wstrict-aliasing -Wstrict-overflow -O0 
CXXFLAGS+=-lX11
CXXFLAGS+=$(shell pkg-config sdl2 --cflags --libs)
CXXFLAGS+=$(shell pkg-config SDL2_image --cflags --libs)
LDFLAGS=
SOURCES=\
	src/scene.cpp \
	src/flyobj.cpp \
	src/render.cpp \
	src/physics.cpp \
	src/main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
RESOURCS=\
	src/assets/astro-gopher-1.png \
	src/assets/astro-gopher-2.png \
	src/assets/astro-gopher-3.png \
	src/assets/astro-gopher-4.png
ASSETS_FILE=src/assets/assets.h


EXECUTABLE=gophersaver

.PHONY: all clean assets clean-assets

all: $(ASSETS_FILE) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CXX) $(LDFLAGS) $(OBJECTS) $(CXXFLAGS) -o $@

.cpp.o:
	$(CXX) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	rm $(OBJECTS)

$(ASSETS_FILE):
	for img in $(RESOURCS); do xxd -i $$img >> $(ASSETS_FILE); done

clean-assets:
	rm $(ASSETS_FILE)