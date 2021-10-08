#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Map.h"

using namespace std;

int main()
{
    vector <vector <int> > v1;
    string file_name = "";
    cout << "Please enter the map file name: \n";
    cin >> file_name;

    if (file_name.compare(".map") != 0)
    {
        cout << endl;
        MapLoader map_loader(file_name);
        delete(map_loader.map_object);
        map_loader.map_object=NULL;
    }
    else
        cout <<"Sorry, wrong file format." << endl;

    return 0;
}
