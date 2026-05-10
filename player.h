#pragma once
#include "character.h"
#include "resources_manager.h"
#include"bullet_time_manager.h"
class Player :public Character {
public:
	enum class AttackDir {
		up, down, left, right
	};
	Player();
	~Player()=default;
	void on_input(const ExMessage& msg)override;
	void on_update(float delta)override;
	void on_render()override;
	void on_hurt()override;
	void set_rolling(bool flag){
		is_rolling = flag;
	}
	bool  get_rolling() {
		return is_rolling;
	}
	bool can_roll() {
		return is_roll_cd_comp && !is_rolling && is_roll_key_down;
	}
	 
	void set_attacking(bool flag) {
		is_attacking = flag;
	}
	bool get_attacking() {
		return is_attacking;
	}
	bool can_attack() {
		return is_attack_cd_comp && !is_attacking && is_attack_key_down;
	}
	bool can_jump() {
		return is_on_floor() && is_jump_key_down;
	}
	int get_move_axis() {
		return is_right_key_down - is_left_key_down;
	}
	AttackDir get_attack_dir() {
		return attack_dir;
	}
	void on_jump();
	void on_land();
	void on_roll();
	void on_attack();
private:
	Timer timer_roll_cd;
	bool is_rolling = false;
	bool is_roll_cd_comp = true;

	Timer timer_attack_cd;
	bool is_attacking = false;
	bool is_attack_cd_comp = true;

	bool is_left_key_down = false;
	bool is_right_key_down = false;
	bool is_jump_key_down = false;
	bool is_down_key_down = false;
	bool is_roll_key_down = false;
	bool is_attack_key_down = false;

	Animation animation_slash_up;
	Animation animation_slash_down;
	Animation animation_slash_left;
	Animation animation_slash_right;
	AttackDir attack_dir = AttackDir::right;
	Animation* current_slash_animation = NULL;

	bool is_jump_vfx_visible = false;//Á£×ÓÌØÐ§
	Animation animation_jump_vfx;

	bool is_land_vfx_visible = false;
	Animation animation_land_vfx;

	const float cd_roll = 0.75f;
	const float cd_attack = 0.5f;
	


	void update_attack_dir(int x, int y);
};
