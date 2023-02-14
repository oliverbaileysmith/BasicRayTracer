#pragma once

#include "HittableObjectList.h"
#include "Camera.h"

class Scene {
public:
	Scene();
	void Construct1();
	void Construct2();
	void Construct3();

public:
	HittableObjectList m_HittableObjectList;
	Camera m_Camera;
	glm::dvec3 m_BackgroundColour;
};