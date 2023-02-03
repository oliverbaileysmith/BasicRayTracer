#include "Texture.h"
#include "RT_STB_Image.h"

SolidColour::SolidColour() {}

SolidColour::SolidColour(glm::dvec3 colour) : m_ColourValue(colour) {}

SolidColour::SolidColour(double red, double green, double blue)
	: SolidColour(glm::dvec3(red, green, blue))
{}

glm::dvec3 SolidColour::value(double u, double v, const glm::dvec3 &p) const {
	return m_ColourValue;
}

CheckerTexture::CheckerTexture() {}

CheckerTexture::CheckerTexture(std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd)
	: m_Even(even), m_Odd(odd)
{}

CheckerTexture::CheckerTexture(glm::dvec3 colour1, glm::dvec3 colour2)
	: m_Even(std::make_shared<SolidColour>(colour1)), m_Odd(std::make_shared<SolidColour>(colour2))
{}

glm::dvec3 CheckerTexture::value(double u, double v, const glm::dvec3 &p) const {
	double sines = std::sin(10.0 * p.x) * std::sin(10.0 * p.y) * std::sin(10.0 * p.z);
	if (sines < 0)
		return m_Odd->value(u, v, p);
	else
		return m_Even->value(u, v, p);
}

ImageTexture::ImageTexture()
	: m_Data(nullptr), m_Width(0), m_Height(0), m_BytesPerScanline(0)
{}

ImageTexture::ImageTexture(const char *filename) {
	int componentsPerPixel = m_BytesPerPixel;

	m_Data = stbi_load(filename, &m_Width, &m_Height, &componentsPerPixel, componentsPerPixel);

	if (!m_Data) {
		std::cerr << "ERROR: Could not load image texture file '" << filename << "'." << std::endl;
		m_Width = m_Height = 0;
	}

	m_BytesPerScanline = m_BytesPerPixel * m_Width;
}

ImageTexture::~ImageTexture() {
	delete m_Data;
}

glm::dvec3 ImageTexture::value(double u, double v, const glm::dvec3 &p) const {
	// If no texture data, return magenta for debugging purposes
	if (m_Data == nullptr)
		return glm::dvec3(1.0, 0.0, 1.0);

	// Clamp texture coordinates to 0 to 1 range
	u = clamp(u, 0.0, 1.0);
	v = 1.0 - clamp(v, 0.0, 1.0); // Flip v

	int i = (int)(u * m_Width);
	int j = (int)(v * m_Height);

	// Clamp integer mapping
	if (i >= m_Width)
		i = m_Width - 1;
	if (j >= m_Height)
		j = m_Height - 1;

	const double colourScale = 1.0 / 255.0;
	auto pixel = m_Data + j * m_BytesPerScanline + i * m_BytesPerPixel;

	return glm::dvec3(colourScale * pixel[0], colourScale * pixel[1], colourScale * pixel[2]);
}