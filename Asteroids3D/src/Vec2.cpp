#include "Vec2.h"

Vec2::Vec2(float _x, float _y)
	:x(_x),
	y(_y) {}

Vec2 Vec2::operator+(Vec2 &rhs) {
	Vec2 ans(x + rhs.x, y + rhs.y);
	return ans;
}
Vec2& Vec2::operator+=(Vec2 &rhs) {
	x += rhs.x;
	y += rhs.y;
	return *this;
}
Vec2 Vec2::operator-(Vec2 &rhs) {
	Vec2 ans(x - rhs.x, y - rhs.y);
	return ans;
}
Vec2& Vec2::operator-=(Vec2 &rhs) {
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}
Vec2 Vec2::operator*(float rhs) {
	Vec2 ans(x*rhs, y*rhs);
	return ans;
}
float Vec2::length() {
	return sqrt(x*x + y * y);
}
Vec2 Vec2::normalized() {
	float len = length();
	Vec2 ans(x /= len, y /= len);
	return ans;
}
Vec2 Vec2::difference(Vec2 &v) {
	return Vec2(x - v.x, y - v.y);
}
float Vec2::distance(Vec2 &v) {
	Vec2 dif(x - v.x, y - v.y);
	return dif.length();
}



std::ostream & operator<<(std::ostream& os, Vec2& v) {
	os << "[" << v.x << ", " << v.y << "]";
	return os;
}
