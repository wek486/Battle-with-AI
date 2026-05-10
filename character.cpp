#include"character.h"
#include "collision_manager.h"
#include<stdio.h>
Character::Character() {
	hit_box = CollisionManager::instance()->create_collision_box();
	hurt_box = CollisionManager::instance()->create_collision_box();
	timer_invulnerable_status.set_wait_time(1.0f);
	timer_invulnerable_status.set_one_shot(true);
	timer_invulnerable_status.set_callback([&]() {
		is_invulnerable = false; });
	timer_invulnerable_blink.set_wait_time(0.075f);
	timer_invulnerable_blink.set_one_shot(false);//实现闪烁是要连续的触发的
	timer_invulnerable_blink.set_callback([&]() {
		is_blink_invisible = !is_blink_invisible; });//实现闪烁间断
}
Character::~Character() {
	CollisionManager::instance()->destroy_collision_box(hit_box);
	CollisionManager::instance()->destroy_collision_box(hurt_box);
}
void Character::decrease_hp() {
	if (is_invulnerable)return;
	hp -= 1;
	if (hp > 0)
		make_invulnerable();//进入无敌状态
	on_hurt();
}
void Character::on_input(const ExMessage& msg) {};
void Character::on_update(float delta) {
	// 1. 先跑状态机更新逻辑
	state_machine.on_update(delta);

	// 2. 处理死亡静止
	if (hp <= 0) velocity.x = 0;

	// 3. 应用重力
	if (enable_gravity) {
		velocity.y += GRAVITY * delta;
	}

	// 4. 【核心改变】先应用位移
	position += velocity * delta;

	// 5. 【核心改变】修正地面锁定逻辑
	if (position.y >= FLOOR_Y) {
		position.y = FLOOR_Y;
		// 重点：只有当角色确实在“往下掉”遇到地面时，才清空 y 速度
		// 这样就不影响 Jump 给出的向上（负数）初速度了
		if (velocity.y > 0) velocity.y = 0;
	}

	// 6. 边界限制
	if (position.x <= 0) position.x = 0;
	if (position.x >= (float)getwidth()) position.x = (float)getwidth();

	// 7. 更新相关组件
	hurt_box->set_position(get_logic_center());
	timer_invulnerable_status.on_update(delta);
	if (is_invulnerable) timer_invulnerable_blink.on_update(delta);

	// 8. 动画驱动
	if (current_animation) {
		Animation& animation = (is_facing_left ? current_animation->left : current_animation->right);
		animation.set_position(position);
		animation.on_update(delta);
	}
}
void Character::on_render() {
	if (!current_animation || (is_invulnerable && is_blink_invisible))return;
	(is_facing_left ? current_animation->left : current_animation->right).on_render();
	printf("Facing Left: %d\n", is_facing_left);
}//这里已经实现了，对普通的移动图像的实现
void Character::switch_state(const std::string& id) {
	state_machine.switch_to(id);
}

void Character::on_hurt(){}//还是空的。后续补上

void Character::set_animation(const std::string& id) {
	if (current_animation == &animation_pool[id]) return;
	current_animation = &animation_pool[id];
	current_animation->left.reset();//重新新动画重第一帧开始
	current_animation->right.reset();
}
