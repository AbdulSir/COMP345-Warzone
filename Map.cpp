#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <unordered_map>
#include <list>
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
    int vertices, edges, weight;
    string v1, v2;

    printf("Enter the Number of Vertices -\n");
    cin >> vertices;

    printf("Enter the Number of Edges -\n");
    cin >> edges;

    // Adjacency List is a map of <string, list>.
    // Where each element in the list is pair<string, int>
    // pair.first -> the edge's destination (string)
    // pair.second -> edge's weight
    unordered_map< string, list< pair<string, int> > > adjacencyList(vertices + 1);

    printf("Enter the Edges V1 -> V2, of weight W\n");
    for (int i = 1; i <= edges; ++i) {
        cin >> v1 >> v2 >> weight;

        // Adding Edge to the Directed Graph
        adjacencyList[v1].push_back(make_pair(v2, weight));
    }

    // Printing Adjacency List
    cout << endl << "The Adjacency List-" << endl;
    for (auto& value : adjacencyList) {
        string vertex = value.first;
        list< pair<string, int> > adjacentVertices = value.second;
        list< pair<string, int> >::iterator itr = adjacentVertices.begin();

        cout << "adjacencyList[" << vertex << "]";

        while (itr != adjacentVertices.end()) {
            cout << " -> " << (*itr).first << " (" << (*itr).second << ")";
            ++itr;
        }

        cout << endl;
    }
}

Map::Map(string text_contents)
{

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
      cout << myText <<endl;
    }

    //creating a map object
    Map map_object(text_contents);
    // Close the file
    MyReadFile.close();
}

string MapLoader::getText_contents(){
    return text_contents;
}

Continent::Continent()
{

}

Territory::Territory ()
{

}
