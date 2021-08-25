#include "MapManager.h"

#include "Game.h"
#include <fstream>
#include <sstream>
#include <format>
#include <bitset>
#include <algorithm>

#include "InGame.h"

Index jmapToIndex(int index)
{
	switch (index)
	{
	case 1:
		return Index::Block;
	case 2:
		return Index::MiniBlock;
	case 3:
		return Index::SpikeUp;
	case 4:
		return Index::SpikeRight;
	case 5:
		return Index::SpikeLeft;
	case 6:
		return Index::SpikeDown;
	case 7:
		return Index::MiniSpikeUp;
	case 8:
		return Index::MiniSpikeRight;
	case 9:
		return Index::MiniSpikeLeft;
	case 10:
		return Index::MiniSpikeDown;
	case 11:
		return Index::Apple;
	case 12:
		return Index::Save;
	case 13:
		return Index::Platform;
	case 14:
		return Index::Water;
	case 15:
		return Index::Water2;
	case 16:
		return Index::WalljumpL;
	case 17:
		return Index::WalljumpR;
	case 18:
		return Index::KillerBlock;
	case 19:
		return Index::BulletBlocker;
	case 20:
		return Index::PlayerStart;
	case 21:
		return Index::Warp;
	case 22:
		return Index::JumpRefresher;
	case 23:
		return Index::Water3;
	case 24:
		return Index::GravityArrowUp;
	case 25:
		return Index::GravityArrowDown;
	case 26:
		return Index::Undefined;
	case 27:
		return Index::Undefined;
	default:
		return Index::Undefined;
	}
}

int indexToJmap(Index index)
{
	switch (index)
	{
	case Index::Block:
		return 1;
	case Index::MiniBlock:
		return 2;
	case Index::SpikeUp:
		return 3;
	case Index::SpikeRight:
		return 4;
	case Index::SpikeLeft:
		return 5;
	case Index::SpikeDown:
		return 6;
	case Index::MiniSpikeUp:
		return 7;
	case Index::MiniSpikeRight:
		return 8;
	case Index::MiniSpikeLeft:
		return 9;
	case Index::MiniSpikeDown:
		return 10;
	case Index::Apple:
		return 11;
	case Index::Save:
		return 12;
	case Index::Platform:
		return 13;
	case Index::Water:
		return 14;
	case Index::Water2:
		return 15;
	case Index::WalljumpL:
		return 16;
	case Index::WalljumpR:
		return 17;
	case Index::KillerBlock:
		return 18;
	case Index::BulletBlocker:
		return 19;
	case Index::PlayerStart:
		return 20;
	case Index::Warp:
		return 21;
	case Index::JumpRefresher:
		return 22;
	case Index::Water3:
		return 23;
	case Index::GravityArrowUp:
		return 24;
	case Index::GravityArrowDown:
		return 25;
	default:
		return -1;
	}
}

Index rmjToIndex(int index)
{
	switch (index)
	{
	case 2:
		return Index::Block;
	case 12:
		return Index::SpikeUp;
	case 11:
		return Index::SpikeRight;
	case 10:
		return Index::SpikeLeft;
	case 9:
		return Index::SpikeDown;
	case 19:
		return Index::MiniSpikeUp;
	case 18:
		return Index::MiniSpikeRight;
	case 17:
		return Index::MiniSpikeLeft;
	case 16:
		return Index::MiniSpikeDown;
	case 20:
		return Index::Apple;
	case 32:
		return Index::Save;
	case 31:
		return Index::Platform;
	case 23:
		return Index::Water;
	case 30:
		return Index::Water2;
	case 29:
		return Index::WalljumpL;
	case 28:
		return Index::WalljumpR;
	case 27:
		return Index::KillerBlock;
	case 3:
		return Index::PlayerStart;
	default:
		return Index::Undefined;
	}
}

int indexToRMJ(Index index)
{
	switch (index)
	{
	case Index::Block:
		return 2;
	case Index::SpikeUp:
		return 12;
	case Index::SpikeRight:
		return 11;
	case Index::SpikeLeft:
		return 10;
	case Index::SpikeDown:
		return 9;
	case Index::MiniSpikeUp:
		return 19;
	case Index::MiniSpikeRight:
		return 18;
	case Index::MiniSpikeLeft:
		return 17;
	case Index::MiniSpikeDown:
		return 16;
	case Index::Apple:
		return 20;
	case Index::Save:
		return 32;
	case Index::Platform:
		return 31;
	case Index::Water:
		return 23;
	case Index::Water2:
		return 30;
	case Index::WalljumpL:
		return 29;
	case Index::WalljumpR:
		return 28;
	case Index::KillerBlock:
		return 27;
	case Index::PlayerStart:
		return 3;
	case Index::Warp:
		return 21;
	default:
		return -1;
	}
}

void MapManager::loadJmap(string filename)
{
	// helper functions
	auto decodeBase32 = [](string str)
	{
		auto base32string = "0123456789abcdefghijklmnopqrstuv"s;
		double result = 0;
		auto length = str.length();
		for (auto i = 0; i < length; i++)
		{
			auto chr = str.at(i);
			auto charvalue = base32string.find(chr);
			auto placevalue = pow(32, length - 1 - i);
			result += charvalue * placevalue;
		}
		return result;
	};

	// magic converter
	union Converter { uint64_t i; double d; };

	auto decodeDouble = [](double value) {
		Converter c;
		auto bs = bitset<64>(value);
		c.i = bs.to_ullong();
		return c.d;
	};

	ifstream file(filename);
	string str;
	file >> str;
	file.close();
	istringstream ss(str);
	string chunk;
	while (getline(ss, chunk, '|'))
	{
		if (chunk.find(":"))
		{
			string key, value;
			istringstream ss2(chunk);
			getline(ss2, key, ':');
			getline(ss2, value, ':');

			if (key == "inf")
			{
				PlayerMgr.infjump = stoi(value);
			}
			else if (key == "dot")
			{
				PlayerMgr.dotkid = stoi(value);
			}
			else if (key == "sav")
			{
				PlayerMgr.saveType = static_cast<SaveType>(stoi(value));
			}
			else if (key == "bor")
			{
				PlayerMgr.deathBorder = static_cast<DeathBorder>(stoi(value));
			}
			else if (key == "px")
			{
				PlayerMgr.currentSave.x = decodeDouble(decodeBase32(value));
			}
			else if (key == "py")
			{
				PlayerMgr.currentSave.y = decodeDouble(decodeBase32(value));
			}
			else if (key == "ps")
			{
				PlayerMgr.currentSave.face = stoi(value);
			}
			else if (key == "pg")
			{
				PlayerMgr.currentSave.y = stoi(value);
			}
			else if (key == "objects")
			{
				Gm.editor.clearUndo();
				for (auto o : ObjMgr.objects)
				{
					if (inPalette(o->index))
						DestroyInst(o);
				}
				auto i = 0;
				auto yy = 0;
				while (i < value.length())
				{
					char* c;
					if (value.substr(i, 1) == "-")
					{
						yy = decodeBase32(value.substr(i + 1, 2));
						i += 3;
					}
					else
					{
						auto index = jmapToIndex(decodeBase32(value.substr(i, 1)));
						auto xx = decodeBase32(value.substr(i + 1, 2));
						CreateInst(static_cast<int>(index), xx - 128.0, yy - 128.0);
						i += 3;
					}
				}
			}
		}
	}
	PlayerMgr.load();
}

void MapManager::saveJmap(string filename)
{
	auto encodeBase32 = [](int number)
	{
		auto base32string = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@"s;
		auto result = ""s;
		while (number > 0)
		{
			float decimal = number / 32.0f;
			number = FloorToInt(decimal);
			auto pos = (decimal - number) * 32;
			result = base32string.at(pos) + result;
		}
		return result;
	};

	auto padStringLeft = [](string str, int length, string padchar)
	{
		while (str.length() < length)
		{
			str = padchar + str;
		}
		return str;
	};

	// magic converter
	union Converter { uint64_t i; double d; };

	auto encodeDouble = [](double value) {
		Converter c;
		auto bs = bitset<64>(value);
		c.d = bs.to_ullong();
		return c.i;
	};

	vector<tuple<int, int, int>> objInfo;
	for (auto i : ObjMgr.objects)
	{
		if (inPalette(i->index))
		{
			objInfo.push_back(make_tuple(i->x, i->y, indexToJmap(static_cast<Index>(i->index))));
		}
	}

	sort(objInfo.begin(), objInfo.end(), [](const tuple<int, int, int>& obj1, const tuple<int, int, int>& obj2)
		{
			return (get<1>(obj1) < get<1>(obj2));
		});

	auto yy = NAN;
	string obj = "";
	for (auto i : objInfo)
	{
		if (yy != get<1>(i))
		{
			yy = get<1>(i);
			obj += "-";
			obj += padStringLeft(encodeBase32(get<1>(i) + 128), 2, "0");
		}
		obj += encodeBase32(get<2>(i));
		obj += padStringLeft(encodeBase32(get<0>(i) + 128), 2, "0");
	}
	string str = format("jtool|1.3.0|inf:{}|dot:{}|sav:{}|bor:{}|px:{}|py:{}|ps:{}|pg:{}|objects:{}",
		static_cast<int>(PlayerMgr.infjump), static_cast<int>(PlayerMgr.dotkid), static_cast<int>(PlayerMgr.saveType), static_cast<int>(PlayerMgr.deathBorder),
		padStringLeft(encodeBase32(encodeDouble(PlayerMgr.currentSave.x)), 13, "0"),
		padStringLeft(encodeBase32(encodeDouble(PlayerMgr.currentSave.y)), 13, "0"),
		static_cast<int>(PlayerMgr.currentSave.face), static_cast<int>(PlayerMgr.currentSave.grav), obj);
	ofstream file(filename);
	file << str;
	file.close();
}

void MapManager::loadRMJ(string filename)
{
	ifstream file(filename);
	string line;
	string ver, mapName, auther;
	for (auto i = 0; getline(file, line); i++) {
		switch (i)
		{
		case 0:
			ver = line;
			break;
		case 1:
			mapName = line;
			break;
		case 2:
			auther = line;
			break;
		case 3:
			Gm.editor.clearUndo();
			for (auto o : ObjMgr.objects)
			{
				if (inPalette(o->index))
					DestroyInst(o);
			}
			istringstream ss(line);
			int xx, yy, index;
			while (ss >> xx)
			{
				ss >> yy;
				ss >> index;
				CreateInst(static_cast<int>(rmjToIndex(index)), xx, yy);
			}
			break;
		}
	}
	file.close();
	PlayerMgr.load();
}

void MapManager::saveRMJ(string filename)
{
	ostringstream objs;
	for (auto i : ObjMgr.objects)
	{
		if (inPalette(i->index))
		{
			objs << i->x << " " << i->y << " " << indexToRMJ(static_cast<Index>(i->index)) << " ";
		}
	}
	ofstream file(filename);
	file << " 1.030000" << endl
		<< "Imported from imjtool" << endl
		<< "someone" << endl
		<< objs.str();
	file.close();
}


