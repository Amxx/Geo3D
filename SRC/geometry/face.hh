#ifndef FACE_HH
#define FACE_HH

#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "vertex.hh"

#include "../structure/priority.hh"
#include "../structure/vec3.hh"

/**
 * \file face.hh Face
 */

/**
 * \namespace Geometry Structures pour la gestion de la geometrie
 */

namespace Geometry
{
	class Triangulation;
	
	/**
	 * Décrit une face dans la triangulation de delaunay
	 */
	class Face : public Structure::Object
	{
		friend Triangulation;
	
		private:
			Vertex*											m_vertices[3];	//!< Sommets de la face
			Face*												m_faces[3];			//!< Faces adjacentes opposés aux sommets
			std::vector<Vertex*>				m_inside;				//!< Points interne (équart maximum en tête)
			double											m_inside_key;		//!< Equart maximum d'un point interne à la face
		
		public:
			Face();
			Face(Vertex&, Vertex&, Vertex&);
			Face(Vertex&, Vertex&, Vertex&, Face&, Face&, Face&);
	
			/**
			 * Acces a un sommet
			 * @param idx Identifiant du sommet
			 * @result Sommet de la face
			 */
			Vertex*								vertex		(int idx);
			/**
			 * Acces a un sommet
			 * @param idx Identifiant du sommet
			 * @result Sommet de la face
			 */
			const Vertex*					vertex		(int idx)									const;
			/**
			 * Recherche d'un sommet
			 * @param v Sommet a chercher
			 * @result Indice du sommet dans la face
			 */
			int										index			(const Vertex* v)					const;
			/**
			 * Acces a une face adjacente
			 * @param idx Identifiant de la face
			 * @result Face adjacente à la face
			 */
			Face*									face			(int idx);
			/**
			 * Acces a une face adjacente
			 * @param idx Identifiant de la face
			 * @result Face adjacente à la face
			 */
			const Face* 					face			(int idx)									const;
			/**
			 * Recherche d'une face
			 * @param f Face a chercher
			 * @result Indice d'adjacence de la face
			 */
			int 									index			(const Face* f)						const;
			/**
			 * Aire du triangle
			 * @return Aire du triangle
			 */
			double								aire			()												const;
			/**
			 * Test interieur
			 * @param pt Point
			 * @return Le point est il dans le triangle
			 */
			bool									in				(const vec3& pt)					const;
			/**
			 * Test interieur au cercle circonscrit
			 * @param pt Point
			 * @return Le point est il dans le cercle circonscrit au triangle
			 */
			bool									in_circle	(const vec3& pt)					const;
			/**
			 * Projection d'un point
			 * @param pt Point
			 * @return Le point résultant de la projection verticale sur la face
			 */
			vec3									project		(const vec3& pt)					const;
			/**
			 * Fonction de vérification de la conherence des information (Sommets - Faces)
			 */
			void 									check			()												const;
			/**
			 * Insertion d'un point dans la face
			 * @param pt Point
			 * @param key Distance associé au point
			 */
			void									insert		(Vertex* pt, const double& key);
			/**
			 * Dumping des points internes vers un vecteur
			 * @param pts Vecteur (vide) dans lequel placer les points
			 */
			void									swap			(std::vector<Vertex*>& pts);
			/**
			 * Distance maximale d'un point interne a la face
			 * @return Distance maximale d'un point interne a la face
			 */
			double&								key				();
			/**
			 * Distance maximale d'un point interne a la face
			 * @return Distance maximale d'un point interne a la face
			 */
			const double&					key				()												const;
	};
};

#endif