#pragma once
#include<vector>
class Vertex
{
public:
	unsigned int index;
	unsigned int grid_x;
	unsigned int grid_y;
	unsigned int grid_z;

	bool isSample;
	bool isSkeleton;
	std::vector<int> original_neighs;
	std::vector<int> sample_neighs;

	Vertex(void);
	~Vertex(void);


};

