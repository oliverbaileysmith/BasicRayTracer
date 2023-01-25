#include "Util.h"
#include "Ray.h"

#include "vendor/glm/ext/vector_double3.hpp"

class Camera {
public:
	Camera();
	~Camera();

	Ray getRay(double pixelX, double pixelY) const;

private:
	glm::dvec3 m_Origin;
	glm::dvec3 m_ViewportHorizontal;
	glm::dvec3 m_ViewportVertical;
	glm::dvec3 m_ViewportLowerLeftCorner;
};