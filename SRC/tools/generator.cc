#include "generator.hh"

using namespace Generator;

vec3 Random::base	(int idx)	const
{
	double x = (idx & 1)?1.:0.;
	double y = 0.;
	double z = (idx & 2)?1.:0.;
	return vec3(x, y, z);
}
vec3 Random::operator() () const
{
	double x = drand48();
	double y = drand48();
	double z = drand48();
	return vec3(x, y, z);
}



Sinus::Sinus(const double& f) :
	m_f(f)
{
}
vec3 Sinus::base (int idx) const
{
	double x = (idx & 1)?1.:0.;
	double y = 0.;
	double z = (idx & 2)?1.:0.;
	return vec3(x, y, z);
}
vec3 Sinus::operator() () const
{
	double x = drand48();
	double z = drand48();
	double y = .5*(1.+sin(m_f*(x+z)));
	return vec3(x, y, z);
}




HeightMap::HeightMap(const std::string& filename, const double& scale) :
	m_map(cv::imread(filename, CV_LOAD_IMAGE_GRAYSCALE)),
	m_ratio((double) m_map.rows / m_map.cols),
	m_scale(scale)
{
	if (!m_map.data) { printf("\n[ERROR] could not open image file `%s`\n", filename.c_str()); exit(0); }
	m_height = 0;
	for (int i=0; i<m_map.rows; ++i)
		for (int j=0; j<m_map.cols; ++j)
			if (m_height < m_map.at<unsigned char>(i, j))
				m_height = m_map.at<unsigned char>(i, j);
}

HeightMap::~HeightMap()
{
	m_map.release();
}

vec3 HeightMap::base (int idx) const
{
	double x = (idx & 1)?1.:0.;
	double y = 0;
	double z = (idx & 2)?m_ratio:0.;
	return vec3(m_scale * x, y, m_scale * z);
}
vec3 HeightMap::operator() () const
{
	double x = drand48();
	double z = drand48();
	double y = (double) m_map.at<unsigned char>( (int) (z * m_map.rows),  (int) (x * m_map.cols));
	return vec3(	x*m_scale,
								y/m_height,
								z*m_scale*m_ratio);
}
