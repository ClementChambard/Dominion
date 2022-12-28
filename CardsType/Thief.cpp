#include "Thief.hpp"
#include "../Player.hpp"
#include "../Game.hpp"

Thief::Thief() : Type("Thief", 4, glm::vec4(6/7.f, 0.0f, 7/7.0f, 0.2f), {CardType::ACTION, CardType::ATTACK}){}

void Thief::onPlay(Player* ) const {
    // TOTO
}

