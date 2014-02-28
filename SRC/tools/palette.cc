#include "palette.hh"

using namespace Palette;

vec3 Color::colors[21] = {	vec3(121, 178, 222),
														vec3(172, 208, 165),
														vec3(148, 191, 139),
														vec3(168, 198, 143),
														vec3(189, 204, 150),
														vec3(209, 215, 171),
														vec3(225, 228, 181),
														vec3(239, 235, 192),
														vec3(232, 225, 182),
														vec3(222, 214, 163),
														vec3(211, 202, 157),
														vec3(202, 185, 130),
														vec3(195, 167, 107),
														vec3(185, 152,  90),
														vec3(170, 135,  83),
														vec3(172, 154, 124),
														vec3(186, 174, 154),
														vec3(202, 195, 184),
														vec3(224, 222, 216),
														vec3(245, 244, 242),
														vec3(255, 255, 255)		};
				
														
BW::BW(const double& maxHeight) :
	m_maxHeight(maxHeight)
{
}
vec3 BW::operator() (const double& h) const
{
	return vec3(h/m_maxHeight, h/m_maxHeight, h/m_maxHeight);
}


Color::Color(const double& maxHeight) :
	m_maxHeight(maxHeight)
{
}
vec3 Color::operator() (const double& h) const
{
	return colors[(int) (20.*h/m_maxHeight)] / 255.;
}
