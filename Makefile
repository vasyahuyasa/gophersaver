CXX?=c++
SDL2FLAGS=$(shell pkg-config sdl2 --cflags --libs)
CXXFLAGS?=-std=c++11 -Wall -pedantic -Werror -Wshadow -Wstrict-aliasing -Wstrict-overflow

.PHONY: all clean

all: main

main: src/main.cpp
	${CXX} ${CXXFLAGS} -O3 -o $@ $< ${SDL2FLAGS}

debug: src/main.cpp
	${CXX} ${CXXFLAGS} -O0 -g -o main $< ${SDL2FLAGS}

clean:
	rm -f main src/*.o
