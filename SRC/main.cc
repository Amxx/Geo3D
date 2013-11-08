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
	int						triangleNumber	= 100000;
	double				precision				= 0.01;
	int						conditionType		= -1;
	std::string		path						= "";
	bool					color						= false;
	

	
	for (int i = 1; i<argc; ++i)	
	{

		if (i+1 < argc && !strcmp(argv[i], "-n"))
		{
			vertexNumber = atoi(argv[++i]);
		}
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
		else if (i+1 < argc && !strcmp(argv[i], "-path"))
		{
			path = argv[++i];
		}
		else if (i < argc && !strcmp(argv[i], "-truecolors"))
		{
			color = true;
		}
		else
			printf("unknown command : %s\n", argv[i]);
	}
	
	
	
	
	
	
	Generator::Generator* gen;
	#ifdef OPENCV
	if (path.empty())	gen		= new Generator::Sinus(10.);
	else							gen		= new Generator::HeightMap(path, 10.);
	#else
	if (!path.empty()) printf("[ERROR] Couldn't load image, OpenCV module isn't compiled\n");
	gen		= new Generator::Sinus(10.);
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
	if (color)				tone	= new Palette::Color();
	else							tone	= new Palette::BW();
	
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
