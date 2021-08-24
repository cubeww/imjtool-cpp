#pragma once
#include <iostream>
#include <string>
using namespace std;

class MapManager
{
	void saveJmap();
	void loadJmap(string filename);

	void saveRMJ();
	void loadRMJ();
};

