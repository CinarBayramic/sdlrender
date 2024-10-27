#include <iostream>
#include <SDL.h>
#include "types.hpp"
#include <thread>
#include <SDL_image.h>
#include <array>
namespace cgl {

	/*class vec4 {
	public:
		double x, y, z,w;
		vec4() : x(0), y(0), z(0), w(0) {}

		// Parametreli oluþturucu
		vec4(float x, float y, float z, float w) : x(x), y(y), z(z) w(w){}
	};*/
	/*class vec3 {
	public:
		double x, y, z;
		inline vec3() : x(0), y(0), z(0) {}

		// Parametreli oluþturucu
		vec3(float x, float y, float z) : x(x), y(y), z(z) {}
	};
	class vec2 {
	public:
		double x, y;
		vec2() : x(0), y(0) {}

		// Parametreli oluþturucu
		vec2(float x, float y) : x(x), y(y) {}
	};*/
	vec3::vec3() : x(0), y(0), z(0) {}

	vec3::vec3(double x, double y, double z) : x(x), y(y), z(z) {}

	vec2::vec2() : x(0), y(0) {}

	vec2::vec2(double x, double y) : x(x), y(y) {}


	poly3::poly3() {
		p[0] = vec3(); // Default initialization
		p[1] = vec3(); // Default initialization
		p[2] = vec3(); // Default initialization
	}
	poly3::poly3(const vec3& v1, const vec3& v2, const vec3& v3) {
		p[0] = v1;
		p[1] = v2;
		p[2] = v3;
	}

	poly2::poly2() {
		p[0] = vec2(); // Default initialization
		p[1] = vec2(); // Default initialization
		p[2] = vec2(); // Default initialization
	}
	poly2::poly2(const vec2& v1, const vec2& v2, const vec2& v3) {
		p[0] = v1;
		p[1] = v2;
		p[2] = v3;
	}

	void poly2::p2scr(SDL_Renderer* r, SDL_Texture* texture) {
		rTT(r, texture,poly2(p[0], p[1], p[2]), poly2(p[0], p[1], p[2]));
	}

	void poly2::p2scr(SDL_Renderer* r) {
		/*std::thread t1(SDL_RenderDrawLine, r, p[0].x, p[0].y, p[1].x, p[1].y);//really slow!
		std::thread t2(SDL_RenderDrawLine, r, p[1].x, p[1].y, p[2].x, p[2].y);
		std::thread t3(SDL_RenderDrawLine, r, p[2].x, p[2].y, p[0].x, p[0].y);
		t1.join();
		t2.join();
		t3.join();*/
			SDL_RenderDrawLine(r, p[0].x, p[0].y, p[1].x, p[1].y);
		SDL_RenderDrawLine(r, p[1].x, p[1].y, p[2].x, p[2].y);
		SDL_RenderDrawLine(r, p[2].x, p[2].y, p[0].x, p[0].y);
	}
	void DrawTriangle(SDL_Renderer* r, poly2 t) {
		SDL_RenderDrawLine(r, t.p[0].x, t.p[0].y, t.p[1].x, t.p[1].y);
		SDL_RenderDrawLine(r, t.p[1].x, t.p[1].y, t.p[2].x, t.p[2].y);
		SDL_RenderDrawLine(r, t.p[2].x, t.p[2].y, t.p[0].x, t.p[0].y);
	}
	double pwr(double n, int p) {
		double ntemp = n;
		for (int i = 1; i < p; i++) {
			ntemp *= n;
		}
		return ntemp;
	}
	
	void normalise(vec2* i) {
		double clen = sqrt((pwr(i->x, 2)) + (pwr(i->y, 2)));
		std::cout << clen;
		i->x /= clen;
		i->y /= clen;
	}
	void normalise(vec3* i) {
		double clen = sqrt((pwr(i->x, 2)) + (pwr(i->y, 2)) + (pwr(i->z, 2)));
		std::cout << clen;
		i->x /= clen;
		i->y /= clen;
		i->z /= clen;

	}
		vec2 multvecby(vec2 v, double d) {
			return { v.x * d,v.y * d };
		}
		vec3 multvecby(vec3 v, double d) {
			return { v.x * d,v.y * d,v.z * d };
		}
	vec2 perspectiveProject(const vec3& point, double fov, double aspectRatio, double near, double far) {
		double scale = 1.0f / tan(fov * 0.5 * M_PI / 180.0);
		vec2 projected;
		projected.x = point.x * scale / (point.z * aspectRatio);
		projected.y = point.y * scale / point.z;
		return projected;
	}
	vec2 perspectiveProjection(const vec3& v, double fov, double aspectRatio, double near, double far) {
		double f = 1.0 / tan(fov / 2.0);
		double screenX = v.x * f / v.z;
		double screenY = v.y * f / (aspectRatio * v.z);
		return vec2(screenX, screenY);
	}
	void Object3::OBJTOSCR(SDL_Renderer *renderer, size_t meshsize,SDL_Texture *t,double m) {
		//int num_polys = sizeof(MESH) / sizeof(MESH[0]); // Calculate number of elements in MESH
		int num_polys = meshsize / sizeof(MESH[0]);
		poly2* projected = (poly2*)malloc(num_polys * sizeof(poly2));
		if (num_polys == 0) {
			//std::cout << "real wrong!" << sizeof(MESH)<< " \n";
		}
		if (projected == nullptr) {
			std::cout << "WRONGER";
			return;
		}
		/*
		poly3 *newmesh = MESH;
		vec3 na = rot;
		
		normalise(&na);
		std::cout <<" ||" << pwr(na.x, 2) + pwr(na.y, 2) + pwr(na.z, 2) << "nn\n";
		if (pwr(na.x, 2) + pwr(na.y, 2) + pwr(na.z, 2) <= 0 ) {
			na.x = 1;
			na.y = 0;
			na.z = 0;
			std::cout << "rong";
		}
		for (int i = 0; i < num_polys; i++) {
			newmesh[i].p[0] = vec3(MESH[i].p[0].x * na.x, MESH[i].p[0].y * na.y, MESH[i].p[0].z * na.z);
			newmesh[i].p[1] = vec3(MESH[i].p[1].x * na.x, MESH[i].p[1].y * na.y, MESH[i].p[1].z * na.z);
			newmesh[i].p[2] = vec3(MESH[i].p[2].x * na.x, MESH[i].p[2].y * na.y, MESH[i].p[2].z * na.z);
		}*/
		for (int i = 0; i < num_polys; i++) {
			
			projected[i].p[0] = cgl::multvecby(cgl::perspectiveProject(offsetpoly(MESH[i],pos,rot).p[0], 90.0, 16 / 9, 0.1, 100.0), m);
			projected[i].p[1] = cgl::multvecby(cgl::perspectiveProject(offsetpoly(MESH[i], pos, rot).p[1], 90.0, 16 / 9, 0.1, 100.0), m);
			projected[i].p[2] = cgl::multvecby(cgl::perspectiveProject(offsetpoly(MESH[i], pos, rot).p[2], 90.0, 16 / 9, 0.1, 100.0), m);
			
		}
		for (int i = 0; i < num_polys; i++) {
			projected[i].p2scr(renderer,t);
			//projected[i].p2scr(renderer);
			//rTT(renderer,t,projected[i],projected[i]);
		}
		free(projected);
	}
	void Object3::setmesh(poly3 *mesh, size_t meshsize) {
		
		MESH = (poly3*)malloc(meshsize);
		if (MESH == nullptr) {
			std::cout << meshsize;
			return;
		}
		//std::cout << "true!" << meshsize /* sizeof(MESH[0])*/ << " \n";
		memcpy(MESH, mesh, meshsize);
	}
	void rTT(SDL_Renderer* renderer, SDL_Texture* texture, poly2 p, poly2 uv) {
		SDL_Vertex sdlVertices[3];

		for (int i = 0; i < 3; ++i) {
			sdlVertices[i] = {
				{ (float)p.p[i].x, (float)p.p[i].y},
				{ 255, 255, 255, 255 },
				{ (float)uv.p[i].x, (float)uv.p[i].y}
			};
		}

		// Render the triangle
		SDL_RenderGeometry(renderer, texture, sdlVertices, 3, nullptr, 0);
	}
}
cgl::poly3 cgl::offsetpoly(cgl::poly3 p, cgl::vec3 pos, cgl::vec3 dir) {
	cgl::poly3 outP;

		outP.p[0].x = p.p[0].x + pos.x;
		outP.p[0].y = p.p[0].y + pos.y;
		outP.p[0].z = p.p[0].z + pos.z;
		outP.p[1].x = p.p[1].x + pos.x;
		outP.p[1].y = p.p[1].y + pos.y;
		outP.p[1].z = p.p[1].z + pos.z;
		outP.p[2].x = p.p[2].x + pos.x;
		outP.p[2].y = p.p[2].y + pos.y;
		outP.p[2].z = p.p[2].z + pos.z;

	return outP;
}
	/*static void my_PerspectiveFOV(double fov, double aspect, double near, double far, double* mret) {
		double D2R = M_PI / 180.0;
		double yScale = 1.0 / tan(D2R * fov / 2);
		double xScale = yScale / aspect;
		double nearmfar = near - far;
		double m[] = {//idontunderstandanythinghere,iwontaddmorefeaturesuntiliunderstand,iwillmakethiscompatibleinthefture
			xScale, 0, 0, 0,
			0, yScale, 0, 0,
			0, 0, (far + near) / nearmfar, -1,
			0, 0, 2 * far * near / nearmfar, 0
		};
		memcpy(mret, m, sizeof(double) * 16);
	}*/
