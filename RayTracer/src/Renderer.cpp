#include "Renderer.h"
#include "Util.h"
#include"vendor/stb/stb_image_write.h"

#include <fstream>
#include <sstream>
#include <iomanip>
#include <time.h>

#include "vendor/glm/ext/vector_double3.hpp"

Renderer::Renderer(int32_t imageWidth, int32_t imageHeight) {
	m_ImageData.reserve(imageWidth * imageHeight);
}

Renderer::~Renderer() {}

void Renderer::RenderPixel(glm::dvec3 pixelColour, int32_t samplesPerPixel){
	double r = pixelColour.r;
	double g = pixelColour.g;
	double b = pixelColour.b;

	// Divide the colour by the number of samples. Correct for gamma = 2.0 (sqrt).
	double scale = 1.0 / (double)samplesPerPixel;
	r = std::sqrt(scale * r);
	g = std::sqrt(scale * g);
	b = std::sqrt(scale * b);

	// Output the translated [0,255] value of each colour component.
	m_ImageData.emplace_back((unsigned char)(256 * clamp(r, 0.0, 0.999)));
	m_ImageData.emplace_back((unsigned char)(256 * clamp(g, 0.0, 0.999)));
	m_ImageData.emplace_back((unsigned char)(256 * clamp(b, 0.0, 0.999)));
}

void Renderer::WriteOutput(int32_t imageWidth, int32_t imageHeight, OutputFormat outputFormat) const {
	std::ofstream outputFile;
	
	time_t rawTime = std::time(nullptr);
	struct tm timeInfo = *std::localtime(&rawTime);

	std::ostringstream oss;
	oss << std::put_time(&timeInfo, "%Y-%m-%d_%H-%M-%S");
	std::string timeString = oss.str();

	switch (outputFormat) {
		case OutputFormat::PPM:
			
			outputFile.open(timeString + std::string(".ppm").c_str());

			outputFile << "P3" << std::endl;
			outputFile << imageWidth << ' ' << imageHeight << std::endl;
			outputFile << "255" << std::endl;

			for (int32_t y = imageHeight - 1; y >= 0; y--) {

				for (int32_t x = 0; x < imageWidth; x++) {
					outputFile
						<< (unsigned int)m_ImageData[(imageHeight - y - 1) * 3 * imageWidth + 3 * x] << ' '
						<< (unsigned int)m_ImageData[(imageHeight - y - 1) * 3 * imageWidth + 3 * x + 1] << ' '
						<< (unsigned int)m_ImageData[(imageHeight - y - 1) * 3 * imageWidth + 3 * x + 2] << std::endl;
				}
			}

			
			break;

		case OutputFormat::JPEG:
			stbi_write_jpg((timeString + std::string(".jpeg")).c_str(), imageWidth, imageHeight, 3, m_ImageData.data(), 100);
			break;

		case OutputFormat::BMP:
			stbi_write_bmp((timeString + std::string(".bmp")).c_str(), imageWidth, imageHeight, 3, m_ImageData.data());
			break;
	}
	outputFile.close();
}