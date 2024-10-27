
#ifndef TYPES_HPP
#define TYPES_HPP
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

namespace cgl {
	double clamp(double value, double min, double max);
	/*class vec4 {
	public:
		double x, y, z, w;
		vec4() : x(0), y(0), z(0), w(0) {}

		// Parametreli oluþturucu
		vec4(float x, float y, float z, float w) : x(x), y(y), z(z) w(w) {}
	};*/
	class vec3 {
	public:
		double x, y, z;
		vec3();
		vec3(double x, double y, double z);
	};

	class vec2 {
	public:
		double x, y;
		vec2();
		vec2(double x, double y);
	};
	class Vertex {
	public:
		vec2 pos, uv;
	};
	class poly2 {
	public:
		vec2 p[3];
		poly2();
		poly2(const vec2& v1, const vec2& v2, const vec2& v3);
		void p2scr(SDL_Renderer* r);
		void p2scr(SDL_Renderer* r, poly2 uv, SDL_Texture* texture);


	};

	class poly3 {
	public:
		vec3 p[3];
		poly3();
		poly3(const vec3& v1, const vec3& v2, const vec3& v3);

	};
	class Object3 {
	public:
		poly3* MESH;
		vec3 pos = cgl::vec3(9,9,1); vec3 vel;
		vec3 rot = vec3(1, 0, 0);
		void setmesh(poly3* mesh, size_t meshsize);
		void OBJTOSCR(SDL_Renderer* renderer, size_t meshsize, SDL_Texture* t, double m);
	};
	class camera {
	public:
		SDL_Renderer* renderer;
		vec3 pos, rot;


	};
	poly3 offsetpoly(poly3 p, vec3 pos,vec3 dir);

	vec2 multvecby(vec2 v, double d);
	vec3 multvecby(vec3 v, double d);
	void DrawTriangle(SDL_Renderer* r, poly2 t);
	double pwr(double n, int p);
	void normalise(vec2* i);
	void normalise(vec3* i);
	vec2 calculatenormals(poly2);
	vec2 perspectiveProject(const vec3& point, double fov, double aspectRatio, double near, double far);
	vec2 perspectiveProjection(const vec3& v, double fov, double aspectRatio, double near, double far);
	void rTT(SDL_Renderer* renderer, SDL_Texture* texture, poly2 p, poly2 uv);
}
#endif