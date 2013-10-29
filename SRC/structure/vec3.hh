#ifndef VEC3_HH
#define VEC3_HH

#include <math.h>

enum sens
{
	POSITIVE	=		+1,
	ALIGNED		=		 0,
	NEGATIVE	=		-1
};


class vec3
{
	private:
		double m_value[3];
	
	public:
		vec3();
		vec3(const double&, const double&, const double&);
		vec3(const vec3&);

  	double& x();
  	double& y();
  	double& z();
		const double x() const;
		const double y() const;
		const double z() const;

		double	aire							(const vec3&, const vec3&) const;
		sens		orientation				(const vec3&, const vec3&) const;
		bool		in_circle					(const vec3&, const vec3&, const vec3&) const;
		
		vec3 		rotateX						(const double& theta) const;
		vec3 		rotateY						(const double& theta) const;
	
		vec3 		operator+ 				() const;
		vec3 		operator- 				() const;
		vec3&		operator+= 				(const vec3&);
		vec3&		operator-= 				(const vec3&);
		vec3&		operator*= 				(const double&);
		vec3&		operator/= 				(const double&);
		
		friend vec3	operator+ 		(const vec3&, const vec3&);
		friend vec3 operator- 		(const vec3&, const vec3&);
		friend vec3 operator* 		(const vec3&, double);
		friend vec3 operator* 		(const double&, const vec3&);
		friend vec3 operator/ 		(const vec3&, const double&);
};


inline vec3 vec3::operator+ () const { return *this;								}
inline vec3 vec3::operator- () const { return vec3(-x(),-y(),-z());	}

inline vec3& vec3::operator+= (const vec3& v)
{
  x() += v.x();
	y() += v.y();
	z() += v.z();
  return *this;
}
inline vec3& vec3::operator-= (const vec3& v)
{
  x() -= v.x();
	y() -= v.y();
	z() -= v.z();
  return *this;
}

inline vec3& vec3::operator*= (const double& a)
{
  x() *= a;
	y() *= a;
	z() *= a;
  return *this;
}
inline vec3& vec3::operator/= (const double& a)
{
  x() /= a;
	y() /= a;
	z() /= a;
  return *this;
}

inline vec3 operator+ (const vec3& u, const vec3& v)		{ return vec3(u) += v;	}
inline vec3 operator- (const vec3& u, const vec3& v)		{ return vec3(u) -= v;	}
inline vec3 operator* (const vec3& u, const double& a)	{ return vec3(u) *= a;	}
inline vec3 operator* (const double& a, const vec3& u)	{ return vec3(u) *= a;	}
inline vec3 operator/ (const vec3& u, const double& a)	{ return vec3(u) /= a;	}


#endif

