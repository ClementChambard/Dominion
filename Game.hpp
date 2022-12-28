#include <iostream>
#include <vector>
#include <map>
#include <array>
#include "CardsType/Type.hpp"
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

public:
    Game(int nbPlayers, std::array<Type*, 10> actionCardTypes);
    ~Game();
    void start();
    void DistributeCard(Player* player,CardPileType cardType, PlayerCards pile);
    void Attack(Player* player,std::function<void(Player*)> attack ,bool cancelable = true);

    void playTurn(Player* player);

    void tempRender(VertexBatch* batch);

    CardPile& getPile(size_t i) { return piles[i]; }
    CardPile& getPile(CardPileType i) { return piles[static_cast<size_t>(i)]; }
    Type* getType(size_t i) { return types[i]; }
    Type* getType(CardPileType i) { return types[static_cast<size_t>(i)]; }

    void getWinner();
    std::vector<Player> getPlayers(){
        return players;
    }
};

#endif // GAME_HS

