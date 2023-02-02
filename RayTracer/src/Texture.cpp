#include "Texture.h"

SolidColour::SolidColour() {}

SolidColour::SolidColour(glm::dvec3 colour) : m_ColourValue(colour) {}

SolidColour::SolidColour(double red, double green, double blue)
	: SolidColour(glm::dvec3(red, green, blue))
{}

glm::dvec3 SolidColour::value(double u, double v, const glm::dvec3 &p) const {
	return m_ColourValue;
}