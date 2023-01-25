#pragma once

#include "Sphere.h"

#include "vendor/glm/gtx/norm.hpp"

Sphere::Sphere(glm::dvec3 center, double radius, std::shared_ptr<Material> material)
	: m_Center(center), m_Radius(radius), m_Material(material)
{}

bool Sphere::Hit(const Ray &ray, double tMin, double tMax, HitRecord &hitRecord) const {

    glm::dvec3 rayOriginToSphereCenter = ray.GetOrigin() - m_Center;
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
    glm::dvec3 outwardNormal = (hitRecord.m_HitPoint - m_Center) / m_Radius;
    hitRecord.m_SetFaceNormal(ray, outwardNormal);
    hitRecord.m_MaterialPtr = m_Material;

    return true;

}