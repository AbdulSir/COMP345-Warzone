#include <iostream>
#include <string>
#ifndef MAP_H
#define MAP_H

using namespace std;
/*
	• Map
		○ can be used to represent any map graph configuration
		○ implemented as a connected graph
		○ The graph’s nodes represents a territory
		○ Edges between nodes represent adjacency between territories.
		○ validate() method that makes the following checks:
			§ 1) the map is a connected graph
			§ 2) continents are connected subgraphs
3) each country belongs to one and only one continent.
*/

class Map
{
    public:
        Map();
        Map(string text_contents);
        Map (const Map &m1); //Copy constructor
        bool validate();
        bool map_is_connected(Map m1);
        bool continents_are_connected(Map m1);

    private:
};

/*
	• Continent
		Connect subgraphs
        Each territory belongs to one and only one continent
*/

class Continent
{
    public:
        Continent();
        Continent (const Continent &c1); //Copy constructor

    protected:

    private:
};

/*
	• Territory
		Owned by a player
        Contain a number of armies
*/
class Territory
{
    public:
        Territory();
        Territory (const Territory &t1); //Copy constructor

    protected:

    private:
};

/*
	• MapLoader
		read any map file
		creates a map object as a graph data structure
        should be able to read any text file (even invalid ones)
*/
class MapLoader
{
    public:
        MapLoader();
        MapLoader(string file_name);
        MapLoader (const MapLoader &mL1); //Copy constructor
        string read_map(string file_name);
        Map create_map();
        string getText_contents();

    private:
        string text_contents;
        Map map_object;
};

#endif // MAP_H
