#ifndef CONDITION_HH
#define CONDITION_HH

#include "../structure/priority.hh"

namespace Condition
{
	class	Condition
	{
		public:
			virtual ~Condition	() {}
			virtual bool loop		(const priority&) const = 0;
	};


	
	class NumberCondition : public Condition
	{
			priority::size_type number;
		public:
			NumberCondition		(priority::size_type n = 100000);
			bool loop					(const priority&) const;
	};
	class FidelityCondition : public Condition
	{
			double precision;
		public:
			FidelityCondition	(const double& p = 0.01);
			bool loop					(const priority&) const;
	};
};

#endif