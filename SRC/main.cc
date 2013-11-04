#include <iostream>
#include <cstdio>

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
	
	
	
	
	int						size =		1000000;
	std::string		path =		"";
	bool					color =		false;
	

	
	for (int i = 1; i<argc; ++i)	
	{
		if (i < argc && !strcmp(argv[i], "-truecolors"))
			color = true;
		else if (i+1 < argc && !strcmp(argv[i], "-n"))
			size = atoi(argv[++i]);
		else if (i+1 < argc && !strcmp(argv[i], "-path"))
			path = argv[++i];
		else
			printf("unknown command : %s\n", argv[i]);
	}
	
	
	
	
	
	
	Generator::Generator* gen;
	if (path.empty())	gen =		new Generator::Sinus(10.);
	else							gen =		new Generator::HeightMap(path, 10.);
	
	Palette::Palette* tone;
	if (color)				tone =	new Palette::Color();
	else							tone =	new Palette::BW();
	
	vec3 camera = 	.5 * gen->base(3); 
	
	
	
	
	
	
	
	
	gettimeofday(&t, NULL);
	timebegin = t.tv_sec + (t.tv_usec/1000000.0);
	printf("Computing points ... ");
	fflush(stdout);
	
	Triangulation* mesh = new Triangulation(size, *gen);
	
	gettimeofday(&t, NULL);
	timeend = t.tv_sec + (t.tv_usec/1000000.0);
	printf("done.\n[%lf] %ld points in mesh\n", timeend-timebegin, mesh->m_vertices.size());

	delete gen;
	
	gettimeofday(&t, NULL);
	timebegin = t.tv_sec + (t.tv_usec/1000000.0);
	printf("Computing triangulation ... ");
	fflush(stdout);
	
	mesh->triangulate();
	
	gettimeofday(&t, NULL);
	timeend = t.tv_sec + (t.tv_usec/1000000.0);
	printf("done.\n[%lf] %ld triangles in mesh\n", timeend-timebegin, mesh->m_faces.size());
	
	
	
	
	Init(argc, argv, 1600, 900);
	SetMesh(*mesh, *tone, camera);
	
	delete mesh;

	glutMainLoop();



	
	return 0;
}
