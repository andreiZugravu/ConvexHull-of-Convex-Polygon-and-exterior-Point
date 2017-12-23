#pragma once

#include "ResourceManager.h"

class AppManager
{
	private:
		static AppManager * instance;

		double dist_squared(Point p1, Point p2);

		AppManager();
		~AppManager();

	public:
		static AppManager * getInstance();
		void freeResources();

		void solve();
};

