#include "Util.h"
#include "Ray.h"

#include "vendor/glm/ext/vector_float3.hpp"

class Camera {
public:
	Camera();
	~Camera();

	Ray getRay(float pixelX, float pixelY) const;

private:
	glm::vec3 m_Origin;
	glm::vec3 m_ViewportHorizontal;
	glm::vec3 m_ViewportVertical;
	glm::vec3 m_ViewportLowerLeftCorner;
};