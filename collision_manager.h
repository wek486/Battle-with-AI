#pragma once
#include "collision_box.h"

class CollisionManager {


public:
	 static CollisionManager* instance();
	 CollisionBox* create_collision_box();
	 void destroy_collision_box(CollisionBox* box);
	 void process_collide();
	 void on_debug_render();
private:
	static CollisionManager* Manager;
	CollisionManager() = default;
	~CollisionManager() = default;
	std::vector<CollisionBox*>collisionBox_list;



};