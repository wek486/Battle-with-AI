#pragma once
class bullet_time_manager {
public:
	enum class Status {
		Entering,
		Exiting
	};
	static bullet_time_manager* instance();
	void set_status(Status status) {
		this->status = status;
	}
	float on_update(float delta);
	void pos_process();//过程处理，画面变暗
private:
	static bullet_time_manager* manager;
	bullet_time_manager()=default;
	~bullet_time_manager() = default;
	Status status=Status::Exiting;
	float progress = 0;//进度
	const float speed_progress = 2.0f;
	const float dst_delta_factor = 0.35f;
	const float dst_color_factor = 0.35f;
	float lerp(float start, float end, float t) {//数值大小，为了让，结果越来越小，亮度变暗
		return (1 - t) * start + t * end;
	}
};
