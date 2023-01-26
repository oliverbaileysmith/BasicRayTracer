#include "Util.h"
#include "Ray.h"

#include "vendor/glm/ext/vector_double3.hpp"

class Camera {
public:
	Camera(glm::dvec3 position, glm::dvec3 lookAt, glm::dvec3 up, double verticalFOV, double aspectRatio, double aperture, double focusDistance);
	~Camera();

	Ray getRay(double pixelX, double pixelY) const;

private:
	glm::dvec3 m_Origin;
	glm::dvec3 m_ViewportHorizontal;
	glm::dvec3 m_ViewportVertical;
	glm::dvec3 m_ViewportLowerLeftCorner;
	glm::dvec3 m_U, m_V, m_W;
	double m_LensRadius;
};