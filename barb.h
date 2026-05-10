#pragma once
#include"animation.h"
#include"collision_box.h"
class Barb {
public:
	Barb();
	~Barb();
	void on_update(float delta);
	void on_render();
	void set_position(const Vector2& position) {
		current_position = position;
		base_position = position;
	}
	bool check_valid() {
		return is_valid;
	}
private:
	enum class Stage {
		Idle,
		Aim,
		Dash,
		Break
	};
	const float speed_dash = 1500.0f;
	Timer timer_idle;
	Timer timer_aim;
	int diff_period=0;//随机值，实现刺球上下浮动
	float total_delta_time = 0;


	Vector2 base_position;
	Vector2 velocity;
	Vector2 current_position;

	Animation animation_loose;
	Animation animation_break;
	Animation* current_animation = NULL;
	Stage stage = Stage::Idle;
	CollisionBox* collision_box = NULL;
	void on_break();
	bool is_valid=true;

};
