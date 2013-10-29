#include "face.hh"

Face::Face()
{
	m_vertices[0] = nullptr;
	m_vertices[1] = nullptr;
	m_vertices[2] = nullptr;
	m_faces[0] = 		nullptr;
	m_faces[1] = 		nullptr;
	m_faces[2] = 		nullptr;
}
Face::Face(Vertex& v1, Vertex& v2, Vertex& v3)
{
	m_vertices[0] = &v1;
	m_vertices[1] = &v2;
	m_vertices[2] = &v3;
	m_faces[0] = 		nullptr;
	m_faces[1] = 		nullptr;
	m_faces[2] = 		nullptr;
	
	assert(aire() >= 0);
}
Face::Face(Vertex& v1, Vertex& v2, Vertex& v3, Face& f1, Face& f2, Face& f3)
{
	m_vertices[0] = &v1;
	m_vertices[1] = &v2;
	m_vertices[2] = &v3;
	m_faces[0] = 		&f1;
	m_faces[1] = 		&f2;
	m_faces[2] = 		&f3;
	
	assert(aire() >= 0);
}



Vertex* Face::vertex(int i)
{
	if (i == 0) return m_vertices[0];
	if (i == 1) return m_vertices[1];
	if (i == 2) return m_vertices[2];
	return nullptr;
}
const Vertex* Face::vertex(int i) const
{
	if (i == 0) return m_vertices[0];
	if (i == 1) return m_vertices[1];
	if (i == 2) return m_vertices[2];
	return nullptr;
}
int Face::index(const Vertex* v) const
{
	if (v == m_vertices[0]) return 0;
	if (v == m_vertices[1]) return 1;
	if (v == m_vertices[2]) return 2;
	return -1;
}

Face* Face::face(int i)
{
	if (i == 0) return m_faces[0];
	if (i == 1) return m_faces[1];
	if (i == 2) return m_faces[2];
	return nullptr;
}
const Face* Face::face(int i) const
{
	if (i == 0) return m_faces[0];
	if (i == 1) return m_faces[1];
	if (i == 2) return m_faces[2];
	return nullptr;
}
int Face::index(const Face* f) const
{
	if (f == m_faces[0]) return 0;
	if (f == m_faces[1]) return 1;
	if (f == m_faces[2]) return 2;
	return -1;
}
	





double Face::aire() const
{
	return vertex(0)->aire(*vertex(1), *vertex(2));
}

bool Face::in(const vec3& pt) const
{
	if (this->aire() < 0) 										return false;
	if (pt.aire(*vertex(1), *vertex(2)) < 0)	return false;
	if (pt.aire(*vertex(2), *vertex(0)) < 0)	return false;
	if (pt.aire(*vertex(0), *vertex(1)) < 0)	return false;
	return true;
}

bool Face::in_circle(const vec3& pt) const
{
	return pt.in_circle(*vertex(0), *vertex(1), *vertex(2));
}

vec3 Face::project(const vec3& pt) const
{
	double At = this->aire();											assert(At >= 0.);
	double Aa = pt.aire(*vertex(1), *vertex(2));	assert(Aa >= 0.);
	double Ab = pt.aire(*vertex(2), *vertex(0));	assert(Ab >= 0.);
	double Ac = pt.aire(*vertex(0), *vertex(1));	assert(Ac >= 0.);
	return (	Aa*(*vertex(0))
					+ Ab*(*vertex(1))
					+ Ac*(*vertex(2)) ) / At;
}

double Face::key() const
{
	if (m_inside.empty())
		return 0.;
	return m_inside.top_key();
}

void Face::check() const
{
	assert(aire() >= 0);
	for (int i=0; i<3; ++i)
	{
		if (face(i) == nullptr) continue;
		assert(face(i)->index(this) != -1);
		assert(vertex((i+1)%3) == face(i)->vertex((face(i)->index(this)+2)%3));		
		assert(vertex((i+2)%3) == face(i)->vertex((face(i)->index(this)+1)%3));		
	}
}

