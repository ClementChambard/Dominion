#include "Gardens.hpp"
#include "../Player.hpp"

Gardens::Gardens() : Type("Gardens", 4, {3/7.0f, 0.0f, 4/7.0f, 0.2f}, {CardType::VICTORY}) {}

void Gardens::onTrash(Player* player) const {
    player->addVictoryPoints(-player->getNumberCards()/10);
}
void Gardens::onAddToDeck(Player* player) const {
   player->addVictoryPoints(player->getNumberCards()/10);
}
void Gardens::onDeckChange(Player* player, int oldCardNumber, int newCardNumber) const {
    player->addVictoryPoints(newCardNumber/10 - oldCardNumber/10);
}
