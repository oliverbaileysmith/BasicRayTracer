#pragma once

#include "HittableObjectList.h"
#include "Camera.h"

class Scene {
public:
	Scene();
	void Construct1();

public:
	HittableObjectList m_HittableObjectList;
	Camera m_Camera;
};