#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>
#include "Map.h"

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

// Territory CLASS
Territory::Territory ()
{

}
//Copy constructor
Territory::Territory(const Territory& obj)
{
    territory_name = obj.territory_name;
    continent_ref = obj.continent_ref;
    army_nb = obj.army_nb;
}

// Overloaded assignment operator
Territory& Territory::operator= (const Territory& terr) {
    territory_name = terr.territory_name;
    continent_ref = terr.continent_ref;
    army_nb = terr.army_nb;
    return *this;
}

// Stream insertion operators
ostream & operator << (ostream &out, const Territory &terr) {
    out << terr.territory_name << endl;
    return out;
}

istream & operator >> (istream &in,  Territory &terr) {
    cout << "Enter territory name ";
    in >> terr.territory_name;
    cout << "Enter continent ref ";
    in >> terr.continent_ref;
    cout << "Enter number of armies for that territory ";
    in >> terr.army_nb;
    return in;
}

Territory::Territory (string terr_name, int contin_ref, int nb_of_armies)
{
    player1 = new Player();
    territory_name = terr_name;
    continent_ref = contin_ref;
    army_nb = nb_of_armies;
}

string Territory::getName()
{
    return territory_name;
}

// Map CLASS

Map::Map()
{

}

//Copy constructor
Map::Map(const Map& obj): territories(obj.territories) {}

// Overloaded assignment operator
Map& Map::operator= (const Map& map1) {
    territories = map1.territories;
    return *this;
}

// Stream insertion operators
ostream & operator << (ostream &out, Map &m1) {

    for (int i=0; i< m1.territories.size(); i++)
    {
        cout << "Territory " << m1.territories[i]->territory_name << endl;
    }
    return out;
}

istream & operator >> (istream &in,  Map &m1) {
    while (true) {
        string name;
        int contin_ref;
        int army_nb;
        cout << "Type end to exit" << endl;
        cout << "Enter territory name ";
        in >> name;
        if (name.compare("end") == 0) {
            break;
        } else {
            cout << "Enter continent ref ";
            in >> contin_ref;
            cout << "Enter number of armies for that territory ";
            in >> army_nb;
            m1.territories.push_back(new Territory(name, contin_ref, army_nb));
        }
    }
    return in;
}

Map::Map(string text_contents)
{
    Map::createTerritories(text_contents);
    Map::createMap(text_contents);
    Map::displayMap();
}

vector<string> Map::load_continents(string text_contents)
{
    size_t starting_index = text_contents.find("[continents]");
    size_t end_index = text_contents.find("\n\n", starting_index);
    string continents_str = text_contents.substr (starting_index + 13, (end_index - starting_index - 13));
    vector<string> continents_vector;
    boost::split(continents_vector, continents_str, boost::is_any_of("\n"));
    return continents_vector;
}

vector<string> Map::load_countries(string text_contents)
{
    size_t starting_index = text_contents.find("[countries]");
    size_t end_index = text_contents.find("\n\n", starting_index);
    string countries_str = text_contents.substr (starting_index + 12, (end_index - starting_index - 12));
    vector<string> countries_vector;
    boost::split(countries_vector, countries_str, boost::is_any_of("\n"));
    return countries_vector;
}

vector<string> Map::load_borders(string text_contents)
{
    size_t starting_index = text_contents.find("[borders]");
    size_t end_index = text_contents.find("\n\n", starting_index);
    string borders_str = text_contents.substr (starting_index + 10, (end_index - starting_index - 10));
    vector<string> borders_vector;
    boost::split(borders_vector, borders_str, boost::is_any_of("\n"));
    return borders_vector;
}

void Map::createTerritories(string text_contents)
{
    //memebers of the Map class
    continents = Map::load_continents(text_contents);
    countries = Map::load_countries(text_contents);

    //Accessing the army numbers for each continent and storing them in a vector<int>
    vector<int> army_numbers;
    vector<string> continent_names;
    for (int i=0; i < continents.size(); i++) {
        vector<string> continents_temp_vector;
        boost::split(continents_temp_vector, continents[i], boost::is_any_of(" "));
        continent_names.push_back(continents_temp_vector[0]);
        army_numbers.push_back(stoi(continents_temp_vector[1]));
    }

    for (int i=0; i < countries.size(); i++) {
        //Getting the country names
        vector<string> countries_temp_vector;
        boost::split(countries_temp_vector, countries[i], boost::is_any_of(" "));
        int contin_ref = stoi(countries_temp_vector[2]) - 1;
        //accessing the army numbers vector to get the corrosponding army number for each territory then pushing it to the territories data member (vector of territory pointers)
        int army_nb = army_numbers[contin_ref];
        territories.push_back(new Territory(countries_temp_vector[1],contin_ref, army_nb));
    }
}

// Function to add edges

void Map::addEdge(int u, int v)
{
    gr1[u].push_back(territories[v]);
    gr2[v].push_back(territories[u]);
}


void Map::createMap(string text_contents)
{
    //Creating edges between territory nodes by iterating over the vector<string> borders
    borders = Map::load_borders(text_contents);
    for (int i=0; i < borders.size() -1; i++) {
        vector<string> borders_temp_vector;
        boost::split(borders_temp_vector, borders[i], boost::is_any_of(" "));
        for (int j=1; j<borders_temp_vector.size(); j++){
            addEdge(i, stoi(borders_temp_vector[j]) - 1);
        }
    }
}

//A function that displays the map
void Map::displayMap()
{
    for (int i=0; i< territories.size(); i++)
    {
        Territory* t1 = territories[i];
        //cout << (t1)->getName() << endl;
        cout << (t1)->getName()<< " -> ";
        for (Territory* nbr:gr1[i])
        {
            cout << nbr->getName() <<"->";
        }
        cout<<endl;
    }
}

// MapLoader CLASS

MapLoader::MapLoader()
{
    //ctor
}

//Copy constructor
MapLoader::MapLoader(const MapLoader& obj)
{
    text_contents = obj.text_contents;
    map_object = obj.map_object;
}

// Overloaded assignment operator
MapLoader& MapLoader::operator= (const MapLoader& ml1)
{
    text_contents = ml1.text_contents;
    map_object = ml1.map_object;
    return *this;
}

// Stream insertion operators
ostream & operator << (ostream &out, const MapLoader &ml1)
{
    out << ml1.text_contents << endl;
    return out;
}

istream & operator >> (istream &in,  MapLoader &ml1)
{
    cout << "Enter map file contents ";
    in >> ml1.text_contents;
    return in;
}

MapLoader::MapLoader(string file_name)
{
    // Create a text string, which is used to output the text file
    string myText;
    // Read from the text file
    ifstream MyReadFile("Resources/" + file_name);
    if(MyReadFile.fail())
    {
        cout << "An error happened while attempting to read the file" << endl;
        return;
    }
    // Use a while loop together with the getline() function to read the file line by line
    text_contents = "";
    while (getline (MyReadFile, myText)) {
      // Output the text from the file
      text_contents += myText + "\n";
    }
    //creating a map object
    map_object = new Map(text_contents);
    // Close the file
    MyReadFile.close();
}

// Continent CLASS

Continent::Continent()
{

}

//Dummy Player CLASS
Player::Player ()
{

}
