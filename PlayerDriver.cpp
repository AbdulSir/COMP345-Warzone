//
//  PlayerDriver.cpp
//  Comp 345 a1
//
//  Created by Beatrice Cobo on 2021-09-28.
//

#include "Player.h"
#include <iostream>

int main( ){

    using std::cout;
    using std::endl;
    Player *p1 = new Player();
    Hand *h2 = new Hand();
    list<Territory*> t2;
    Player *p2 = new Player("Bob", h2, t2);
    cout << *p1 << endl;
    cout << *p2 << endl;
    p1->toDefend();
    p1->toAttack();
    p1->issueOrder();
    *p1=*p2;
    cout << *p1 << endl;

    return 0;
}
