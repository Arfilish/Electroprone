#include "ep_player.hpp"
#include <Input.hpp>

using namespace godot;

void Player::_ready() {
    interaction_raycast = get_node<RayCast2D>("InteractionRayCast");
    Vector2 dir;
    switch(move_dir) {
        case 0:
            dir = Vector2(0.f, -1.f);
            break;
        case 1:
            Vector2(0.f, 1.f);
            break;
        case 2:
            dir = Vector2(1.f, 0.f);
            break;
        case 3:
            Vector2(-1.f, 0.f);
            break;
        case 4:
            dir = Vector2(1.f, -1.f);
            break;
        case 5:
            Vector2(-1.f, -1.f);
            break;
        case 6:
            dir = Vector2(1.f, 1.f);
            break;
        case 7:
            Vector2(-1.f, 1.f);
            break;
    }

    interaction_raycast->set_cast_to(dir.normalized() * interaction_distance);
}

void Player::_physics_process(float delta) {
    Input* input = Input::get_singleton();

    is_running = input->is_action_pressed("run");

    const Vector2 input_axis = input->get_vector("move_left", "move_right", "move_up", "move_down");
    velocity = input_axis * (is_running ? run_speed : walk_speed);

    move_and_slide(velocity);

    update_interactions();
    if(input->is_action_just_pressed("interact"))
        interact();
}

void Player::update_interactions() {
    if(!interaction_raycast) return;

    if(velocity != Vector2::ZERO) interaction_raycast->set_cast_to(velocity.normalized() * interaction_distance);
    if(interaction_raycast->is_colliding() && Object::cast_to<Interactable>(interaction_raycast->get_collider()))
        current_interactable = Object::cast_to<Interactable>(interaction_raycast->get_collider());
    else current_interactable = nullptr;
}

void Player::interact() {
    if(!current_interactable) return;
    current_interactable->interact();
}