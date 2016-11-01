#include "Vertex.h"


Vertex::Vertex(void)
{
}

Vertex::~Vertex(void)
{
}

Vertex::Vertex(unsigned int index,Point3D p)
{
	sample_index = index;
	point_data = Point3D(p);
	isSample = true;
}
