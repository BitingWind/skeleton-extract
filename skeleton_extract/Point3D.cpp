#include "Point3D.h"


Point3D::Point3D(void)
{
}


Point3D::~Point3D(void)
{
}

Point3D::Point3D(double x0,double y0,double z0)
{
	x = x0;
	y = y0;
	z = z0;

}
Point3D::Point3D(const Point3D& p)
{
	x = p.x;
	y = p.y;
	z = p.z;

}

