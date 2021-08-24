#include "MapManager.h"

#include <fstream>

void MapManager::loadJmap(string filename)
{
	ifstream file(filename);
	string str;
	file >> str;
	cout << str << endl;
}
