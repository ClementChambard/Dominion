#include "Tresor.hpp"
#include "Player.hpp"

Tresor::Tresor(int coin, std::string name, int cost, glm::vec4 uvs) : Type(name, cost, uvs), coin(coin)
{
}
void Tresor::onDiscard(Player* player) const {
    player->addCoins(-coin);
}
void Tresor::onDraw(Player* player) const {
    player->addCoins(coin);
}
void Tresor::onTrash(Player* player)const {
    player->addCoins(-coin);
} 
