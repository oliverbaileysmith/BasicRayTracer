#pragma once

#include "Util.h"
#include "HittableObject.h"

class XYRect : public HittableObject {
public:
	XYRect();
	XYRect(double x0, double x1, double y0, double y1, double k, std::shared_ptr<Material> mat);

	virtual bool Hit(const Ray &ray, double tMin, double tMax, HitRecord &hitRecord) const override;

	virtual bool buildAABB(double time0, double time1, AABB &outputAABB) const override;

public:
	std::shared_ptr<Material> m_MaterialPtr;
	double m_X0, m_X1, m_Y0, m_Y1, m_K;
};

class XZRect : public HittableObject {
public:
	XZRect();
	XZRect(double x0, double x1, double z0, double z1, double k, std::shared_ptr<Material> mat);

	virtual bool Hit(const Ray &ray, double tMin, double tMax, HitRecord &hitRecord) const override;

	virtual bool buildAABB(double time0, double time1, AABB &outputAABB) const override;

public:
	std::shared_ptr<Material> m_MaterialPtr;
	double m_X0, m_X1, m_Z0, m_Z1, m_K;
};

class YZRect : public HittableObject {
public:
	YZRect();
	YZRect(double y0, double y1, double z0, double z1, double k, std::shared_ptr<Material> mat);

	virtual bool Hit(const Ray &ray, double tMin, double tMax, HitRecord &hitRecord) const override;

	virtual bool buildAABB(double time0, double time1, AABB &outputAABB) const override;

public:
	std::shared_ptr<Material> m_MaterialPtr;
	double m_Y0, m_Y1, m_Z0, m_Z1, m_K;
};