#include "Mouse.hpp"
#include "Player.hpp"
#include "Card.hpp"
#include "Game.hpp"

#include <vector>
#include <algorithm>


Player::Player(Game* game) : game(game), deck(false), discard(true)
{   
    actions = 1;
    buys = 1;
    coins = 0;
    Victorypoints = 0;
    glm::vec2 winSize = Mouse::getWindowSize();
  
    this->hand.setPos(Mouse::toWorld(winSize.x/2.f, winSize.y, -0.5f, glm::vec3{0.f,-1.f,5.f}));
    this->hand.fixPos();

    this->deck.setPos(Mouse::toWorld(130.f*winSize.x/1500.f, winSize.y-150.f*winSize.y/900.f, -1.5f, glm::vec3{0.f,-1.f,5.f}));
    this->deck.fixPos();

    this->discard.setPos(Mouse::toWorld(winSize.x-130.f*winSize.x/1500.f, winSize.y-150.f*winSize.y/900.f, -1.5f, glm::vec3{0.f,-1.f,5.f}));
    this->discard.fixPos();
    
    this->board.setPos(Mouse::toWorld(winSize.x/2.f, winSize.y/2.f+100.f, -1.f, glm::vec3{0.f,-1.f,5.f}));
    this->board.fixPos();

    this->game->DistributeCard(this, CardPileType::COPPER, PlayerCards::DECK);
    this->game->DistributeCard(this, CardPileType::COPPER, PlayerCards::DECK);
    this->game->DistributeCard(this, CardPileType::COPPER, PlayerCards::DECK);
    this->game->DistributeCard(this, CardPileType::COPPER, PlayerCards::DECK);
    this->game->DistributeCard(this, CardPileType::COPPER, PlayerCards::DECK);
    this->game->DistributeCard(this, CardPileType::COPPER, PlayerCards::DECK);
    this->game->DistributeCard(this, CardPileType::COPPER, PlayerCards::DECK);
    this->game->DistributeCard(this, CardPileType::ESTATE, PlayerCards::DECK);
    this->game->DistributeCard(this, CardPileType::ESTATE, PlayerCards::DECK);
    this->game->DistributeCard(this, CardPileType::ESTATE, PlayerCards::DECK);
    this->deck.shuffle();
    draw(5);


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

void Player::update(){
    deck.on_tick();
    hand.on_tick();
    discard.on_tick();
    board.on_tick();
    if(state)state->on_tick();
}