#include<iostream>
#include<graphics.h>
#include<chrono>
#include<thread>
#include"collision_manager.h"
#include"character_manager.h"
#include"resources_manager.h"
#include"bullet_time_manager.h"
#include<ctime>
#include<stdlib.h>
#pragma comment(lib,"Imm32.lib")
static void draw_background(){
	static IMAGE* img_background = ResourcesManager::instance()->find_image("background");
	static Rect rect_dst = {
		(getwidth() - img_background->getwidth()) / 2,
		(getheight() - img_background->getheight()) / 2,
		img_background->getwidth(),
		img_background->getheight()
	};
	putimage_ex(img_background, &rect_dst);
}
static void draw_remain_hp() {
	static IMAGE* img_ui_heart = ResourcesManager::instance()->find_image("ui_heart");
	Rect rect_dst = { 0,10,img_ui_heart->getwidth(),img_ui_heart->getheight() };
	for (int i = 0; i < CharacterManager::instance()->get_player()->get_hp(); i++) {
		rect_dst.x = 10 + i * 40;
		putimage_ex(img_ui_heart, &rect_dst);
	}
}
int main(void) {
	srand(time(NULL));
	using namespace std::chrono;
	const nanoseconds frame_duration(1000000000 / 144);
	HWND hwnd = initgraph(1280, 720, EW_SHOWCONSOLE);//后续可以关闭的控制台
	HIMC himc = ImmGetContext(hwnd);
	if (himc) {
		ImmAssociateContext(hwnd, NULL); // 立即解除关联，这样游戏过程中按 A/D 就不会跳输入法了
		ImmReleaseContext(hwnd, himc);   // 释放获取到的上下文句柄
	}
	SetWindowText(hwnd, _T("空洞大冒险"));

	try {
		ResourcesManager::instance()->load();
	}
	catch (std::string err) {
		MessageBox(hwnd,err.c_str(), _T("资源加载失败"), (MB_OK | MB_ICONERROR));
		return -1;
	}
	//HWND f = GetForegroundWindow();
	//HIMC PrevImc = ImmAssociateContext(f, NULL);换成更稳妥的方法

	
	ExMessage msg;
	bool is_quit = false;
	BeginBatchDraw();
	steady_clock::time_point last_frame = steady_clock::now();
	play_audio(_T("bgm"), true);
	while (!is_quit) {
		ImmAssociateContext(hwnd, NULL);
		while (peekmessage(&msg)) {
			CharacterManager::instance()->on_input(msg);
			//处理信息
		}
		steady_clock::time_point current_frame = steady_clock::now();
		duration<float> delta = duration<float>(current_frame - last_frame);//把纳秒换成小数的时间间隔，由chrono提供
		
		float scaled_delta = bullet_time_manager::instance()->on_update(delta.count());
		CharacterManager::instance()->on_update(scaled_delta);
	
		CollisionManager::instance()->process_collide();

		//更新
		setbkcolor(RGB(0, 0, 0));
		cleardevice();
		//绘图
		
		draw_background();
		CharacterManager::instance()->on_render();
		draw_remain_hp();
		CollisionManager::instance()->on_debug_render();
		FlushBatchDraw();
		last_frame = current_frame;
		nanoseconds sleep_duration = frame_duration - (steady_clock::now() - current_frame);
		if(sleep_duration>nanoseconds(0))
			std::this_thread::sleep_for(sleep_duration);//休眠
		
	}
	stop_audio(_T("bgm"));
	EndBatchDraw();
	closegraph();
	//ImmAssociateContext(f, PrevImc);

	return 0;
}