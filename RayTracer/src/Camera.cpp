#include "Camera.h"

#include "vendor/glm/gtx/norm.hpp"

Camera::Camera(glm::dvec3 position, glm::dvec3 lookAt, glm::dvec3 up, double verticalFOV, double aspectRatio, double aperture, double focusDistance) {

	double theta = degreesToRadians(verticalFOV);
	double h = std::tan(theta / 2);
	double viewportHeight = 2.0 * h;
	double viewportWidth = aspectRatio * viewportHeight;

	m_W = glm::normalize(position - lookAt);
	m_U = glm::normalize(glm::cross(up, m_W));
	m_V = glm::cross(m_W, m_U);

	m_Origin = position;
	m_ViewportHorizontal = focusDistance * viewportWidth * m_U;
	m_ViewportVertical = focusDistance * viewportHeight * m_V;
	m_ViewportLowerLeftCorner = m_Origin - m_ViewportHorizontal / 2.0 - m_ViewportVertical / 2.0 - focusDistance * m_W;

	m_LensRadius = aperture / 2.0;
}

Camera::~Camera() {}

Ray Camera::getRay(double pixelX, double pixelY) const {
	glm::dvec3 rd = m_LensRadius * randomInUnitDisk();
	glm::dvec3 offset = m_U * rd.x + m_V * rd.y;

	return Ray(
		m_Origin + offset,
		m_ViewportLowerLeftCorner + pixelX * m_ViewportHorizontal + pixelY * m_ViewportVertical - m_Origin - offset
	);
}