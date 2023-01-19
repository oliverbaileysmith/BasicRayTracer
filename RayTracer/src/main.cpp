#include <vector>

#include "vendor/glm/ext/vector_float3.hpp"
#include "vendor/glm/ext/vector_int3.hpp"

#include "Renderer.h"

void main() {

	// Image details

	const int32_t IMAGE_WIDTH = 256;
	const int32_t IMAGE_HEIGHT = 256;

	// Create image data

	std::vector<glm::ivec3> imageData;
	imageData.reserve(IMAGE_WIDTH * IMAGE_HEIGHT);

	for (int32_t y = IMAGE_HEIGHT - 1; y >= 0; y--) {

		for (int32_t x = 0; x < IMAGE_WIDTH; x++) {

			glm::vec3 floatColour;

			floatColour.r = (float)x / (float)(IMAGE_WIDTH - 1);
			floatColour.g = (float)y / (float)(IMAGE_HEIGHT - 1);
			floatColour.b = 0.25;

			glm::ivec3 integerColour;

			integerColour = (glm::ivec3)(floatColour * 255.999f);

			imageData.emplace_back(integerColour);
		}
	}

	// Render

	Renderer renderer;

	renderer.Render(IMAGE_WIDTH, IMAGE_HEIGHT, imageData);

}