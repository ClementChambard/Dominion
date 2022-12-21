#include "ActionSimple.hpp"
#include "Player.hpp"


ActionSimple::ActionSimple(int action, int buy, int coin, int card, std::string name, int cost, glm::vec4 uvs) : Type(name, cost, uvs)
{
    this->action = action;
    this->buy = buy;
    this->coin = coin;
    this->card = card;
}
void ActionSimple::onPlay(Player* player) const 
{
    player->addActions(action);
    player->addBuys(buy);
    player->addCoins(coin);
    player->draw(card);

}