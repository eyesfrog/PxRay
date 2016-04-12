//
// Created by eyesfrog on 15/7/15.
//

#ifndef TINYRAY_WORLD_H
#define TINYRAY_WORLD_H

#include <vector>
#include "ViewPlane.h"
#include "../GeometricObjects/GeometricObject.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/Math.h"
#include "../Tracer/Tracer.h"
#include "../Camera/Camera.h"
#include "../Lights/Light.h"
#include "../Lights/Ambient.h"
#include "../GeometricObjects/Sphere.h"

class World {
public:
	ViewPlane vp;
	RGBColor back_ground_color;
	Tracer* tracer_ptr;
	Camera* camera_ptr;
	Light* ambient_ptr;
	Material* material_ptr;
	Sphere sphere;

	std::vector<GeometricObject*> objects;
	std::vector<Light*> lights;
	std::vector<Material*> materials;

	World(void);

	~World();

	void add_object(GeometricObject* o_ptr);

	void add_light(Light* l_ptr);

	void add_material(Material* m_ptr);

	void set_ambient_light(Light* l_ptr);

	void build(void);

	void set_camera(Camera* c_ptr);

	//void render_perspective(void) const;

	//void render_scene(void) const;

	RGBColor
			max_to_one(const RGBColor& c) const;

	RGBColor
			clamp_to_color(const RGBColor& c) const;

	//void display() const;

	ShadeRec hit_object(const Ray& ray);

	ShadeRec hit_bare_bones_objects(const Ray& ray);

private:
	void delete_objects();

	void delete_lights();

	void delete_materials();

};

inline void
World::add_object(GeometricObject* o_ptr)
{
	objects.push_back(o_ptr);
}

inline void
World::add_light(Light* l_ptr)
{
	lights.push_back(l_ptr);
}

inline void
World::add_material(Material* m_ptr)
{
	materials.push_back(m_ptr);
}

inline void
World::set_camera(Camera* c_ptr)
{
	camera_ptr = c_ptr;
}

inline void
World::set_ambient_light(Light* l_ptr)
{
	ambient_ptr = l_ptr;
}

#endif //TINYRAY_WORLD_H
