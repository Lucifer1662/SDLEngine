#pragma once
struct vec3ui {
	size_t x;
	size_t y;
	size_t z;
	inline vec3ui(size_t x = 0, size_t y =0 , size_t z = 0) : x(x), y(y), z(z) {
	}
};