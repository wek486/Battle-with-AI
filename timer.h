#ifndef TIMER_H
#define TIMER_H
#include <functional>
#include <iostream>
class Timer {

public:
	Timer() = default;
	~Timer() = default;
	void restart() {
		passed_time = 0.0;
		is_shotted = false;
	}
	void resume() {
		is_paused = false;
	}
	void pause() {
		is_paused = true;
	}
	void set_wait_time(float time) {
		wait_time = time;
	}
	void set_one_shot(bool one_shot) {
		is_one_shot = one_shot;
	}
	void set_callback(std::function<void()> callback) { this->callback = callback; }//动画问题，攻击没消失检查定时器回调函数
	void on_update(float delta) {
		if (is_paused)return;
		passed_time += delta;
		if (passed_time >= wait_time) {
			bool can_shot = (!is_one_shot || (is_one_shot && !is_shotted));
				is_shotted = true;
			if (can_shot && callback) {
				callback();
				passed_time -= wait_time;
			}
		}



	}
private:
	float passed_time = 0.0;
	float wait_time = 0.0;
	bool is_one_shot = false;
	bool is_shotted = false;
	bool is_paused = false;
	std::function<void()> callback;
};




#endif
