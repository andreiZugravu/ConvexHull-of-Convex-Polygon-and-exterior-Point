#include "AppManager.h"
#include <iostream>
#include "ResourceManager.h"
#include <climits>
#include "Menu.h"

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

double AppManager::dist_squared(Point p1, Point p2)
{
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
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
	double dist_min = INT_MAX;
	int ind_min = 0;
	double dist;
	for (int i = 0; i < n; i++)
	{
		dist = dist_squared(points[i], A);

		if (dist < dist_min)
		{
			//update
			dist_min = dist;
			ind_min = i;
		}

	}
	std::cout << points[ind_min].x << " " << points[ind_min].y << " " << dist_min << "\n";

	//step 2
	//step 2.1. move to the left and get the tangent
	int ind_tg_left;
	int skipped_left = 1;
	int ind_min_is_tangent_left = false;
	int ind_min_is_tangent_right = false;
	Point pmin = points[ind_min];
	Point min_left = (ind_min == 0 ? points[n - 1] : points[ind_min - 1]);
	Point min_right = (ind_min == n - 1 ? points[0] : points[ind_min + 1]);

	int min_leftSign = A.x * min_left.y + pmin.x * A.y + pmin.y * min_left.x -
		A.x * pmin.y - min_left.x * A.y - min_left.y * pmin.x;
	std::cout << "Left : " << min_leftSign << "\n";
	if (min_leftSign < 0.f)
		min_leftSign = -1;
	else if (min_leftSign > 0.f)
		min_leftSign = 1;
	else
		min_leftSign = 0;

	int min_rightSign = A.x * min_right.y + pmin.x * A.y + pmin.y * min_right.x -
		A.x * pmin.y - min_right.x * A.y - min_right.y * pmin.x;
	std::cout << "Right : " << min_rightSign << "\n";
	if (min_rightSign < 0.f)
		min_rightSign = -1;
	else if (min_rightSign > 0.f)
		min_rightSign = 1;
	else
		min_rightSign = 0;

	if (min_leftSign == min_rightSign)
	{
		std::cout << "Semn : " << min_leftSign << "\n";
		if (min_leftSign == -1)
			ind_min_is_tangent_right = true;
		else if(min_leftSign == 1)
			ind_min_is_tangent_left = true;
		//else it is 0, so it is somewhere between a point and A, so there's no reason to keep it in the convex hull
	}
	
	if (ind_min_is_tangent_left == false)
	{
		if (ind_min == 0)
			ind_tg_left = n - 1;
		else
			ind_tg_left = ind_min - 1;


		bool found_tg_left = false;
		while (found_tg_left == false && ind_min != ind_tg_left)
		{
			int ind_left;
			int ind_right;

			if (ind_tg_left == 0)
			{
				ind_left = n - 1;
				ind_right = 1;
			}
			else if (ind_tg_left == n - 1)
			{
				ind_left = n - 2;
				ind_right = 0;
			}
			else
			{
				ind_left = ind_tg_left - 1;
				ind_right = ind_tg_left + 1;
			}

			Point P = points[ind_tg_left];
			Point left = points[ind_left];
			Point right = points[ind_right];

			//delta(p,q,r) = 
			// |  1  1  1 |
			// | p1 q1 r1 |
			// | p2 q2 r2 |
			//if delta == 0 then R is on PQ
			//if delta < 0 then R is on the right of PQ
			//if delta > 0 then R is on the left of PQ
			//in our case, P = P, Q = A, R = left or right
			//that is :
			//delta (P,A,R)
			// |   1     1        1          |
			// | P.x  A.x  left or right.x |
			// | P.y  A.y  left or right.y |
			int leftSign = A.x * left.y + P.x * A.y + P.y * left.x -
				A.x * P.y - left.x * A.y - left.y * P.x;

			if (leftSign < 0)
				leftSign = -1;
			else if (leftSign > 0)
				leftSign = 1;
			else
				leftSign = 0;

			int rightSign = A.x * right.y + P.x * A.y + P.y * right.x -
				A.x * P.y - right.x * A.y - right.y * P.x;

			if (rightSign < 0)
				rightSign = -1;
			else if (rightSign > 0)
				rightSign = 1;
			else
				rightSign = 0;

			if (leftSign + rightSign != 0)
			{
				found_tg_left = true; std::cout << "Left P : " << P.x << " " << P.y << "\n";
			}
			else
			{
				if (ind_tg_left == 0)
					ind_tg_left = n - 1;
				else
					ind_tg_left--;

				skipped_left++;
			}
		}
	}
	else
	{
		skipped_left = 0;
		ind_tg_left = ind_min;
	}

	//step 2.2. move to the right and get the tangent
	int ind_tg_right;
	int skipped_right = 1;
	if (ind_min_is_tangent_right == false)
	{
		if (ind_min == n - 1)
			ind_tg_right = 0;
		else
			ind_tg_right = ind_min + 1;

		bool found_tg_right = false;
		while (found_tg_right == false && ind_min != ind_tg_right)
		{
			int ind_left;
			int ind_right;

			if (ind_tg_right == 0)
			{
				ind_left = n - 1;
				ind_right = 1;
			}
			else if (ind_tg_right == n - 1)
			{
				ind_left = n - 2;
				ind_right = 0;
			}
			else
			{
				ind_left = ind_tg_right - 1;
				ind_right = ind_tg_right + 1;
			}

			Point P = points[ind_tg_right];
			Point left = points[ind_left];
			Point right = points[ind_right];

			int leftSign = A.x * left.y + P.x * A.y + P.y * left.x -
				A.x * P.y - left.x * A.y - left.y * P.x;

			if (leftSign < 0)
				leftSign = -1;
			else if (leftSign > 0)
				leftSign = 1;
			else
				leftSign = 0;

			int rightSign = A.x * right.y + P.x * A.y + P.y * right.x -
				A.x * P.y - right.x * A.y - right.y * P.x;

			if (rightSign < 0)
				rightSign = -1;
			else if (rightSign > 0)
				rightSign = 1;
			else
				rightSign = 0;

			//leftSign + rightSign != 0 means they we don't accept when they are on different sides or on the same line
			//however, we should never worry about them being on the same line since all polygon angles are less than 180 degrees
			if (leftSign + rightSign != 0)
			{
				found_tg_right = true;
				std::cout << "Right P : " << P.x << " " << P.y << "\n";
			}
			else
			{
				if (ind_tg_right == n - 1)
					ind_tg_right = 0;
				else
					ind_tg_right++;

				skipped_right++;
			}
		}
	}
	else
	{
		skipped_right = 0;
		ind_tg_right = ind_min;
	}

	//std::cout << "Left tangent : " << points[ind_tg_left].x << " " << points[ind_tg_left].y << "\n";
	//std::cout << "Right tangent : " << points[ind_tg_right].x << " " << points[ind_tg_right].y << "\n";

	//return convex hull
	sf::ConvexShape shape;

	int nr_now = n - skipped_left - skipped_right + 1 + 1; //first + 1 because they are both counting points[ind_min]. second +1 because we add A
	//if (ind_min_is_tangent_left || ind_min_is_tangent_right)
		//nr_now -= 1; //small fix

	Point * convexHullPoints = new Point[nr_now];

	convexHullPoints[0] = A;
	int follow_right_tg = ind_min - 1;
	while (follow_right_tg != ind_tg_right)
	{
		if (follow_right_tg == n - 1)
			follow_right_tg = 0;
		else
			follow_right_tg++;
	}

	for (int i = 1; i < nr_now; i++)
	{
		convexHullPoints[i] = points[follow_right_tg];

		if (follow_right_tg == n - 1)
			follow_right_tg = 0;
		else
			follow_right_tg++;
	}

	ResourceManager::getInstance()->setConvexHullPoints(convexHullPoints, nr_now);

	std::cout << "nr_now : " << nr_now << "\n";
	for (int i = 0; i < nr_now; i++)
		std::cout << convexHullPoints[i].x << " " << convexHullPoints[i].y << "\n";

	shape.setPosition(sf::Vector2f(0.f, 0.f));
	shape.setFillColor(sf::Color::Red);
	shape.setOutlineThickness(1.f);

	shape.setPointCount(nr_now);
	for (int i = 0; i < shape.getPointCount(); i++)
	{
		double x_coord, y_coord;

		x_coord = _WINDOW_WIDTH / 2 + convexHullPoints[i].x * ((_WINDOW_WIDTH / 2) / _MAX_X_VALUE);
		y_coord = _WINDOW_HEIGHT / 2 - convexHullPoints[i].y * ((_WINDOW_HEIGHT / 2) / _MAX_Y_VALUE); //- pt ca y-ul creste de sus in jos pe window
		shape.setPoint(i, sf::Vector2f(x_coord, y_coord));
	}

	ResourceManager::getInstance()->setConvexShape(shape);

	delete [] convexHullPoints;
}