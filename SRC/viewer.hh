#ifndef VIEWER_HH
#define VIEWER_HH

#include <cstdio>
#include <GL/glut.h>

#include "geometry/triangulation.hh"
#include "tools/palette.hh"
#include "tools/layout.hh"

/**
 * \file viewer.hh Fonctions d'affichage et de deplacement de la surface 3D
 */


/**
 * Initialisation de la fenetre graphique
 * @param argc
 * @param argv
 * @param width		Largeur de la fenetre graphique
 * @param height 	Hauteur de la fenetre graphique
 */
void Init(int& argc,
					char* argv[],
					int width = 800,
					int height = 600);
/**
 * Calcul des maillages pour une triangulation
 * @param mesh		Triangulation de la surface
 * @param tone		Palette pour la coloration de la surface
 * @param c				Position initiale de la camera
 */
void SetMesh(	const Geometry::Triangulation& mesh,
							const Palette::Palette& tone = Palette::BW(),
							vec3 c = vec3());
/**
 * Affchage des maillages
 */
void Display();
/**
 * Redimentionnement de la fenetre graphique
 * @param width		Nouvelle largeur
 * @param height	Nouvelle hauteur
 */
void Resize(int width, int height);
/**
 * Modification de la disposition clavier
 * @param l				Disposition clavier à utiliser
 */
void Keyboard_setLayout(KeyActions::Layout l);
/**
 * Action clavier
 */
void Keyboard(unsigned char key, int x, int y);
/**
 * Action clavier speciales
 */
void Special(int key, int x, int y);
/**
 * Action souris
 */
void MousePush(int button, int state, int x, int y);
/**
 * Deplacement souris
 */
void MouseMove(int x, int y);

#endif