#include "ep_pickupable.hpp"
#include "ep_player.hpp"

using namespace godot;

void Pickupable::on_interacted(Node* interacted) {
    Player* plr = Object::cast_to<Player>(interacted);
    if(!plr) return;

    if(plr->add_item_to_inventory(id)) 
    {
        emit_signal("picked_up");
        queue_free();
    }
}

bool Pickupable::can_interact(Node* interacted) const {
    if(!this) return false;
    Player* plr = Object::cast_to<Player>(interacted);
    if(!plr) return false;

    return Interactable::can_interact(interacted) && !plr->inventory_has_items(Array::make(id));
}