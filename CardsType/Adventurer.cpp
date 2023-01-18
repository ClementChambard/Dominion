#include "Adventurer.hpp"
#include "../Player.hpp"
#include "../Game.hpp"
#include "../PlayerState/PlayerStateTrashCards.hpp"

Adventurer::Adventurer() : Type("Adventurer", 6, glm::vec4( 6/7.0f, 0.2f, 7/7.0f, 0.4f), {CardType::ACTION}){}

void Adventurer::onPlay(Player* player) const 
{
    int nbTreasure = 0;
    
    while (nbTreasure < 2 && player->getDeck().size() != 0) {
        Card* card = player->getDeck().getOnTop();
        player->getDeck().removeOnTop();
        if (card->getType()->isType(CardType::TREASURE)) {
            nbTreasure++;
            player->getHand().Add(card);
            card->getType()->onDraw(player);
        } else {
            player->getDiscard().AddOnTop(card);
        }
    }
}
