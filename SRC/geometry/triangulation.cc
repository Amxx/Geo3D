#include "triangulation.hh"


#include <cstdio>

Triangulation::Triangulation(int nb, const Generator::Generator& generator)
{
	Vertex* v0 = new Vertex(generator.base(0));
	Vertex* v1 = new Vertex(generator.base(1));
	Vertex* v2 = new Vertex(generator.base(2));
	Vertex* v3 = new Vertex(generator.base(3));
	
	Face*		f0 = new Face(*v0, *v1, *v2);
	Face*		f1 = new Face(*v3, *v2, *v1);
	
	f0->m_faces[0] = f1;
	f1->m_faces[0] = f0;

	m_vertices.push_back(v0);
	m_vertices.push_back(v1);
	m_vertices.push_back(v2);
	m_vertices.push_back(v3);
	
	m_faces.push_back(f0);
	m_faces.push_back(f1);
	
	for (int i=4; i<nb; ++i)
	{
		Vertex* pt = new Vertex(generator());
		if 			(f0->in(*pt))
			f0->insert(pt, fabs(pt->y()));
		else if	(f1->in(*pt))
			f1->insert(pt, fabs(pt->y()));
		else
			assert(false);
		m_vertices.push_back(pt);
	}
	
}

Triangulation::Triangulation(std::vector<vec3>& pts)
{
	// TODO
	assert(false);
}


Triangulation::~Triangulation()
{
	#ifdef CPP11
	for (Vertex* v : m_vertices)
		delete v;
	for (Face* f : m_faces)
		delete f;
	#else
	for (std::vector<Vertex*>::iterator it = m_vertices.begin(); it != m_vertices.end(); ++it)
		delete (*it);
	for (std::vector<Face*>::iterator it = m_faces.begin(); it != m_faces.end(); ++it)
		delete (*it);
	#endif
}





void Triangulation::triangulate(const Condition::Condition& condition)
{
	m_priority.clear();
	
	#ifdef CPP11
	for (Face* face : m_faces)
		m_priority.push(face, face->key());
	#else
	for (std::vector<Face*>::iterator it = m_faces.begin(); it != m_faces.end(); ++it)
		m_priority.push(*it, (*it)->key());
	#endif
	
	while (condition.loop(m_priority))
		divide(static_cast<Face*> (m_priority.pop()));
	
}








void Triangulation::divide(Face* face0)
{
	assert(face0);
		
	Vertex*		center =	face0->m_inside.front();
	std::swap(face0->m_inside.front(), face0->m_inside.back());
	face0->m_inside.pop_back();
	assert(center);
	
	Vertex 		*v0 = face0->vertex(0);				
	Vertex		*v1 = face0->vertex(1);				
	Vertex 		*v2 = face0->vertex(2);

	Face			*f0 = face0->face(0);
	Face			*f1 = face0->face(1);
	Face			*f2 = face0->face(2);
	
	face0->m_vertices[0] = center;
	Face* face1 = new Face(*center, *v2, *v0);
	Face* face2 = new Face(*center, *v0, *v1);
	
	face0->m_faces[0] = f0;	face0->m_faces[1] = face1; face0->m_faces[2] = face2;
	face1->m_faces[0] = f1;	face1->m_faces[1] = face2; face1->m_faces[2] = face0;
	face2->m_faces[0] = f2;	face2->m_faces[1] = face0; face2->m_faces[2] = face1;
		
	if (f0) f0->m_faces[f0->index(face0)] = face0;
	if (f1) f1->m_faces[f1->index(face0)] = face1;
	if (f2) f2->m_faces[f2->index(face0)] = face2;
	
	std::vector<Vertex*> inside;
	face0->swap(inside);
	
	#ifdef CPP11
	for (Vertex* pt : inside)
	{
		if 				(center->orientation(*pt, *v2) != NEGATIVE && center->orientation(*pt, *v1) != POSITIVE)
			face0->insert(pt, fabs(pt->y() - face0->project(*pt).y()));
		else if 	(center->orientation(*pt, *v0) != NEGATIVE && center->orientation(*pt, *v2) != POSITIVE)
			face1->insert(pt, fabs(pt->y() - face1->project(*pt).y()));
		else if 	(center->orientation(*pt, *v1) != NEGATIVE && center->orientation(*pt, *v0) != POSITIVE)
			face2->insert(pt, fabs(pt->y() - face2->project(*pt).y()));
		else
			assert(false);		
	}
	#else
	for (std::vector<Vertex*>::iterator it = inside.begin(); it != inside.end(); ++it)
	{
		if 				(center->orientation(*(*it), *v2) != NEGATIVE && center->orientation(*(*it), *v1) != POSITIVE)
			face0->insert((*it), fabs((*it)->y() - face0->project(*(*it)).y()));
		else if 	(center->orientation(*(*it), *v0) != NEGATIVE && center->orientation(*(*it), *v2) != POSITIVE)
			face1->insert((*it), fabs((*it)->y() - face1->project(*(*it)).y()));
		else if 	(center->orientation(*(*it), *v1) != NEGATIVE && center->orientation(*(*it), *v0) != POSITIVE)
			face2->insert((*it), fabs((*it)->y() - face2->project(*(*it)).y()));
		else
			assert(false);		
	}
	#endif


	m_faces.push_back(face1);
	m_faces.push_back(face2);
	
	m_priority.push(face0, face0->key());
	m_priority.push(face1, face1->key());
	m_priority.push(face2, face2->key());
	
	m_queue.push(face0);
	m_queue.push(face1);
	m_queue.push(face2);
	
	while (!m_queue.empty())
	{
		Face* c = m_queue.front();
		m_queue.pop();
		delaunay(c);
	}
	
}




void Triangulation::delaunay(Face* f)
{
	Face*					g;
	Vertex* 			v_f;
	Vertex* 			v_g;
	int 					i_f;
	int 					i_g;
				
	for (i_f=0; i_f<3; ++i_f)
	{
		g =	f->face(i_f);
		if (g == NULL)																								continue;
		i_g =	g->index(f);
		v_f = f->vertex(i_f);
		v_g = g->vertex(i_g);
		if (v_f->orientation(*f->vertex((i_f+1)%3), *v_g) != POSITIVE)	continue;
		if (v_g->orientation(*g->vertex((i_g+1)%3), *v_f) != POSITIVE)	continue;
		if (!f->in_circle(*v_g) && !g->in_circle(*v_f))									continue;
		
		bascule(f, g);
		m_queue.push(g);
		
		return;
	}
}


void Triangulation::bascule(Face* f, Face* g)
{
	int 					i_f = f->index(g);
	int 					i_g = g->index(f);
	Vertex* 			v_f = f->vertex(i_f);
	Vertex* 			v_g = g->vertex(i_g);
		
	f->m_vertices[(i_f+1)%3] = v_g;
	g->m_vertices[(i_g+1)%3] = v_f;
	
	f->m_faces[i_f] 			= g->m_faces[(i_g+2)%3];
	g->m_faces[i_g] 			= f->m_faces[(i_f+2)%3];
	f->m_faces[(i_f+2)%3] =	g;
	g->m_faces[(i_g+2)%3] =	f;
	
	if (f->face(i_f)) f->face(i_f)->m_faces[f->face(i_f)->index(g)] = f;
	if (g->face(i_g)) g->face(i_g)->m_faces[g->face(i_g)->index(f)] = g;
	
	std::vector<Vertex*> inside_f;
	std::vector<Vertex*> inside_g;
	f->swap(inside_f);
	g->swap(inside_g);
	
	#ifdef CPP11
	for (Vertex* pt : inside_f)
	{
		if (f->in(*pt))
			f->insert(pt, fabs(pt->y() - f->project(*pt).y()));
		else if (g->in(*pt))
			g->insert(pt, fabs(pt->y() - g->project(*pt).y()));
		else
			assert(false);
	}
	for (Vertex* pt : inside_g)
	{
		if (f->in(*pt))
			f->insert(pt, fabs(pt->y() - f->project(*pt).y()));
		else if (g->in(*pt))
			g->insert(pt, fabs(pt->y() - g->project(*pt).y()));
		else
			assert(false);
	}
	#else
	for (std::vector<Vertex*>::iterator it = inside_f.begin(); it != inside_f.end(); ++it)
	{
		if (f->in(*(*it)))
			f->insert((*it), fabs((*it)->y() - f->project(*(*it)).y()));
		else if (g->in(*(*it)))
			g->insert((*it), fabs((*it)->y() - g->project(*(*it)).y()));
		else
			assert(false);
	}
	for (std::vector<Vertex*>::iterator it = inside_g.begin(); it != inside_g.end(); ++it)
	{
		if (f->in(*(*it)))
			f->insert((*it), fabs((*it)->y() - f->project(*(*it)).y()));
		else if (g->in(*(*it)))
			g->insert((*it), fabs((*it)->y() - g->project(*(*it)).y()));
		else
			assert(false);
	}

	#endif
	
	m_priority.update(f, f->key());
	m_priority.update(g, g->key());
}


















/*
	printf(	"Face %p [%d]\n\t(%8.6lg, %8.6lg) -> %p\n\t(%8.6lg, %8.6lg) -> %p\n\t(%8.6lg, %8.6lg) -> %p\n",
					f, i_f,
					f->vertex(0)->x(), f->vertex(0)->z(), f->face(0),
					f->vertex(1)->x(), f->vertex(1)->z(), f->face(1),
					f->vertex(2)->x(), f->vertex(2)->z(), f->face(2)
					);
	printf(	"Face %p [%d]\n\t(%8.6lg, %8.6lg) -> %p\n\t(%8.6lg, %8.6lg) -> %p\n\t(%8.6lg, %8.6lg) -> %p\n",
					g, i_g,
					g->vertex(0)->x(), g->vertex(0)->z(), g->face(0),
					g->vertex(1)->x(), g->vertex(1)->z(), g->face(1),
					g->vertex(2)->x(), g->vertex(2)->z(), g->face(2)
					);
	*/
	
