#include <iostream>
#include <vector>
#ifndef PLAYER_H
#define PLAYER_H

#include "PlayerState/PlayerState.hpp"
#include "Card.hpp"
#include "CardPile.hpp"
#include "CardFan.hpp"
#include "CardBoard.hpp"
#include "PlayerState/PlayerStateActions.hpp"
#include "PlayerState/PlayerStateBuyCards.hpp"
#include <stdexcept>

class Game;

class Player {
    int actions; 
    int buys; 
    int coins; 
    int Victorypoints; 
    int NumberToDiscard;
    int ActionMultiplier;


    Game* game;

    PlayerState* state;
    CardPile deck;
    CardPile discard;
    CardFan hand;
    CardBoard board;

    std::vector<const PlayerState*> states_to_cleanup;
    
    public:
    Player(Game* game);
    ~Player();
    void draw(int numcards );
    void update();
    void exit_state(const PlayerState* state) { states_to_cleanup.push_back(state); }
    void startTurn();
    void endTurn();

    void playCard(Card* c);

    CardPile& getDeck() { return deck; }
    CardPile& getDiscard() { return discard; }
    CardFan& getHand() { return hand; }
    CardBoard& getBoard() { return board; }
   
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
    int getNumberCards() const { return deck.size() + hand.size() + board.size(); }

    void setActionMultiplier (int multiplier){
        this->ActionMultiplier=multiplier;
    }
    int getActionMultiplier() const { return ActionMultiplier; }
    int getVictory () const{
        return Victorypoints;
    }
    
    
};


#endif
