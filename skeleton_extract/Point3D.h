#pragma once
class Point3D
{
public:
	double x,y,z;
	Point3D(void);
	~Point3D(void);
	Point3D(double x0,double y0,double z0);
	Point3D(const Point3D& p);
	//double dist(const Point3D& p);
};

