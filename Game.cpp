#include "Game.hpp"

Game::Game(std::vector<Player> players)
{
    this->players=players;
}
Game::~Game()
{
}
void Game::Attack(Player* player,std::function<void(Player*)> attack )
{
    for (Player &p : players)
    {
        if (&p!=player)
        {
            // check si ya une carte de reaction
            attack(&p);

        }
    }
}

void Game::DistributeCard(Player* player,CardType cardType, Pile pile)
{
   
}