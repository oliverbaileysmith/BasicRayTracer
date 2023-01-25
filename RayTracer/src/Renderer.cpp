#include "Renderer.h"
#include "Util.h"

#include <fstream>

#include "vendor/glm/ext/vector_double3.hpp"

Renderer::Renderer(int32_t imageWidth, int32_t imageHeight) {
	m_ImageData.reserve(imageWidth * imageHeight);
}

Renderer::~Renderer() {}

void Renderer::RenderPixel(glm::dvec3 pixelColour, int32_t samplesPerPixel){
	double r = pixelColour.r;
	double g = pixelColour.g;
	double b = pixelColour.b;

	// Divide the colour by the number of samples.
	double scale = 1.0 / (double)samplesPerPixel;
	r *= scale;
	g *= scale;
	b *= scale;

	// Output the translated [0,255] value of each colour component.
	pixelColour.r = (int)(256 * clamp(r, 0.0, 0.999));
	pixelColour.g = (int)(256 * clamp(g, 0.0, 0.999));
	pixelColour.b = (int)(256 * clamp(b, 0.0, 0.999));

	m_ImageData.emplace_back(pixelColour);
}

void Renderer::WriteOutput(int32_t imageWidth, int32_t imageHeight) const {

	std::ofstream outputFile;
	outputFile.open("output.ppm");

	outputFile << "P3" << std::endl;
	outputFile << imageWidth << ' ' << imageHeight << std::endl;
	outputFile << "255" << std::endl;

	for (int32_t y = imageHeight - 1; y >= 0; y--) {

		for (int32_t x = 0; x < imageWidth; x++) {

			outputFile << m_ImageData[(imageHeight - y - 1) * imageWidth + x].r
				<< ' ' << m_ImageData[(imageHeight - y - 1) * imageWidth + x].g
				<< ' ' << m_ImageData[(imageHeight - y - 1) * imageWidth + x].b
				<< std::endl;
		}
	}

	outputFile.close();
}