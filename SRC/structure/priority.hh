#ifndef PRIORITY_HH
#define PRIORITY_HH

#include <cassert>
#include <vector>

/**
 * \file priority.hh File de priorité
 */

/**
 * \namespace Structure Structure de données
 */
 
namespace Structure
{
	/**
	 * Objet engeristrable dans la file de priorité
	 */
	class Object
	{
			int m_id;
		public:		
			Object() : m_id(-1) 					{}			
			int& 						id() 					{ return m_id; 		}
			const int&			id() 		const	{ return m_id;		}
	};	
	
	/**
	 * File de priorité
	 */
	class Priority : private std::vector< std::pair<double, Object*> >
	{
		public:
			typedef double																					key_type;
			typedef Object*																					value_type;
			typedef std::vector< std::pair<key_type, value_type> >	container_type;
			typedef typename container_type::size_type							size_type;
			typedef typename container_type::iterator								iterator;
			typedef typename container_type::const_iterator					const_iterator;
	
		public:
			/**
			 * Iterateur sur le debut de la file de priorité
			 * \warning L'iteration ne parcours par les objet selon leur ordre de priorité
			 */
			iterator					begin();
			/**
			 * Iterateur sur le debut de la file de priorité
			 * \warning L'iteration ne parcours par les objet selon leur ordre de priorité
			 */
			const_iterator		begin() const;
			/**
			 * Iterateur sur la fin de la file de priorité
			 * \warning L'iteration ne parcours par les objet selon leur ordre de priorité
			 */
			iterator					end();
			/**
			 * Iterateur sur la fin de la file de priorité
			 * \warning L'iteration ne parcours par les objet selon leur ordre de priorité
			 */
			const_iterator		end() const;
			/**
			 * Vide la file de priorité
			 */
			void							clear();
			/**
			 * Test si la file de priorité
			 */
			bool							empty() const;
			/**
			 * Taille de la file de priorité
			 */
			size_type					size() const;
			/**
			 * Objet en tête
			 * @result Tête de la file de priorité
			 */
			value_type&				top();
			/**
			 * Objet en tête
			 * @result Tête de la file de priorité
			 */
			const value_type&	top() const;
			/**
			 * Priorité de l'objet en tête
			 * @result Valeur de priorité de l'objet en tête
			 */
			key_type&					top_key();
			/**
			 * Priorité de l'objet en tête
			 * @result Valeur de priorité de l'objet en tête
			 */
			const key_type&		top_key() const;
			/**
			 * Ajout d'un objet
			 * @param o Objet à ajouter
			 * @param key Valeur de priorité de l'objet
			 */
			void							push(Object* o, const double& key);
			/**
			 * Mise a jour d'un objet
			 * @param o Objet à mettre a jour
			 * @param key Nouvelle valeur de priorité
			 */
			void							update(Object* o, const double& key);
			/**
			 * Depilement de l'objet en tête
			 * @result Tête de la file de priorité
			 */
			value_type				pop();
		
		private:
			void							swap(int, int);
			void							heap(int);
			void							heapUp(int);
			void							heapDown(int);
	
	};
};
#endif