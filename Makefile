CXX=g++
CXXFLAGS=-Wall -Wextra 
LIBFLAGS=-lSDL2 -lGL -lGLEW -lSDL2_image

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@

dominion: main.o Shader.o Texture.o VertexBatch.o Game.o Player.o Card.o Type.o ActionSimple.o Victoire.o Tresor.o Witch.o CouncilRoom.o Chancelor.o
	$(CXX) $^ -o $@ $(LIBFLAGS) 

.PHONY: run clean

run: dominion
	./$<

clean:
	rm -f *.o *~ *.core