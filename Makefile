CXX=g++
CXXFLAGS=-Wall -Wextra -Werror
LIBFLAGS=-lSDL2 -lGL -lGLEW -lSDL2_image

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@

dominion: main.o Shader.o Texture.o VertexBatch.o
	$(CXX) $(LIBFLAGS) $^ -o $@

.PHONY: run clean

run: dominion
	./$<

clean:
	rm -f *.o *~ *.core
