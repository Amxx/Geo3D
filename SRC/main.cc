#include <iostream>
#include <cstdio>

#include <string.h>
#include <time.h>
#include <sys/time.h>



#include "viewer.hh"
#include "geometry/triangulation.hh"
#include "tools/generator.hh"
#include "tools/palette.hh"





int main(int argc, char* argv[])
{
	
	srand(time(NULL));
	
	struct timeval t;
	double timebegin, timeend;
	
	
	
	
	int						vertexNumber		= 1000000;
	double				scale						=	10.;
	double				height					= 1.;
	
	int						triangleNumber	= 100000;
	double				precision				= 0.01;
	int						conditionType		= -1;
	
	std::string		path						= "";
	bool					color						= false;
	

	
	for (int i = 1; i<argc; ++i)	
	{

		if (i < argc && !strcmp(argv[i], "-help"))
		{
			printf("============== Geo3D - A simple terrain viewer ==============\n");
			printf("Usage: %s [options]                                          \n", argv[0]);
			printf("    -truecolors           Affichage en couleurs reelles      \n");
			printf("  generation de points :                                     \n");
			printf("    -n <int>              Nombre de points a cree            \n");
			printf("    -scale <float>        Taille de la zone de tracé         \n");
			printf("    -height <float>       Hauteur de la zone de tracé        \n");
			printf("    -input <path>         Path to greyscale image used       \n");
			printf("                          to generate the points             \n");
			printf("  conditions d'arret :                                       \n");
			printf("    -triangle <int>       Nombre de triangle a construire    \n");
			printf("    -precision <float>    Precision a atteinder (ecart max)  \n");
			printf("=============================================================\n");
			return 0;
		}
		// --------------------------------------------------
		else if (i < argc && !strcmp(argv[i], "-truecolors"))
		{
			color = true;
		}
		// --------------------------------------------------
		else if (i+1 < argc && !strcmp(argv[i], "-n"))
		{
			vertexNumber = atoi(argv[++i]);
		}
		else if (i+1 < argc && !strcmp(argv[i], "-scale"))
		{
			scale = atof(argv[++i]);
		}
		else if (i+1 < argc && !strcmp(argv[i], "-height"))
		{
			height = atof(argv[++i]);
		}
		else if (i+1 < argc && !strcmp(argv[i], "-input"))
		{
			path = argv[++i];
		}
		// --------------------------------------------------
		else if (i+1 < argc && !strcmp(argv[i], "-triangles"))
		{
			triangleNumber = atoi(argv[++i]);
			conditionType = 0;
		}
		else if (i+1 < argc && !strcmp(argv[i], "-precision"))
		{
			precision = atof(argv[++i]);
			conditionType = 1;
		}
		// --------------------------------------------------
		else
			printf("unknown command : %s\n", argv[i]);
	}
	
	
	
	
	
	
	Generator::Generator* gen;
	#ifdef OPENCV
	if (path.empty())	gen		= new Generator::Sinus(10., scale, height);
	else							gen		= new Generator::HeightMap(path, scale, height);
	#else
	if (!path.empty()) printf("[ERROR] Couldn't load image, OpenCV module isn't compiled\n");
	gen		= new Generator::Sinus(scale);
	#endif
	
	Condition::Condition* cond;
	switch (conditionType)
	{
		case 0:
			cond = new Condition::NumberCondition(triangleNumber);
			break;
		case 1:
			cond = new Condition::FidelityCondition(precision);
			break;
		default:
			cond = new Condition::FidelityCondition();
			break;
	}
	
	Palette::Palette* tone;
	if (color)				tone	= new Palette::Color(height);
	else							tone	= new Palette::BW(height);
	
	vec3 camera = 	.5 * gen->base(3); 
	
	
	
	
	
	
	
	
	gettimeofday(&t, NULL);
	timebegin = t.tv_sec + (t.tv_usec/1000000.0);
	printf("Computing points ... ");
	fflush(stdout);
	
	Triangulation* mesh = new Triangulation(vertexNumber, *gen);
	
	gettimeofday(&t, NULL);
	timeend = t.tv_sec + (t.tv_usec/1000000.0);
	printf("done.\n[%lf] %ld points in mesh\n", timeend-timebegin, mesh->m_vertices.size());

	gettimeofday(&t, NULL);
	timebegin = t.tv_sec + (t.tv_usec/1000000.0);
	printf("Computing triangulation ... ");
	fflush(stdout);
	
	mesh->triangulate(*cond);
	
	gettimeofday(&t, NULL);
	timeend = t.tv_sec + (t.tv_usec/1000000.0);
	printf("done.\n[%lf] %ld triangles in mesh\n", timeend-timebegin, mesh->m_faces.size());
	
	
	
	
	Init(argc, argv, 1600, 900);
	SetMesh(*mesh, *tone, camera);

	delete gen;
	delete mesh;
	delete cond;
	delete tone;

	glutMainLoop();



	
	return 0;
}
