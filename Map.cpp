#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <boost/algorithm/string.hpp>
#include "Map.h"

using namespace std;

// Territory CLASS
Territory::Territory ()
{

}
//Copy constructor
Territory::Territory(const Territory& obj)
{
    owner = NULL;
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
ostream & operator << (ostream &out, const Territory &t1) {
    out << endl << "Territory name " << t1.territory_name << endl;
    out << "Number of armies: " << t1.army_nb << endl;
    if (t1.owner != NULL) {
        out << "Owner: " << t1.owner->getName() << endl;
    }
    return out;
}

Territory::Territory (string terr_name, int contin_ref, int nb_of_armies)
{
    owner = NULL;
    territory_name = terr_name;
    continent_ref = contin_ref;
    army_nb = nb_of_armies;
}

string Territory::getName()
{
    return territory_name;
}

void Territory::setArmy(int numberOfArmy) {
    army_nb = numberOfArmy;
}

void Territory::setOwner(Player* p) {
    if (owner != NULL) {
        vector<Territory*> playerTerritories = owner->getTerritories();
        playerTerritories.erase(find(playerTerritories.begin(), playerTerritories.end(), this));
        owner->setTerritories(playerTerritories);
    }
    vector<Territory*> playerTerritories = p->getTerritories();
    playerTerritories.push_back(this);
    p->setTerritories(playerTerritories);
    owner = p;
};

void Territory::resetOwner() {
    if (owner != NULL) {
        vector<Territory*> playerTerritories = owner->getTerritories();
        playerTerritories.erase(find(playerTerritories.begin(), playerTerritories.end(), this));
        owner->setTerritories(playerTerritories);
    }
    owner = NULL;
}

Player* Territory::getOwner() {
    return owner;
};

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

bool Map::adjacent_territory(string terr1, string terr2) {
    bool returnValue = false;
    for (int i=0; i<territories.size(); i++)
    {
        if (terr1.compare(territories[i]->getName()) == 0)
        {
            for (Territory* terr:territory_graph[i])
            {
                if (terr2.compare(terr->getName()) == 0) {
                    returnValue = true;
                }
            }
        }
    }
    return returnValue;
};

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
    Map::displayContinents();
    // if(Map::validate())
        // cout << "\nThe Map is a valid map" << endl;
    // else
        // cout << "\nThe Map is NOT a valid map" << endl;
    // Map::delete_pointers();
}

bool Map::validate()
{
    if (Map::map_is_connected())
        cout << "\nThe map is a connected graph" << endl;
    else
        cout << "\nThe map is NOT a connected graph" << endl;

    if (Map::continents_are_connected())
        cout << "\nContinents are connected subgraphs" << endl;
    else
        cout << "\nContinents are NOT connected subgraphs" << endl;

    if (Map::territory_belongs_to_one_continent())
        cout << "\nTerritories belong to only one continent" << endl;
    else
        cout << "\nTerritories DO NOT belong to only one continent" << endl;

    if (Map::map_is_connected()==true && Map::continents_are_connected()==true && Map::territory_belongs_to_one_continent()==true)
        return true;
    else
        return false;
}

vector<string> Map::load_continents(string text_contents)
{
    size_t starting_index = text_contents.find("[continents]"); //
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
    num_of_continents = continents.size();
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
        continent_graph[contin_ref].push_back(territories[i]);
    }
}

// Function to add edges
void Map::addEdge(int u, int v)
{
    territory_graph[u].push_back(territories[v]);
    territories_border_list.push_back(v);
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
        cout << (territories[i])->getName()<< " -> ";
        for (Territory* terr:territory_graph[i])
        {
            cout << terr->getName() <<"->";
        }
        cout<<endl;
    }
    cout<<endl;
}

void Map::displayContinents()
{
    for (int i=0; i< num_of_continents; i++)
    {
        cout << "Continent " << i << ": ";
        for (Territory* terr:continent_graph[i])
        {
            cout << terr->getName() <<"->";
        }
        cout<<endl;
    }
}

bool Map::map_is_connected()
{
    bool vis[territories.size()];
    //set the array to false. i.e. no node has been visited yet
    memset(vis, false, sizeof(vis));
    //iterate through the borders list and mark node visited if this is the first time visiting it, if it is already visited we skip it
    for (int i=0; i < territories_border_list.size(); i++)
    {
        if (!vis[territories_border_list[i]])
            vis[territories_border_list[i]]=true;
    }
    //check if all nodes have been visited
    for (int i=0; i < sizeof(vis); i++)
    {
        if (!vis[i])
            return false;
    }
    //we return true because the previous loop did not find a node that was not visited
    return true;
}

bool Map::continents_are_connected()
{
    bool vis[num_of_continents];
    //set the array to false. i.e. no node has been visited yet
    memset(vis, false, sizeof(vis));
    for (int i=0; i < territories.size(); i++)
    {
        if (!vis[(territories[i])->continent_ref])
            vis[(territories[i])->continent_ref]=true;
    }
    //check if all nodes have been visited
    for (int i=0; i < sizeof(vis); i++)
    {
        if (!vis[i])
            return false;
    }
    //we return true because the previous loop did not find a node that was not visited
    return true;
}

bool Map::territory_belongs_to_one_continent()
{
    for (int i=0; i<territories.size(); i++)
    {
        int contin_num = (territories[i])->continent_ref;
        for (int j=0; j<num_of_continents; j++)
        {
            if (j!= contin_num)
            {
                for (Territory* terr:continent_graph[j])
                {
                    if ( terr==territories[i])
                        return false;
                }
            }
        }
    }
    return true;
}

void Map::delete_pointers()
{
    for (int i=0; i < territories.size(); i++)
    {
        for (Territory* terr:continent_graph[i])
        {
            delete(terr->owner);
            terr->owner=NULL;
            delete(terr);
            terr = NULL;
        }
        for (Territory* terr1:territory_graph[i])
        {
            delete(terr1->owner);
            terr1->owner=NULL;
            delete(terr1);
            terr1 = NULL;
        }
        delete(territories[i]->owner);
        territories[i]->owner = NULL;
        delete(territories[i]);
        territories[i]=NULL;
    }
}

// MapLoader CLASS
MapLoader::MapLoader()
{

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
