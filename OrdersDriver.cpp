#include "Orders.h"
#include "Orders.cpp"
#include <iostream>
using namespace std;

int main(){
    
    
    OrderList* orderList = new OrderList();
    
    //Create multiple types of Orders
    Order* order1=new Order("1","","");
    Deploy* order2=new Deploy("2","trip","");
    Advance* order3=new Advance("3","advance","");
    Bomb* order4=new Bomb("4","bomb","");
    Blockade* order5=new Blockade("5","trip now","");
    Airlift* order6=new Airlift("6","airlift","");
    Negotiate* order7=new Negotiate("7","advance","");
    
    //Insert each order to the orderList
    orderList->addOrder(order1);
    orderList->addOrder(order2);
    orderList->addOrder(order3);
    orderList->addOrder(order4);
    orderList->addOrder(order5);
    orderList->addOrder(order6);
    orderList->addOrder(order7);
    cout<<endl<<endl;
    
    //Display orderList
    cout<<*orderList<<endl;
    
    //Move order1 to the 2nd position in the list
    orderList->move(order1,2);
    cout<<endl;
    
    //Display orderList
    cout<<*orderList<<endl;
    
    //Move order7 to the 0 position in the list
    orderList->move(order7,0);
    cout<<endl;
    
    //Display orderList
    cout<<*orderList<<endl;
    
    //remove order1
    orderList->remove(order1);
    cout<<endl;
    
    //Display orderList
    cout<<*orderList<<endl;
    
    //Validate order7
    if(order7->validate())
        cout<<"Order 7 is a valid order."<<endl;
    else
        cout<<"Order 7 is invalid order."<<endl;
    cout<<endl;
    
    //Execute order7
    order7->execute();
    cout<<endl;
    
    //Display order7
    cout<<*order7<<endl;
    
    //Validate order3
    if(order3->validate())
        cout<<"Order 3 is a valid order."<<endl;
    else
        cout<<"Order 3 is invalid order."<<endl;
    cout<<endl;
    
    //Execute order3
    order3->execute();
    cout<<endl;
    
    //Display order3
    cout<<*order3<<endl;
    
    //delete all pointers
    delete orderList;

    return 0;
}
