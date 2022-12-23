#include <iostream>
#include <vector>
#ifndef PLAYER_H
#define PLAYER_H

#include "PlayerState.hpp"
#include "Card.hpp"
#include "CardPile.hpp"

class Game;

    enum PlayerTurnState
    {
        Action,
        Buy,
        TrashCard,
        DiscardCard,
        UpgradeCard,
    };

class Player {
    int actions; 
    int buys; 
    int coins; 
    int Victorypoints; 
    int NumberToDiscard;


    Game* game;
    int UpgradeCardCost;
    int upgradeCardIndex;
    Card* lastplayedCard;
   
    PlayerTurnState turnState;
    PlayerState* state;
    PlayerTurnState previousTurnState;
    std::vector<Card*> hand;
    CardPile deck {false};
    CardPile discard {false};


    
    public:
    Player();
    ~Player();
    void draw(int numcards );
    void playCard(Card* card);
    void buyCard(Card* card);
    void endTurn();

    CardPile& getDeck() { return deck; }
    CardPile& getDiscard() { return discard; }

    PlayerState* set_state(PlayerState* playerState) { return state = playerState; }
    Game* getGame(){
        return game;
    }

    // Getters and setter for the attributes
    void addActions(int numActions){
        this->actions+=numActions;
    }
    void addBuys(int numBuys){
        this->buys+=numBuys;
    }
    void addCoins(int numCoins){
        this->coins+=numCoins;
    }
    void addVictoryPoints(int numVictoryPoints){
        this->Victorypoints+=numVictoryPoints;
    }
    void allowDiscardCard(int NumberToDiscard){
        turnState = PlayerTurnState::DiscardCard;
        this->NumberToDiscard = NumberToDiscard;
    }
    void allowTrashCard( int NumberToTrash){
        turnState = PlayerTurnState::TrashCard;
        this->NumberToDiscard = NumberToTrash;
    }
    void allowUpgradeCard(int UpgradeCardCost, int upgradeCardIndex){
        turnState = PlayerTurnState::UpgradeCard;
        this->UpgradeCardCost = UpgradeCardCost;
        this->upgradeCardIndex = upgradeCardIndex;
    }
    Card* getLastPlayedCard(){
        return lastplayedCard;
    }
    void trashCard(Card* card);

    void allowbuyCard(int cost){
        turnState = PlayerTurnState::Buy;
        this->UpgradeCardCost = cost;
    }
    
 

    
    
};


#endif
