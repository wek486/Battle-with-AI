#ifndef COLLISION_BOX_H
#define COLLISION_BOX_H
#include "vector2.h"
#include "collision_layer.h"
#include <functional>
class CollisionManager;
class CollisionBox {
public:
	friend class CollisionManager;
	void set_enabled(bool is_enabled) {
		this->enabled = is_enabled;
	}
	void set_layer_src(CollisionLayer layer) {
		layer_src = layer;
	}
	void set_layer_dst(CollisionLayer layer) {
		layer_dst = layer;
	}
	void set_size(const Vector2& new_size) {
		size = new_size;

	}
	const Vector2& get_size()const {
		return size;
	}
	void set_position(const Vector2& new_position) {
		position = new_position;
	}
	void set_on_collide(std::function<void()>on_collide) {
		this->on_collide = on_collide;
	}
private:
	Vector2 size;
	Vector2 position;
	bool enabled = true;//ÊÇ·ñ¿ªÆôÅö×²¼ì²â
	std::function<void()> on_collide;
	CollisionLayer layer_src = CollisionLayer::None;
	CollisionLayer layer_dst = CollisionLayer::None;
	CollisionBox() = default;
	~CollisionBox() = default;


};






#endif
