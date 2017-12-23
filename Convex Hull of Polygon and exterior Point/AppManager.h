#pragma once

class AppManager
{
	private:
		static AppManager * instance;

		AppManager();
		~AppManager();

	public:
		static AppManager * getInstance();
		void freeResources();

		void solve();
};

