#include "Rotate.h"

RotateY::RotateY(std::shared_ptr<HittableObject> obj, double angle)
	: m_Obj(obj) {
	double radians = degreesToRadians(angle);
	m_SinTheta = std::sin(radians);
	m_CosTheta = std::cos(radians);
	m_HasAABB = m_Obj->buildAABB(0, 1, m_AABB);

	glm::dvec3 min( INFINITY,  INFINITY,  INFINITY);
	glm::dvec3 max(-INFINITY, -INFINITY, -INFINITY);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				double x = i * m_AABB.m_Maximum.x + (1 - i) * m_AABB.m_Minimum.x;
				double y = j * m_AABB.m_Maximum.y + (1 - j) * m_AABB.m_Minimum.y;
				double z = k * m_AABB.m_Maximum.z + (1 - k) * m_AABB.m_Minimum.z;

				double newX =  m_CosTheta * x + m_SinTheta * z;
				double newZ = -m_SinTheta * x + m_CosTheta * z;

				glm::dvec3 tester(newX, y, newZ);

				for (int c = 0; c < 3; c++) {
					min[c] = std::fmin(min[c], tester[c]);
					max[c] = std::fmax(max[c], tester[c]);
				}
			}
		}
	}

	m_AABB = AABB(min, max);
}

bool RotateY::Hit(const Ray &ray, double tMin, double tMax, HitRecord &hitRecord) const {
	glm::dvec3 origin = ray.GetOrigin();
	glm::dvec3 direction = ray.GetDirection();

	origin[0] = m_CosTheta * ray.GetOrigin()[0] - m_SinTheta * ray.GetOrigin()[2];
	origin[2] = m_SinTheta * ray.GetOrigin()[0] + m_CosTheta * ray.GetOrigin()[2];

	direction[0] = m_CosTheta * ray.GetDirection()[0] - m_SinTheta * ray.GetDirection()[2];
	direction[2] = m_SinTheta * ray.GetDirection()[0] + m_CosTheta * ray.GetDirection()[2];

	Ray rotatedRay(origin, direction, ray.GetTime());

	if(!m_Obj->Hit(rotatedRay, tMin, tMax, hitRecord))
		return false;

	glm::dvec3 p = hitRecord.m_HitPoint;
	glm::dvec3 normal = hitRecord.m_Normal;

	p[0] =  m_CosTheta * hitRecord.m_HitPoint[0] + m_SinTheta * hitRecord.m_HitPoint[2];
	p[2] = -m_SinTheta * hitRecord.m_HitPoint[0] + m_CosTheta * hitRecord.m_HitPoint[2];

	normal[0] =  m_CosTheta * hitRecord.m_Normal[0] + m_SinTheta * hitRecord.m_Normal[2];
	normal[2] = -m_SinTheta * hitRecord.m_Normal[0] + m_CosTheta * hitRecord.m_Normal[2];

	hitRecord.m_HitPoint = p;
	hitRecord.m_SetFaceNormal(rotatedRay, normal);

	return true;
}

bool RotateY::buildAABB(double time0, double time1, AABB &outputAABB) const {
	outputAABB = m_AABB;
	return m_HasAABB;
}