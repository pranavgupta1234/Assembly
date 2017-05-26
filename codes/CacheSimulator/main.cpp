#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <math.h>

#include "seqLinearList.hpp"
#include "list.hpp"

using namespace std;
using namespace cs202;

#define BLOCK_SIZE 16
#define EMPTY -1

class stats{
public:
	int miss;
	int hit;
	double missRatio;

	stats(){

		miss = 0;
		hit = 0;
		missRatio = 0;
	}

	stats(int m, int h, double mr){

		miss = m;
		hit = h;
		missRatio = mr;
	}
};

unsigned int convertHex(string hex);
stats FIFO(int size, string filename);
stats FIFO_K_WAY(int K, int size, string filename);
stats LRU(int size, string filename);
stats LRU_K_WAY(int K, int size, string filename);

int main(int argc, char *argv[]){

	LinearList<int> sizes;
	sizes.push_back(1024);
	sizes.push_back(2048);
	sizes.push_back(4096);
	sizes.push_back(8192);
	sizes.push_back(16384);

	//cout.precision(5);
	cout<<"\nRESULTS\n\n";
	cout<<"LRU:\n";
		
	cout<<"MissRatio\\Size\t";
	for(int j = 0 ; j < sizes.size(); j++)
		cout<<sizes[j]<<"\t\t";
	cout<<"\n";

	cout<<"Direct Mapping\t";
	for(int j = 0 ; j < sizes.size(); j++)
		cout<<LRU(sizes[j], argv[1]).missRatio<<"\t";
	cout<<"\n";

	cout<<"2-Way Mapping\t";
	for(int j = 0 ; j < sizes.size(); j++)
		cout<<LRU_K_WAY(2, sizes[j], argv[1]).missRatio<<"\t";
	cout<<"\n";

	cout<<"\nFIFO:\n";
		
	cout<<"MissRatio\\Size\t";
	for(int j = 0 ; j < sizes.size(); j++)
		cout<<sizes[j]<<"\t\t";
	cout<<"\n";

	cout<<"Direct Mapping\t";
	for(int j = 0 ; j < sizes.size(); j++)
		cout<<FIFO(sizes[j], argv[1]).missRatio<<"\t";
	cout<<"\n";

	cout<<"2-Way Mapping\t";
	for(int j = 0 ; j < sizes.size(); j++)
		cout<<FIFO_K_WAY(2, sizes[j], argv[1]).missRatio<<"\t";
	cout<<"\n";
}

unsigned int convertHex(string hex){

	unsigned int dec = 0;
	
	for(int i = 0; i < hex.length() - 1; i++){
		
		if(hex[i] >= '0' && hex[i] <= '9')
			dec += (hex[i] - '0') * pow(16, hex.length() - i - 2);

		if(hex[i] >= 'A' && hex[i] <= 'F')
			dec += (hex[i] - 'A' + 10) * pow(16, hex.length() - i - 2);
	}

	return dec;
}

stats FIFO(int size, string filename){

	//cout<<"Executing FIFO\nSize : "<<size<<"B\n";
	int N = size, cacheMiss = 0, cacheHit = 0;
	string input;
	bool has;
	unsigned int address;

	N /= BLOCK_SIZE;

	ifstream read;

	read.open(filename.c_str(), ios::in);

	if(!read.is_open()){
		exit(EXIT_FAILURE);
	}

	LinearList<int> cache(N);
	cache.fill(EMPTY);

	list<unsigned int> counter;

	while(!read.eof()){

		read >> input;

		address = convertHex(input);

		has = (cache[address%N] == address/N);

		if(!has){

			counter.remove(cache[address%N]*N + (address%N));
			counter.append(address);
			cache[address%N] = address/N;
			cacheMiss++;
		}
		else
			cacheHit++;
	}

	read.close();

	return stats(cacheMiss, cacheHit, (double)cacheMiss/(double)(cacheMiss + cacheHit));
}

stats FIFO_K_WAY(int K, int size, string filename){

	//cout<<"Executing FIFO 2-Way Set Associative\nSize : "<<size<<"B\n";
	int N = size, cacheMiss = 0, cacheHit = 0;
	string input;
	bool has;
	unsigned int address;
	int baseIndex, setIndex;

	N /= BLOCK_SIZE;
	N /= K;

	ifstream read;

	read.open(filename.c_str(), ios::in);

	if(!read.is_open()){
		cout<<"Invalid file.\n";
		exit(EXIT_FAILURE);
	}

	LinearList<int> cache[N];
	
	list<int> counter[N];

	while(!read.eof()){

		read >> input;

		address = convertHex(input);

		baseIndex = address%N;

		setIndex = cache[baseIndex].find(address/N);

		has = setIndex != cache[baseIndex].size();

		if(has){

			cacheHit++;
		}
		else{

			if(cache[baseIndex].size() == K){
				setIndex = cache[baseIndex].find(counter[baseIndex].front());
				cache[baseIndex][setIndex] = address/N;		

				counter[baseIndex].remove(counter[baseIndex].front());		
			}
			else
				cache[baseIndex].push_back(address/N);

			counter[baseIndex].append(address/N);
			cacheMiss++;
		}
	}

	read.close();

	return stats(cacheMiss, cacheHit, (double)cacheMiss/(double)(cacheMiss + cacheHit));
}

stats LRU(int size, string filename){

	//cout<<"Executing LRU\nSize : "<<size<<"B\n";
	unsigned int N = size, address, cacheMiss = 0, cacheHit = 0;
	string input;
	bool has;

	N /= BLOCK_SIZE;

	ifstream read;

	read.open(filename.c_str(), ios::in);

	if(!read.is_open()){
		cout<<"Invalid file.\n";
		exit(EXIT_FAILURE);
	}

	LinearList<unsigned int> cache(N);
	cache.fill(EMPTY);

	list<unsigned int> counter;

	while(!read.eof()){
		read >> input;

		address = convertHex(input);

		has = (cache[address%N] == address/N);

		if(!has){
			
			if(cache[address%N] != -1)
				counter.remove((cache[address%N]*N) + address%N);

			counter.append(address);
			cache[address%N] = address/N;
			cacheMiss++;
		}
		else{

			counter.remove(address);
			counter.append(address);
			cacheHit++;
		}
	}

	read.close();

	return stats(cacheMiss, cacheHit, (double)cacheMiss/(double)(cacheMiss + cacheHit));
}

stats LRU_K_WAY(int K, int size, string filename){


	//cout<<"Executing LRU 2-Way Set Associative\nSize : "<<size<<"B\n";
	int N = size, cacheMiss = 0, cacheHit = 0, baseIndex, setIndex;
	string input;
	bool has;
	unsigned int address;

	N /= BLOCK_SIZE;
	N /= K;

	ifstream read;

	read.open(filename.c_str(), ios::in);

	if(!read.is_open()){
		cout<<"Invalid file.\n";
		exit(EXIT_FAILURE);
	}

	LinearList<int> cache[N];
	list<int> counter[N];

	while(!read.eof()){

		read >> input;

		address = convertHex(input);

		baseIndex = address%N;

		setIndex = cache[baseIndex].find(address/N);

		has = setIndex != cache[baseIndex].size();

		if(has){
			
			counter[baseIndex].remove(address/N);
			cacheHit++;
		}
		else{

			if(cache[baseIndex].size() == K){
				setIndex = cache[baseIndex].find(counter[baseIndex].front());
				cache[baseIndex][setIndex] = address/N;		

				counter[baseIndex].remove(counter[baseIndex].front());		
			}
			else
				cache[baseIndex].push_back(address/N);

			cacheMiss++;
		}

		counter[baseIndex].append(address/N);
	}

	read.close();

	return stats(cacheMiss, cacheHit, (double)cacheMiss/(double)(cacheMiss + cacheHit));
}