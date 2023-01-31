#pragma once

#include "MovingSphere.h"
#include "AABB.h"

MovingSphere::MovingSphere() {}

MovingSphere::MovingSphere(glm::dvec3 center0, glm::dvec3 center1, double time0, double time1, double radius, std::shared_ptr<Material> material)
	: m_Center0(center0),
	m_Center1(center1),
	m_Time0(time0),
	m_Time1(time1),
	m_Radius(radius),
	m_Material(material)
{}

MovingSphere::~MovingSphere() {}

bool MovingSphere::Hit(const Ray &ray, double tMin, double tMax, HitRecord &hitRecord) const {
    glm::dvec3 rayOriginToSphereCenter = ray.GetOrigin() - getCenter(ray.GetTime());
    double a = glm::length2(ray.GetDirection());
    double halfB = glm::dot(rayOriginToSphereCenter, ray.GetDirection());
    double c = glm::length2(rayOriginToSphereCenter) - m_Radius * m_Radius;

    double discriminant = halfB * halfB - a * c;
    if (discriminant < 0.0)
        return false;
    double sqrtDiscriminant = sqrt(discriminant);

    double root = (-halfB - sqrtDiscriminant) / a;
    if (root < tMin || root > tMax) {
        root = (-halfB + sqrtDiscriminant) / a;
        if (root < tMin || root > tMax)
            return false;
    }

    hitRecord.m_T = root;
    hitRecord.m_HitPoint = ray.GetPositionAtDistance(hitRecord.m_T);
    glm::dvec3 outwardNormal = (hitRecord.m_HitPoint - getCenter(ray.GetTime())) / m_Radius;
    hitRecord.m_SetFaceNormal(ray, outwardNormal);
    hitRecord.m_MaterialPtr = m_Material;

    return true;
}

bool MovingSphere::buildAABB(double time0, double time1, AABB &outputAABB) const {
    AABB box0(
        getCenter(time0) - glm::dvec3(m_Radius),
        getCenter(time0) + glm::dvec3(m_Radius)
    );

    AABB box1(
        getCenter(time1) - glm::dvec3(m_Radius),
        getCenter(time1) + glm::dvec3(m_Radius)
    );

    outputAABB = buildSurroundingAABB(box0, box1);
    return true;
}

glm::dvec3 MovingSphere::getCenter(double time) const {
	return m_Center0 + ((time - m_Time0) / (m_Time1 - m_Time0)) * (m_Center1 - m_Center0);
}