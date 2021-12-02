//
//  PlayerStrategiesDriver.cpp
//  Warzone
//
//  Created by Beatrice Cobo on 2021-12-01.
//

#include "PlayerStrategies.h"
#include "Player.h"

int main(){
    MapLoader* map_loader = new MapLoader();
    Map* m = map_loader->map_object;
    Hand* h = new Hand;
    Hand* h2 = new Hand;
    Territory* firstTerritory = m->territories[0];
    Territory* secondTerritory = m->territories[1];
    Territory* thirdTerritory = m->territories[2];
    Territory* firstTerritory2 = m->territories[3];
    Territory* secondTerritory2 = m->territories[4];
    Territory* thirdTerritory2 = m->territories[5];
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
    Player* player = new Player("Aggressive", h, v,m, new Aggressive);
    player->ps->issueOrder();
    cout<<*player->getOrders()<<endl;
    cout<<endl;
    Player* player2 = new Player("Benevolent", h2, v2,m, new Benevolent);
    player2->ps->issueOrder();
    cout<<*player2->getOrders()<<endl;
    return 0;
}
