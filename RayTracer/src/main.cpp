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

	const double IMAGE_ASPECT_RATIO = 16.0 / 9.0;
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

	std::shared_ptr<Texture> earthTexture = std::make_shared<ImageTexture>("res/textures/earthmap.jpg");
	std::shared_ptr<Material> earthSurface = std::make_shared<Lambertian>(earthTexture);
	scene.add(std::make_shared<Sphere>(glm::dvec3(0.0, 0.0, 0.0), 2.0, earthSurface));

	// Camera

	glm::dvec3 cameraPosition(13.0, 2.0, 3.0);
	glm::dvec3 lookAt(0.0, 0.0, 0.0);
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