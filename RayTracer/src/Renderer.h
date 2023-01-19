#pragma once

#include <stdint.h>
#include <vector>

#include "vendor/glm/ext/vector_int3.hpp"

class Renderer {
public:
	Renderer();
	~Renderer();

	void Render(int32_t imageWidth, int32_t imageHeight, std::vector<glm::ivec3> imageData);

};