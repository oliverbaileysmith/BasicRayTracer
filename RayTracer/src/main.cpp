#include <iostream>
#include <memory>

#include "Util.h"
#include "Renderer.h"
#include "Ray.h"
#include "HittableObjectList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"
#include "MovingSphere.h"
#include "AARect.h"
#include "Box.h"

#include "vendor/glm/ext/vector_double3.hpp"
#include "vendor/glm/gtx/vector_angle.hpp"

glm::dvec3 rayColour(const Ray &ray, const glm::dvec3 &BGColour, const HittableObject &scene, uint32_t maxRayBounces) {

	HitRecord hitRecord;

	if (maxRayBounces <= 0)
		return glm::dvec3(0.0, 0.0, 0.0);

	if (!scene.Hit(ray, 0.001, POSITIVE_INFINITY, hitRecord))
		return BGColour;
	
	Ray scattered;
	glm::dvec3 attenuation;
	glm::dvec3 emitted = hitRecord.m_MaterialPtr->emitted(hitRecord.m_U, hitRecord.m_V, hitRecord.m_HitPoint);

	if (!hitRecord.m_MaterialPtr->Scatter(ray, hitRecord, attenuation, scattered))
		return emitted;

	return emitted + attenuation * rayColour(scattered, BGColour, scene, maxRayBounces - 1);
}


void main() {

	// Image details

	const double IMAGE_ASPECT_RATIO = 1.0;
	const int32_t IMAGE_WIDTH = 400;
	const int32_t IMAGE_HEIGHT = (int32_t)(IMAGE_WIDTH / IMAGE_ASPECT_RATIO);
	const int32_t SAMPLES_PER_PIXEL = 100;
	const int32_t MAX_RAY_BOUNCES = 50;
	const double VERTICAL_FOV = 40.0;
	const glm::dvec3 BACKGROUND_COLOUR(0.0, 0.0, 0.0);

	// Scene

	double R = std::cos(PI / 4);

	HittableObjectList scene;

	/*std::shared_ptr<Material> materialGround = std::make_shared<Lambertian>(glm::dvec3(0.8, 0.8, 0.0));
	std::shared_ptr<Material> materialSphere1 = std::make_shared<Lambertian>(glm::dvec3(0.1, 0.2, 0.5));
	std::shared_ptr<Material> materialSphere2 = std::make_shared<Dielectric>(1.5);
	std::shared_ptr<Material> materialSphere3 = std::make_shared<Metal>(glm::dvec3(0.8, 0.6, 0.2), 0.0);

	scene.add(std::make_shared<Sphere>(glm::vec3( 0.0, -100.5, -1.0), 100.0, materialGround));
	scene.add(std::make_shared<Sphere>(glm::vec3( 0.0,    0.0, -1.0),   0.5, materialSphere1));
	scene.add(std::make_shared<Sphere>(glm::vec3(-1.0,    0.0, -1.0),   0.5, materialSphere2));
	scene.add(std::make_shared<Sphere>(glm::vec3(-1.0,    0.0, -1.0),  -0.4, materialSphere2));
	scene.add(std::make_shared<Sphere>(glm::vec3( 1.0,    0.0, -1.0),   0.5, materialSphere3));
	scene.add(std::make_shared<MovingSphere>(glm::vec3(0.0, 1.0, -1.0), glm::vec3(0.0, 1.25, -1.0), 0.0, 1.0, 0.3, materialSphere1));*/

	/*std::shared_ptr<Texture> checker = std::make_shared<CheckerTexture>(glm::dvec3(0.2, 0.3, 0.1), glm::dvec3(0.9, 0.9, 0.9));
	scene.add(std::make_shared<Sphere>(glm::dvec3(0.0, -10.0, 0.0), 10.0, std::make_shared<Lambertian>(checker)));
	scene.add(std::make_shared<Sphere>(glm::dvec3(0.0,  10.0, 0.0), 10.0, std::make_shared<Lambertian>(checker)));*/

	/*std::shared_ptr<Texture> earthTexture = std::make_shared<ImageTexture>("res/textures/earthmap.jpg");
	std::shared_ptr<Material> earthSurface = std::make_shared<Lambertian>(earthTexture);
	scene.add(std::make_shared<Sphere>(glm::dvec3(0.0, 0.0, 0.0), 2.0, earthSurface));*/

	/*std::shared_ptr<Texture> earthTexture = std::make_shared<ImageTexture>("res/textures/earthmap.jpg");
	scene.add(std::make_shared<Sphere>(glm::dvec3(0.0, -1000.0, 0), 1000.0, std::make_shared<Lambertian>(earthTexture)));
	scene.add(std::make_shared<Sphere>(glm::dvec3(0.0, 2.0, 0), 2, std::make_shared<Lambertian>(earthTexture)));

	std::shared_ptr<Material> diffLight = std::make_shared<DiffuseLight>(glm::dvec3(4.0, 4.0, 4.0));
	scene.add(std::make_shared<XYRect>(3.0, 5.0, 1.0, 3.0, -2.0, diffLight));*/

	std::shared_ptr<Material> red = std::make_shared<Lambertian>(glm::dvec3(0.65, 0.05, 0.05));
	std::shared_ptr<Material> white = std::make_shared<Lambertian>(glm::dvec3(0.73, 0.73, 0.73));
	std::shared_ptr<Material> green = std::make_shared<Lambertian>(glm::dvec3(0.12, 0.45, 0.15));
	std::shared_ptr<Material> light = std::make_shared<DiffuseLight>(glm::dvec3(15.0, 15.0, 15.0));

	scene.add(std::make_shared<YZRect>(  0.0, 555.0,   0.0, 555.0, 555.0, green));
	scene.add(std::make_shared<YZRect>(  0.0, 555.0,   0.0, 555.0,   0.0, red));
	scene.add(std::make_shared<XZRect>(213.0, 343.0, 227.0, 332.0, 554.0, light));
	scene.add(std::make_shared<XZRect>(  0.0, 555.0,   0.0, 555.0,   0.0, white));
	scene.add(std::make_shared<XZRect>(  0.0, 555.0,   0.0, 555.0, 555.0, white));
	scene.add(std::make_shared<XYRect>(  0.0, 555.0,   0.0, 555.0, 555.0, white));

	scene.add(std::make_shared<Box>(glm::dvec3(130.0, 0.0, 65.0), glm::dvec3(295.0, 165.0, 230.0), white));
	scene.add(std::make_shared<Box>(glm::dvec3(265.0, 0.0, 295.0), glm::dvec3(430.0, 330.0, 460.0), white));

	// Camera

	glm::dvec3 cameraPosition(278.0, 278.0, -800.0);
	glm::dvec3 lookAt(278.0, 278.0, 0.0);
	glm::dvec3 up(0.0, 1.0, 0.0);
	double focusDistance = glm::length(cameraPosition - lookAt);
	double aperture = 0.0;

	Camera camera(cameraPosition, lookAt, up, VERTICAL_FOV, IMAGE_ASPECT_RATIO, aperture, focusDistance, 0.0, 1.0);

	Renderer renderer(IMAGE_WIDTH, IMAGE_HEIGHT);

	for (int32_t y = IMAGE_HEIGHT - 1; y >= 0; y--) {
		
		// Progress indicator
		std::cout << "\rScanlines remaining: " << y << ' ' << std::flush;

		for (int32_t x = 0; x < IMAGE_WIDTH; x++) {

			glm::dvec3 pixelColour(0.0, 0.0, 0.0);
			for (int s = 0; s < SAMPLES_PER_PIXEL; s++) {

				double u = ((double)x + randomDouble()) / (double)(IMAGE_WIDTH - 1);
				double v = ((double)y + randomDouble()) / (double)(IMAGE_HEIGHT - 1);

				Ray ray = camera.getRay(u, v);
				pixelColour += rayColour(ray, BACKGROUND_COLOUR, scene, MAX_RAY_BOUNCES);

			}
			renderer.RenderPixel(pixelColour, SAMPLES_PER_PIXEL);
		}
	}

	// Render

	renderer.WriteOutput(IMAGE_WIDTH, IMAGE_HEIGHT);

}