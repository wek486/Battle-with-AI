#ifndef VECTOR2_H
#define VECTOR2_H
#include <cmath>
class Vector2 {
public:
	Vector2() = default;
	Vector2(float x,float y): x(x),y(y){}
	~Vector2() = default;
	float x=0.0;
	float y=0.0;
	void set_position(float new_x, float new_y) {
		x = new_x;
		y = new_y;
	}
	Vector2& get_position() {
		return *this;
	}
	Vector2 operator+(const Vector2& vec)const {
		return Vector2(x + vec.x, y + vec.y);
	}
	Vector2 operator-(const Vector2& vec)const {
		return Vector2(x - vec.x, y - vec.y);
	}
	void operator+=(const Vector2& vec) {
		x += vec.x; y += vec.y;
	}
	void operator-=(const Vector2& vec) {
		x -= vec.x; y -= vec.y;
	}
	Vector2 operator-(const Vector2& vec) {
		return Vector2(x - vec.x, y - vec.y);
	}
	float operator*(const Vector2& vec)const {
		 return x * vec.x+ y * vec.y;
	}
	Vector2 operator*(float val)const{
		return Vector2(x * val, y * val);
	}
	
	float length() {
		return sqrt(x*x+y*y);
	}
	void operator*=(float val) {
		x *= val; y *= val;
	}
	Vector2 normalize() {
		float len = length();
		if (len == 0)return Vector2(0, 0);
		return Vector2(x / len, y / len);
	}
private:



};




#endif
