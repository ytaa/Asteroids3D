#pragma once
#include <cmath>
#include <iostream>
#include "rng.h"
#define VEC3_SQRT2 1.41421356237f
#define VEC3_PI 3.14159265359f
#define	VEC3_EPS 0.0001f
class Vec3 {
public:
	float x;
	float y;
	float z;

	Vec3(float=0.f, float=0.f, float=0.f);

	Vec3 operator+(Vec3&);
	Vec3& operator+=(Vec3&);
	Vec3 operator-(Vec3&);
	Vec3& operator-=(Vec3&);
	Vec3& operator*=(Vec3 &);
	Vec3& operator/=(Vec3 &);
	Vec3 operator+(float);
	Vec3 operator*(float);
	bool operator==(Vec3 &);
	Vec3 cross(Vec3&);
	float dot(Vec3&);
	float length();
	Vec3 normalized();
	Vec3& limit(Vec3&);
	Vec3 difference(Vec3&);
	float distance(Vec3&);
	float angle(Vec3&);
	

	static Vec3 random(float, float);

	friend std::ostream & operator<<(std::ostream&, Vec3&);
};