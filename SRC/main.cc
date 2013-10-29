#include <iostream>
#include <cstdio>

#include <time.h>
#include <sys/time.h>



#include "viewer.hh"
#include "geometry/triangulation.hh"
#include "tools/generator.hh"




int main(int argc, char* argv[])
{
	
	srand(time(NULL));
	
	struct timeval t;
	double timebegin, timeend;
	
	
	
	
	int					size = 1000000;
	std::string	path = "";
	
	// gen	= new HeightMap("DATA/Srtm_ramp2.world.21600x10800.jpg", 10.);
	// gen	=	new HeightMap("DATA/uk.png", 10.);
	// gen	=	new HeightMap("DATA/ireland.png", 10.);
	// gen	=	new HeightMap("DATA/BW_DTED_small.png", 10.);
	
	for (int i = 1; i<argc; ++i)	
	{
		if (i+1 < argc && !strcmp(argv[i], "-n"))
			size = atoi(argv[++i]);
		else if (i+1 < argc && !strcmp(argv[i], "-path"))
			path = argv[++i];
		else
			printf("unknown command : %s\n", argv[i]);
	}
	
	
	Generator* gen;
	if (path.empty())	gen = new Sinus(10.);
	else							gen = new HeightMap(path, 10.);
	
	
	
	gettimeofday(&t, NULL);
	timebegin = t.tv_sec + (t.tv_usec/1000000.0);
	printf("Computing points ... ");
	
	Triangulation* mesh = new Triangulation(size, *gen);
	
	gettimeofday(&t, NULL);
	timeend = t.tv_sec + (t.tv_usec/1000000.0);
	printf("done.\n[%lf] %ld points in mesh\n", timeend-timebegin, mesh->m_vertices.size());

	delete gen;
	
	
	gettimeofday(&t, NULL);
	timebegin = t.tv_sec + (t.tv_usec/1000000.0);
	printf("Computing triangulation ... ");
	
	mesh->triangulate();
	
	gettimeofday(&t, NULL);
	timeend = t.tv_sec + (t.tv_usec/1000000.0);
	printf("done.\n[%lf] %ld triangles in mesh\n", timeend-timebegin, mesh->m_faces.size());
	
	
	
	

	Init(argc, argv, 1600, 900);
	SetMesh(mesh);
	
	delete mesh;
  
	glutMainLoop();



	
	return 0;
}
