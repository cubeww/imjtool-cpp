#pragma once
#include <iostream>
#include <string>
using namespace std;

class MapManager
{
public:
	void saveJmap(string filename);
	void loadJmap(string filename);

	void saveRMJ(string filename);
	void loadRMJ(string filename);
};

