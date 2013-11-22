#ifndef PALETTE_HH
#define PALETTE_HH

#include "../structure/vec3.hh"

namespace Palette
{

	class Palette
	{
		public:
			virtual ~Palette				()					{};
			virtual vec3 operator() (const double& h) const = 0;
	};


	class BW : public Palette
	{
		public:
			BW(const double& maxHeight = 1.);
			vec3 operator() (const double& h) const;
		private:
			double m_maxHeight;
	};
	
	class Color : public Palette
	{
		public:
			Color(const double& maxHeight = 1.);
			vec3 operator() (const double& h) const;
		private:
			double m_maxHeight;
			static vec3 colors[21];
	};
}




#endif

