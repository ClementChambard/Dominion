#ifndef GameCards_H
#define GameCards_H

#include "Chapel.hpp"        
#include "Mine.hpp"         
#include "ThroneRoom.hpp"
#include "ActionSimple.hpp" 
#include "CouncilRoom.hpp"  
#include "Moat.hpp"         
#include "Tresor.hpp"
#include "Adventurer.hpp"    
#include "Feast.hpp"         
#include "MoneyLender.hpp"  
#include "Type.hpp"
#include "Bureaucrat.hpp"    
#include "Gardens.hpp"      
#include "Remodel.hpp"      
#include "Victoire.hpp"
#include "Cellar.hpp"        
#include "Library.hpp"      
#include "Spy.hpp"          
#include "Witch.hpp"
#include "Chancelor.hpp"     
#include "Militia.hpp"      
#include "Thief.hpp"        
#include "WorkShop.hpp"
#include <vector>
#include <algorithm>

class GameCards {
    public:
        GameCards() = delete;
        static void InitGameCardsTypes();
        static void CleanupGameCardsTypes();
        static Type* GetGameCardsTypes(int i) { return gameCards[i]; }
        static int GetGameCardsTypeID(Type* type) { return std::find(gameCards.begin(), gameCards.end(), type) - gameCards.begin();}
        
    private:
        static std::vector<Type*> gameCards;
};
#endif