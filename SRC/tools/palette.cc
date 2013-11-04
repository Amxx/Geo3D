#include "palette.hh"

using namespace Palette;

vec3 Color::colors[20] = {	vec3(121, 178, 222),
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
														vec3(245, 244, 242)		};
				
vec3 BW::operator() (double& h) const
{
	return vec3(h, h, h);
}

vec3 Color::operator() (double& h) const
{
	return colors[(int) (h*20)] / 255.;
}
