#ifndef TRIANGULATION_HH
#define TRIANGULATION_HH

#include <assert.h>
#include <math.h>
#include <queue>
#include <vector>

#include "vertex.hh"
#include "face.hh"

#include "../structure/priority.hh"
#include "../structure/vec3.hh"
#include "../tools/condition.hh"
#include "../tools/generator.hh"

/**
 * \file triangulation.hh Triangulation
 */

/**
 * \namespace Geometry Structures pour la gestion de la geometrie
 */

namespace Geometry
{
	/**
	 * Represente une triangulation de delaunay
	 */
	class Triangulation
	{
		public:
			std::vector<Vertex*>	m_vertices;		//!< Sommets
			std::vector<Face*>		m_faces;			//!< Faces (triangles)
			std::queue<Face*> 		m_queue;			//!< File d'attente des faces à flipper
			Structure::Priority		m_priority;		//!< File de priorité des faces à diviser
	
		public:
			/**
			 * Constructeur
			 * Initialise un debut de triangulation
			 * @param n Nombre de points aleatoires à placer
			 * @param generator Generateur de points à utiliser
			 */
			Triangulation(int n, const Generator::Generator& generator = Generator::Random());
			~Triangulation();
			/**
			 * Calcul de la triangulation
			 * @param condition Critère d'arret de la triangulation
			 */
			void triangulate(const Condition::Condition& condition);
		
		private:
			/**
			 * Division d'une face par l'ajout d'un point interne a cette face
			 * @param f Face a diviser
			 */
			void divide(Face* f);
			/**
			 * Transformation de la triangulation pour la rendre de delaunay
			 * @param f Face initiale à vérifier
			 */
			void delaunay(Face* f);
			/**
			 * Vérification de la condition de flip (et flip) de deux faces adjacentes
			 * @param f Premiere face
			 * @param g Deuxieme face
			 */
			void bascule(Face* f, Face* g);	
	};
};

#endif