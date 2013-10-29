#ifndef OBJECT_HH
#define OBJECT_HH

class Object
{
		int m_id;	
		// int m_stamp;
	public:
		
		Object() : m_id(-1) {}
		// Object() : m_id(-1), m_stamp(-1) {}
			
		int& 						id() 					{ return m_id; 		}
		const int&			id() 		const	{ return m_id;		}
		// int&						stamp()				{ return m_stamp;	}
		// const int&			stamp() const { return m_stamp;	}
};

#endif
