#include "Scene.h"
#include "Material.h"
#include "AARect.h"
#include "Box.h"
#include "Sphere.h"
#include "Rotate.h"
#include "Translate.h"
#include "BVH.h"
#include "MovingSphere.h"

Scene::Scene()
	:
	m_Camera(glm::dvec3(0.0,0.0,0.0),
	glm::dvec3(0.0, 0.0, -1.0),
	glm::dvec3(0.0,1.0,0.0),
	60.0,
	16.0/9.0,
	0.1,
	glm::length(glm::dvec3(0.0,0.0,0.0) - glm::dvec3(0.0,0.0,-1.0))),
	m_BackgroundColour(glm::dvec3(0.0))
{}

void Scene::Construct1() {
	m_BackgroundColour = glm::dvec3(0.725, 0.890, 0.953);

	HittableObjectList objects;

	std::shared_ptr<Material> green = std::make_shared<Lambertian>(glm::dvec3(0.20, 0.45, 0.10));
	std::shared_ptr<Material> blue = std::make_shared<Lambertian>(glm::dvec3(0.20, 0.10, 0.45));
	std::shared_ptr<Material> glass = std::make_shared<Dielectric>(1.5);
	std::shared_ptr<Material> metal = std::make_shared<Metal>(glm::dvec3(0.8, 0.6, 0.6), 0.2);

	objects.add(std::make_shared<Sphere>(glm::dvec3(0.0, -100.0, 0.0), 100.0, green));
	objects.add(std::make_shared<Sphere>(glm::dvec3(-1.0, 1.0, 0.0), 1.0, glass));
	objects.add(std::make_shared<Sphere>(glm::dvec3(-1.0, 1.0, 0.0), -0.9, glass));
	objects.add(std::make_shared<Sphere>(glm::dvec3(1.0, 1.0, -1.0), 1.0, blue));
	objects.add(std::make_shared<Sphere>(glm::dvec3(3.0, 1.0, -6.0), 1.0, metal));

	m_HittableObjectList = objects;

	glm::dvec3 cameraPosition(-5.0, 3.0, 5.0);
	glm::dvec3 lookAt(-1.0, 1.0, 0.0);
	glm::dvec3 up(0.0, 1.0, 0.0);
	double focusDistance = glm::length(cameraPosition - lookAt);
	double aperture = 0.2;
	double vFOV = 30.0;
	double imageAspectRatio = 16.0 / 9.0;

	Camera camera(cameraPosition, lookAt, up, vFOV, imageAspectRatio, aperture, focusDistance, 0.0, 1.0);

	m_Camera = camera;
}

void Scene::Construct2() {
	m_BackgroundColour = glm::dvec3(0.0);

	HittableObjectList objects;

	std::shared_ptr<Material> red = std::make_shared<Lambertian>(glm::dvec3(0.65, 0.05, 0.05));
	std::shared_ptr<Material> white = std::make_shared<Lambertian>(glm::dvec3(0.73, 0.73, 0.73));
	std::shared_ptr<Material> green = std::make_shared<Lambertian>(glm::dvec3(0.12, 0.45, 0.15));
	std::shared_ptr<Material> light = std::make_shared<DiffuseLight>(glm::dvec3(15.0, 15.0, 15.0));

	objects.add(std::make_shared<YZRect>(0.0, 555.0, 0.0, 555.0, 555.0, green));
	objects.add(std::make_shared<YZRect>(0.0, 555.0, 0.0, 555.0, 0.0, red));
	objects.add(std::make_shared<XZRect>(213.0, 343.0, 227.0, 332.0, 554.0, light));
	objects.add(std::make_shared<XZRect>(0.0, 555.0, 0.0, 555.0, 0.0, white));
	objects.add(std::make_shared<XZRect>(0.0, 555.0, 0.0, 555.0, 555.0, white));
	objects.add(std::make_shared<XYRect>(0.0, 555.0, 0.0, 555.0, 555.0, white));

	std::shared_ptr<HittableObject> box1 = std::make_shared<Box>(glm::dvec3(0.0, 0.0, 0.0), glm::dvec3(165.0, 330.0, 165.0), white);
	box1 = std::make_shared<RotateY>(box1, 15.0);
	box1 = std::make_shared<Translate>(box1, glm::dvec3(265.0, 0.0, 295.0));

	std::shared_ptr<HittableObject> box2 = std::make_shared<Box>(glm::dvec3(0.0, 0.0, 0.0), glm::dvec3(165.0, 165.0, 165.0), white);
	box2 = std::make_shared<RotateY>(box2, -18.0);
	box2 = std::make_shared<Translate>(box2, glm::dvec3(130.0, 0.0, 65.0));

	objects.add(box1);
	objects.add(box2);

	m_HittableObjectList = objects;

	glm::dvec3 cameraPosition(278.0, 278.0, -800.0);
	glm::dvec3 lookAt(278.0, 278.0, 0.0);
	glm::dvec3 up(0.0, 1.0, 0.0);
	double focusDistance = glm::length(cameraPosition - lookAt);
	double aperture = 0.0;
	double vFOV = 40.0;
	double imageAspectRatio = 1.0;

	Camera camera(cameraPosition, lookAt, up, vFOV, imageAspectRatio, aperture, focusDistance, 0.0, 1.0);

	m_Camera = camera;
}

void Scene::Construct3() {
	m_BackgroundColour = glm::dvec3(0.0);

	HittableObjectList objects;

	std::shared_ptr<Texture> earthTexture = std::make_shared<ImageTexture>("res/textures/earthmap.jpg");

	std::shared_ptr<Material> pink = std::make_shared<Lambertian>(glm::dvec3(0.88, 0.55, 0.85));
	std::shared_ptr<Material> blue = std::make_shared<Lambertian>(glm::dvec3(0.1, 0.3, 0.85));
	std::shared_ptr<Material> white = std::make_shared<Lambertian>(glm::dvec3(0.9));
	std::shared_ptr<Material> metal = std::make_shared<Metal>(glm::dvec3(1.0), 0.05);
	std::shared_ptr<Material> light = std::make_shared<DiffuseLight>(glm::dvec3(10.0, 10.0, 10.0));
	std::shared_ptr<Material> earth = std::make_shared<Lambertian>(earthTexture);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			std::vector<std::shared_ptr<HittableObject>> section;
			section.reserve(4);

			if (i == 1 && j == 1) {
				continue;
			}
			for (int k = 0; k < 2; k++) {
				for (int l = 0; l < 2; l++) {
					double z = randomDouble(0.0, 0.25);
					section.push_back(std::make_shared<Box>(glm::dvec3(-1.5 + j + 0.5 * l, -1.5 + i + 0.5 * k, 0.0), glm::dvec3(-1.0 + j + 0.5 * l, -1.0 + i + 0.5 * k, 0.0 + z), pink));
				}
			}

			std::shared_ptr<HittableObject> node = std::make_shared<BVHNode>(section, 0, section.size(), 0.0, 1.0);
			objects.add(node);
		}
	}
	objects.add(std::make_shared<XYRect>(-0.5, 0.5, -0.5, 0.5, 0.0, metal));
	objects.add(std::make_shared<XYRect>(-3.0, 3.0, -3.0, 3.0, 5.0, white));
	objects.add(std::make_shared<Sphere>(glm::dvec3(-0.3, 0.0, 1.0), 0.2, earth));
	objects.add(std::make_shared<Sphere>(glm::dvec3(2.0, 2.0, 2.0), 0.5, light));
	objects.add(std::make_shared<MovingSphere>(glm::dvec3(0.4, 0.4, 1.0), glm::dvec3(0.4, 0.3, 1.0), 0.0, 1.0, 0.1, blue));

	m_HittableObjectList = objects;

	glm::dvec3 cameraPosition(0.2, 0.0, 3.0);
	glm::dvec3 lookAt(0.1, 0.0, 0.0);
	glm::dvec3 up(0.0, 1.0, 0.0);
	double focusDistance = glm::length(cameraPosition - lookAt);
	double aperture = 0.0;
	double vFOV = 45.0;
	double imageAspectRatio = 1.0;

	Camera camera(cameraPosition, lookAt, up, vFOV, imageAspectRatio, aperture, focusDistance, 0.0, 1.0);

	m_Camera = camera;
}