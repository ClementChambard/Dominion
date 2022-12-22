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

void Player::draw(int numcards )
{

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
                hand.erase(std::remove(hand.begin(), hand.end(), c), hand.end());
                return;
            }
        }
        for (Card* c : deck ) {
            if (c == card){
                deck.erase(std::remove(deck.begin(), deck.end(), c), deck.end());
                return;
            }
        }
        for (Card* c : discard ) {
            if (c == card){
                discard.erase(std::remove(discard.begin(), discard.end(), c), discard.end());
                return;
            }
        }

        
    }
