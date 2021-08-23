#include "SkinManager.h"
#include "ini.h"
#include <sstream>

using namespace mINI;

void SkinManager::loadConfig()
{
	INIFile inifile("skins/skins.ini");
	INIStructure ini;
	inifile.read(ini);

	string names = ini["skins"]["names"];
	istringstream ss(names);
	string name;

	while (getline(ss, name, ','))
	{
		skinNames.push_back(name);
	}
}
