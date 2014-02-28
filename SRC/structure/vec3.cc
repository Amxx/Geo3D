#include "vec3.hh"

vec3::vec3()
{
	m_value[0] = 0;
	m_value[1] = 0;
	m_value[2] = 0;
}
vec3::vec3(const double& x, const double& y, const double& z)
{
	m_value[0] = x;
	m_value[1] = y;
	m_value[2] = z;
}
vec3::vec3(const vec3& cpy)
{
	m_value[0] = cpy.m_value[0];
	m_value[1] = cpy.m_value[1];
	m_value[2] = cpy.m_value[2];
}


double& vec3::x() { return m_value[0]; }
double& vec3::y() { return m_value[1]; }
double& vec3::z() { return m_value[2]; }
const double vec3::x() const { return m_value[0]; }
const double vec3::y() const { return m_value[1]; }
const double vec3::z() const { return m_value[2]; }

double vec3::aire(const vec3& pt1, const vec3& pt2) const
{
	return .5 * ((pt1.x()-x()) * (pt2.z()-z()) - (pt1.z()-z()) * (pt2.x()-x()));
}

sens vec3::orientation(const vec3& pt1, const vec3& pt2) const
{
	double a = this->aire(pt1, pt2);
	sens	o;
	if (a>0)
		o = POSITIVE;
	else if (a<0)
		o = NEGATIVE;
	else
		o = ALIGNED;
	return o;
}

bool vec3::in_circle(const vec3& pt1, const vec3& pt2, const vec3& pt3) const
{
  double adx = pt1.m_value[0] - m_value[0];
  double ady = pt1.m_value[2] - m_value[2];
  double bdx = pt2.m_value[0] - m_value[0];
  double bdy = pt2.m_value[2] - m_value[2];
  double cdx = pt3.m_value[0] - m_value[0];
  double cdy = pt3.m_value[2] - m_value[2];

  double ab_det = adx * bdy - bdx * ady;
  double bc_det = bdx * cdy - cdx * bdy;
  double ca_det = cdx * ady - adx * cdy;
  double a_lift = adx * adx + ady * ady;
  double b_lift = bdx * bdx + bdy * bdy;
  double c_lift = cdx * cdx + cdy * cdy;

  return (a_lift * bc_det + b_lift * ca_det + c_lift * ab_det) > 0.;
}

vec3 vec3::rotateX(const double& a) const
{
	return vec3( x(), y()*cos(a)-z()*sin(a), y()*sin(a)+z()*cos(a) );
}

vec3 vec3::rotateY(const double& a) const
{
	return vec3( x()*cos(a)-z()*sin(a), y(), x()*sin(a)+z()*cos(a) );
}









