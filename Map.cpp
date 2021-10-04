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


Map::Map()
{

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
    string countries_str = text_contents.substr (starting_index + 11, (end_index - starting_index - 11));
    vector<string> countries_vector;
    boost::split(countries_vector, countries_str, boost::is_any_of("\n"));
    return countries_vector;
}

vector<string> Map::load_borders(string text_contents)
{
    size_t starting_index = text_contents.find("[borders]");
    size_t end_index = text_contents.find("\n\n", starting_index);
    string borders_str = text_contents.substr (starting_index + 10, (end_index - starting_index - 4));
    vector<string> borders_vector;
    boost::split(borders_vector, borders_str, boost::is_any_of("\n"));
    return borders_vector;
}

void Map::createTerritories(string text_contents)
{
    continents = Map::load_continents(text_contents);
    countries = Map::load_countries(text_contents);

    vector<int> army_numbers;
    for (int i=0; i < continents.size(); i++) {
        vector<string> continents_temp_vector;
        boost::split(continents_temp_vector, continents[i], boost::is_any_of(" "));
        army_numbers.push_back(stoi(continents_temp_vector[1]));
    }

    vector<string> countries_temp_vector;
    for (int i=0; i < countries.size(); i++) {
        //Getting the country names
        size_t start_index = countries[i].find(" ");
        size_t end_index = countries[i].find(" ", start_index + 1);
        string country_name = countries[i].substr(start_index +1, (end_index - start_index));
        //Getting the Army numbers from the continent
        size_t continent_start_index = countries[i].find(" ", end_index);
        string continent_num = countries[i].substr(continent_start_index +1,1);
        //Converting the army number from string to int
        int continent_ref = 0;
        stringstream get_int(continent_num);
        get_int >> continent_ref;

        //accessing the army numbers vector to get the corrosponding army number for each territory then pushing it to the territories data member (vector of territory pointers)
        int army_nb = army_numbers[continent_ref -1];
        territories.push_back(new Territory(country_name, army_nb));
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
    //Creating edges between territory nodes
    borders = Map::load_borders(text_contents);
    for (int i=0; i < borders.size() -1; i++) {
        vector<string> borders_temp_vector;
        boost::split(borders_temp_vector, borders[i], boost::is_any_of(" "));
        for (int j=1; j<borders_temp_vector.size(); j++){
            addEdge(i, stoi(borders_temp_vector[j]));
        }
    }
}

//A function that displays the map
void Map::displayMap()
{
    for (int i=0; i< territories.size() -1; i++)
    {
        cout << "Vertex " << i + 1 << "->";
        for (Territory* nbr:gr1[i])
        {
            cout << nbr->getName() <<"->";
        }
        cout<<endl;
    }
}

MapLoader::MapLoader()
{
    //ctor
}

MapLoader::MapLoader(string file_name)
{
    // Create a text string, which is used to output the text file
    string myText;
    // Read from the text file
    ifstream MyReadFile("Resources/" + file_name);

    // Use a while loop together with the getline() function to read the file line by line
    text_contents = "";

    while (getline (MyReadFile, myText)) {
      // Output the text from the file
      text_contents += myText + "\n";
    }

    //creating a map object
    Map map_object(text_contents);
    // Close the file
    MyReadFile.close();
}

Continent::Continent()
{

}

Player::Player ()
{

}

Territory::Territory ()
{

}


Territory::Territory (string terr_name, int nb_of_armies)
{
    player1 = new Player();
    territory_name = terr_name;
    army_nb = nb_of_armies;
}

string Territory::getName()
{
    return territory_name;
}
