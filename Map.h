#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>
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

//Dummy class
class Player
{
    public:
        Player();
};

class Territory
{
    public:
        Territory();
        Territory (string terr_name, int num_of_armies);
        Territory (const Territory &t1); //Copy constructor
        Territory& operator= (const Territory& t1); // overloaded assignment operator
        // stream insertion operators
        friend ostream & operator << (ostream &out, const Territory &t1);
        friend istream & operator >> (istream &in,  Territory &t1);
        string getName();
        string territory_name;
        Player* player1;
        int army_nb;
};

class Map
{
    public:
        Map();
        Map(string text_contents);
        Map (const Map &m1); //Copy constructor
        Map& operator= (const Map& m1); // overloaded assignment operator
        // stream insertion operators
        friend ostream & operator << (ostream &out, const Map &m1);
        friend istream & operator >> (istream &in,  Map &m1);
        vector<string> load_continents(string text_contents);
        vector<string> load_countries(string text_contents);
        vector<string> load_borders(string text_contents);
        void createTerritories(string text_contents);
        void createMap(string text_contents);
        void displayMap();
        void addEdge(int u, int v);
        bool validate();
        bool map_is_connected(Map m1);
        bool continents_are_connected(Map m1);
        vector<string> continents;
        vector<string> countries;
        vector<string> borders;
        vector<Territory*> territories;
        // To keep correct and reverse direction
        vector<Territory*> gr1[100], gr2[100];
        //bool vis1[100], vis2[100];
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
        Continent& operator= (const Continent& c1); // overloaded assignment operator
        // stream insertion operators
        friend ostream & operator << (ostream &out, const Continent &c1);
        friend istream & operator >> (istream &in,  Continent &c1);
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
        MapLoader& operator= (const MapLoader& mL1); // overloaded assignment operator
        // stream insertion operators
        friend ostream & operator << (ostream &out, const MapLoader &mL1);
        friend istream & operator >> (istream &in,  MapLoader &mL1);
        string text_contents;
        Map map_object;
};

#endif // MAP_H
