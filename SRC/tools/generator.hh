#ifndef GENERATOR_HH
#define GENERATOR_HH

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "../structure/vec3.hh"

#ifdef OPENCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#endif

/**
 * \file generator.hh Generation de points
 */

/**
 * \namespace Generator Generation de points
 */
namespace Generator
{
	/**
	 * Generateur de points
	 */
	class Generator
	{
		public:
			virtual ~Generator			() {};
			/**
			 * Limites de la surface
			 * @param idx Identifiant du coin
			 * @result Coin de la surface
			 */
			virtual vec3 base				(int  idx)	const = 0;
			/**
			 * Generation d'un point
			 * @result Point sur la surface virtuelle
			 */
			virtual vec3 operator() () 		const = 0;
	};

	/**
	 * Implementation de la classe Generator, points aleatoires
	 */
	class Random : public Generator
	{
			double m_scale;
			double m_height;
		public:
			/**
			 * Constructeur
			 * @param scale Echelle de la base (taille de la surface)
			 * @param height Altitude maximale des points
			 */
			Random(const double& scale = 1., const double& height = 1.);
			/**
			 * Limites de la surface
			 * @param idx Identifiant du coin
			 * @result Coin de la surface
			 */
			vec3 base				(int idx)	const;
			/**
			 * Generation d'un point
			 * @result Point sur la surface virtuelle
			 */
			vec3 operator() ()		const;
	};

	/**
	 * Implementation de la classe Generator, surface sinusoidale
	 */
	class Sinus : public Generator
	{
			double m_f;
			double m_scale;
			double m_height;
		public:
			/**
			 * Constructeur
			 * @param f Frequence de la sinusoide
			 * @param scale Echelle de la base (taille de la surface)
			 * @param height Altitude maximale des points
			 */
			Sinus(const double& f, const double& scale = 1., const double& height = 1.);
			/**
			 * Limites de la surface
			 * @param idx Identifiant du coin
			 * @result Coin de la surface
			 */
			vec3 base				(int idx)	const;
			/**
			 * Generation d'un point
			 * @result Point sur la surface virtuelle
			 */
			vec3 operator() ()		const;
	};
	#ifdef OPENCV
	/**
	 * Implementation de la classe Generator, carte de niveaux
	 */
	class HeightMap : public Generator
	{
			cv::Mat 			m_map;
			double				m_ratio;
			double				m_scale;
			double				m_height;
			unsigned char	m_maxValue;
	
		public:
			/**
			 * Constructeur
			 * @param filename Image descriptive de la surface (niveau de gris)
			 * @param scale Echelle de la base (taille de la surface)
			 * @param height Altitude maximale des points (mise a l'echelle)
			 */
			HeightMap(const std::string& filename, const double& scale = 1., const double& height = 1.);
			~HeightMap			();
			/**
			 * Limites de la surface
			 * @param idx Identifiant du coin
			 * @result Coin de la surface
			 */
			vec3 base				(int idx)	const;
			/**
			 * Generation d'un point
			 * @result Point sur la surface virtuelle
			 */
			vec3 operator() ()		const;	
	};
	#endif
}

#endif