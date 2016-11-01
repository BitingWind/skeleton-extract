#pragma once
class Point3D
{
public:
	float x,y,z;
	Point3D(void);
	~Point3D(void);
	Point3D(float x0,float y0,float z0);
	Point3D(const Point3D& p);
	//double dist(const Point3D& p);
};

