#include <iostream>
#include <stdlib.h>
#include "OpenMap.hpp"

int options(){

	int choice;

	std::cout<<std::endl;
	std::cout<<"[1] Insert an element"<<std::endl;
	std::cout<<"[2] Delete an element"<<std::endl;
	std::cout<<"[3] View an element"<<std::endl;
	std::cout<<"[4] Check a key."<<std::endl;
	std::cout<<"[0] Exit"<<std::endl;

	std::cout<<"Enter your choice : ";
	std::cin>>choice;
	std::cout<<std::endl;

	return choice;
}

int main(int argc, char* argv[]){

	OM::OpenMap<int, int> openMap;

	int key;
	int value;

	while(true){

		switch(options()){

			case 1	:	std::cout<<"Enter key : ";
						std::cin>>key;
						std::cout<<"Enter value : ";
						std::cin>>value;
						openMap.put(key, value);
						break;

			case 2	:	std::cout<<"Enter key : ";
						std::cin>>key;
						openMap.remove(key);
						break;

			case 3 	:	std::cout<<"Enter key : ";
						std::cin>>key;
						try{
							std::cout<<openMap.get(key)<<std::endl;
						}
						catch(const char* err){
							std::cerr<<err<<std::endl;
						}
						break;

			case 4	:	std::cout<<"Enter key : ";
						std::cin>>key;
						std::cout<<(openMap.has(key)? "Exists." : "Does not exist.")<<std::endl;
						break;

			case 0	:	exit(EXIT_SUCCESS);

			default	:	std::cout<<"Invalid choice."<<std::endl;
						break;
		}
	}

	return 0;
}