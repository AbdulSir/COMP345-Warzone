#include "Order.h"
#include <iostream>
using namespace std;

int main(){

//cout << "Orders Driver";


    OrderList* orderList = new OrderList();
    Order* order1=new Order("1","");
    
    orderList->addOrder(order1);
    
     
    Deploy* order2 = new Deploy();
     //execute(order1);

    
    // delete pointers
    //delete orderList
    //delete newOrder;

    //newOrder = NULL;
    //gameDeck = NULL;
    //hand = NULL;
    //orderList = NULL;

   return 0;
}
