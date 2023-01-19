#include "Renderer.h"

#include <iostream>
#include <fstream>

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
			float r = (float)x / (float)(imageWidth - 1);
			float g = (float)y / (float)(imageHeight - 1);
			float b = 0.25;

			int32_t ir = (int32_t)(255.999 * r);
			int32_t ig = (int32_t)(255.999 * g);
			int32_t ib = (int32_t)(255.999 * b);

			outputFile << ir << ' ' << ig << ' ' << ib << std::endl;
		}
	}

	outputFile.close();
}