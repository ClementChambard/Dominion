#include <iostream>
#include <vector>
#ifndef PLAYER_H
#define PLAYER_H

#include "Card.hpp"
class Game;

class Player {
    int actions; 
    int buys; 
    int coins; 
    int Victorypoints; 
    Game* game;
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
    void discardDeck(){
        for (int i = 0; i < deck.size(); i++)
        {
            discard.push_back(deck[i]);
        }
        deck.clear();
    }
    
    
};


#endif 