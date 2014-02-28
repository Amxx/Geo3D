#include "condition.hh"
#include "../geometry/triangulation.hh"

using namespace Condition;

bool Condition_set::loop(const Geometry::Triangulation& tri) const
{
	if (tri.m_priority.empty())
		return false;
	#ifdef CPP11
	for (Condition* cd : *this)
		if (!cd->loop(tri))
			return false;
	#else
	for (std::vector<Condition*>::const_iterator it = this->begin(); it != this->end(); ++it)
		if (!(*it)->loop(tri))
			return false;
	#endif
	return true;
}


NumberCondition::NumberCondition(Structure::Priority::size_type n) : number(n)
{
}
bool NumberCondition::loop(const Geometry::Triangulation& tri) const
{
	return tri.m_faces.size() < number;
}
			
			
FidelityCondition::FidelityCondition(const double& p) : precision(p)
{
}
bool FidelityCondition::loop(const Geometry::Triangulation& tri) const
{
	return tri.m_priority.top_key() >= precision;
}