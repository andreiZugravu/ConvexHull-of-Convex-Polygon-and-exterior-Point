#pragma once

#include <SFML\Graphics\ConvexShape.hpp>
#include <vector>

class ResourceManager
{
	private:
		static ResourceManager * instance;

		int n;
		sf::VertexArray vertices;
		sf::Vertex A;

		ResourceManager();
		~ResourceManager();

	public:
		static ResourceManager * getInstance();
		void freeResources();

		//getters
		int getNrVertices();
		sf::VertexArray getVertices();
		sf::Vertex getExteriorPoint();

		//setters
		void setNrVertices(int NrVertices);
		void setVertices(sf::VertexArray Vertices);
		void setExteriorPoint(sf::Vertex ExteriorPoint);

		//other methods
		void addVertexToVerticesArray(sf::Vertex vertex);
};