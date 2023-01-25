#pragma once

#include "Material.h"

Lambertian::Lambertian(const glm::dvec3 &albedo) : m_Albedo(albedo) {}

bool Lambertian::Scatter(const Ray &rayIncident, const HitRecord &hitRecord, glm::dvec3 &attenuation, Ray &rayScattered) const {
	glm::dvec3 scatterDirection = hitRecord.m_Normal + randomUnitVector();

	// Catch scatter direction close to zero
	if (nearZero(scatterDirection))
		scatterDirection = hitRecord.m_Normal;

	rayScattered = Ray(hitRecord.m_HitPoint, scatterDirection);
	attenuation = m_Albedo;
	return true;
}