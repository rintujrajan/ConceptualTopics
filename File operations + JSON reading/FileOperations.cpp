
#include <iostream>
#include <map>
#include <fstream>
#include "json.h"

using namespace std;


unsigned int getSpeedLimitAtDistance(const map<unsigned int, unsigned int>& spdRstricionMap, unsigned int distance)
{
	unsigned int restrictiveSpeed = spdRstricionMap.begin()->second;
	for (auto it : spdRstricionMap)
	{
		if (it.first <= distance)
		{
			restrictiveSpeed = it.second;
		}
		else
		{
			return restrictiveSpeed;
		}
	}
	return restrictiveSpeed;
}
void readDataAndFormModel(map<unsigned int, unsigned int>& spdRstricionMap, unsigned int& maxDistance)
{
	try {

		ifstream myfile("SpeedRestrictions.json");
		myfile.exceptions(ifstream::badbit | ifstream::failbit);
		Json::Reader reader;
		Json::Value root;

		if (myfile.is_open())
		{
			if (!reader.parse(myfile, root))
			{
				cout << reader.getFormattedErrorMessages();
			}
			else
			{

				unsigned int curDistance, curSpeedLimit;
				const Json::Value speedRestrictions = root["SpeedRestrictions"];
				for (size_t i = 0; i < speedRestrictions.size(); i++)
				{
					curDistance = speedRestrictions[i]["StartDistance"].asUInt();
					curSpeedLimit = speedRestrictions[i]["SpeedLimt"].asUInt();
					spdRstricionMap.emplace(pair<unsigned int, unsigned int>(curDistance, curSpeedLimit));
				}
				maxDistance = speedRestrictions[speedRestrictions.size() - 1]["EndDistance"].asUInt();
			}
		}
		myfile.close();

	}
	catch (std::exception const& e) {
		cout << "There was an error: " << e.what() << endl;
	}
}
int main() {

	map<unsigned int, unsigned int> spdRstricionMap;
	unsigned int maxDistance = 0;

	readDataAndFormModel(spdRstricionMap, maxDistance);

	if (spdRstricionMap.size() > 0)
	{
		int input = 0;
		while (input != -1)
		{
			cout << "Enter distance to get speed limit or hit '-1' to exit:";
			cin >> input;
			if (!cin.good())
			{
				cout << "Incorrect distance entered." << endl;
				cin.clear();
				cin.ignore(256, '\n');
			}
			else
			{
				if (input == -1)
				{
					cout << "That's all folks!" << endl;
				}
				else if (input > maxDistance)
				{
					cout << "Distance outside range entered. Input values till " << maxDistance << "." << endl;
				}
				else if (input < -1)
				{
					cout << "Negative distance entered. Input positive values." << endl;
				}
				else if (input > -1)
				{
					cout << "Speed limit at distance " << input << " is " << getSpeedLimitAtDistance(spdRstricionMap, input) << endl;
				}


			}
		}
	}
}