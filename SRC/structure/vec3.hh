#ifndef VEC3_HH
#define VEC3_HH

#include <math.h>

/**
 * \file vec3.hh Vecteur en dimension 3
 */

/**
 * \enum sens Decription d'orientation
 */
enum sens
{
	POSITIVE	=		+1,	//!< Sens positif
	ALIGNED		=		 0,	//!< Aligné
	NEGATIVE	=		-1	//!< Sens negatif
};

	
/**
 * Vecteur en dimension 3
 */
class vec3
{

	private:
		double m_value[3];	//!< Coordonnées du vecteur
	
	public:
		/**
		 * Constructeur
		 */
		vec3();
		/**
		 * Constructeur
		 */
		vec3(const double& x, const double& y, const double& z);
		/**
		 * Constructeur par copie
		 */
		vec3(const vec3& cpy);

		/** Acces a la premiere composante du vecteur */
  	double& x();
  	/** Acces a la seconde composante du vecteur */
  	double& y();
  	/** Acces a la troisieme composante du vecteur */
  	double& z();
		/** Acces a la premiere composante du vecteur */
  	const double x() const;
		/** Acces a la seconde composante du vecteur */
  	const double y() const;
		/** Acces a la troisieme composante du vecteur */
  	const double z() const;

		/**
		 * Aire signé du triangle formé par deux autres points
		 * @param pt1 Point
		 * @param pt2 Point
		 * @result Aire du triangle (self, pt1, pt2)
		 */
		double	aire							(const vec3& pt1, const vec3& pt2) const;
		/**
		 * Orientation de l'angle formé par deux autres points
 		 * @param pt1 Point
		 * @param pt2 Point
		 * @result Orientation de l'angle (pt1, self, pt2)
		 */
		sens		orientation				(const vec3& pt1, const vec3& pt2) const;
		/** 
		 * Prédicat d'apparenance a un triangle décrit par 3 points
		 * @param pt1 Point
		 * @param pt2 Point
		 * @param pt3 Point
		 * @result Le point (self) est il dans le cercle passant par les points pt1, pt2 pt3
		 */
		bool		in_circle					(const vec3& pt1, const vec3& pt2, const vec3& pt3) const;
		
		/**
		 * Rotation autour de l'axe Ox
		 * @param theta Angle de rotation
		 */
		vec3 		rotateX						(const double& theta) const;
		/**
		 * Rotation autour de l'axe Oy
		 * @param theta Angle de rotation
		 */
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

