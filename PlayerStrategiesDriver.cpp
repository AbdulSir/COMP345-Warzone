//
//  PlayerStrategiesDriver.cpp
//  Warzone
//
//  Created by Beatrice Cobo on 2021-12-01.
//

#include "PlayerStrategies.h"
#include "Player.h"
Map* map_obj;
int main(){
    MapLoader* map_loader = new MapLoader();
    map_obj = map_loader->map_object;
    Hand* h = new Hand;
    Hand* h2 = new Hand;
    Territory* firstTerritory = map_obj->territories[0];
    Territory* secondTerritory = map_obj->territories[1];
    Territory* thirdTerritory = map_obj->territories[2];
    Territory* firstTerritory2 = map_obj->territories[3];
    Territory* secondTerritory2 = map_obj->territories[4];
    Territory* thirdTerritory2 = map_obj->territories[5];
    OrderList* orderList = new OrderList();
    vector <Territory*> v;
    vector <Territory*> v2;
    v.push_back(firstTerritory);
    v.push_back(secondTerritory);
    v.push_back(thirdTerritory);
    v2.push_back(firstTerritory2);
    v2.push_back(secondTerritory2);
    v2.push_back(thirdTerritory2);
    cout<<endl;
    Player* player = new Player("Aggressive", h, v, new Aggressive);
    player->ps->issueOrder();
    cout<<*player->getOrders()<<endl;
    cout<<endl;
    Player* player2 = new Player("Benevolent", h2, v2, new Benevolent);
    player2->ps->issueOrder();
    cout<<*player2->getOrders()<<endl;
    return 0;
}
