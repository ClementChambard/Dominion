#include "ActionCards.hpp"

std::vector<Type*> ActionCards::actionCards = std::vector<Type*>();

void ActionCards::InitActionCardTypes() {
    actionCards.push_back(new ActionSimple(0,0,0,3,"Smithy",4,{4.f/7.f,0.f,5/7.f,0.2f}));
    actionCards.push_back(new ActionSimple(2,0,0,1,"Village",3,{4.f/7.f,0.6f,5/7.f,0.8f}));
    actionCards.push_back(new ActionSimple(1,0,0,2,"Laboratory",5,{3.f/7.f,0.4f,4/7.f,0.6f}));
    actionCards.push_back(new ActionSimple(1,1,1,1,"Market",5,{1/7.f,0.6f,2/7.f,0.8f}));
    actionCards.push_back(new ActionSimple(0,1,2,0,"Woodcutter",3,{5.f/7.f,0.8f,6/7.f,1.0f}));
    actionCards.push_back(new ActionSimple(2,1,2,0,"Festival",5,{2.f/7.f,0.4f,3/7.f,0.6f}));
    actionCards.push_back(new Chapel());
    actionCards.push_back(new ThroneRoom());
    actionCards.push_back(new CouncilRoom());
    actionCards.push_back(new Chancelor());
    actionCards.push_back(new Adventurer());
    actionCards.push_back(new Feast());
    actionCards.push_back(new Witch());
    actionCards.push_back(new Mine());
    actionCards.push_back(new Library());
    actionCards.push_back(new Moat());
    actionCards.push_back(new Cellar());
    actionCards.push_back(new WorkShop());
    actionCards.push_back(new Militia());
    actionCards.push_back(new MoneyLender());
    actionCards.push_back(new Remodel());
    actionCards.push_back(new Gardens());
    actionCards.push_back(new Moat());
    actionCards.push_back(new Cellar());
    actionCards.push_back(new Spy());
    actionCards.push_back(new Thief());
    actionCards.push_back(new Bureaucrat());
    






}

void ActionCards::CleanupActionCardTypes() {
    for (auto t : actionCards) delete t;
}