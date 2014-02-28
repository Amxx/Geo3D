#ifndef VERTEX_HH
#define VERTEX_HH

#include "../structure/priority.hh"
#include "../structure/vec3.hh"

/**
 * \file vertex.hh Point
 */

/**
 * \namespace Geometry Structures pour la gestion de la geometrie
 */

namespace Geometry
{
	/**
	 * Decrit un sommet dans la triangulation de delaunay
	 */
	class Vertex : public vec3
	{
		public:
			Vertex();
			Vertex(const vec3& v);
	};
};

#endif