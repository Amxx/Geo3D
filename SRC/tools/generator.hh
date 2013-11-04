#ifndef GENERATOR_HH
#define GENERATOR_HH

#include <cstdlib>

#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "../structure/vec3.hh"


namespace Generator
{
	class Generator
	{
		public:
			virtual ~Generator			() {};
			virtual vec3 base				(int)	const = 0;
			virtual vec3 operator() () 		const = 0;
	};


	class Random : public Generator
	{
		public:
			vec3 base				(int)	const;
			vec3 operator() ()		const;
	};

	class Sinus : public Generator
	{
			double m_f;
		public:
			Sinus(const double& f = 1.);
			vec3 base				(int)	const;
			vec3 operator() ()		const;
	};

	class HeightMap : public Generator
	{
			cv::Mat 			m_map;
			double				m_ratio;
			double				m_scale;
			unsigned char	m_height;
	
		public:
			HeightMap(const std::string& filename, const double& scale = 1.);
			~HeightMap			();
			vec3 base				(int)	const;
			vec3 operator() ()		const;	
	};
}

#endif