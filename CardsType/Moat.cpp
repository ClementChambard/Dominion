#include "Moat.hpp"
#include "../Player.hpp"

Moat::Moat() : ActionSimple(0,0,0,2,"Moat", 2, glm::vec4(3/7.0f, 0.6f, 4/7.0f, 0.8f), {CardType::ACTION, CardType::REACTION}){}




bool Moat::onReact(Player* ) const {
    // reveal this card from hand
    return true; 
}