#include <iostream>
using namespace std;
#include "HelloWorld.h"


void HelloWorld::print() {
	cout << "Hello world";
}

int main() {
	HelloWorld test;
	test.print();
	return 0;
}