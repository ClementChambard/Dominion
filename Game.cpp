#include "Game.hpp"
#include "CardsType/Victoire.hpp"
#include "CardsType/Tresor.hpp"

const int cardCount[] = {
    30, 24, 12, 12,
    60, 40, 30,
    10, 10, 10, 10, 10,
    10, 10, 10, 10, 10
};

Game::Game(int nbPlayers, std::array<Type*, 10> actionCardTypes)
{
    types.resize(static_cast<int>(CardPileType::LENGTH), nullptr);
    piles.resize(static_cast<int>(CardPileType::LENGTH), true);

    types[static_cast<int>(CardPileType::CURSE   )] = new Victoire(-1, "Curse"   , 0, { 2/7.f, 0.2f, 3/7.f, 0.4f });
    types[static_cast<int>(CardPileType::ESTATE  )] = new Victoire( 1, "Estate"  , 2, { 0/7.f, 0.4f, 1/7.f, 0.6f });
    types[static_cast<int>(CardPileType::DUCHY   )] = new Victoire( 3, "Duchy"   , 5, { 4/7.f, 0.2f, 5/7.f, 0.4f });
    types[static_cast<int>(CardPileType::PROVINCE)] = new Victoire( 6, "Province", 8, { 3/7.f, 0.2f, 4/7.f, 0.4f });
    types[static_cast<int>(CardPileType::COPPER  )] = new Tresor   (1, "Copper"  , 0, { 2/7.f, 0.0f, 3/7.f, 0.2f });
    types[static_cast<int>(CardPileType::SILVER  )] = new Tresor   (2, "Silver"  , 3, { 1/7.f, 0.0f, 2/7.f, 0.2f });
    types[static_cast<int>(CardPileType::GOLD    )] = new Tresor   (3, "Gold"    , 6, { 1/7.f, 0.4f, 2/7.f, 0.6f });
    types[static_cast<int>(CardPileType::ACTION1 )] = actionCardTypes[0];
    types[static_cast<int>(CardPileType::ACTION2 )] = actionCardTypes[1];
    types[static_cast<int>(CardPileType::ACTION3 )] = actionCardTypes[2];
    types[static_cast<int>(CardPileType::ACTION4 )] = actionCardTypes[3];
    types[static_cast<int>(CardPileType::ACTION5 )] = actionCardTypes[4];
    types[static_cast<int>(CardPileType::ACTION6 )] = actionCardTypes[5];
    types[static_cast<int>(CardPileType::ACTION7 )] = actionCardTypes[6];
    types[static_cast<int>(CardPileType::ACTION8 )] = actionCardTypes[7];
    types[static_cast<int>(CardPileType::ACTION9 )] = actionCardTypes[8];
    types[static_cast<int>(CardPileType::ACTION10)] = actionCardTypes[9];

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

    this->players.resize(nbPlayers);
}
Game::~Game()
{
    for (Type* t : types) delete t;
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

void Game::tempRender(VertexBatch* batch)
{
    for (size_t i = 0; i < piles.size(); i++)
    {
        piles[i].on_render(batch);
    }
}
