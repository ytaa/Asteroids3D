#include "Vec3.h"

Vec3::Vec3(float _x, float _y, float _z)
	:x(_x),
	y(_y),
	z(_z) {}

Vec3 Vec3::operator+(Vec3 &rhs) {
	Vec3 ans(x + rhs.x, y + rhs.y, z + rhs.z);
	return ans;
}
Vec3& Vec3::operator+=(Vec3 &rhs) {
	x += rhs.x;
	y += rhs.y; 
	z += rhs.z;
	return *this;
}
Vec3 Vec3::operator-(Vec3 &rhs) {
	Vec3 ans(x - rhs.x, y - rhs.y, z - rhs.z);
	return ans;
}
Vec3& Vec3::operator-=(Vec3 &rhs) {
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}
Vec3& Vec3::operator*=(Vec3 &rhs) {
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	return *this;
}
Vec3& Vec3::operator/=(Vec3 &rhs) {
	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;
	return *this;
}
Vec3 Vec3::operator+(float rhs) {
	Vec3 ans(x+rhs, y+rhs, z+rhs);
	return ans;
}
Vec3 Vec3::operator*(float rhs) {
	Vec3 ans(x*rhs, y*rhs, z*rhs);
	return ans;
}
bool Vec3::operator==(Vec3 &rhs) {
	return x == rhs.x && y == rhs.y && z == rhs.z;
}
Vec3 Vec3::cross(Vec3 &rhs) {
	Vec3 ans(y*rhs.z - z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y - y*rhs.x);
	return ans;
}
float Vec3::dot(Vec3 &rhs) {
	return x*rhs.x + y*rhs.y + z*rhs.z;
}
float Vec3::length() {
	return sqrt(x*x + y*y + z*z);
}
Vec3 Vec3::normalized() {
	float len = length()+VEC3_EPS;
	Vec3 ans(x / len, y / len, z / len);
	return ans;
}
Vec3& Vec3::limit(Vec3 &v) {
	if (fabs(x) > fabs(v.x))
		x = v.x;
	if (fabs(y) > fabs(v.y))
		y = v.y;
	if (fabs(z) > fabs(v.z))
		z = v.z;
	return *this;
}
Vec3 Vec3::difference(Vec3 &v) {
	return Vec3(x - v.x, y - v.y, z - v.z);
}
float Vec3::distance(Vec3 &v) {
	Vec3 dif(x - v.x, y - v.y, z - v.z);
	return dif.length();
}
Vec3 Vec3::random(float min, float max) {
	return Vec3(rng::rand(min,max), rng::rand(min, max), rng::rand(min, max));
}
float Vec3::angle(Vec3 &rhs) {
	return acos(dot(rhs) / (length()*rhs.length()))*180.f/VEC3_PI;
}


std::ostream & operator<<(std::ostream& os, Vec3& v) {
	os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
	return os;
}
