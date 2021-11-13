/**
 Part 2: PlayerDriver.cpp
 */

#include "Player.h"
#include <iostream>


int main( ){

    //create player using default constructor
    Player *p1 = new Player();

    //create player using default constructor
    Hand *h2 = new Hand(); //pointer to hand of cards object
    Territory* spain=new Territory("Spain", 0, 5);
    Territory* portugal=new Territory("Portugal", 0, 5);
    vector<Territory*> t2= {spain, portugal}; //collection of territories
    Player *p2 = new Player("Bob", h2, t2); //player stores name, hand of cards, and territories
    cout<<endl;
    cout<<*p2<<endl;


    //call to toDefend method
    vector<Territory*> dt = p1->toDefend();
    //Display all territoriest to defend from collection
    cout<<"Territories to defend: ";
    string separator="";
    for (auto d_territory : dt) {
        cout << separator << d_territory->territory_name;
        separator = ", ";
    }

    cout<<"\n"<<endl;

    //call to toAttack method
    vector<Territory*> at = p1->toAttack();
    //Display all territoriest to attack from collection
    cout<<"Territories to attack: ";
    separator="";
    for (auto a_territory : at) {
        cout << separator << a_territory->territory_name;
        separator = ", ";
    }

    cout<<"\n"<<endl;

    //call to issueOrder method
    p1->issueOrder();
    cout<<"List of orders of the player:"<<endl;
    for(int k=0;k<p1->getOrders()->list_orders.size();k++){
        cout<<p1->getOrders()->list_orders[k]->description<<endl;
    }
    cout<<endl;


    //delete pointers
    for(int i=0; i < dt.size();i++){
        delete dt[i];
        dt[i]=NULL;
    }

    for(int j=0; j < at.size();j++){
        delete at[j];
        at[j]=NULL;
    }

    delete p1;
    delete p2;
    p1=NULL;
    p2=NULL;

    return 0;
}

