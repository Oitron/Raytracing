#pragma once

#include <iostream>


class Vector3 {

private:
	float x;
	float y;
	float z;

public:
	//ctor
	Vector3() { x = 0.0; y = 0.0; z = 0.0; }
	Vector3(float x_, float y_, float z_) { x = x_; y = y_; z = z_; }

	float getX() const { return x; }
	float getY() const { return y; }
	float getZ() const { return z; }

	float setX(float x_) { x = x_; }
	float setY(float y_) { y = y_; }
	float setZ(float z_) { z = z_; }

	float length() const { return sqrt(x * x + y * y + z * z); }


	Vector3 operator+(const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
	Vector3 operator-(const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
	Vector3 operator*(const Vector3& v) const { return Vector3(x * v.x, y * v.y, z * v.z); }
	Vector3 operator*(const float l) const { return Vector3(x * l, y * l, z * l); }
	Vector3 operator/(const float l) const {
		float inv = 1 / l;
		return Vector3(x * inv, y * inv, z * inv);
	}

	Vector3 normalize() const {
		float inv = 1 / length();
		return Vector3(x * inv, y * inv, z * inv);
	}

	float scalar(const Vector3& v) const {
		return x * v.x + y * v.y + z * v.z;
	}
	Vector3 cross(const Vector3& v) const {
		return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
	
	friend std::ostream& operator<<(std::ostream& out, Vector3& vect) {
		out << "[" << vect.x << ", " << vect.y << ", " << vect.z << "]";
		return out;
	}
};