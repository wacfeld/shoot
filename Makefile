CXX = g++
CXXFLAGS = -std=c++14 -g -MMD -Wall -fcompare-debug-second -Wshadow -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image `sdl2-config --cflags --libs`
# CXX = clang-14
# CXXFLAGS = -std=c++2a -g -MMD -Wall -Wshadow -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image `sdl2-config --cflags --libs`
EXEC = $(shell basename $(CURDIR)).out
LIBS = 
OBJECTS = main.o drawer.o camera.o linalg.o
DEPENDS = ${OBJECTS:.o=.d}
${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} ${CXXFLAGS} -o ${EXEC} ${LIBS}
-include ${DEPENDS}
.PHONY: clean
clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}

