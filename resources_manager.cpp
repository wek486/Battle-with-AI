#include "resources_manager.h"
ResourcesManager* ResourcesManager::manager = nullptr;
ResourcesManager* ResourcesManager::instance() {
	if (!manager) {
		manager = new ResourcesManager();
	}
	return manager;
}
ResourcesManager::ResourcesManager() = default;
ResourcesManager::~ResourcesManager() = default;
struct ImageInfo {
	std::string id;
	std::string path;
};
struct AtlasInfo {
	std::string id;
	std::string path;
	int num_frame = 0;
};
static const std::vector<ImageInfo>image_info_list={
	{"background",R"(resources/background.png)"},
	{"ui_heart",R"(resources/ui_heart.png)"},
	{"player_attack_right",R"(resources/player/attack.png)"},
	{"player_dead_right",R"(resources/player/dead.png)"},
	{"player_fall_right",R"(resources/player/fall.png)"},
	{"player_idle_right",R"(resources/player/idle.png)"},
	{"player_jump_right",R"(resources/player/jump.png)"},
	{"player_run_right",R"(resources/player/run.png)"},
	{"player_roll_right",R"(resources/player/roll.png)"},

	{"player_vfx_attack_down",R"(resources/player/vfx_attack_down.png)"},
	{"player_vfx_attack_left",R"(resources/player/vfx_attack_left.png)"},
	{"player_vfx_attack_right",R"(resources/player/vfx_attack_right.png)"},
	{"player_vfx_attack_up",R"(resources/player/vfx_attack_up.png)"},
	{"player_vfx_jump",R"(resources/player/vfx_jump.png)"},
	{"player_vfx_land",R"(resources/player/vfx_land.png)"},
};
static const  std::vector<AtlasInfo>atlas_info_list = {
	{"barb_break",R"(resources/enemy/barb_break/%d.png)",3},
	{"barb_loose",R"(resources/enemy/barb_loose/%d.png)",5},
	{"silk",R"(resources/enemy/silk/%d.png)",9},
	{"sword_left",R"(resources/enemy/sword/%d.png)",3},

	{"enemy_aim_left",R"(resources/enemy/aim/%d.png)",9},
	{"enemy_dash_in_air_left",R"(resources/enemy/dash_in_air/%d.png)",2},
	{"enemy_dash_on_floor_left",R"(resources/enemy/dash_on_floor/%d.png)",2},
	{"enemy_fall_left",R"(resources/enemy/fall/%d.png)",4},
	{"enemy_idle_left",R"(resources/enemy/idle/%d.png)",6},
	{"enemy_jump_left",R"(resources/enemy/jump/%d.png)",8},
	{"enemy_run_left",R"(resources/enemy/run/%d.png)",8},
	{"enemy_squat_left",R"(resources/enemy/squat/%d.png)",10},
	{"enemy_throw_barb_left",R"(resources/enemy/throw_barb/%d.png)",8},
	{"enemy_throw_silk_left",R"(resources/enemy/throw_silk/%d.png)",17},
	{"enemy_throw_sword_left",R"(resources/enemy/throw_sword/%d.png)",16},
	{"enemy_vfx_dash_in_air_left",R"(resources/enemy/vfx_dash_in_air/%d.png)",5},
	{"enemy_vfx_dash_on_floor_left",R"(resources/enemy/vfx_dash_on_floor/%d.png)",6},
};
static inline bool check_image_valid(IMAGE* image) {
	return GetImageBuffer(image);//获取不了像素缓冲区自然就是没有成功获取图片
}

void ResourcesManager::load() {
	for (const auto& info : image_info_list) {
		IMAGE* image = new IMAGE();
		loadimage(image, info.path.c_str());
		if (!check_image_valid(image))throw info.path+"路径不对";//抛异常
		image_pool[info.id] = image;
	}
	for (const auto& info : atlas_info_list) {
		Atlas* atlas = new Atlas();
		atlas->load_image(info.path, info.num_frame);
		for (int i = 0; i < atlas->get_size(); i++) {
			IMAGE* image = atlas->get_image(i);
			if (!check_image_valid(image))throw info.path+"路径不对";
		}
		atlas_pool[info.id] = atlas;
	}
	flip_image("player_attack_right", "player_attack_left", 5);
	flip_image("player_dead_right", "player_dead_left", 6);
	flip_image("player_fall_right", "player_fall_left", 5);
	flip_image("player_idle_right", "player_idle_left", 5);
	flip_image("player_jump_right", "player_jump_left", 5);
	flip_image("player_run_right", "player_run_left", 10);
	flip_image("player_roll_right", "player_roll_left", 7);
	flip_atlas("sword_left", "sword_right");
	flip_atlas("enemy_aim_left", "enemy_aim_right");
	flip_atlas("enemy_dash_on_floor_left", "enemy_dash_on_floor_right");
	flip_atlas("enemy_dash_in_air_left", "enemy_dash_in_air_right");
	flip_atlas("enemy_fall_left", "enemy_fall_right");
	flip_atlas("enemy_idle_left", "enemy_idle_right");
	flip_atlas("enemy_jump_left", "enemy_jump_right");
	flip_atlas("enemy_run_left", "enemy_run_right");
	flip_atlas("enemy_squat_left", "enemy_squat_right");
	flip_atlas("enemy_throw_barb_left", "enemy_throw_barb_right");
	flip_atlas("enemy_throw_silk_left", "enemy_throw_silk_right");
	flip_atlas("enemy_throw_sword_left", "enemy_throw_sword_right");
	flip_atlas("enemy_vfx_dash_in_air_left", "enemy_vfx_dash_in_air_right");
	flip_atlas("enemy_vfx_dash_on_floor_left", "enemy_vfx_dash_on_floor_right");
	load_audio(R"(resources\audio\bgm.mp3)","bgm");
	load_audio(R"(resources\audio\barb_break.mp3)", "barb_break");
	load_audio(R"(resources\audio\bullet_time.mp3)", "bullet_time");
	load_audio(R"(resources\audio\enemy_dash.mp3)", "enemy_dash");
	load_audio(R"(resources\audio\enemy_run.mp3)", "enemy_run");
	load_audio(R"(resources\audio\enemy_hurt_1.mp3)", "enemy_hurt_1");
	load_audio(R"(resources\audio\enemy_hurt_2.mp3)", "enemy_hurt_2");
	load_audio(R"(resources\audio\enemy_hurt_3.mp3)", "enemy_hurt_3");
	load_audio(R"(resources\audio\enemy_throw_barbs.mp3)", "enemy_throw_barbs");
	load_audio(R"(resources\audio\enemy_throw_silk.mp3)", "enemy_throw_silk");
	load_audio(R"(resources\audio\enemy_throw_sword.mp3)", "enemy_throw_sword");
	load_audio(R"(resources\audio\player_attack_1.mp3)", "player_attack_1");
	load_audio(R"(resources\audio\player_attack_2.mp3)", "player_attack_2");
	load_audio(R"(resources\audio\player_attack_3.mp3)", "player_attack_3");
	load_audio(R"(resources\audio\player_dead.mp3)", "player_dead");
	load_audio(R"(resources\audio\player_hurt.mp3)", "player_hurt");
	load_audio(R"(resources\audio\player_jump.mp3)", "player_jump");
	load_audio(R"(resources\audio\player_land.mp3)", "player_land");
	load_audio(R"(resources\audio\player_roll.mp3)", "player_roll");
	load_audio(R"(resources\audio\player_run.mp3)", "player_run");
}
Atlas* ResourcesManager::find_atlas(const std::string& id){
	const auto& itor = atlas_pool.find(id);
	if (itor == atlas_pool.end())return NULL;
	return itor->second;
}
IMAGE* ResourcesManager::find_image(const std::string& id){
	const auto& itor = image_pool.find(id);
	if (itor == image_pool.end())return NULL;
	return itor->second;
}
void ResourcesManager::flip_image(IMAGE* src_img, IMAGE* dst_img, int num_h ) {
	if (!src_img && !dst_img)return;
	int w = src_img->getwidth();
	int h = src_img->getheight();
	int w_frame = w / num_h;
	Resize(dst_img, w, h);//一定在下一步之前有，不然错
	DWORD* src_buffer = GetImageBuffer(src_img);
	DWORD* dst_buffer = GetImageBuffer(dst_img);//先分配空间，图片的大小，即宽高，不然就是空指针了，危险

	for (size_t i = 0; i < num_h; i++) {
		int x_left = i * w_frame;
		int x_right = (i + 1) * w_frame;
		for (int y = 0; y < h; y++) {
			//用了int x = x_left; x < x_right，那么就是x不是从0开始不用减1，对齐
			for (int x = x_left; x < x_right; x++) {
				int idx_src = y * w + x;
				int idx_dst = y * w + x_right - x + x_left;
				dst_buffer[idx_dst] = src_buffer[idx_src];
			}
		}
	}
}
void ResourcesManager:: flip_image(const std::string& src_id, const std::string& dst_id, int num_h ) {
	
	
	IMAGE* src_image = image_pool[src_id];
	if (src_image == NULL)return;
	IMAGE* dst_image = new IMAGE();
	flip_image(src_image, dst_image, num_h);
	image_pool[dst_id] = dst_image;


}
void ResourcesManager::flip_atlas(const std::string& src_id, const std::string& dst_id) {
	Atlas* src_atlas = atlas_pool[src_id];
	if (src_atlas == NULL)return;
	Atlas* dst_atlas = new Atlas();
	for (int i = 0; i < src_atlas->get_size(); i++) {
		IMAGE* image=new IMAGE();
		flip_image(src_atlas->get_image(i),image);
		dst_atlas->add_image(image);
	}
	atlas_pool[dst_id] = dst_atlas;

}