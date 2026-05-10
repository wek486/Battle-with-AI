#pragma once
#include"timer.h"
#include"state_node.h"
class EnemyAimState :public StateNode {
public:
	EnemyAimState();
	~EnemyAimState()=default;
	void on_update(float delta)override;
	void on_render();
	void on_enter()override;
private:
	Timer timer_aim;
};
class EnemyDashInAirState :public StateNode {
public:
	EnemyDashInAirState()=default;
	~EnemyDashInAirState() = default;
	void on_update(float delta)override;
	void on_enter()override;
	void on_exit()override;
private:
	const float speed_dash = 1000.0f;
};
class EnemyDashOnFloorState :public StateNode {
public:
	EnemyDashOnFloorState();
	~EnemyDashOnFloorState() = default;
	void on_update(float delta)override;
	void on_enter()override;

private:
	Timer timer_on_floor;
	const float speed_dash = 1000.0f;
};
class EnemyDeadState :public StateNode {
public:
	EnemyDeadState()=default;
	~EnemyDeadState() = default;
	void on_enter()override;
private:
	
};
class EnemyFallState :public StateNode {
public:
	EnemyFallState() = default;
	~EnemyFallState() = default;
	void on_enter()override;
	void on_update(float delta)override;
private:

};
class EnemyIdleState :public StateNode {
public:
	EnemyIdleState();
	~EnemyIdleState() = default;
	void on_update(float delta)override;
	void on_enter()override;
	void on_exit()override;
private:
	Timer timer_idle;
};
class EnemyJumpState :public StateNode {
public:
	EnemyJumpState() = default;
	~EnemyJumpState() = default;
	void on_enter()override;
	void on_update(float delta)override;
private:
	const float speed_jump = 1000.0f;
};
class EnemyRunState :public StateNode {
public:
	EnemyRunState() = default;
	~EnemyRunState() = default;
	void on_enter()override;
	void on_update(float delta)override;
	void on_exit()override;

private:
	const float min_dis = 350.0f;
	const float speed_run = 500.0f;

};
class EnemySquatState :public StateNode {
public:
	EnemySquatState();
	~EnemySquatState() = default;
	void on_update(float delta)override;
	void on_enter()override;
private:
	Timer timer_squat;
};
class EnemyThrowBarbState :public StateNode {
public:
	EnemyThrowBarbState();
	~EnemyThrowBarbState() = default;
	void on_update(float delta)override;
	void on_enter()override;
private:
	Timer timer_throw_barb;
};
class EnemyThrowSilkState :public StateNode {
public:
	EnemyThrowSilkState();
	~EnemyThrowSilkState() = default;
	void on_update(float delta)override;
	void on_enter()override;
private:
	Timer timer_throw_silk;
};
class EnemyThrowSwordState :public StateNode {
public:
	EnemyThrowSwordState();
	~EnemyThrowSwordState() = default;
	void on_update(float delta)override;
	void on_enter()override;
private:
	Timer timer_throw_sword;
	Timer timer_switch;
};