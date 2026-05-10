#ifndef CHARACTER_H
#define CHARACTER_H
#include "animation.h"
#include "vector2.h"
#include "state_machine.h"
#include "collision_box.h "
class Character {
public:
	Character();
	~Character();
	void decrease_hp();
	int get_hp()const {
		return hp;
	}
	void set_position(const Vector2& position) {
		this->position = position;
	}
	const Vector2 get_position()const {
		return position;
	}
	void set_velocity(const Vector2& velocity) {
		this->velocity = velocity;
	}
	const Vector2 get_velocity() {
		return velocity;
	}
	Vector2 get_logic_center()const {//为了获得逻辑中心
		return Vector2(position.x, position.y - logic_height / 2);
	}
	void set_gravity_enable(bool flag) {
		enable_gravity = flag;
	}
	CollisionBox* get_hit_box() {
		return hit_box;
	}
	CollisionBox* get_hurt_box() {
		return hurt_box;
	}
	float get_floor_y() {
		return FLOOR_Y;
	}
	bool is_on_floor() {
		return position.y >= (FLOOR_Y-5.0f);
	}
	void make_invulnerable() {
		is_invulnerable = true;
		timer_invulnerable_status.restart();

	}
	virtual void on_input(const ExMessage& msg);
	virtual void on_update(float delta);
	virtual void on_render();
	virtual void on_hurt();
	void switch_state(const std::string& id);
	void set_animation(const std::string& id);
protected:
	struct AnimationGroup {
		Animation left;
		Animation right;
	};
	const float FLOOR_Y = 620;//地板y轴坐标
	const float GRAVITY = 980 * 2;//重力
	Vector2 position;
	int hp = 10;
	Vector2 velocity;//速度
	float logic_height = 0;
	bool is_facing_left = true;
	StateMachine state_machine;//角色状态机
	bool enable_gravity = true;
	bool is_invulnerable = false;//为了实现无敌状态
	Timer timer_invulnerable_blink;//闪烁定时器
	Timer timer_invulnerable_status;//无敌装态定时器
	bool is_blink_invisible = false;
	CollisionBox* hit_box;
	CollisionBox* hurt_box;
	AnimationGroup* current_animation = NULL;
	std::unordered_map<std::string, AnimationGroup>animation_pool;
protected:
	// ... 原有变量 ...
	float speed_run = 0;   // 声明在这里
	float speed_jump = 0;
	float speed_roll = 0;
};





#endif
