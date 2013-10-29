#ifndef VIEWER_HH
#define VIEWER_HH

#include <cstdio>
#include <GL/glut.h>

#include "geometry/triangulation.hh"


void Init(int& argc, char* argv[], int width = 800, int height = 600);
void SetMesh(Triangulation*);

void Display();
void Resize(int width, int height);

void Keyboard(unsigned char key, int x, int y);
void Special(int key, int x, int y);
void MousePush(int button, int state, int x, int y);
void MouseMove(int x, int y);

#endif