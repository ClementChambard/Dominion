#include <iostream>
#include <vector>
#include <map>
#include "Type.hpp"
#ifndef GAME_H
#define GAME_H

#include "Player.hpp"

class Game
{
private:
    Player currentPlayer;
    std::vector<Player> players;
    std::map<Type, int> SupplyPiles;
public:
    Game();
    ~Game();
    void start();
    void playTurn(Player player);
    void getWinner();
};

#endif // GAME_HS


