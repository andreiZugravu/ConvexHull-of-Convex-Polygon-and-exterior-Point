#include "ResourceManager.h"

ResourceManager * ResourceManager::instance = nullptr;

ResourceManager::ResourceManager()
{

}


ResourceManager::~ResourceManager()
{

}

ResourceManager * ResourceManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new ResourceManager();
	}

	return instance;
}

void ResourceManager::freeResources()
{
	if (instance != nullptr)
		delete instance;
}

//getters
int ResourceManager::getNrVertices()
{
	return n;
}

sf::VertexArray ResourceManager::getVertices()
{
	return vertices;
}

sf::Vertex ResourceManager::getExteriorPoint()
{
	return A;
}

//setters
void ResourceManager::setNrVertices(int NrVertices)
{
	n = NrVertices;
}

void ResourceManager::setVertices(sf::VertexArray Vertices)
{
	vertices = Vertices;
}

void ResourceManager::setExteriorPoint(sf::Vertex ExteriorPoint)
{
	A = ExteriorPoint;
}

//other methods
void ResourceManager::addVertexToVerticesArray(sf::Vertex vertex)
{
	//add
}