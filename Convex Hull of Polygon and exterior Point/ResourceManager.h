#pragma once

#include <SFML\Graphics\ConvexShape.hpp>
#include <vector>

struct Point {
	double x, y;

	Point()
	{

	}

	Point(sf::Vertex v)
	{
		x = v.position.x;
		y = v.position.y;
	}
};

class ResourceManager
{
	private:
		static ResourceManager * instance;

		int n;
		sf::VertexArray vertices;
		sf::Vertex A;

		sf::ConvexShape polyToDraw;

		std::vector < Point > V;
		std::vector < Point> convexHullPoints;

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

		std::vector < Point > getPoints();

		sf::ConvexShape getConvexShape();
		void setConvexShape(sf::ConvexShape shape);

		std::vector < Point > getConvexHullPoints();
		void setConvexHullPoints(Point[], int);
};