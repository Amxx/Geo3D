#include "viewer.hh"

static vec3			camera_position;
static double 	camera_orientation_x	=	60.;
static double 	camera_orientation_y	=	0.;

static int			mouse_status					= 0;
static int			mouse_x;
static int			mouse_y;

static GLuint		points;
static GLuint		maillage2D;
static GLuint		maillage3D;
static GLuint		surface;
static int			display								= 0x00000001;




static vec3 inCamera(const vec3& p)
{
// double thetaX = -M_PI*camera_orientation_x/180;
	double thetaY =  M_PI*camera_orientation_y/180;
// return p.rotateX(thetaX).rotateY(thetaY);
	return p.rotateY(thetaY);
}

static void check_camera()
{
	if (camera_orientation_x > +90) camera_orientation_x = +90;
	if (camera_orientation_x < -90) camera_orientation_x = -90;
}

inline void glColorVec3(const vec3& v)			{	glColor3f(v.x(),	v.y(),			v.z());			}
inline void glVertexVec3D(const vec3& v)		{	glVertex3d(v.x(), 0.2* v.y(),	v.z());			}
inline void glVertexVec2D(const vec3& v)		{	glVertex3d(v.x(), 0., 				v.z());			}







void Init(int& argc, char* argv[], int width, int height)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA | GLUT_DEPTH);

	glutInitWindowSize(width, height);  
	glutInitWindowPosition(50, 50);  
	glutCreateWindow("Geo3D - By Hadrien Croubois");
	
	glutDisplayFunc(Display);
	glutReshapeFunc(Resize);
	
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);
	glutMouseFunc(MousePush);
	glutMotionFunc(MouseMove);

	glClearColor (0.2, 0.3, 0.4, 1.0);
	glClearDepth(1.0);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glShadeModel(GL_SMOOTH);

	Resize(width, height);
}


void SetMesh(const Triangulation& mesh, const Palette::Palette& tone, vec3 c)
{	
	camera_position = vec3(0., 2., 1.) + c;
	
	surface = glGenLists(1);
	glNewList(surface, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	#ifdef CPP11
	for (Face* face : mesh.m_faces)
	{
		glColorVec3(tone(face->vertex(0)->y()));	glVertexVec3D(*face->vertex(0));
		glColorVec3(tone(face->vertex(1)->y()));	glVertexVec3D(*face->vertex(1));
		glColorVec3(tone(face->vertex(2)->y()));	glVertexVec3D(*face->vertex(2));
	}
	#else
	for (std::vector<Face*>::const_iterator it = mesh.m_faces.begin(); it != mesh.m_faces.end(); ++it)
	{
		glColorVec3(tone((*it)->vertex(0)->y()));	glVertexVec3D(*(*it)->vertex(0));
		glColorVec3(tone((*it)->vertex(1)->y()));	glVertexVec3D(*(*it)->vertex(1));
		glColorVec3(tone((*it)->vertex(2)->y()));	glVertexVec3D(*(*it)->vertex(2));
	}
	#endif
	glEnd();
	glEndList();
	
	maillage2D = glGenLists(1);
	glNewList(maillage2D, GL_COMPILE);
	#ifdef CPP11
	for (Face* face : mesh.m_faces)
	{
		glBegin(GL_LINE_LOOP);
		glColorVec3(tone(face->vertex(0)->y()));	glVertexVec2D(*face->vertex(0));
		glColorVec3(tone(face->vertex(1)->y()));	glVertexVec2D(*face->vertex(1));
		glColorVec3(tone(face->vertex(2)->y()));	glVertexVec2D(*face->vertex(2));
		glEnd();
	}
	#else
	for (std::vector<Face*>::const_iterator it = mesh.m_faces.begin(); it != mesh.m_faces.end(); ++it)
	{
		glBegin(GL_LINE_LOOP);
		glColorVec3(tone((*it)->vertex(0)->y()));	glVertexVec2D(*(*it)->vertex(0));
		glColorVec3(tone((*it)->vertex(1)->y()));	glVertexVec2D(*(*it)->vertex(1));
		glColorVec3(tone((*it)->vertex(2)->y()));	glVertexVec2D(*(*it)->vertex(2));
		glEnd();
	}
	#endif
  glEndList();

	maillage3D = glGenLists(1);
	glNewList(maillage3D, GL_COMPILE);
	#ifdef CPP11
	for (Face* face : mesh.m_faces)
	{
		glBegin(GL_LINE_LOOP);
		glColorVec3(tone(face->vertex(0)->y()));	glVertexVec3D(*face->vertex(0));
		glColorVec3(tone(face->vertex(1)->y()));	glVertexVec3D(*face->vertex(1));
		glColorVec3(tone(face->vertex(2)->y()));	glVertexVec3D(*face->vertex(2));
		glEnd();
	}
	#else
	for (std::vector<Face*>::const_iterator it = mesh.m_faces.begin(); it != mesh.m_faces.end(); ++it)
	{
		glBegin(GL_LINE_LOOP);
		glColorVec3(tone((*it)->vertex(0)->y()));	glVertexVec3D(*(*it)->vertex(0));
		glColorVec3(tone((*it)->vertex(1)->y()));	glVertexVec3D(*(*it)->vertex(1));
		glColorVec3(tone((*it)->vertex(2)->y()));	glVertexVec3D(*(*it)->vertex(2));
		glEnd();
	}
	#endif
  glEndList();
	
	points = glGenLists(1);
	glNewList(points, GL_COMPILE);
	glBegin(GL_POINTS);
	#ifdef CPP11
	for (Vertex* vertex : mesh.m_vertices)
	{
		glColorVec3(tone(vertex->y()));
		glVertexVec3D(*vertex);
	}
	#else
	for (std::vector<Vertex*>::const_iterator it = mesh.m_vertices.begin(); it != mesh.m_vertices.end(); ++it)
	{
		glColorVec3(tone((*it)->y()));
		glVertexVec3D(*(*it));
	}	
	#endif
  glEnd();
  glEndList();
	
}

void Display()
{
	glColor3f(0., 0., 0.);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
	glRotatef(camera_orientation_x, 1.0, 0.0, 0.0);
	glRotatef(camera_orientation_y, 0.0, 1.0, 0.0);
	glTranslatef(-camera_position.x(), -camera_position.y(), -camera_position.z());
	
	if (display & 0x00000001)	glCallList(surface);
	if (display & 0x00000002)	glCallList(points);
	if (display & 0x00000004)	glCallList(maillage2D);
	if (display & 0x00000008)	glCallList(maillage3D);
	
	glutSwapBuffers();
}

void Resize(int width, int height)
{
	if (height==0) height=1;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
  glLoadIdentity();  
  gluPerspective(90.0, (GLfloat)width/(GLfloat)height, 0.01, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{		
		case 27: exit(0);
		case 'q': camera_position -= inCamera(vec3(0.1, 0.0, 0.0)); break;
		case 'd': camera_position += inCamera(vec3(0.1, 0.0, 0.0)); break;
		case 'f':	camera_position -= inCamera(vec3(0.0, 0.1, 0.0)); break;
		case 'r': camera_position += inCamera(vec3(0.0, 0.1, 0.0)); break;
		case 'z': camera_position -= inCamera(vec3(0.0, 0.0, 0.1)); break;
		case 's': camera_position += inCamera(vec3(0.0, 0.0, 0.1)); break;
		// default: printf("-- unmapped key : %d\n", key); break;
		default: break;
	}
	glutPostRedisplay();
}

void Special(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_F1:			display = display xor 0x00000001;						break;
		case GLUT_KEY_F2:			display = display xor 0x00000002;						break;
		case GLUT_KEY_F3:			display = display xor 0x00000004;						break;
		case GLUT_KEY_F4:			display = display xor 0x00000008;						break;
		
		case GLUT_KEY_LEFT:		camera_orientation_y -= 1; 									break;
		case GLUT_KEY_RIGHT:	camera_orientation_y += 1; 									break;
		case GLUT_KEY_DOWN:		camera_orientation_x -= 1; check_camera();	break;
		case GLUT_KEY_UP:			camera_orientation_x += 1; check_camera();	break;
		default: break;
	}
	glutPostRedisplay();
}

void MousePush(int button, int state, int x, int y)
{
	mouse_status = (button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN);
	mouse_x = x;
	mouse_y = y;
}

void MouseMove(int x, int y)
{
	if (mouse_status)
	{
		camera_orientation_y += 0.1 * (mouse_x-x);
		camera_orientation_x += 0.1 * (mouse_y-y);
		check_camera();
		mouse_x = x;
		mouse_y = y;
		glutPostRedisplay();
	}
}









