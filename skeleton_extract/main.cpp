#include<iostream>
#include "Point3D.h"
#include "PointCloud.h"
int main()
{
	PointCloud* pc = new PointCloud("3_Y_noisy.ply") ;
	//PointCloud* pc = new PointCloud("maize.pcd");
	//PointCloud* pc = new PointCloud();
	//pc->read_file("maize.pcd");
	/*for(int i = 0; i < 10; i++)
	{
		std::cout << "( " << pc->points[i].x << " "
			<<pc->points[i].y << " " << pc->points[i].z << " )" << std::endl;
	}
    */
	pc->search_neighbours();
}