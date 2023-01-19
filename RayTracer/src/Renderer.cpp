#include "Renderer.h"

#include <iostream>
#include <fstream>

#include "vendor/glm/ext/vector_float3.hpp"
#include "vendor/glm/ext/vector_int3.hpp"

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::Render(int32_t imageWidth, int32_t imageHeight) {

	std::ofstream outputFile;
	outputFile.open("output.ppm");

	outputFile << "P3" << std::endl;
	outputFile << imageWidth << ' ' << imageHeight << std::endl;
	outputFile << "255" << std::endl;

	for (int32_t y = imageHeight - 1; y >= 0; y--) {

		// Progress indicator
		std::cout << "\rScanlines remaining: " << y << ' ' << std::flush;

		for (int32_t x = 0; x < imageWidth; x++) {

			glm::vec3 floatColour;

			floatColour.r = (float)x / (float)(imageWidth - 1);
			floatColour.g = (float)y / (float)(imageHeight - 1);
			floatColour.b = 0.25;

			glm::ivec3 integerColour;

			integerColour = (glm::ivec3)(floatColour * 255.999f);

			outputFile << integerColour.r << ' ' << integerColour.g << ' ' << integerColour.b << std::endl;
		}
	}

	outputFile.close();
}