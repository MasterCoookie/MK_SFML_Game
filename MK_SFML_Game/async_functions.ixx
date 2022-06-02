#include <semaphore>

#include "GameEngine.h"

export module async_functions;

export void async_read_input(GameEngine* g);
export void async_move_players(Player* p1, Player* p2);
export void async_recovery(Player* p);
export void async_animation(Player* p);
export void init_gameobject_variables(GameObject& gameObject);

module :private;

std::counting_semaphore<1> prepare(0);

void async_read_input(GameEngine* g) {
	g->updateInput();
	prepare.release();
}

void async_move_players(Player* p1, Player* p2) {
	bool can_p1_move = p1->canMove();
	bool can_p2_move = p2->canMove();
	prepare.acquire();

	if (can_p1_move) {
		p1->duck();
		p1->move();
		p1->jump();
	}
	if (can_p2_move) {
		p2->duck();
		p2->move();
		p2->jump();
	}
}

void async_recovery(Player* p) {
	p->updateRecovery();
}

void async_animation(Player* p) {
	p->updateAnimation();
	p->resetMovementMatrix();
}

void init_gameobject_variables(GameObject& gameObject) {
	gameObject.initVariables();
}