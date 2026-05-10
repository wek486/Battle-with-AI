#ifndef UTIL_H
#define UTIL_H
#include <graphics.h>
#pragma comment(lib,"MSIMG32.lib")
#pragma comment(lib,"WINMM.lib")
#include<iostream>
typedef struct {
	int x, y;
	int w, h;
}Rect;
inline void putimage_ex( IMAGE* img,const Rect* rect_dst,const Rect* rect_src=NULL) {
	static BLENDFUNCTION blend_func = { AC_SRC_OVER,0,255,AC_SRC_ALPHA };
	AlphaBlend(GetImageHDC(GetWorkingImage()), rect_dst->x, rect_dst->y, rect_dst->w, rect_dst->h, GetImageHDC(img), rect_src ? rect_src->x : 0, rect_src ? rect_src->y: 0, rect_src ? rect_src->w : img->getwidth(), rect_src ? rect_src->h : img->getheight(), blend_func);
}
inline void load_audio(std::string path, std::string id) {
	std::string str_cmd = "open "+path+ " alias "+ id;
	mciSendString(str_cmd.c_str(), NULL, 0, NULL);
}
inline void play_audio(std::string id,bool is_loop) {
	std::string str_cmd = "play " + id + (is_loop ? " repeat" : " from 0");//一定加上from 0在 mciSendString 中，如果你给音频起了一个固定的 alias（比如 player_attack_1），而这个音频还没播放完你就再次触发播放指令，MCI 往往会忽略第二次请求。
	mciSendString(str_cmd.c_str(), NULL, 0, NULL);
}
inline void stop_audio(std::string id) {
	std::string str_cmd = "stop " + id;
	mciSendString(str_cmd.c_str(), NULL, 0, NULL);
}
#endif