#include "Util.h"

#include <iostream>

class Texture {
public:
	virtual glm::dvec3 value(double u, double v, const glm::dvec3 &p) const = 0;
};

class SolidColour : public Texture {
public:
	SolidColour();
	SolidColour(glm::dvec3 colour);
	SolidColour(double red, double green, double blue);

	virtual glm::dvec3 value(double u, double v, const glm::dvec3 &p) const override;

private:
	glm::dvec3 m_ColourValue;
};

class CheckerTexture : public Texture {
public:
	CheckerTexture();
	CheckerTexture(std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd);
	CheckerTexture(glm::dvec3 colour1, glm::dvec3 colour2);

	virtual glm::dvec3 value(double u, double v, const glm::dvec3 &p) const override;

	std::shared_ptr<Texture> m_Odd;
	std::shared_ptr<Texture> m_Even;
};

class ImageTexture : public Texture {
public:
	ImageTexture();
	ImageTexture(const char *filename);
	~ImageTexture();

	virtual glm::dvec3 value(double u, double v, const glm::dvec3 &p) const override;
	
	const static int m_BytesPerPixel = 3;

private:
	unsigned char *m_Data;
	int m_Width, m_Height;
	int m_BytesPerScanline;
};