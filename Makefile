CXX=g++
CXXFLAGS=-Wall -Wextra -g
LIBFLAGS=-lSDL2 -lGL -lGLEW -lSDL2_image
PLAYERSTATEOBJECT = PlayerState/PlayerState.o PlayerState/PlayerStateTrashCards.o PlayerState/PlayerStateDiscardCards.o PlayerState/PlayerStateBuyCards.o PlayerState/PlayerStateBool.o PlayerState/PlayerStateActions.o
CARDTYPEOBJECT = CardsType/ActionSimple.o CardsType/Bureaucrat.o CardsType/Chancelor.o CardsType/CouncilRoom.o CardsType/Gardens.o CardsType/Militia.o CardsType/Moat.o CardsType/Remodel.o CardsType/Thief.o CardsType/Tresor.o CardsType/Victoire.o CardsType/WorkShop.o CardsType/Adventurer.o CardsType/Cellar.o CardsType/Chapel.o CardsType/Feast.o CardsType/Library.o CardsType/Mine.o CardsType/MoneyLender.o CardsType/Spy.o CardsType/ThromeRoom.o CardsType/Type.o CardsType/Witch.o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@

dominion: main.o Shader.o Texture.o VertexBatch.o SpriteFont.o Game.o Player.o Card.o CardPile.o CardFan.o CardBoard.o Mouse.o $(PLAYERSTATEOBJECT) $(CARDTYPEOBJECT) Button.o
	$(CXX) $^ -o $@ $(LIBFLAGS)

.PHONY: run clean

run: dominion
	./$<

clean:
	rm -f *.o *~ *.core PlayerState/*.o CardsType/*.o
