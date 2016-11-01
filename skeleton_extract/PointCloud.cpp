#include "PointCloud.h"


PointCloud::PointCloud(void)
{

}

PointCloud::PointCloud(std::string filename)
{
	
	read_file(filename);
	
}

PointCloud::~PointCloud(void)
{
}


void PointCloud::read_file(std::string filename)
{
	std::string postfix = filename.substr(filename.length() - 3);
	//std::cout << postfix << std::endl;
	if(postfix == "ply")
		read_PLY(filename);
	else if(postfix == "pcd")
		read_PCD(filename);
	else 
	{
		std::cout<<"The process can only read the data from the file that end with \".ply\" and \".pcd\"!"<<std::endl;
		exit(1);
	}

}
void PointCloud::read_PLY(std::string filename)
{
	//std::cout << "invoke the read_PLY " << std::endl;
	std::ifstream inFile;
	inFile.open(filename);
	const unsigned int LENGTH = 100;
	const unsigned int SIZE_LINE = 4;
	const unsigned int DATA_LINE = 11;

	char s[LENGTH];
	for(int i = 1; i < SIZE_LINE; i++)
		inFile.getline(s,LENGTH);

	//in the line  "element vertex ******"
	inFile >> s;inFile >> s;inFile >> number;

	std::cout << "Downloading "<< number <<" Points ..." << std::endl;

	points = new Point3D[number];

	float data;

	for(int i = SIZE_LINE; i < DATA_LINE; i++)
		inFile.getline(s,LENGTH);
	for(int i = 0; i < number; i++)
	{
		inFile >> data;points[i].x = data;
		inFile >> data;points[i].y = data;
		inFile >> data;points[i].z = data;	
	}

	std::cout << "Point Data Download Finished !" << std::endl;

}
void PointCloud::read_PCD(std::string filename)
{
	std::ifstream inFile;
	inFile.open(filename);
	const unsigned int LENGTH = 100;
	const unsigned int SIZE_LINE = 10;
	const unsigned int DATA_LINE = 12;

	char s[LENGTH];
	for(int i = 1; i < SIZE_LINE; i++)
		inFile.getline(s,LENGTH);
	
	//in the line  "POINTS ******"
	inFile >> s;inFile >> number;

	points = new Point3D[number];

	float data;

	std::cout << "Downloading "<< number <<" Points ..." << std::endl;

	for(int i = SIZE_LINE; i < DATA_LINE; i++)
		inFile.getline(s,LENGTH);
	for(int i = 0; i < number; i++)
	{
		inFile >> data;points[i].x = data;
		inFile >> data;points[i].y = data;
		inFile >> data;points[i].z = data;	
	}
	std::cout << "Point Data Download Finished !" << std::endl;

}

//INIT
void PointCloud::init_parameters()
{
	// count the Axis Range( (min,max) >< (x,y,z) )and default radius(RADIUS_DEFAULT)
	count_default_radius();
}


void PointCloud::sample_points()
{
	sample_points((unsigned int)(number * 0.06));
}

void PointCloud::sample_points(float ratio)
{
	sample_points((unsigned int)(number * ratio));
}

void PointCloud::sample_points(unsigned int num)
{
	if(num > number)
	{
		std::cout << "The number you give is larger than size of points !!!" << std::endl;
		exit(0);
	}

	//memory the number of sampled points
	sample_number = num;

	vertexs = new Vertex[num];
	srand(time(NULL));
	for(int i = 0; i < num; i++)
	{
		int sample_index = rand() % number;
		if(vertexs[sample_index].isSample)
		{
			i--; continue;
		}
		vertexs[i] = Vertex(i,points[sample_index]);
	}
}

void PointCloud::count_default_radius()
{
	if(number == 0)
	{
		std::cout << "The Number of Points is 0 !!! "<< std::endl;
		exit(0);
	}
	//float min_x,min_y,min_z,max_x,max_y,max_z;
	min_x = min_y = min_z =  2^10;
	max_x = max_y = max_z = - 2^10;
	for(int i = 0; i < number; i++)
	{
		if(points[i].x < min_x) min_x = points[i].x;
		if(points[i].x > max_x) max_x = points[i].x;
		if(points[i].y < min_y) min_y = points[i].y;
		if(points[i].y > max_y) max_y = points[i].y;
		if(points[i].z < min_z) min_z = points[i].z;
		if(points[i].z > max_z) max_z = points[i].z;
	}

	//default radius ,respect for 20 points in the neighbour with the default radius 
    DEFAULT_RADIUS = (max_x - min_x + max_y - min_y + max_z - min_z ) / number * 20 / 3;
	
	//std::cout << "RADIUS_DEFAULT £º" << RADIUS_DEFAULT << std::endl;

}

//Core algorithm : seach neighbour points via distance !!! 
//@parameter radius ; specify distance
void PointCloud::search_neighbours(float radius)
{
	std::map<Coordiate,std::vector<int>> Map;
	
	//grid ,make the double directory index 
	for(int i = 0; i < number; i++)
	{
	    int grid_x = (int)((points[i].x - min_x)/radius);
		int grid_y = (int)((points[i].y - min_y)/radius);
		int grid_z = (int)((points[i].z - min_z)/radius);

		Coordiate point_in_grid(grid_x,grid_y,grid_z);
		if(!Map.count(point_in_grid))
		{
			std::vector<int> vec;
			vec.push_back(i);
			Map[point_in_grid] = vec;
		}
		else Map[point_in_grid].push_back(i);
	}

	// stored the original neighbour,search by the grid_index of sample point
	for(int i = 0; i < sample_number; i++)
	{
		int grid_x = (int)((vertexs[i].point_data.x - min_x)/radius);
		int grid_y = (int)((vertexs[i].point_data.y - min_y)/radius);
		int grid_z = (int)((vertexs[i].point_data.z - min_z)/radius);
		Coordiate point_in_grid(grid_x,grid_y,grid_z);
		if(Map.count(point_in_grid))
			vertexs[i].original_neighs = std::vector<int>(Map[point_in_grid]);
		for(int j = -1; j < 2; j++)
			for(int k = -1; k < 2; k++)
				for(int l = -1; l < 2; l++)
				{
					if(j==0 && k==0 && l==0) continue;
					Coordiate point_in_grid(grid_x + j,grid_y + k,grid_z + l);
					if(Map.count(point_in_grid))
					{
						std::vector<int> search_result = Map[point_in_grid];
						for(int m = 0; m < search_result.size(); m++)
						{
							if(distance2(points[search_result[m]],vertexs[i].point_data) < radius * radius )
                                vertexs[i].original_neighs.push_back(search_result[m]);
						}
					}
						
				}
	}

}
float PointCloud::distance2(Point3D p1,Point3D p2)
{
	return (p1.x - p2.x) * (p1.x - p2.x) + 
		   (p1.y - p2.y) * (p1.y - p2.y) + 
		   (p1.z - p2.z) * (p1.z - p2.z);
}








