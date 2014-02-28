#include "priority.hh"

using namespace Structure;

Priority::iterator						Priority::begin()					{ return container_type::begin(); 				}
Priority::const_iterator			Priority::begin() 	const	{ return container_type::begin(); 				}
Priority::iterator						Priority::end()						{ return container_type::end();						}
Priority::const_iterator			Priority::end()			const	{ return container_type::end();						}

void													Priority::clear()					{ container_type::clear();								}
bool													Priority::empty()		const	{ return container_type::empty();					}
Priority::size_type						Priority::size()		const { return container_type::size();					}

Priority::value_type&					Priority::top()						{ return container_type::front().second;	}
const Priority::value_type&		Priority::top()			const	{ return container_type::front().second;	}
Priority::key_type&						Priority::top_key()				{ return container_type::front().first;		}
const Priority::key_type&			Priority::top_key()	const	{ return container_type::front().first;		}





void Priority::push(Object* value, const double& key)
{
	int s = size();
	container_type::push_back(std::make_pair(key, value));
	if (value) value->id() = s;
	heapUp(s);
}

void Priority::update(Object* o, const double& key)
{
	assert(o && container_type::at(o->id()).second == o);
	container_type::at(o->id()).first = key;
	heap(o->id());
}

Priority::value_type Priority::pop()
{
	value_type result = container_type::front().second;
	swap(0, size()-1);
	container_type::pop_back();
	heapDown(0);
	return result;
}





void Priority::swap(int i, int j)
{
	std::swap(container_type::at(i), container_type::at(j));
	if (container_type::at(i).second) container_type::at(i).second->id() = i;
	if (container_type::at(j).second) container_type::at(j).second->id() = j;
}
void Priority::heap(int idx)
{
	if ( idx > 0 && container_type::at(idx).first > container_type::at((idx-1)/2).first)
		heapUp(idx);
	else
		heapDown(idx);
}
void Priority::heapUp(int idx)
{
	int i = idx;
	while ( i>0 && container_type::at(i).first > container_type::at((i-1)/2).first )
	{	
		swap(i, (i-1)/2);
		i = (i-1)/2;
	}
}
void Priority::heapDown(int idx)
{
	int i = idx, l = size()-1;
	while (2*i+1 <= l)
	{
		int j = 2*i+1;
		if (j < l && (container_type::at(j+1).first > container_type::at(j).first))
			j++;
		if (container_type::at(i).first > container_type::at(j).first)
			return;		
		swap(i, j);
		i = j;
	}
	
}