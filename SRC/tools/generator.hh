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
			double m_scale;
			double m_height;
		public:
			Random(const double& scale = 1., const double& height = 1.);
			vec3 base				(int)	const;
			vec3 operator() ()		const;
	};

	class Sinus : public Generator
	{
			double m_f;
			double m_scale;
			double m_height;
		public:
			Sinus(const double& f, const double& scale = 1., const double& height = 1.);
			vec3 base				(int)	const;
			vec3 operator() ()		const;
	};
	#ifdef OPENCV
	class HeightMap : public Generator
	{
			cv::Mat 			m_map;
			double				m_ratio;
			double				m_scale;
			double				m_height;
			unsigned char	m_maxValue;
	
		public:
			HeightMap(const std::string& filename, const double& scale = 1., const double& height = 1.);
			~HeightMap			();
			vec3 base				(int)	const;
			vec3 operator() ()		const;	
	};
	#endif
}

#endif