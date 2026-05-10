#include"barb.h"
#include"resources_manager.h"
#include"collision_manager.h"
#include"character_manager.h"
#include<random>
Barb::Barb() {
	diff_period =rand()%6;
	animation_loose.set_interval(0.15f);
	animation_loose.set_loop(true);
	animation_loose.set_anchor_mode(Animation::AnchorMode::Centerd);
	animation_loose.add_frame(ResourcesManager::instance()->find_atlas("barb_loose"));

	animation_break.set_interval(0.1f);
	animation_break.set_loop(false);
	animation_break.set_anchor_mode(Animation::AnchorMode::Centerd);
	animation_break.add_frame(ResourcesManager::instance()->find_atlas("barb_break"));
	animation_break.set_callback([&]() {is_valid = false; });

	collision_box = CollisionManager::instance()->create_collision_box();
	collision_box->set_layer_src(CollisionLayer::Enemy);
	collision_box->set_layer_dst(CollisionLayer::Player);
	collision_box->set_size({ 20,20 });
	collision_box->set_on_collide([&]() {on_break(); });

	timer_idle.set_wait_time((float)(rand() % 8 + 3));
	timer_idle.set_one_shot(true);
	timer_idle.set_callback([&]() {
		if (stage == Stage::Idle) {
			stage = Stage::Aim;
			base_position = current_position;
		}
		});
	timer_aim.set_wait_time(0.75f);
	timer_aim.set_one_shot(true);
	timer_aim.set_callback([&]() {
		if (stage == Stage::Aim) {
			stage = Stage::Dash;
			const Vector2& pos_player = CharacterManager::instance()->get_player()->get_position();
			velocity = (pos_player - current_position).normalize() * speed_dash;//normalize函数功能没完善
		}
		});
}
void Barb::on_update(float delta) {
	if (stage == Stage::Idle) {
		timer_idle.on_update(delta);
	}
	if (stage == Stage::Aim) {
		timer_aim.on_update(delta);
	}
	total_delta_time += delta;
	switch (stage) {
	case Barb::Stage::Idle:
		current_position.y = base_position.y + sin(total_delta_time * 2 + diff_period) * 30;
		break;
	case Barb::Stage::Aim:
		current_position.x = base_position.x + (rand() % 21 - 10);
		break;
	case Barb::Stage::Dash:
		current_position += velocity * delta;
		if (current_position.y >= CharacterManager::instance()->get_player()->get_floor_y()) {//看冲刺时候是否装上地面
			on_break();
		}
		if (current_position.y <= 0)is_valid = false;
		break;
	}
	collision_box->set_position(current_position);

	current_animation = (stage == Stage::Break ? &animation_break :& animation_loose);
	current_animation->set_position(current_position);
	current_animation->on_update(delta);
}
void Barb::on_render() {
	current_animation->on_render();
}
void Barb::on_break() {
	if (stage == Stage::Break)return;
	stage = Stage::Break;
	collision_box->set_enabled(false);
	play_audio(_T("barb_break"), false);
}
Barb::~Barb() {
	CollisionManager::instance()->destroy_collision_box(collision_box);
}