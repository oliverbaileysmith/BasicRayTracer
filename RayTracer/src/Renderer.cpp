#include "Renderer.h"

#include <fstream>

#include "vendor/glm/ext/vector_float3.hpp"
#include "vendor/glm/ext/vector_int3.hpp"

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::Render(int32_t imageWidth, int32_t imageHeight, std::vector<glm::ivec3> imageData) {

	std::ofstream outputFile;
	outputFile.open("output.ppm");

	outputFile << "P3" << std::endl;
	outputFile << imageWidth << ' ' << imageHeight << std::endl;
	outputFile << "255" << std::endl;

	for (int32_t y = imageHeight - 1; y >= 0; y--) {

		for (int32_t x = 0; x < imageWidth; x++) {

			outputFile << imageData[(imageHeight - y - 1) * imageWidth + x].r
				<< ' ' << imageData[(imageHeight - y - 1) * imageWidth + x].g
				<< ' ' << imageData[(imageHeight - y - 1) * imageWidth + x].b
				<< std::endl;
		}
	}

	outputFile.close();
}