#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Cache{

	int size;
	int* memory;

public:

	Cache(){}

	Cache(int size){
		this -> size = size;
	}

	int getSize(){
		return size;
	}

	void setReference(int* memory){
		memory = memory;
	}
};

class Main{

	int size;
	int* memory;

public: 

	Main(){}

	Main(int size){
		this -> size = size;
	}

	int getSize(){
		return size;
	}

	void setReference(int* memory){
		memory = memory;
	}
};

int main(){

	int cms,mms;
	Cache cache_memory;
	Main main_memory;
	int block_size;
	string mapping_function;
	string replacement_policy;

	cout<<"Enter the size of main memory"<<endl;
	cin>>mms;
	main_memory = Main(mms);
	
	cout<<"Enter the size of cache memory"<<endl;
	cin>>cms;
	cache_memory = Cache(cms);

	cout<<"Enter replacement policy (LRU or FIFO)"<<endl;
	cout<<"Enter mapping policy ( or FIFO)"<<endl;
	main_memory.setReference(new int[mms]);
	cache_memory.setReference(new int[cms]);




	return 0;
}