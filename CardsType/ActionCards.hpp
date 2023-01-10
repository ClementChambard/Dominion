#ifndef ACTIONCARDS_H
#define ACTIONCARDS_H

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

class ActionCards {
    public:
        ActionCards() = delete;
        static void InitActionCardTypes();
        static void CleanupActionCardTypes();
        static Type* GetActionCardTypes(int i) { return actionCards[i]; }
        static int GetActionCardTypeId(Type* type) { return std::find(actionCards.begin(), actionCards.end(), type) - actionCards.begin();}
    
    private:
        static std::vector<Type*> actionCards;
};
#endif