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
    Territory* test2 = new Territory("2", 0, 0);

    OrderList* orderList = new OrderList();

    Deploy* order1=new Deploy("2", player1, test, 3);
    order1->execute();

    Advance* order2 = new Advance("3", player1, test, test2, 3);
    order2->execute();

    Airlift* order3 = new Airlift("4", player1, test, test2, 3);
    order3->execute();
    orderList->addOrder(order1);
    orderList->addOrder(order2);
    orderList->addOrder(order3);
    cout << *orderList << endl;

    //delete all pointers
    delete orderList;

    return 0;
}
