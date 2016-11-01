#pragma once
#include<vector>
#include "Point3D.h"
#include "PointCloud.h"
class Vertex
{
public:
	//
	unsigned int sample_index;
	Point3D point_data;
	

	// init ture
	bool isSample;
	//init false
	bool isSkeleton;
	std::vector<int> original_neighs;
	std::vector<int> sample_neighs;

	Vertex(void);
	~Vertex(void);
	Vertex(unsigned int index,Point3D p);
};

