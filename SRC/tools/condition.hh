#ifndef CONDITION_HH
#define CONDITION_HH

#include "../structure/priority.hh"

/**
 * \file condition.hh Critères d'arret pour la triangulation
 */
 
namespace Geometry
{
	class Triangulation;
};

/**
 * \namespace Condition Critères d'arret pour la triangulation
 */
namespace Condition
{
	/**
	 * Condition d'arret de la triangulation
	 */
	class	Condition
	{
		public:
			virtual ~Condition	() {}
			/**
			 * Evaluation de la condition d'arret
			 * @param triangulation Triangulation à considerer
			 * @return La triangulation est elle inachevé pour la condition décrite
			 */
			virtual bool loop		(const Geometry::Triangulation& triangulation) const = 0;
	};
	
	/**
	 * Ensembles de condition d'arret
	 */
	class Condition_set : public Condition, public std::vector<Condition*>
	{
		public:
			/**
			 * Evaluation de la condition d'arret
			 * @param triangulation Triangulation à considerer
			 * @return La triangulation est elle inachevé pour une des sous conditions décrites
			 */
			bool loop						(const Geometry::Triangulation& triangulation) const;
	};
	
	
	/**
	 * Condition sur de nombre de triangles dans la triangulation
	 */
	class NumberCondition : public Condition
	{
			Structure::Priority::size_type number;
		public:
			/**
			 * Constructeur
			 * @param n Nombre de triangle à atteindre
			 */
			NumberCondition			(Structure::Priority::size_type n = 100000);
			/**
			 * Evaluation de la condition d'arret
			 * @param triangulation Triangulation à considerer
			 * @return La triangulation est elle inachevé pour la condition décrite
			 */
			bool loop						(const Geometry::Triangulation& triangulation) const;
	};
	/**
	 * Condition sur la fidélité de la triangulation
	 */
	class FidelityCondition : public Condition
	{
			double precision;
		public:
			/**
			 * Constructeur
			 * @param p Précision à atteindre
			 */
			FidelityCondition		(const double& p = 0.01);
			/**
			 * Evaluation de la condition d'arret
			 * @param triangulation Triangulation à considerer
			 * @return La triangulation est elle inachevé pour la condition décrite
			 */
			bool loop						(const Geometry::Triangulation& triangulation) const;
	};
};

#endif