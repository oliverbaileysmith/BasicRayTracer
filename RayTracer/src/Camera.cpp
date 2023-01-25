#include "Camera.h"

Camera::Camera() {
	double aspectRatio = 16.0 / 9.0;
	double viewportHeight = 2.0;
	double viewportWidth = aspectRatio * viewportHeight;
	double focalLength = 1.0;

	m_Origin = glm::dvec3(0.0, 0.0, 0.0);
	m_ViewportHorizontal = glm::dvec3(viewportWidth, 0.0, 0.0);
	m_ViewportVertical = glm::dvec3(0.0, viewportHeight, 0.0);
	m_ViewportLowerLeftCorner = m_Origin - m_ViewportHorizontal / 2.0 - m_ViewportVertical / 2.0 - glm::dvec3(0.0, 0.0, focalLength);
}

Camera::~Camera() {}

Ray Camera::getRay(double pixelX, double pixelY) const {
	return Ray(m_Origin, m_ViewportLowerLeftCorner + pixelX * m_ViewportHorizontal + pixelY * m_ViewportVertical - m_Origin);
}