#ifndef VERTEX_HH
#define VERTEX_HH

#include "../structure/object.hh"
#include "../structure/vec3.hh"

class Vertex : public Object, public vec3
{
	public:
		Vertex();
		Vertex(const vec3& v);
};

#endif