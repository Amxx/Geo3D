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
	
	
	
	
	int																	vertexNumber		= 100000;
	double															scale						=	10.;
	double															height					= 1.;
	int																	generatorID			= 0;
	std::string													path						= "";
	bool																color						= false;
	
	
	Condition::Condition_set						limitations;
	
	for (int i = 1; i<argc; ++i)	
	{

		if (i < argc && !strcmp(argv[i], "-help"))
		{
			printf("================== Geo3D - A simple terrain viewer ==================\n");
			printf("Usage: %s [options]                                                  \n", argv[0]);
			printf("    -truecolors              	    Affichage en couleurs reelles      \n");
			printf("  generation de points :                                             \n");
			printf("    -generator=sinus                                                 \n");
			printf("    -generator=rand                                                  \n");
			printf("    -generator=greyscale <path>   Path to greyscale image used       \n");
			printf("                                	to generate the points             \n");
			printf("    -n <int>                      Nombre de points a cree            \n");
			printf("    -scale <float>                Taille de la zone de tracé         \n");
			printf("    -height <float>               Hauteur de la zone de tracé        \n");
			printf("                                                                     \n");
			printf("  conditions d'arret :                                               \n");
			printf("    -stop=triangle <int>          Nombre de triangle a construire    \n");
			printf("    -stop=precision <float>       Precision a atteinder (ecart max)  \n");
			printf("                                                                     \n");
			printf("  compatibilité :                                                    \n");
			printf("    -layout=[azerty|qwerty]       Disposition clavier                \n");
			printf("=====================================================================\n");
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
		// --------------------------------------------------
		else if (i < argc && !strcmp(argv[i], "-generator=sinus"))
		{
			generatorID = 0;
		}
		else if (i < argc && !strcmp(argv[i], "-generator=random"))
		{
			generatorID = 1;
		}
		else if (i+1 < argc && !strcmp(argv[i], "-generator=greyscale"))
		{
			generatorID = 2;
			path = argv[++i];
		}
		// --------------------------------------------------
		else if (i+1 < argc && !strcmp(argv[i], "-stop=triangle"))
		{
			limitations.push_back(new Condition::NumberCondition(atoi(argv[++i])));
		}
		else if (i+1 < argc && !strcmp(argv[i], "-stop=precision"))
		{
			limitations.push_back(new Condition::FidelityCondition(atof(argv[++i])));
		}
		// --------------------------------------------------
		else if (i < argc && !strcmp(argv[i], "-layout=azerty"))
		{
			Keyboard_setLayout(KeyActions::AZERTY());
		}
		else if (i < argc && !strcmp(argv[i], "-layout=qwerty"))
		{
			Keyboard_setLayout(KeyActions::QWERTY());
		}
		// --------------------------------------------------
		else
			printf("unknown command : %s\n", argv[i]);
	}
	
	
	
	
	if (limitations.empty())
		limitations.push_back(new Condition::FidelityCondition());
	
	Generator::Generator* generator;
	switch (generatorID)
	{
		case 1:
			generator = new Generator::Random(scale, height);
			break;
		case 2:
			#ifdef OPENCV
			if (!path.empty())
				generator		= new Generator::HeightMap(path, scale, height);
			else
				generator		= new Generator::Sinus(10., scale, height);
			break;
			#else
			if (!path.empty()) printf("[ERROR] Couldn't load image, OpenCV module isn't compiled\n");
			#endif
		default:
			generator = new Generator::Sinus(10., scale, height);
			break;
	}
	
	Palette::Palette* tone;
	if (color)				tone	= new Palette::Color(height);
	else							tone	= new Palette::BW(height);
	
	vec3 camera = 	.5 * generator->base(3); 
	
	
	
	
	
	
	
	
	gettimeofday(&t, NULL);
	timebegin = t.tv_sec + (t.tv_usec/1000000.0);
	printf("Computing points ... ");
	fflush(stdout);
	
	Geometry::Triangulation* mesh = new Geometry::Triangulation(vertexNumber, *generator);
	
	gettimeofday(&t, NULL);
	timeend = t.tv_sec + (t.tv_usec/1000000.0);
	printf("done.\n[%lf] %ld points in mesh\n", timeend-timebegin, mesh->m_vertices.size());

	gettimeofday(&t, NULL);
	timebegin = t.tv_sec + (t.tv_usec/1000000.0);
	printf("Computing triangulation ... ");
	fflush(stdout);
	
	mesh->triangulate(limitations);
	
	gettimeofday(&t, NULL);
	timeend = t.tv_sec + (t.tv_usec/1000000.0);
	printf("done.\n[%lf] %ld triangles in mesh\n", timeend-timebegin, mesh->m_faces.size());
	
	
	
	
	Init(argc, argv, 1600, 900);
	SetMesh(*mesh, *tone, camera);

	delete generator;
	delete mesh;
	delete tone;

	glutMainLoop();



	
	return 0;
}
