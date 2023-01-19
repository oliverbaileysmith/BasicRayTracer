#pragma once

#include <stdint.h>

class Renderer {
public:
	Renderer();
	~Renderer();

	void Render(int32_t imageWidth, int32_t imageHeight);

};