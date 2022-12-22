#include "MoneyLender.hpp"
#include "Player.hpp"
#include "Card.hpp"

MoneyLender::MoneyLender() : Type("MoneyLender", 4, glm::vec4(4/7.f, 0.8f, 5/7.0f, 1.0f)) {}

MoneyLender::~MoneyLender(){
    std::cout << "MoneyLender destructor" << std::endl;
}

void MoneyLender::onPlay(Player* player) const 
{
    player->allowTrashCard(1);
    // TODO : add 3 coins
    
}
