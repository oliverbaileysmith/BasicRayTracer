#include "Camera.h"

#include "vendor/glm/gtx/norm.hpp"

Camera::Camera(glm::dvec3 position, glm::dvec3 lookAt, glm::dvec3 up, double verticalFOV, double aspectRatio) {

	double theta = degreesToRadians(verticalFOV);
	double h = std::tan(theta / 2);
	double viewportHeight = 2.0 * h;
	double viewportWidth = aspectRatio * viewportHeight;

	glm::dvec3 w = glm::normalize(position - lookAt);
	glm::dvec3 u = glm::normalize(glm::cross(up, w));
	glm::dvec3 v = glm::cross(w, u);

	m_Origin = position;
	m_ViewportHorizontal = viewportWidth * u;
	m_ViewportVertical = viewportHeight * v;
	m_ViewportLowerLeftCorner = m_Origin - m_ViewportHorizontal / 2.0 - m_ViewportVertical / 2.0 - w;
}

Camera::~Camera() {}

Ray Camera::getRay(double pixelX, double pixelY) const {
	return Ray(m_Origin, m_ViewportLowerLeftCorner + pixelX * m_ViewportHorizontal + pixelY * m_ViewportVertical - m_Origin);
}