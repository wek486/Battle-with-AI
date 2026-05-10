#include"bullet_time_manager.h"
#include<iostream>
#include<graphics.h>
bullet_time_manager* bullet_time_manager::manager =NULL;
bullet_time_manager* bullet_time_manager::instance() {
	if (!manager) {
		manager = new bullet_time_manager();
	}
	return manager;
}
void bullet_time_manager::pos_process() {
	DWORD* buffer = GetImageBuffer();
	int w = getwidth(), h = getheight();
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int idx = y * w + x;
			DWORD color = buffer[idx];
			BYTE r = (BYTE)(GetBValue(color) * lerp(1.0f, dst_color_factor, progress));
			BYTE g = (BYTE)(GetGValue(color) * lerp(1.0f, dst_color_factor, progress));
			BYTE b = (BYTE)(GetRValue(color) * lerp(1.0f, dst_color_factor, progress));
			buffer[idx] = BGR(RGB(r, g, b) | ((DWORD)(BYTE)(255) << 24));//交换颜色通道，但如果获取颜色通道没反的话，就不用了
		}
	}
}
float bullet_time_manager::on_update(float delta) {
	float delta_progress = speed_progress * delta;
	progress += delta_progress*(status == Status::Entering ? 1 : -1);//比例进程//实现没进入时的时间正常
	if (progress < 0)progress = 0;//防止超过头尾....
	if (progress > 1.0f)progress = 1.0f;
	return delta * lerp(1.0f, dst_delta_factor, progress);//真实时间乘上缩放时间比例
}