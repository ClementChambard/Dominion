#include "Library.hpp"
#include "../Player.hpp"
#include "../Game.hpp"
#include "../PlayerState/PlayerStateBool.hpp"

Library::Library() : Type("Library", 5, glm::vec4(2/7.f, 0.6f, 3/7.0f, 0.8f),{Type::CardType::ACTION}){}

void Library::onPlay(Player* player) const 
{
    CardPile deck = player->getDeck();
    while (player->getHand().size() < 7)
    {
        if (!deck.getOnTop()) {
            deck.transmitFrom(player->getDiscard());
            deck.shuffle();
        }
        Card* newCard = deck.getOnTop();
        deck.removeOnTop();
        if ( newCard->getType()->isType(Type::CardType::ACTION) ) {
            player->set_state(new PlayerStateBool(player, nullptr, "Do you want to keep the card " + newCard->getType()->getName() + "?"))
                ->then([player, newCard](Player* p, PlayerStateResult* result) {
                    PlayerStateBool::Result* cast_res = dynamic_cast<PlayerStateBool::Result*>(result);
                    if (cast_res->res) {
                        p->getHand().Add(newCard);
                    } else {
                        p->getDiscard().AddOnTop(newCard);
                    }
                });
        } else {
            player->getHand().Add(newCard);
        }
        

        
    }
}
