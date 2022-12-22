#include <iostream>
#include <vector>
#include <map>
#include <array>
#include "Type.hpp"
#include <functional>
#ifndef GAME_H
#define GAME_H

#include "Player.hpp"


enum class CardType
{
    Curse=0,
    Estate,
    Duchy,
    Province,
    Copper,
    Silver,
    Gold,
    Action1,
    Action2,
    Action3,
    Action4,
    Action5,
    Action6,
    Action7,
    Action8,
    Action9,
    Action10,
};
enum class Pile
{
    Main,
    Deck,
    Discard,
    Board
};

class Game
{
private:
    Player currentPlayer;
    std::vector<Player> players;
    // std::array<int, 17> piles;   initialiser les piles une fois on a tout les types de cartes
    // std::array<Type, 17> Type;


public:
    Game(std::vector<Player> players);
    ~Game();
    void start();
    void DistributeCard(Player* player,CardType cardType, Pile pile);
    void Attack(Player* player,std::function<void(Player*)> attack );

    void playTurn(Player* player);
    void getWinner();
    std::vector<Player> getPlayers(){
        return players;
    }
};

#endif // GAME_HS

