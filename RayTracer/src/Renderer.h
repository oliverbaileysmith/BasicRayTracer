#pragma once

#include <stdint.h>
#include <vector>

#include "vendor/glm/ext/vector_double3.hpp"

enum class OutputFormat {
	PPM,
	JPEG,
	BMP
};

class Renderer {
public:
	Renderer(int32_t imageWidth, int32_t imageHeight);
	~Renderer();

	void RenderPixel(glm::dvec3 pixelColour, int32_t samplesPerPixel);
	void WriteOutput(int32_t imageWidth, int32_t imageHeight, OutputFormat outputFormat) const;

private:
	std::vector<unsigned char> m_ImageData;
};