#include "Adventurer.hpp"
#include "../Player.hpp"
#include "../Game.hpp"
#include "../PlayerState/PlayerStateTrashCards.hpp"

Adventurer::Adventurer() : Type("Adventurer", 6, glm::vec4( 6/7.0f, 0.2f, 7/7.0f, 0.4f), {CardType::ACTION}){}

void Adventurer::onPlay(Player* player) const 
{
    CardPile deck = player->getDeck();
    CardPile discard= player->getDiscard();
    CardFan hand= player->getHand();
    int nbTreasure = 0;
    
    while (nbTreasure < 2 && deck.size() != 0) {
        Card* card = deck.getOnTop();
        deck.removeOnTop();
        if (card->getType()->isType(CardType::TREASURE)) {
            nbTreasure++;
            hand.Add(card);
        } else {
            discard.AddOnTop(card);
        }
    }
}
