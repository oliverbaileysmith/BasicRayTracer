#include "AARect.h"

XYRect::XYRect() {}

XYRect::XYRect(double x0, double x1, double y0, double y1, double k, std::shared_ptr<Material> mat)
	: m_X0(x0), m_X1(x1), m_Y0(y0), m_Y1(y1), m_K(k), m_MaterialPtr(mat)
{}

bool XYRect::Hit(const Ray &ray, double tMin, double tMax, HitRecord &hitRecord) const {
	double t = (m_K - ray.GetOrigin().z) / ray.GetDirection().z;

	if (t < tMin || t > tMax)
		return false;

	double x = ray.GetOrigin().x + t * ray.GetDirection().x;
	double y = ray.GetOrigin().y + t * ray.GetDirection().y;

	if (x < m_X0 || x > m_X1 || y < m_Y0 || y > m_Y1)
		return false;

	hitRecord.m_U = (x - m_X0) / (m_X1 - m_X0);
	hitRecord.m_V = (y - m_Y0) / (m_Y1 - m_Y0);
	hitRecord.m_T = t;

	glm::dvec3 outwardNormal = glm::dvec3(0.0, 0.0, 1.0);
	hitRecord.m_SetFaceNormal(ray, outwardNormal);
	hitRecord.m_MaterialPtr = m_MaterialPtr;
	hitRecord.m_HitPoint = ray.GetPositionAtDistance(t);
	return true;
}

bool XYRect::buildAABB(double time0, double time1, AABB &outputAABB) const {
	outputAABB = AABB(glm::dvec3(m_X0, m_Y0, m_K - 0.0001), glm::dvec3(m_X1, m_Y1, m_K + 0.0001));
	return true;
}

XZRect::XZRect() {}

XZRect::XZRect(double x0, double x1, double z0, double z1, double k, std::shared_ptr<Material> mat)
	: m_X0(x0), m_X1(x1), m_Z0(z0), m_Z1(z1), m_K(k), m_MaterialPtr(mat) {
}

bool XZRect::Hit(const Ray &ray, double tMin, double tMax, HitRecord &hitRecord) const {
	double t = (m_K - ray.GetOrigin().y) / ray.GetDirection().y;

	if (t < tMin || t > tMax)
		return false;

	double x = ray.GetOrigin().x + t * ray.GetDirection().x;
	double z = ray.GetOrigin().z + t * ray.GetDirection().z;

	if (x < m_X0 || x > m_X1 || z < m_Z0 || z > m_Z1)
		return false;

	hitRecord.m_U = (x - m_X0) / (m_X1 - m_X0);
	hitRecord.m_V = (z - m_Z0) / (m_Z1 - m_Z0);
	hitRecord.m_T = t;

	glm::dvec3 outwardNormal = glm::dvec3(0.0, 1.0, 0.0);
	hitRecord.m_SetFaceNormal(ray, outwardNormal);
	hitRecord.m_MaterialPtr = m_MaterialPtr;
	hitRecord.m_HitPoint = ray.GetPositionAtDistance(t);
	return true;
}

bool XZRect::buildAABB(double time0, double time1, AABB &outputAABB) const {
	outputAABB = AABB(glm::dvec3(m_X0, m_K - 0.0001, m_Z0), glm::dvec3(m_X1, m_K + 0.0001, m_Z1));
	return true;
}

YZRect::YZRect() {}

YZRect::YZRect(double y0, double y1, double z0, double z1, double k, std::shared_ptr<Material> mat)
	: m_Y0(y0), m_Y1(y1), m_Z0(z0), m_Z1(z1), m_K(k), m_MaterialPtr(mat) {
}

bool YZRect::Hit(const Ray &ray, double tMin, double tMax, HitRecord &hitRecord) const {
	double t = (m_K - ray.GetOrigin().x) / ray.GetDirection().x;

	if (t < tMin || t > tMax)
		return false;

	double y = ray.GetOrigin().y + t * ray.GetDirection().y;
	double z = ray.GetOrigin().z + t * ray.GetDirection().z;

	if (y < m_Y0 || y > m_Y1 || z < m_Z0 || z > m_Z1)
		return false;

	hitRecord.m_U = (y - m_Y0) / (m_Y1 - m_Y0);
	hitRecord.m_V = (z - m_Z0) / (m_Z1 - m_Z0);
	hitRecord.m_T = t;

	glm::dvec3 outwardNormal = glm::dvec3(1.0, 0.0, 0.0);
	hitRecord.m_SetFaceNormal(ray, outwardNormal);
	hitRecord.m_MaterialPtr = m_MaterialPtr;
	hitRecord.m_HitPoint = ray.GetPositionAtDistance(t);
	return true;
}

bool YZRect::buildAABB(double time0, double time1, AABB &outputAABB) const {
	outputAABB = AABB(glm::dvec3(m_K - 0.0001, m_Y0, m_Z0), glm::dvec3(m_K + 0.0001, m_Y1, m_Z1));
	return true;
}