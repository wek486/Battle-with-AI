#include"character_manager.h"
CharacterManager* CharacterManager::manager = NULL;
CharacterManager* CharacterManager::instance() {
	if (!manager)
	{
		manager = new CharacterManager();
	}
	return manager;
}
void CharacterManager::on_input(const ExMessage& msg) {
	player->on_input(msg);
	enemy->on_input(msg);
}
void CharacterManager::on_update(float delta) {
	player->on_update(delta);
	enemy->on_update(delta);
}
void CharacterManager::on_render() {
	bullet_time_manager::instance()->pos_process();
	player->on_render();
	enemy->on_render();
}
CharacterManager::CharacterManager() {
	player = new Player();
	enemy = new Enemy();
}
CharacterManager::~CharacterManager() {
	delete enemy;
	delete player;
}