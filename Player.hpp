#include <iostream>
#include <vector>
#ifndef PLAYER_H
#define PLAYER_H

#include "Card.hpp"

class Player {
    int actions; 
    int buys; 
    int coins; 
    int Victorypoints; 
    std::vector<Card> hand;
    std::vector<Card> deck;
    std::vector<Card> discard;

    
    public:
    Player();
    ~Player();
    void draw(int numcards );
    void playCard(Card card);
    void buyCard(Card card);
    void endTurn();

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
    
};


#endif 