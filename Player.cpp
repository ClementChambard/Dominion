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

    this->hand.setPos(Mouse::toWorld(winSize.x/2.f, winSize.y, -0.5f));

    this->deck.setPos(Mouse::toWorld(130.f*winSize.x/1500.f, winSize.y-150.f*winSize.y/900.f, -1.5f));

    this->discard.setPos(Mouse::toWorld(winSize.x-130.f*winSize.x/1500.f, winSize.y-150.f*winSize.y/900.f, -1.5f));
    this->discard.fixPos();

    this->board.setPos(Mouse::toWorld(winSize.x/2.f, winSize.y/2.f+100.f, -1.f));
    this->board.fixPos();
    this->hand.fixPos();
}

Player::~Player(){}

void Player::playCard(Card* c) {
    multAltered = false;
    for (int i = 0; i < ActionMultiplier; i++) {
        c->getType()->onPlay(this);
    }
    if (!multAltered) ActionMultiplier = 1;
    actions--;
}

void Player::draw(int numcards)
{
    for (int i = 0; i < numcards; i++) {
        if (!deck.getOnTop()) {
            deck.transmitFrom(discard);
            deck.shuffle();
        }
        Card* newCard = deck.getOnTop();
        if (newCard) {
            deck.removeOnTop();
            hand.Add(newCard);
            newCard->getType()->onDraw(this);
        }
    }
}

void Player::startTurn() {
    actions = 1;
    buys = 1;
    ActionMultiplier = 1;
    for (const PlayerState* ps : states_to_cleanup) delete ps;
    states_to_cleanup.clear();
    game->setPhaseName("Action phase");
    set_state(new PlayerStateActions(this, nullptr))
        ->then([](Player* p, PlayerStateResult*) {
            //std::cout << "actions done\n";
            p->getGame()->setPhaseName("Buy phase");
            for (size_t i = 0; i < p->getHand().size(); i++) {
                if (p->getHand().get(i)->getType()->isType(Type::CardType::TREASURE))
                {
                    p->getBoard().Add(p->getHand().get(i));
                    p->getHand().remove(i);
                    i--;
                }
            }
            p->set_state(new PlayerStateBuyCards(p, nullptr, p->coins, p->buys, Type::CardType::NONE, true))
                ->then([](Player* p, PlayerStateResult*) {
                    //std::cout << "buys done\n";
                    p->endTurn();
                    
                });
        });
}

void Player::endTurn()
{
    while (board.get(0)) {
        discard.AddOnTop(board.get(0));
        board.get(0)->getType()->onDiscard(this);
        board.remove(0);
    }
    while (hand.get(0)) {
        discard.AddOnTop(hand.get(0));
        hand.get(0)->getType()->onDiscard(this);
        hand.remove(0);
    }
    coins = 0;
    draw(5);
    
    game->next_player();
    //startTurn();
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
