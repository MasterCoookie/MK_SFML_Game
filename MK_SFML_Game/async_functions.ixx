#include <semaphore>

#include "GameEngine.h"

export module async_functions;

export void async_read_input(GameEngine* g);
export void async_move_players(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2);
export void async_recovery(std::shared_ptr<Player> p);
export void async_animation(std::shared_ptr<Player> p);
export const bool update_view(GameEngine* g, std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, sf::View* view, const float& dist_between_players);
export void init_gameobject_variables(GameObject* gameObject);

module :private;


std::counting_semaphore<1> prepare(0);

void async_read_input(GameEngine* g) {
	g->updateInput();
	prepare.release();
}

void async_move_players(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2) {
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

void async_recovery(std::shared_ptr<Player> p) {
	p->updateRecovery();
}

void async_animation(std::shared_ptr<Player> p) {
	p->updateAnimation();
	p->resetMovementMatrix();
}

//returns true if screen was moved
const bool update_view(GameEngine* g, std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, sf::View* view, const float& dist_between_players) {
	if ((p1->getPosition().x - (p1->getBounds().width / 3) < (view->getCenter().x - 640.f))
		&& view->getCenter().x > 640.f
		&& dist_between_players < 1020.f) {
		view->move(-10.f, 0.f);
		g->moveGUIElements(-10.f, 0.f);
		return true;
	} else if ((p2->getPosition().x + (p2->getBounds().width / 3) > (view->getCenter().x + 640.f))
		&& view->getCenter().x < 1920.f
		&& dist_between_players < 1020.f) {
		view->move(+10.f, 0.f);
		g->moveGUIElements(+10.f, 0.f);
		return true;
	}
	return false;
}


void init_gameobject_variables(GameObject* gameObject) {
	gameObject->initVariables();
}