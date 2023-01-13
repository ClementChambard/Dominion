#include <iostream>
#include <vector>
#include <map>
#include <array>
#include "CardsType/Type.hpp"
#include "CardsType/GameCards.hpp"
#include <functional>
#ifndef GAME_H
#define GAME_H

#include "Player.hpp"


enum class CardPileType
{
    CURSE=0,
    ESTATE,
    DUCHY,
    PROVINCE,
    COPPER,
    SILVER,
    GOLD,
    ACTION1,
    ACTION2,
    ACTION3,
    ACTION4,
    ACTION5,
    ACTION6,
    ACTION7,
    ACTION8,
    ACTION9,
    ACTION10,
    LENGTH,
};

enum class PlayerCards
{
    HAND,
    DECK,
    DISCARD,
    BOARD
};

class Game
{
private:
    Player* currentPlayer;
    std::vector<Player> players;
    std::vector<Card> allCards;
    std::vector<CardPile> piles;
    std::vector<Type*> types;
    int curPlayerId = 0;
    std::string phaseName = "Action phase";
    bool endGame=false;

public:
    Game(int nbPlayers, std::array<int, 10> actionCardTypes );
  
    void start();
    void DistributeCard(Player* player,CardPileType cardType, PlayerCards pile);
    void DistributeCard(Player* player,int cardPileId, PlayerCards pile) { DistributeCard(player, (CardPileType) cardPileId, pile); }
    void Attack(Player* player,std::function<void(Player*)> attack ,bool cancelable = true);

    void playTurn(Player* player);


    CardPile& getPile(size_t i) { return piles[i]; }
    CardPile& getPile(CardPileType i) { return piles[static_cast<size_t>(i)]; }
    Type* getType(size_t i) { return types[i]; }
    Type* getType(CardPileType i) { return types[static_cast<size_t>(i)]; }
    void onDraw(VertexBatch *batch);
    void onRenderUI(VertexBatch *batch);
    void onTick();
    void render_piles(VertexBatch* batch);

    void save();

    void next_player();

    int getHoveredPileId();
    void highlightPiles(Type::CardType t, int price);

    void setPhaseName(std::string const& phn) { phaseName = phn; }
    std::string getTopStr() { return "Player " + std::to_string(curPlayerId+1) + " : " + phaseName; }

    void loadGame();
    
    void getWinner();
    std::vector<Player> getPlayers(){
        return players;
    }
    bool getEndGame(){
        return endGame;
    }
    void checkEndGame();
    void setCardCount(int cardCount_[]);
};

#endif // GAME_HS

