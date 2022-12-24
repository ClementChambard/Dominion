#include <iostream>
#include <vector>
#ifndef PLAYER_H
#define PLAYER_H

#include "PlayerState.hpp"
#include "Card.hpp"
#include "CardPile.hpp"
#include "CardFan.hpp"
#include "PlayerStateActions.hpp"
#include "PlayerStateBuyCards.hpp"

class Game;

class Player {
    int actions; 
    int buys; 
    int coins; 
    int Victorypoints; 
    int NumberToDiscard;


    Game* game;

    PlayerState* state;
    CardPile deck;
    CardPile discard;
    CardFan hand;
    CardFan board;

    std::vector<PlayerState*> states_to_cleanup;
    
    public:
    Player();
    ~Player();
    void draw(int numcards );
    void exit_state(PlayerState* state) { states_to_cleanup.push_back(state); }
    void startTurn();
    void endTurn();

    CardPile& getDeck() { return deck; }
    CardPile& getDiscard() { return discard; }
    CardFan& getHand() { return hand; }
    CardFan& getBoard() { return board; }

    PlayerState* set_state(PlayerState* playerState) { return state = playerState; }
    PlayerState* get_state() const { return state; }
    Game* getGame(){
        return game;
    }

    int getBuys() const { return buys; }
    int getActions() const { return actions; }
    int getCoins() const { return coins; }

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
    void trashCard(Card* card);

    
    
};


#endif
