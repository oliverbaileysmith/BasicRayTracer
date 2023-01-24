#include "Camera.h"

Camera::Camera() {
	float aspectRatio = 16.0f / 9.0f;
	float viewportHeight = 2.0f;
	float viewportWidth = aspectRatio * viewportHeight;
	float focalLength = 1.0f;

	m_Origin = glm::vec3(0.0f, 0.0f, 0.0f);
	m_ViewportHorizontal = glm::vec3(viewportWidth, 0.0f, 0.0f);
	m_ViewportVertical = glm::vec3(0.0f, viewportHeight, 0.0f);
	m_ViewportLowerLeftCorner = m_Origin - m_ViewportHorizontal / 2.0f - m_ViewportVertical / 2.0f - glm::vec3(0.0f, 0.0f, focalLength);
}

Camera::~Camera() {}

Ray Camera::getRay(float pixelX, float pixelY) const {
	return Ray(m_Origin, m_ViewportLowerLeftCorner + pixelX * m_ViewportHorizontal + pixelY * m_ViewportVertical - m_Origin);
}