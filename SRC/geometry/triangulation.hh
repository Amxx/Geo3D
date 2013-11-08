#ifndef TRIANGULATION_HH
#define TRIANGULATION_HH

#include <assert.h>
#include <math.h>


#include "vertex.hh"
#include "face.hh"

#include "../tools/generator.hh"

#include <queue>
#include <vector>
#include "../structure/object.hh"
#include "../structure/priority.hh"
#include "../structure/vec3.hh"


#include "../tools/condition.hh"

class Triangulation
{
	
	public:
		std::vector<Vertex*>	m_vertices;
		std::vector<Face*>		m_faces;
		std::queue<Face*> 		m_queue;	
		
		priority							m_priority;
	
	public:
		Triangulation(int, const Generator::Generator& generator = Generator::Random());
		Triangulation(std::vector<vec3>&);
		~Triangulation();
	
		void triangulate(const Condition::Condition&);
	
	private:
		void divide(Face*);
		void delaunay(Face*);
		void bascule(Face* f, Face* g);
	
};

#endif