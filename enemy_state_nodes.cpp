#include"enemy_states_nodes.h"
#include"character_manager.h"
#include"enemy.h"
EnemyAimState::EnemyAimState() {
	timer_aim.set_one_shot(true);
	timer_aim.set_wait_time(0.5f);
	timer_aim.set_callback([&]() {

		Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
		enemy->set_gravity_enable(true);
		enemy->switch_state("dash_in_air");
		});
}
void EnemyAimState::on_enter() {
	CharacterManager::instance()->get_enemy()->set_animation("aim");
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
	enemy->set_gravity_enable(false);
	enemy->set_velocity({ 0,0 });
	timer_aim.restart();
}
void EnemyAimState::on_update(float delta) {
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
	timer_aim.on_update(delta);
	if (enemy->get_hp() < 0)
		enemy->switch_state("dead");
}
void EnemyDashInAirState::on_enter() {
	CharacterManager::instance()->get_enemy()->set_animation("dash_in_air");
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
	const Character* player = CharacterManager::instance()->get_player();
	Vector2 pos_target = { player->get_position().x,player->get_position().y };
	enemy->set_velocity(((pos_target - enemy->get_position()).normalize() * speed_dash));//normalize函数weiwnags
	enemy->set_dashing_in_air(true);
	enemy->set_gravity_enable(false);
	enemy->on_dash();
	play_audio(_T("enemy_dash"), false);
}
void EnemyDashInAirState::on_update(float delta) {
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
	if (enemy->get_hp() <= 0)
		enemy->switch_state("dead");
	else if (enemy->is_on_floor()) {
		enemy->switch_state("idle");
	}
}
void EnemyDashInAirState::on_exit() {
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
	enemy->set_gravity_enable(true);
	enemy->set_dashing_in_air(false);
}
EnemyDashOnFloorState::EnemyDashOnFloorState() {
	timer_on_floor.set_one_shot(true);
	timer_on_floor.set_wait_time(0.5f);
	timer_on_floor.set_callback([&]() {
		Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
		enemy->set_dashing_on_floor(false);
		});
}
void EnemyDashOnFloorState::on_enter() {
	CharacterManager::instance()->get_enemy()->set_animation("dash_on_floor");
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
	enemy->set_velocity({ enemy->get_facing_left() ? -speed_dash : speed_dash,0 });
	enemy->set_dashing_on_floor(true);
	enemy->on_dash();
	timer_on_floor.restart();
	play_audio(_T("enemy_dash"), false);
}
void EnemyDashOnFloorState::on_update(float delta) {
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
	timer_on_floor.on_update(delta);
	if (enemy->get_hp() <= 0)
		enemy->switch_state("dead");
	else if (!enemy->get_dashing_on_floor()) {
		enemy->switch_state("idle");
	}
}
void EnemyDeadState::on_enter() {
	MessageBox(GetHWnd(), _T("good，你不是太笨！"), _T("挑战成功，完结散花！"), MB_OK);
	exit(0);
}
void EnemyFallState::on_enter() {
	CharacterManager::instance()->get_enemy()->set_animation("fall");
}
void EnemyFallState::on_update(float delta) {
	Enemy* enemy= (Enemy*)CharacterManager::instance()->get_enemy();
	if (enemy->get_hp() <= 0)enemy->switch_state("dead");
	else if (enemy->is_on_floor()) {
		enemy->switch_state("idle");
	}
}
EnemyIdleState::EnemyIdleState() {
	timer_idle.set_one_shot(true);
	timer_idle.set_callback([&]() {
		Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
		int rand_num = rand() % 101;
		if (enemy->get_hp() > 5) {
			if (rand_num <= 25) {
				if (!enemy->is_on_floor()) {
					enemy->switch_state("fall");//下降
				}
				else {
					enemy->switch_state("jump");
				}
			}
			else if (rand_num <= 50) {
				enemy->switch_state("throw_barb");
			}
			else if (rand_num <= 80) {
				enemy->switch_state("squat");
			}
			else if(rand_num<=90){
				enemy->switch_state("throw_silk");

			}
			else { enemy->switch_state("throw_sword"); }
		}
		else {
			if (rand_num <= 20) {
				if (!enemy->is_on_floor()) {
					enemy->switch_state("fall");//下降
				}
				else {
					enemy->switch_state("jump");
				}
			}
			else if (rand_num <= 50) {
				enemy->switch_state("throw_sword");
			}
			else if (rand_num <= 70) {
				enemy->switch_state("throw_silk");
			}
			else if (rand_num <= 80) { enemy->switch_state("throw_barb"); }
			else enemy->switch_state("squat");
		}
		});
}
void EnemyIdleState::on_enter() {
	CharacterManager::instance()->get_enemy()->set_animation("idle");
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
	enemy->set_facing_left(enemy->get_position().x > CharacterManager::instance()->get_player()->get_position().x);
	enemy->set_velocity({ 0,0 });
	float wait_time = 0;
	if (enemy->get_hp() > 5)
		wait_time = rand() % 3 * 0.25f;
	else
		wait_time = rand() % 2 * 0.25f;
	timer_idle.set_wait_time(wait_time);
	timer_idle.restart();
	
}
void EnemyIdleState::on_update(float delta) {
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
	enemy->set_facing_left(enemy->get_position().x > CharacterManager::instance()->get_player()->get_position().x);
	timer_idle.on_update(delta);
	if (enemy->get_hp() <= 0)enemy->switch_state("dead");
	else if (enemy->get_velocity().y > 0)
		enemy->switch_state("fall");
}
void EnemyIdleState::on_exit() {
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
	
}
void EnemyJumpState::on_enter() {
	CharacterManager::instance()->get_enemy()->set_animation("jump");
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
	enemy->set_velocity({ 0,-speed_jump });
}
void EnemyJumpState::on_update(float delta) {
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
	if (enemy->get_hp() <= 0)
		enemy->switch_state("dead");
	else if (enemy->get_velocity().y > 0) {
		int rand_num = rand() % 101;
		if(enemy->get_hp()>5)
		if (rand_num <= 50) {
			enemy->switch_state("aim");
		}
		else if (rand_num <= 80) {
			enemy->switch_state("fall");
		}
		else {
			enemy->switch_state("throw_silk");
		}
	else {
			if (rand_num <= 50) {
				enemy->switch_state("throw_silk");
			}
			else if (rand_num <= 80) {
				enemy->switch_state("fall");
			}
			else
				enemy->switch_state("aim");
	}
	}
}
void EnemyRunState::on_enter() {
	CharacterManager::instance()->get_enemy()->set_animation("run");
	play_audio(_T("enemy_run"), true);
 }
void EnemyRunState::on_update(float delta) {
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
	const Vector2& pos_enemy = enemy->get_position();
	const Vector2& pos_player = CharacterManager::instance()->get_player()->get_position();
	enemy->set_facing_left(enemy->get_position().x > CharacterManager::instance()->get_player()->get_position().x);
	enemy->set_velocity({ pos_enemy.x < pos_player.x ? speed_run : -speed_run,0 });
	if (enemy->get_hp() <= 0)enemy->switch_state("dead");
	else if (abs(pos_enemy.x - pos_player.x) <= min_dis) {//奔跑状态退出为，与玩家的距离小于一定值
		int rand_num = rand() % 101;
		if (enemy->get_hp() > 5) {
			if (rand_num <= 75)enemy->switch_state("squat");
			else enemy->switch_state("throw_silk");
		}
		else {
			if (rand_num <= 75)
				enemy->switch_state("throw_silk");
			else enemy->switch_state("squat");
		}
		stop_audio(_T("enemy_run"));
	}

}
void EnemyRunState::on_exit() {
	Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
	enemy->set_velocity({ 0,0 });
}
 EnemySquatState::EnemySquatState() {
	timer_squat.set_one_shot(true);
	timer_squat.set_wait_time(0.5f);
	timer_squat.set_callback([&]() {
		Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
		enemy->switch_state("dash_on_floor");
		});
}
 void EnemySquatState::on_enter() {
	 Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
	 enemy->set_animation("squat");
	 enemy->set_facing_left(enemy->get_position().x > CharacterManager::instance()->get_player()->get_position().x);//面朝向有问题，改了一下，后续有问题再改
		 timer_squat.restart();
 }
 void EnemySquatState::on_update(float delta) {
	 timer_squat.on_update(delta);
	 Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
	 if (enemy->get_hp() <= 0) {
		 enemy->switch_state("dead");
	 }
 }
 EnemyThrowBarbState::EnemyThrowBarbState() {
	 timer_throw_barb.set_one_shot(true);
	 timer_throw_barb.set_wait_time(0.8f);
	 timer_throw_barb.set_callback([&]() {
		 Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
		 enemy->throw_barb();
		 enemy->switch_state("idle");
		 });
 }
 void EnemyThrowBarbState::on_enter() {
	 Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
	 enemy->set_animation("throw_barb");
	 timer_throw_barb.restart();
	 play_audio(_T("enemy_throw_brabs"), false);
 }
 void EnemyThrowBarbState::on_update(float delta) {
	 Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
	 timer_throw_barb.on_update(delta);
	 if (enemy->get_hp() <= 0)
		 enemy->switch_state("dead");
 }
 EnemyThrowSilkState::EnemyThrowSilkState() {
	 timer_throw_silk.set_one_shot(true);
	 timer_throw_silk.set_wait_time(0.9f);
	 timer_throw_silk.set_callback([&]() {
		 Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
		 enemy->set_gravity_enable(true);
		 enemy->set_throwing_silk(false);
		 if (!enemy->is_on_floor() && enemy->get_hp() > 5 &&(rand()%101)<=25) {
			 enemy->switch_state("aim");
		 }
		 else if (!enemy->is_on_floor()) {
			 enemy->switch_state("fall");
		 }
		 else {
			 enemy->switch_state("idle");
		 }
		 });
 }
 void EnemyThrowSilkState::on_enter() {
	 Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
	 enemy->set_animation("throw_silk");
	 enemy->set_gravity_enable(false);
	 enemy->set_velocity({ 0,0 });
	 enemy->set_throwing_silk(true);
	 timer_throw_silk.restart();
	 play_audio(_T("enemy_throw_silk"), false);
 }
 void EnemyThrowSilkState::on_update(float delta) {
	 timer_throw_silk.on_update(delta);
	 Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
	 if (enemy->get_hp() <= 0)enemy->switch_state("dead");

 }
 EnemyThrowSwordState::EnemyThrowSwordState() {
	 timer_throw_sword.set_wait_time(0.65f);
	 timer_throw_sword.set_one_shot(true);
	 timer_throw_sword.set_callback([&]() {
		 Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
		 enemy->throw_sword();
		 play_audio(_T("enemy_throw_sword"), false);
		 });
	 timer_switch.set_one_shot(true);
	 timer_switch.set_wait_time(1.0f);
	 timer_switch.set_callback([&]() {
		 Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
		 int rand_num = rand() % 101;
		 if (enemy->get_hp() > 5) {
			 if (rand_num <= 50)enemy->switch_state("squat");
			 else if (rand_num <= 80)enemy->switch_state("jump");
			 else enemy->switch_state("idle");
		 }
		 else {
			 if (rand_num <= 50)enemy->switch_state("jump");
			 else if (rand_num <= 80)enemy->switch_state("throw_silk");
			 else enemy->switch_state("idle");
		 }
		 });
 }
 void EnemyThrowSwordState::on_enter() {
	 Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
	 enemy->set_animation("throw_sword");
	 timer_throw_sword.restart();
	 timer_switch.restart();
 }
 void EnemyThrowSwordState::on_update(float delta) {
	 timer_throw_sword.on_update(delta);
	 timer_switch.on_update(delta);
	 Enemy* enemy = (Enemy*)CharacterManager::instance()->get_enemy();
	 if (enemy->get_hp() < 0)enemy->switch_state("dead");
 }