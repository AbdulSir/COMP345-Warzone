#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Map.h"

/*
MapDriver.cpp file > creates a map by reading a set of map files
MapDriver.cpp file > create a map object for valid maps (reject invalid map files)
MapDriver.cpp file > Should demonstrate that the Map class does the following:
	• the map is a connected graph
	• continents are connected subgraphs
	• each country belongs to one and only one continent.

MapDriver.cpp file
	• reads many different map files
	• creates a Map object for valid files
rejects the invalid ones
*/
using namespace std;

int main()
{
    string file_name = "";
    cout << "Please enter the map file name: \n";
    cin >> file_name;

    if (file_name.find(".map") != string::npos)
    {
        cout << endl;
        MapLoader map_loader(file_name);
    }

    else
        cout <<"Sorry, wrong file format." << endl;

    return 0;
}

