#include "Game.hpp"
#include "CardsType/Victoire.hpp"
#include "CardsType/Tresor.hpp"
#include <json/json.h> 

int cardCount[] = {
    30, 24, 12, 12,
    60, 40, 30,
    10, 10, 10, 10, 10,
    10, 10, 10, 10, 10
};

Game::Game(int nbPlayers, std::array<int, 10> actionCardTypes)
{
    types.resize(static_cast<int>(CardPileType::LENGTH), nullptr);
    piles.resize(static_cast<int>(CardPileType::LENGTH), true);

    if (nbPlayers < 3) cardCount[static_cast<int>(CardPileType::PROVINCE)] = 8;

    types[static_cast<int>(CardPileType::CURSE   )] = new Victoire(-1, "Curse"   , 0, { 2/7.f, 0.2f, 3/7.f, 0.4f });
    types[static_cast<int>(CardPileType::ESTATE  )] = new Victoire( 1, "Estate"  , 2, { 0/7.f, 0.4f, 1/7.f, 0.6f });
    types[static_cast<int>(CardPileType::DUCHY   )] = new Victoire( 3, "Duchy"   , 5, { 4/7.f, 0.2f, 5/7.f, 0.4f });
    types[static_cast<int>(CardPileType::PROVINCE)] = new Victoire( 6, "Province", 8, { 3/7.f, 0.2f, 4/7.f, 0.4f });
    types[static_cast<int>(CardPileType::COPPER  )] = new Tresor   (1, "Copper"  , 0, { 2/7.f, 0.0f, 3/7.f, 0.2f });
    types[static_cast<int>(CardPileType::SILVER  )] = new Tresor   (2, "Silver"  , 3, { 1/7.f, 0.0f, 2/7.f, 0.2f });
    types[static_cast<int>(CardPileType::GOLD    )] = new Tresor   (3, "Gold"    , 6, { 1/7.f, 0.4f, 2/7.f, 0.6f });
    types[static_cast<int>(CardPileType::ACTION1 )] = ActionCards::GetActionCardTypes(actionCardTypes[0]);
    types[static_cast<int>(CardPileType::ACTION2 )] = ActionCards::GetActionCardTypes(actionCardTypes[1]);
    types[static_cast<int>(CardPileType::ACTION3 )] = ActionCards::GetActionCardTypes(actionCardTypes[2]);
    types[static_cast<int>(CardPileType::ACTION4 )] = ActionCards::GetActionCardTypes(actionCardTypes[3]);
    types[static_cast<int>(CardPileType::ACTION5 )] = ActionCards::GetActionCardTypes(actionCardTypes[4]);
    types[static_cast<int>(CardPileType::ACTION6 )] = ActionCards::GetActionCardTypes(actionCardTypes[5]);
    types[static_cast<int>(CardPileType::ACTION7 )] = ActionCards::GetActionCardTypes(actionCardTypes[6]);
    types[static_cast<int>(CardPileType::ACTION8 )] = ActionCards::GetActionCardTypes(actionCardTypes[7]);
    types[static_cast<int>(CardPileType::ACTION9 )] = ActionCards::GetActionCardTypes(actionCardTypes[8]);
    types[static_cast<int>(CardPileType::ACTION10)] = ActionCards::GetActionCardTypes(actionCardTypes[9]);

    for (size_t i = 0; i < types.size(); i++) {
        for (int j = 0; j < cardCount[i]; j++) {
            allCards.emplace_back(types[i]);
        }
    }

    int n = 0;
    for (size_t i = 0; i < piles.size(); i++) {
        for (int j = 1; j <= cardCount[i]; j++) {
            piles[i].AddOnTop(&allCards[n++]);
        }
    }

    piles[static_cast<int>(CardPileType::CURSE   )].setPos({-4.0f,1.4f,-3.5f}); //   T T T   A A A A A
    piles[static_cast<int>(CardPileType::ESTATE  )].setPos({-3.0f,1.4f,-3.5f}); //  C V V V  A A A A A
    piles[static_cast<int>(CardPileType::DUCHY   )].setPos({-2.0f,1.4f,-3.5f});
    piles[static_cast<int>(CardPileType::PROVINCE)].setPos({-1.0f,1.4f,-3.5f});
    piles[static_cast<int>(CardPileType::COPPER  )].setPos({-3.5f,2.8f,-3.5f});
    piles[static_cast<int>(CardPileType::SILVER  )].setPos({-2.5f,2.8f,-3.5f});
    piles[static_cast<int>(CardPileType::GOLD    )].setPos({-1.5f,2.8f,-3.5f});
    piles[static_cast<int>(CardPileType::ACTION1 )].setPos({ 0.5f,1.4f,-3.5f});
    piles[static_cast<int>(CardPileType::ACTION2 )].setPos({ 1.5f,1.4f,-3.5f});
    piles[static_cast<int>(CardPileType::ACTION3 )].setPos({ 2.5f,1.4f,-3.5f});
    piles[static_cast<int>(CardPileType::ACTION4 )].setPos({ 3.5f,1.4f,-3.5f});
    piles[static_cast<int>(CardPileType::ACTION5 )].setPos({ 4.5f,1.4f,-3.5f});
    piles[static_cast<int>(CardPileType::ACTION6 )].setPos({ 0.5f,2.8f,-3.5f});
    piles[static_cast<int>(CardPileType::ACTION7 )].setPos({ 1.5f,2.8f,-3.5f});
    piles[static_cast<int>(CardPileType::ACTION8 )].setPos({ 2.5f,2.8f,-3.5f});
    piles[static_cast<int>(CardPileType::ACTION9 )].setPos({ 3.5f,2.8f,-3.5f});
    piles[static_cast<int>(CardPileType::ACTION10)].setPos({ 4.5f,2.8f,-3.5f});
    for (size_t i = 0; i < piles.size(); i++) piles[i].fixPos();

    this->players.resize(nbPlayers, this);
    this->currentPlayer= &players[0];
    this->currentPlayer->startTurn();
}

void Game::Attack(Player* player,std::function<void(Player*)> attack, bool cancelable )
{
    for (Player &p : players)
    {
        if (&p!=player)
        {
            bool cancled = false;
            if (cancelable) {
                for  ( Card* c : p.getHand() ){
                    if (c->getType()->onReact(&p)){ 
                        cancled = true;
                    }   
                }
            }
            if (!cancled) {
                attack(&p);
            }
        }
    }
}

void Game::DistributeCard(Player* p, CardPileType pile, PlayerCards playerPile)
{
    Card* c = piles[static_cast<size_t>(pile)].getOnTop();
    piles[static_cast<size_t>(pile)].removeOnTop();
    c->getType()->onAddToDeck(p);
    switch (playerPile) {
        case PlayerCards::DECK:
            p->getDeck().AddOnTop(c);
            break;
        case PlayerCards::HAND:
            c->getType()->onDraw(p);
            p->getHand().Add(c);
            break;
        case PlayerCards::DISCARD:
            p->getDiscard().AddOnTop(c);
            break;
        case PlayerCards::BOARD:
            p->getBoard().Add(c);
            break;
    }
}

int Game::getHoveredPileId() {
    for (size_t i = 0; i < piles.size(); i++) {
        if (piles[i].isHovered()) return i;
    }
    return -1;
}

void Game::highlightPiles(Type::CardType t, int price) {
    for (size_t i = 0; i < piles.size(); i++) {
        if (piles[i].size() <= 0) continue;
        auto type = piles[i].getOnTop()->getType();
        piles[i].setHighlight(type->getCost() <= price && type->isType(t));
    }
}

void Game::render_piles(VertexBatch* batch, bool hov) {
    Card* hoveredCard = nullptr;
    for (size_t i = 0; i < piles.size(); i++)
    {
        piles[i].on_render(batch, hov);
        if (hov && piles[i].isHovered() && piles[i].isHighlighted()) hoveredCard = piles[i].getOnTop();
    }
    if (hoveredCard) hoveredCard->on_render(batch, true);
}

void Game::onDraw(VertexBatch* batch)
{
    if (currentPlayer && currentPlayer->get_state()) currentPlayer->get_state()->on_render(batch);
}

void Game::onRenderUI(VertexBatch *batch){
    if (currentPlayer && currentPlayer->get_state()) currentPlayer->get_state()->on_renderUI(batch);
}

void Game::onTick(){
    for (auto p : piles) p.on_tick();
    if (currentPlayer) currentPlayer->update();
}

void Game::next_player() { 
    checkEndGame();
    curPlayerId = (curPlayerId + 1) % players.size();
    currentPlayer = &players[curPlayerId];
    currentPlayer->startTurn();
}

void printWinner(std::vector<Player> const& players) {
    int maxScore = 0;
    int winnerId = 0;
    for (size_t i = 0; i < players.size(); i++) {
        int score = players[i].getVictory();
        if (score > maxScore) {
            maxScore = score;
            winnerId = i;
        }
    }
    std::cout << "Player " << winnerId+1 << " wins!\nScores : \n";
    for (size_t i = 0; i < players.size(); i++) {
        std::cout << " - Player " << i+1 << " : " << players[i].getVictory() << "\n";
    }
}
void Game::checkEndGame(){
    if (piles[static_cast<int>(CardPileType::PROVINCE)].size() <= 0) {
        std::cout << "Game Over\n";
        // check winner
        printWinner(players);
        endGame = true;
        return;
    }
    int depletedPileCount = 0;
    for (size_t i = 0; i < piles.size(); i++) {
        if (piles[i].size() <= 0) depletedPileCount++;
    }
    if (depletedPileCount >= 3) {
        std::cout << "Game Over\n";
        // check winner
        printWinner(players);
        endGame = true;
    };

}

void Game::save() {
    Json::Value root;
    root["nbPlayers"] = players.size();
    root["curPlayerId"] = curPlayerId;

    std::cout << root;
    
}
