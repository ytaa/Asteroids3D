#pragma once
#include <cmath>
#include <iostream>
#define VEC2_SQRT2 1.41421356237
class Vec2 {
public:
	float x;
	float y;

	Vec2(float=0.f, float=0.f);

	Vec2 operator+(Vec2&);
	Vec2& operator+=(Vec2&);
	Vec2 operator-(Vec2&);
	Vec2& operator-=(Vec2&);
	Vec2 operator*(float);
	Vec2 cross(Vec2&);
	float length();
	Vec2 normalized();
	Vec2 difference(Vec2&);
	float distance(Vec2&);

	friend std::ostream & operator<<(std::ostream&, Vec2&);
};