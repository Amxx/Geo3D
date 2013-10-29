#ifndef FACE_HH
#define FACE_HH

#include <cassert>
#include <cmath>

#include "vertex.hh"

#include "../structure/object.hh"
#include "../structure/priority.hh"
#include "../structure/vec3.hh"


class Triangulation;

class Face : public Object
{
		friend Triangulation;
	
	private:
		Vertex*											m_vertices[3];
		Face*												m_faces[3];
		priority										m_inside;
		
	
	public:
		Face();
		Face(Vertex&, Vertex&, Vertex&);
		Face(Vertex&, Vertex&, Vertex&, Face&, Face&, Face&);
	
		Vertex*					vertex		(int);
		const Vertex*		vertex		(int)										const;
		int							index			(const Vertex*)					const;
	
		Face*						face			(int);
		const Face* 		face			(int)										const;
		int 						index			(const Face*)						const;
	
	
		double					aire			()											const;
		bool						in				(const vec3&)						const;
		bool						in_circle	(const vec3& pt)				const;
		vec3						project		(const vec3&)						const;
	
		double					key				()											const;
		void 						check			()											const;
};

#endif