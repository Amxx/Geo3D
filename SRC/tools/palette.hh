#ifndef PALETTE_HH
#define PALETTE_HH

#include "../structure/vec3.hh"

namespace Palette
{

	class Palette
	{
		public:
			virtual ~Palette				()					{};
			virtual vec3 operator() (double& h) const = 0;
	};


	class BW : public Palette
	{
		public:
			vec3 operator() (double& h) const;
	};
	class Color : public Palette
	{
		public:
			vec3 operator() (double& h) const;
		private:
			static vec3 colors[20];
	};
}




#endif

