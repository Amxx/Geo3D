#ifndef PALETTE_HH
#define PALETTE_HH

#include "../structure/vec3.hh"

/**
 * \file palette.hh Coloration des surfaces
 */

/**
 * \namespace Palette Coloration des surfaces
 */
namespace Palette
{
	/**
	 * Palette de couleur pour la colorisation de la surface 3D
   */
	class Palette
	{
		public:
			virtual ~Palette				()					{};
			/**
			 * Renvoit la couleur associé a un point d'altitude donnée.
			 * @param h Altitude
			 * @return Couleur
       */
			virtual vec3 operator() (const double& h) const = 0;
	};


	/**
	 * Implementation de la classe Palette a l'aide de niveau de gris
   */
	class BW : public Palette
	{
		public:
			/**
			 * Constructeur
			 * @param maxHeight Altitude maximal de la palette (mise a l'echelle)
		   */
			BW(const double& maxHeight = 1.);
			/**
			 * Renvoit la couleur associé a un point d'altitude donnée.
			 * @param h Altitude
			 * @return Couleur
       */
			vec3 operator() (const double& h) const;
		private:
			double m_maxHeight;
	};
	
	/**
	 * Implementation de la classe Palette a l'aide de couleur realistes
   */
	class Color : public Palette
	{
		public:
			/**
			 * Constructeur
			 * @param maxHeight Altitude maximal de la palette (mise a l'echelle)
		   */
			Color(const double& maxHeight = 1.);
			/**
			 * Renvoit la couleur associé a un point d'altitude donnée.
			 * @param h Altitude
			 * @return Couleur
       */
			vec3 operator() (const double& h) const;
		private:
			double m_maxHeight;
			static vec3 colors[21];
	};
}




#endif

