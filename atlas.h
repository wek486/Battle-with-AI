#ifndef ATLAS_H
#define ATLAS_H
#include <vector>
#include <graphics.h>
#include <iostream>
#include <string>
class Atlas {
public:
	Atlas() = default;
	~Atlas() = default;
	void clear() {
		if (image_list.empty())return;
		for (IMAGE* img : image_list) {
			delete img;
	}
		image_list.clear();
	}
	void add_image(IMAGE* img) {
		image_list.push_back(img);
	}
	void load_image(std::string path, int num) {
		image_list.clear();
		
		for (size_t i = 0; i < num; i++) {
			char full_path[256];
			sprintf_s(full_path, path.c_str(), i + 1);
			IMAGE* img = new IMAGE();
			loadimage(img, full_path);
			image_list.push_back(img);
		}

	}
	int get_size() {
		if (image_list.empty())return 0;
		return image_list.size();
	}
	IMAGE* get_image(int idx) {
		if (idx < 0 || idx >= image_list.size())return NULL;
		return image_list[idx];
	}
	friend class Animation;
private:

	std::vector<IMAGE*>image_list;//这里用指针也有要防止空指针


};

#endif
