#include "Bureaucrat.hpp"
#include "../Player.hpp"



Bureaucrat::Bureaucrat() : Type("Bureaucrat", 4, glm::vec4(1/7.f, 0.8f, 2/7.0f, 1.0f), {CardType::ACTION, CardType::ATTACK}){}

void Bureaucrat::onPlay(Player*) const {
    // TOTO
}
