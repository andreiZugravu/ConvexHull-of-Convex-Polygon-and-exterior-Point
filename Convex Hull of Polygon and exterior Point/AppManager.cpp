#include "AppManager.h"
#include <iostream>
#include "ResourceManager.h"

AppManager * AppManager::instance = nullptr;

AppManager::AppManager()
{

}


AppManager::~AppManager()
{

}

AppManager * AppManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new AppManager;
	}

	return instance;
}

void AppManager::freeResources()
{
	if (instance != nullptr)
	{
		delete instance;
	}
}

void AppManager::solve()
{
	//step 0 : prepare resources
	//get number of vertices
	int n = ResourceManager::getInstance()->getNrVertices();
	//get points
	std::vector < Point > points = ResourceManager::getInstance()->getPoints();
	//get exterior points
	Point A = ResourceManager::getInstance()->getExteriorPoint();

	//step 1 : get closest vertex to A
	std::cout << n << "\n";
	for (Point p : points)
	{
		std::cout << p.x << " " << p.y << "\n";
	}

	std::cout << "A : " << A.x << " " << A.y;
}