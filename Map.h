#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#ifndef MAP_H
#define MAP_H

using namespace std;

class Territory
{
    public:
        Territory();
        Territory (string terr_name, int contin_ref, int num_of_armies);
        Territory (const Territory &t1); //Copy constructor
        Territory& operator= (const Territory& t1); // overloaded assignment operator
        // stream insertion operators
        friend ostream & operator << (ostream &out, const Territory &t1);
        friend istream & operator >> (istream &in,  Territory &t1);
        string getName();
        string territory_name;
        int continent_ref;
        int army_nb;
        int army_bonus;
        void setArmy(int numberOfArmy);
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
        void displayContinents();
        void addEdge(int u, int v);
        void delete_pointers();
        void delete_continent_graph();
        bool validate();
        bool map_is_connected();
        bool continents_are_connected();
        bool territory_belongs_to_one_continent();
        bool adjacent_territory(string terr1, string terr2);
        //bool
        int num_of_continents;
        vector<string> continents;
        vector<string> countries;
        vector<string> borders;
        vector<Territory*> territories;
        vector <int> territories_border_list;
        vector<Territory*> territory_graph[1000];
        vector<Territory*> continent_graph[1000];
};

class MapLoader
{
    public:
        MapLoader();
        MapLoader (const MapLoader &mL1); //Copy constructor
        MapLoader& operator= (const MapLoader& mL1); // overloaded assignment operator
        // stream insertion operators
        friend ostream & operator << (ostream &out, const MapLoader &mL1);
        friend istream & operator >> (istream &in,  MapLoader &mL1);
        string text_contents;
        Map* map_object;
};

#endif // MAP_H
