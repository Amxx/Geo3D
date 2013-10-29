#ifndef PRIORITY_HH
#define PRIORITY_HH

#include <cassert>

#include <vector>
#include "object.hh"


class priority : private std::vector<std::pair<double, Object*>>
{
	public:
	
		typedef double																				key_type;
		typedef Object*																				value_type;
		typedef std::vector<std::pair<key_type, value_type>>	container_type;
		typedef typename container_type::size_type						size_type;
		typedef typename container_type::iterator							iterator;
		typedef typename container_type::const_iterator				const_iterator;
	
	public:
			
		iterator					begin();
		const_iterator		begin() const;
		iterator					end();
		const_iterator		end() const;
		
		void							clear();
		bool							empty() const;
		size_type					size() const;
		
		value_type&				top();
		const value_type&	top() const;
		key_type&					top_key();
		const key_type&		top_key() const;
	
		void							push(Object*, const double&);
		void							update(Object*, const double&);
		void							pop();
	
	private:
		void							swap(int, int);
		void							heap(int);
		void							heapUp(int);
		void							heapDown(int);
	
};

#endif