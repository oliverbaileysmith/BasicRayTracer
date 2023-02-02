#include "Texture.h"

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