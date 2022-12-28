#include "Type.hpp"
#include "../Player.hpp"
bool Type::isType(CardType t) const
{
    for (CardType ct : types) if (t == ct) return true;
    return false;
}

void Type::onDraw     (Player*) const {} // quand on pioche et on l ajoute a la main
void Type::onPlay     (Player*) const {} // quand on joue la carte et on l'active
void Type::onAddToDeck(Player*) const {} // quand on achete une ou on resoit une malediction et elle part au deck du joueur
void Type::onDiscard  (Player*) const {} // quand le joueur defausse une carte depuis sa main
void Type::onTrash    (Player*) const {} // quand le joueur jette une carte dans la poubelle permanente
void Type::onDeckChange(Player* , int , int ) const{} // quand le deck du joueur change de taille
bool Type::onReact    (Player*) const { return false; } // quand le joueur est attaqué