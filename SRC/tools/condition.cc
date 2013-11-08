#include "condition.hh"

using namespace Condition;

NumberCondition::NumberCondition(priority::size_type n) : number(n)
{
}
bool NumberCondition::loop(const priority& faces) const
{
	return faces.size() < number;
}
			
			
FidelityCondition::FidelityCondition(double p) : precision(p)
{
}
bool FidelityCondition::loop(const priority& faces) const
{
	return faces.top_key() > precision;
}