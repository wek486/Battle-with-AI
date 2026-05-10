#pragma once
#include"animation.h"
#include"collision_box.h"
class Sword {
public:
	Sword(const Vector2& position, bool move_left);
	~Sword();
	void on_update(float delta);
	void on_render();
	bool check_valid()const {
		return is_valid;
	}
private:
	const float speed_move = 550.0f;
	Vector2 position;
	Vector2 velocity;
	Animation animation;
	bool is_valid=true;
	CollisionBox* collision_box = NULL;
};
