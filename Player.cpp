#include "Player.hpp"
#include "Card.hpp"
#include <vector>
#include <algorithm>


Player::Player() 
{   
    actions = 1;
    buys = 1;
    coins = 0;
    Victorypoints = 0;
}

Player::~Player(){}

void Player::draw(int numcards)
{
    for (int i = 0; i < numcards; i++) {
        if (!deck.getOnTop()) {
            deck.transmitFrom(discard);
            deck.shuffle();
        }
        Card* newCard = deck.getOnTop();
        deck.removeOnTop();
        hand.push_back(newCard); // TODO
    }
}

void Player::playCard(Card* card)
{

}
void Player::buyCard(Card* card)
{

}
void Player::endTurn()
{

}
void Player::trashCard(Card* card){
        for (Card* c : hand ) {
            if (c == card){
                // TODO
                return;
            }
        }
        for (Card* c : deck ) {
            if (c == card){
                return;
            }
        }
        for (Card* c : discard ) {
            if (c == card){
                return;
            }
        }

        
    }
