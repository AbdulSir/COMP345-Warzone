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
    Territory* firstTerritory = m->territories[0];
    Territory* secondTerritory = m->territories[1];
    Territory* thirdTerritory = m->territories[2];
    OrderList* orderList = new OrderList();
    vector <Territory*> v;
    v.push_back(firstTerritory);
    v.push_back(secondTerritory);
    v.push_back(thirdTerritory);
    cout<<endl;
    Player* player = new Player("Aggressive", h, v,m, new Aggressive);
    player->ps->issueOrder();
    return 0;
}
