#include "Player.hpp"
#include "Card.hpp"
#include <vector>
#include <algorithm>


Player::Player() : deck(false), discard(true)
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
        hand.Add(newCard);
    }
}

void Player::startTurn() {
    for (PlayerState* ps : states_to_cleanup) delete ps;
    states_to_cleanup.clear();
    set_state(new PlayerStateActions(this, nullptr)) 
        ->then([](Player* p, PlayerStateResult*) {
            p->set_state(new PlayerStateBuyCards(p, nullptr, p->coins, p->buys))
                ->then([](Player* p, PlayerStateResult*) {
                    p->endTurn();
                });
        });
}

void Player::endTurn()
{
    while (board.get(0)) {
        discard.AddOnTop(board.get(0));
        board.remove(0);
    }
    while (hand.get(0)) {
        discard.AddOnTop(hand.get(0));
        hand.remove(0);
    }
    draw(5);
    // game->nextPlayer();
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
