#pragma once

#include <iostream>
#include <vector>
#include "json.hpp"

using namespace std;

class ConfigManager
{
public:
	nlohmann::json curConfig;

	void save();
	void load();
};

