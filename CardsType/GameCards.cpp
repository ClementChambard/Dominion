#include "GameCards.hpp"

std::vector<Type*> GameCards::gameCards = std::vector<Type*>();

void GameCards::InitGameCardsTypes() {
    
    gameCards.push_back(new WorkShop());
    gameCards.push_back(new ActionSimple(0,1,2,0,"Woodcutter",3,{5.f/7.f,0.8f,6/7.f,1.0f}));
    gameCards.push_back(new Cellar());
    gameCards.push_back(new Chapel());
    gameCards.push_back(new ActionSimple(0,0,0,3,"Smithy",4,{4.f/7.f,0.f,5/7.f,0.2f}));
    gameCards.push_back(new ActionSimple(1,1,1,1,"Market",5,{1/7.f,0.6f,2/7.f,0.8f}));
    gameCards.push_back(new Mine());
    gameCards.push_back(new Remodel());
    gameCards.push_back(new Witch());
    gameCards.push_back(new ActionSimple(2,0,0,1,"Village",3,{4.f/7.f,0.6f,5/7.f,0.8f}));
    gameCards.push_back(new ActionSimple(1,0,0,2,"Laboratory",5,{3.f/7.f,0.4f,4/7.f,0.6f}));
    gameCards.push_back(new ActionSimple(2,1,2,0,"Festival",5,{2.f/7.f,0.4f,3/7.f,0.6f}));
    gameCards.push_back(new ThroneRoom());
    gameCards.push_back(new CouncilRoom());
    gameCards.push_back(new Chancelor());
    gameCards.push_back(new Adventurer());
    gameCards.push_back(new Feast());
    gameCards.push_back(new Library());
    gameCards.push_back(new Moat());
    gameCards.push_back(new Militia());
    gameCards.push_back(new MoneyLender());
    gameCards.push_back(new Gardens());
    gameCards.push_back(new Moat());
    gameCards.push_back(new Spy());
    gameCards.push_back(new Thief());
    gameCards.push_back(new Bureaucrat());
    gameCards.push_back(new Victoire(-1, "Curse"   , 0, { 2/7.f, 0.2f, 3/7.f, 0.4f }));
    gameCards.push_back(new Victoire( 1, "Estate"  , 2, { 0/7.f, 0.4f, 1/7.f, 0.6f }));
    gameCards.push_back(new Victoire( 3, "Duchy"   , 5, { 4/7.f, 0.2f, 5/7.f, 0.4f }));
    gameCards.push_back(new Victoire( 6, "Province", 8, { 3/7.f, 0.2f, 4/7.f, 0.4f }));
    gameCards.push_back(new Tresor  (1, "Copper"  , 0, { 2/7.f, 0.0f, 3/7.f, 0.2f }));
    gameCards.push_back(new Tresor  (2, "Silver"  , 3, { 1/7.f, 0.0f, 2/7.f, 0.2f }));
    gameCards.push_back(new Tresor  (3, "Gold"    , 6, { 1/7.f, 0.4f, 2/7.f, 0.6f }));
}

void GameCards::CleanupGameCardsTypes() {
    for (auto t : gameCards) delete t;
}