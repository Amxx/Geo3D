#include "priority.hh"

priority::iterator						priority::begin()					{ return container_type::begin(); 				}
priority::const_iterator			priority::begin() 	const	{ return container_type::begin(); 				}
priority::iterator						priority::end()						{ return container_type::end();						}
priority::const_iterator			priority::end()			const	{ return container_type::end();						}

void													priority::clear()					{ container_type::clear();								}
bool													priority::empty()		const	{ return container_type::empty();					}
priority::size_type						priority::size()		const { return container_type::size();					}

priority::value_type&					priority::top()						{ return container_type::front().second;	}
const priority::value_type&		priority::top()			const	{ return container_type::front().second;	}
priority::key_type&						priority::top_key()				{ return container_type::front().first;		}
const priority::key_type&			priority::top_key()	const	{ return container_type::front().first;		}





void priority::push(Object* value, const double& key)
{
	int s = size();
	container_type::push_back(std::make_pair(key, value));
	if (value) value->id() = s;
	heapUp(s);
}

void priority::update(Object* o, const double& key)
{
	assert(o && container_type::at(o->id()).second == o);
	container_type::at(o->id()).first = key;
	heap(o->id());
}

void priority::pop()
{
	swap(0, size()-1);
	container_type::pop_back();
	heapDown(0);
}









void priority::swap(int i, int j)
{
	std::swap(container_type::at(i), container_type::at(j));
	if (container_type::at(i).second) container_type::at(i).second->id() = i;
	if (container_type::at(j).second) container_type::at(j).second->id() = j;
}
void priority::heap(int idx)
{
	if ( idx > 0 && container_type::at(idx).first > container_type::at((idx-1)/2).first)
		heapUp(idx);
	else
		heapDown(idx);
}
void priority::heapUp(int idx)
{
	int i = idx;
	while ( i>0 && container_type::at(i).first > container_type::at((i-1)/2).first )
	{	
		swap(i, (i-1)/2);
		i = (i-1)/2;
	}
}
void priority::heapDown(int idx)
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