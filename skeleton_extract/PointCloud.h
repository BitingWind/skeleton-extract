#pragma once
//#include<stdio.h>
#include<iostream>
#include<string>
#include<fstream>
#include<time.h>
#include "Point3D.h"
#include "Vertex.h"
#include<map>
#include<vector>
#include<math.h>
class Coordiate
{
	int x;
	int y;
	int z;
public:
	Coordiate(void);
	Coordiate(int xx,int yy,int zz):x(xx),y(yy),z(zz)
	{

	}

	bool operator==(Coordiate other)
	{
		return x==other.x && y==other.y && z==other.z;
	}
};
class PointCloud
{
public:
	
	int number;
	int sample_number;
	Point3D* points;
	Vertex* vertexs;

	PointCloud(void);
	~PointCloud(void);

	//constructor for filename parameter 
	PointCloud(std::string filename);

	//read the point data from ".ply" or ".pcd"
	void read_file(std::string filename);

	//count the static parameters !!
	void init_parameters();

	//sample points from original points
	void sample_points();
	void sample_points(unsigned int num);
	void sample_points(float ratio);

	//default radius ,respect for 20 points in the neighbour with the default radius 
    double DEFAULT_RADIUS;

	// for function grid() more than once
	float min_x,min_y,min_z,max_x,max_y,max_z;
	
	void search_neighbours(float radius);
	
private:
	
	void read_PLY(std::string filename);
	void read_PCD(std::string filename);

	// count the Axis Range( (min,max) >< (x,y,z) )and default radius(RADIUS_DEFAULT)
	void count_default_radius();

	float distance2(Point3D p1,Point3D p2);
	//make the grids via radius 
	//void grid(float radius);
};

