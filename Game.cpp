#include "Game.hpp"
#include "CardsType/Victoire.hpp"
#include "CardsType/Tresor.hpp"
#include <jsoncpp/json/json.h> 
#include <fstream>
#include "CardsType/Type.hpp"


int cardCount[] = {

    30, 24, 12, 12,
    60, 40, 30,
    10, 10, 10, 10, 10,
    10, 10, 10, 10, 10
};


    



Game::Game(int nbPlayers, std::array<int, 10> actionCardTypes )
{
    types.resize(static_cast<int>(CardPileType::LENGTH), nullptr);
    piles.resize(static_cast<int>(CardPileType::LENGTH), true);


    types[static_cast<int>(CardPileType::CURSE   )] = GameCards::GetGameCardsTypes(26);
    types[static_cast<int>(CardPileType::ESTATE  )] = GameCards::GetGameCardsTypes(27);
    types[static_cast<int>(CardPileType::DUCHY   )] = GameCards::GetGameCardsTypes(28);
    types[static_cast<int>(CardPileType::PROVINCE)] = GameCards::GetGameCardsTypes(29);
    types[static_cast<int>(CardPileType::COPPER  )] = GameCards::GetGameCardsTypes(30);
    types[static_cast<int>(CardPileType::SILVER  )] = GameCards::GetGameCardsTypes(31);
    types[static_cast<int>(CardPileType::GOLD    )] = GameCards::GetGameCardsTypes(32);

    types[static_cast<int>(CardPileType::ACTION1 )] = GameCards::GetGameCardsTypes(actionCardTypes[0]);
    types[static_cast<int>(CardPileType::ACTION2 )] = GameCards::GetGameCardsTypes(actionCardTypes[1]);
    types[static_cast<int>(CardPileType::ACTION3 )] = GameCards::GetGameCardsTypes(actionCardTypes[2]);
    types[static_cast<int>(CardPileType::ACTION4 )] = GameCards::GetGameCardsTypes(actionCardTypes[3]);
    types[static_cast<int>(CardPileType::ACTION5 )] = GameCards::GetGameCardsTypes(actionCardTypes[4]);
    types[static_cast<int>(CardPileType::ACTION6 )] = GameCards::GetGameCardsTypes(actionCardTypes[5]);
    types[static_cast<int>(CardPileType::ACTION7 )] = GameCards::GetGameCardsTypes(actionCardTypes[6]);
    types[static_cast<int>(CardPileType::ACTION8 )] = GameCards::GetGameCardsTypes(actionCardTypes[7]);
    types[static_cast<int>(CardPileType::ACTION9 )] = GameCards::GetGameCardsTypes(actionCardTypes[8]);
    types[static_cast<int>(CardPileType::ACTION10)] = GameCards::GetGameCardsTypes(actionCardTypes[9]);

    if (nbPlayers < 3) cardCount[static_cast<int>(CardPileType::PROVINCE)] = 8;

    types[static_cast<int>(CardPileType::CURSE   )] = new Victoire(-1, "Curse"   , 0, { 2/7.f, 0.2f, 3/7.f, 0.4f });
    types[static_cast<int>(CardPileType::ESTATE  )] = new Victoire( 1, "Estate"  , 2, { 0/7.f, 0.4f, 1/7.f, 0.6f });
    types[static_cast<int>(CardPileType::DUCHY   )] = new Victoire( 3, "Duchy"   , 5, { 4/7.f, 0.2f, 5/7.f, 0.4f });
    types[static_cast<int>(CardPileType::PROVINCE)] = new Victoire( 6, "Province", 8, { 3/7.f, 0.2f, 4/7.f, 0.4f });
    types[static_cast<int>(CardPileType::COPPER  )] = new Tresor   (1, "Copper"  , 0, { 2/7.f, 0.0f, 3/7.f, 0.2f });
    types[static_cast<int>(CardPileType::SILVER  )] = new Tresor   (2, "Silver"  , 3, { 1/7.f, 0.0f, 2/7.f, 0.2f });
    types[static_cast<int>(CardPileType::GOLD    )] = new Tresor   (3, "Gold"    , 6, { 1/7.f, 0.4f, 2/7.f, 0.6f });
    types[static_cast<int>(CardPileType::ACTION1 )] = ActionCards::GetActionCardTypes(actionCardTypes[0]);
    types[static_cast<int>(CardPileType::ACTION2 )] = ActionCards::GetActionCardTypes(actionCardTypes[1]);
    types[static_cast<int>(CardPileType::ACTION3 )] = ActionCards::GetActionCardTypes(actionCardTypes[2]);
    types[static_cast<int>(CardPileType::ACTION4 )] = ActionCards::GetActionCardTypes(actionCardTypes[3]);
    types[static_cast<int>(CardPileType::ACTION5 )] = ActionCards::GetActionCardTypes(actionCardTypes[4]);
    types[static_cast<int>(CardPileType::ACTION6 )] = ActionCards::GetActionCardTypes(actionCardTypes[5]);
    types[static_cast<int>(CardPileType::ACTION7 )] = ActionCards::GetActionCardTypes(actionCardTypes[6]);
    types[static_cast<int>(CardPileType::ACTION8 )] = ActionCards::GetActionCardTypes(actionCardTypes[7]);
    types[static_cast<int>(CardPileType::ACTION9 )] = ActionCards::GetActionCardTypes(actionCardTypes[8]);
    types[static_cast<int>(CardPileType::ACTION10)] = ActionCards::GetActionCardTypes(actionCardTypes[9]);


    for (size_t i = 0; i < types.size(); i++) {
        for (int j = 0; j < cardCount[i]; j++) {
            allCards.emplace_back(types[i]);
        }
    }

    int n = 0;
    for (size_t i = 0; i < piles.size(); i++) {
        for (int j = 1; j <= cardCount[i]; j++) {
            piles[i].AddOnTop(&allCards[n++]);
        }
    }

    piles[static_cast<int>(CardPileType::CURSE   )].setPos({-4.0f,1.4f,-3.5f}); //   T T T   A A A A A
    piles[static_cast<int>(CardPileType::ESTATE  )].setPos({-3.0f,1.4f,-3.5f}); //  C V V V  A A A A A
    piles[static_cast<int>(CardPileType::DUCHY   )].setPos({-2.0f,1.4f,-3.5f});
    piles[static_cast<int>(CardPileType::PROVINCE)].setPos({-1.0f,1.4f,-3.5f});
    piles[static_cast<int>(CardPileType::COPPER  )].setPos({-3.5f,2.8f,-3.5f});
    piles[static_cast<int>(CardPileType::SILVER  )].setPos({-2.5f,2.8f,-3.5f});
    piles[static_cast<int>(CardPileType::GOLD    )].setPos({-1.5f,2.8f,-3.5f});
    piles[static_cast<int>(CardPileType::ACTION1 )].setPos({ 0.5f,1.4f,-3.5f});
    piles[static_cast<int>(CardPileType::ACTION2 )].setPos({ 1.5f,1.4f,-3.5f});
    piles[static_cast<int>(CardPileType::ACTION3 )].setPos({ 2.5f,1.4f,-3.5f});
    piles[static_cast<int>(CardPileType::ACTION4 )].setPos({ 3.5f,1.4f,-3.5f});
    piles[static_cast<int>(CardPileType::ACTION5 )].setPos({ 4.5f,1.4f,-3.5f});
    piles[static_cast<int>(CardPileType::ACTION6 )].setPos({ 0.5f,2.8f,-3.5f});
    piles[static_cast<int>(CardPileType::ACTION7 )].setPos({ 1.5f,2.8f,-3.5f});
    piles[static_cast<int>(CardPileType::ACTION8 )].setPos({ 2.5f,2.8f,-3.5f});
    piles[static_cast<int>(CardPileType::ACTION9 )].setPos({ 3.5f,2.8f,-3.5f});
    piles[static_cast<int>(CardPileType::ACTION10)].setPos({ 4.5f,2.8f,-3.5f});
    for (size_t i = 0; i < piles.size(); i++) piles[i].fixPos();

    this->players.resize(nbPlayers, this);
    this->currentPlayer= &players[0];
    this->currentPlayer->startTurn();
}

void Game::Attack(Player* player,std::function<void(Player*)> attack, bool cancelable )
{
    for (Player &p : players)
    {
        if (&p!=player)
        {
            bool cancled = false;
            if (cancelable) {
                for  ( Card* c : p.getHand() ){
                    if (c->getType()->onReact(&p)){ 
                        cancled = true;
                    }   
                }
            }
            if (!cancled) {
                attack(&p);
            }
        }
    }
}

void Game::DistributeCard(Player* p, CardPileType pile, PlayerCards playerPile)
{
    Card* c = piles[static_cast<size_t>(pile)].getOnTop();
    piles[static_cast<size_t>(pile)].removeOnTop();
    c->getType()->onAddToDeck(p);
    switch (playerPile) {
        case PlayerCards::DECK:
            p->getDeck().AddOnTop(c);
            break;
        case PlayerCards::HAND:
            c->getType()->onDraw(p);
            p->getHand().Add(c);
            break;
        case PlayerCards::DISCARD:
            p->getDiscard().AddOnTop(c);
            break;
        case PlayerCards::BOARD:
            p->getBoard().Add(c);
            break;
    }
}

int Game::getHoveredPileId() {
    for (size_t i = 0; i < piles.size(); i++) {
        if (piles[i].isHovered()) return i;
    }
    return -1;
}

void Game::highlightPiles(Type::CardType t, int price) {
    for (size_t i = 0; i < piles.size(); i++) {
        if (piles[i].size() <= 0) continue;
        auto type = piles[i].getOnTop()->getType();
        piles[i].setHighlight(type->getCost() <= price && type->isType(t));
    }
}

void Game::render_piles(VertexBatch* batch, bool hov) {
    Card* hoveredCard = nullptr;
    for (size_t i = 0; i < piles.size(); i++)
    {
        piles[i].on_render(batch, hov);
        if (hov && piles[i].isHovered() && piles[i].isHighlighted()) hoveredCard = piles[i].getOnTop();
    }
    if (hoveredCard) hoveredCard->on_render(batch, true);
}

void Game::onDraw(VertexBatch* batch)
{
    if (currentPlayer && currentPlayer->get_state()) currentPlayer->get_state()->on_render(batch);
}

void Game::onRenderUI(VertexBatch *batch){
    if (currentPlayer && currentPlayer->get_state()) currentPlayer->get_state()->on_renderUI(batch);
}

void Game::onTick(){
    for (auto p : piles) p.on_tick();
    if (currentPlayer) currentPlayer->update();
}

void Game::next_player() { 
    checkEndGame();
    curPlayerId = (curPlayerId + 1) % players.size();
    currentPlayer = &players[curPlayerId];
    currentPlayer->startTurn();
}

void printWinner(std::vector<Player> const& players) {
    int maxScore = 0;
    int winnerId = 0;
    for (size_t i = 0; i < players.size(); i++) {
        int score = players[i].getVictory();
        if (score > maxScore) {
            maxScore = score;
            winnerId = i;
        }
    }
    std::cout << "Player " << winnerId+1 << " wins!\nScores : \n";
    for (size_t i = 0; i < players.size(); i++) {
        std::cout << " - Player " << i+1 << " : " << players[i].getVictory() << "\n";
    }
}
void Game::checkEndGame(){
    if (piles[static_cast<int>(CardPileType::PROVINCE)].size() <= 0) {
        std::cout << "Game Over\n";
        // check winner
        printWinner(players);
        endGame = true;
        return;
    }
    int depletedPileCount = 0;
    for (size_t i = 0; i < piles.size(); i++) {
        if (piles[i].size() <= 0) depletedPileCount++;
    }
    if (depletedPileCount >= 3) {
        std::cout << "Game Over\n";
        // check winner
        printWinner(players);
        endGame = true;
    };

}

void Game::save() {
    Json::Value root;
    root["curPlayerId"] = curPlayerId;
    root["nextPlayerId"] = (curPlayerId + 1) % players.size();
    Json::Value pile;
    for (size_t i = 0; i < types.size(); i++) {
        pile["id"] = GameCards::GetGameCardsTypeID(types[i]);
        pile["size"] = piles[i].size();
        pile["Name"] = types[i]->getName();
        root["Game"].append(pile);
    }
    for (size_t i = 0; i < players.size(); i++) {
        Json::Value player; // on enregistre les donnee de chaque joueur
        player["id"] = i;
        CardPile playerDiscard= players[i].getDiscard();  
        Json::Value discard;
        for ( auto card : playerDiscard){
            discard["id"] = GameCards::GetGameCardsTypeID(card->getType());
            discard["Name"] = card->getType()->getName();
            player["discard"].append(discard);
        }
        CardFan playerHand = players[i].getHand();
        Json::Value hand;
        for ( auto card : playerHand){
            hand["id"] = GameCards::GetGameCardsTypeID(card->getType());
            hand["Name"] = card->getType()->getName();
            player["hand"].append(hand);
        }
        CardPile playerDeck = players[i].getDeck();
        Json::Value deck;
        for ( auto card : playerDeck){
            deck["id"] = GameCards::GetGameCardsTypeID(card->getType());
            deck["Name"] = card->getType()->getName();
            player["deck"].append(deck);
        }
        root["players"].append(player);
    }
    std::ofstream jsonFile("Game.json");

    // Serialize the JSON object to the file
    Json::StreamWriterBuilder builder;
    builder["indentation"] = "\t";  // Use tabs for indentation
    std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    writer->write(root, &jsonFile);

    // Close the file
    jsonFile.close();
}
int globalToLocalId(int id , Json::Value root ){
    int i = 0;
    for ( auto a : root["Game"]){
        if ( a["id"].asInt() == id ){
            return i;
        }
        i++;
    }
    return 0;
}
void Game::loadGame(){
    std::ifstream jsonFile("Game.json");
    Json::Value root;
    Json::CharReaderBuilder builder;
    std::string errs;
    bool ok = Json::parseFromStream(builder, jsonFile, &root, &errs);
    if (!ok) {
        std::cout << errs << std::endl;
    }
    curPlayerId = root["curPlayerId"].asInt();
    currentPlayer = &players[curPlayerId];
    &players[curPlayerId];

    int playerSize = root["players"].size();
    std::vector<int> cardCount;
    int cardCount_l[] = {
    30, 24, 12, 12,
    60, 40, 30,
    10, 10, 10, 10, 10,
    10, 10, 10, 10, 10
    };
    std::array<int, 10> actionCardTypes ={ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    


    types[static_cast<int>(CardPileType::CURSE   )] = GameCards::GetGameCardsTypes(root["Game"][static_cast<int>(CardPileType::CURSE   )]["id"].asInt());
    types[static_cast<int>(CardPileType::ESTATE  )] = GameCards::GetGameCardsTypes(root["Game"][static_cast<int>(CardPileType::ESTATE  )]["id"].asInt());
    types[static_cast<int>(CardPileType::DUCHY   )] = GameCards::GetGameCardsTypes(root["Game"][static_cast<int>(CardPileType::DUCHY   )]["id"].asInt());
    types[static_cast<int>(CardPileType::PROVINCE)] = GameCards::GetGameCardsTypes(root["Game"][static_cast<int>(CardPileType::PROVINCE   )]["id"].asInt());
    types[static_cast<int>(CardPileType::COPPER  )] = GameCards::GetGameCardsTypes(root["Game"][static_cast<int>(CardPileType::COPPER   )]["id"].asInt());
    types[static_cast<int>(CardPileType::SILVER  )] = GameCards::GetGameCardsTypes(root["Game"][static_cast<int>(CardPileType::SILVER   )]["id"].asInt());
    types[static_cast<int>(CardPileType::GOLD    )] = GameCards::GetGameCardsTypes(root["Game"][static_cast<int>(CardPileType::GOLD   )]["id"].asInt());

    types[static_cast<int>(CardPileType::ACTION1 )] = GameCards::GetGameCardsTypes(root["Game"][static_cast<int>(CardPileType::ACTION1    )]["id"].asInt());
    types[static_cast<int>(CardPileType::ACTION2 )] = GameCards::GetGameCardsTypes(root["Game"][static_cast<int>(CardPileType::ACTION2    )]["id"].asInt());
    types[static_cast<int>(CardPileType::ACTION3 )] = GameCards::GetGameCardsTypes(root["Game"][static_cast<int>(CardPileType::ACTION3    )]["id"].asInt());
    types[static_cast<int>(CardPileType::ACTION4 )] = GameCards::GetGameCardsTypes(root["Game"][static_cast<int>(CardPileType::ACTION4    )]["id"].asInt());
    types[static_cast<int>(CardPileType::ACTION5 )] = GameCards::GetGameCardsTypes(root["Game"][static_cast<int>(CardPileType::ACTION5    )]["id"].asInt());
    types[static_cast<int>(CardPileType::ACTION6 )] = GameCards::GetGameCardsTypes(root["Game"][static_cast<int>(CardPileType::ACTION6    )]["id"].asInt());
    types[static_cast<int>(CardPileType::ACTION7 )] = GameCards::GetGameCardsTypes(root["Game"][static_cast<int>(CardPileType::ACTION7    )]["id"].asInt());
    types[static_cast<int>(CardPileType::ACTION8 )] = GameCards::GetGameCardsTypes(root["Game"][static_cast<int>(CardPileType::ACTION8    )]["id"].asInt());
    types[static_cast<int>(CardPileType::ACTION9 )] = GameCards::GetGameCardsTypes(root["Game"][static_cast<int>(CardPileType::ACTION9    )]["id"].asInt());
    types[static_cast<int>(CardPileType::ACTION10)] = GameCards::GetGameCardsTypes(root["Game"][static_cast<int>(CardPileType::ACTION10   )]["id"].asInt());

    for (size_t i = 0; i < types.size(); i++) {
        for (int j = 0; j < cardCount[i]; j++) {
            allCards.emplace_back(types[i]);
        }
    }

    int n = 0;
    for (size_t i = 0; i < piles.size(); i++) {
        piles[i].clear();
        for (int j = 1; j <= cardCount[i]; j++) {
            piles[i].AddOnTop(&allCards[n++]);
            if  ( i==7)std::cout<< "hello world" << std::endl;
            
        }
    }
    int i =0;
    //std::vector<Player> players
    players.clear();
    for ( size_t i=0; i < root["players"].size();i++){
        players.emplace_back(this);
    } 
        
    for ( auto a : root["players"]){
        for (auto carte : a["deck"]){
            DistributeCard(&players[i],globalToLocalId(carte["id"].asInt(),root),PlayerCards::DECK);
        }
        for (auto carte : a["discard"]){
            DistributeCard(&players[i],globalToLocalId(carte["id"].asInt(),root),PlayerCards::DISCARD);

        }
        for (auto carte : a["hand"]){
            DistributeCard(&players[i],globalToLocalId(carte["id"].asInt(),root),PlayerCards::HAND);
        }
        i++;
        
    }
    


    curPlayerId = root["curPlayerId"].asInt();
    currentPlayer = &players[curPlayerId];
    currentPlayer->startTurn();



    
    
   

}
    
