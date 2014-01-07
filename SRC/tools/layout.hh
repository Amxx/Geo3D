#ifndef LAYOUT_HH
#define LAYOUT_HH

/**
 * \file layout.hh Gestion des disposition differentes claviers
 */

class KeyActions
{
	public:
		/**
		 * \enum Action Actions possible (deplacements)
		 */
		enum Action
		{
			FRONT,	//!< Avancer
			BACK,		//!< Reculer
			LEFT,		//!< Deplacement vers la gauche
			RIGHT,	//!< Deplacement vers la droite
			UP,			//!< Deplacement vers le haut
			DOWN		//!< Deplacement vers le bas
		};
		/**
		 * \typedef Layout
		 * Descripteurs de disposition clavier
		 */
		typedef unsigned char (*Layout) (Action);
		
		/**
		 * Pointeur vers la fonction de disposition (clavier AZERTY)
		 */
		static Layout AZERTY() { return &AZERTY_fun; }
		/**
		 * Pointeur vers la fonction de disposition (clavier QWERTY)
		 */
		static Layout QWERTY() { return &QWERTY_fun; }
	
	private:
		static unsigned char AZERTY_fun(Action a);
		static unsigned char QWERTY_fun(Action a);
};


#endif