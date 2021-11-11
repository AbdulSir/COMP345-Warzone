#include "Player.h"
#include "Orders.h"

#include <iostream>
using namespace std;

int main() {
    Hand* h = new Hand;
    vector <Territory*> v;
    v.push_back(new Territory("1", 0, 0));
    v.push_back(new Territory("2", 0, 0));
    v.push_back(new Territory("3", 0, 0));
    v.push_back(new Territory("4", 0, 0));
    v.push_back(new Territory("5", 0, 0));
    v.push_back(new Territory("6", 0, 0));

    Player* player1 = new Player("testName", h, v);
    Territory* test = new Territory("1", 0, 0);

    OrderList* orderList = new OrderList();

    Deploy* order2=new Deploy("2", player1, test, 3);
    order2->execute();


    //delete all pointers
    delete orderList;

    return 0;
}
