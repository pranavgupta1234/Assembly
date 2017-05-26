#include <iostream>
#include <string>
#include <climits>
#include "ChainedMap_General.hpp"
#include <string>

using namespace std;

int main(){

	CM::ChainedMap<int,int> map;
	//map.setDefaultValues("","","emp","e");
	
	map.put(1,2);
	map.put(2,5);
	map.put(3,6);
	map.put(78,54);

	CM::ChainedMap<int,int> map2(map);

	map2.printTable();

	return 0;
}