
#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

map<unsigned int, unsigned int> speedRestrictionMap;
unsigned int maxDistance;

void readFileAndCreateModel()
{
	string fileName = "SpeedRestrictions.csv";
	try
	{
		ifstream fileStream(fileName);
		fileStream.exceptions(ifstream::badbit | ifstream::failbit);
		string line;

		string speedRestriction;
		string startDistance;
		string endDistance;
		
		if (fileStream.is_open())
		{
			fileStream.ignore(256, '\n');
			cout << "Speed\tStart\tEnd" << endl;
			while (!fileStream.eof() && getline(fileStream, line))
			{
				speedRestriction = line.substr(0, line.find(","));
				line.erase(0, line.find(",")+1);
				startDistance = line.substr(0, line.find(","));
				line.erase(0, line.find(",")+1);
				endDistance = line.substr(0, line.find(","));
				speedRestrictionMap.emplace(pair<unsigned int, unsigned int>(stoi(startDistance), stoi(speedRestriction)));
				cout << speedRestriction << "\t" << startDistance << "\t" << endDistance <<endl;
				maxDistance = stoi(endDistance);
			}
		}
		fileStream.close();
	}
	catch (exception const &e)
	{
		cout << "Error while opening/reading file '" << fileName << "' \nError:" << e.what();
	}
}
unsigned int getSpeedRestrictionAtDistance(unsigned int distance)
{
	unsigned int speed = 0;
	for (auto& speedRestriction : speedRestrictionMap)
	{
		if (speedRestriction.first <= distance)
		{
			speed = speedRestriction.second;
		}
	}
	return speed;
}
int main() {
	readFileAndCreateModel();
	if (speedRestrictionMap.size() > 0)
	{
		int input = 0;
		while (input != -1)
		{
			cout << "Enter distance to get speed restriction or hit '-1' to exit:";
				cin >> input;
				if (!cin.good())
				{
					cout << "Incorrect input"<<endl;
					cin.clear();
					cin.ignore(256, '\n');
				}
				else if (input == -1)
				{
					cout << "Exiting.That's all folks!";
				}
				else if (input < -1)
				{
					cout << "Distance entered negative." << endl;
				}
				else if (input > maxDistance)
				{
					cout << "Distance greater than max distance. Enter upto "<<maxDistance<<endl;
				}
				else
				{
					cout<<"Speed restriction at "<<input<<" is "<<getSpeedRestrictionAtDistance(input)<<endl;
				}
		}
	}
	cin.get();
}