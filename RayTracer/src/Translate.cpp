#include "Translate.h"

Translate::Translate(std::shared_ptr<HittableObject> obj, const glm::dvec3 &offset)
	: m_Obj(obj), m_Offset(offset)
{}

bool Translate::Hit(const Ray &ray, double tMin, double tMax, HitRecord &hitRecord) const {
	Ray movedRay(ray.GetOrigin() - m_Offset, ray.GetDirection(), ray.GetTime());

	if (!m_Obj->Hit(movedRay, tMin, tMax, hitRecord))
		return false;

	hitRecord.m_HitPoint += m_Offset;
	hitRecord.m_SetFaceNormal(movedRay, hitRecord.m_Normal);

	return true;
}

bool Translate::buildAABB(double time0, double time1, AABB &outputAABB) const {
	if (!m_Obj->buildAABB(time0, time1, outputAABB))
		return false;

	outputAABB = AABB(
		outputAABB.m_Minimum + m_Offset,
		outputAABB.m_Maximum + m_Offset
	);

	return true;
}