#include <iostream>
#include <stdlib.h>
#include <string>
#include "DoubleHashMap2.hpp"

int main(int argc,char* argv[]){

	int blocks_main, blocks_cache, blocks, input, max;

	if(argc<=3){
		std::cout<<"Too few arguments..,first parameter is blocks in main memory,second is blocks in cache memory,third is size of blocks"<<std::endl;
		exit(0);
	}

	blocks_main = atoi(argv[1]);
	blocks_cache = atoi(argv[2]);
	blocks = atoi(argv[3]);

	if(blocks > blocks_main or  blocks > blocks_cache){
		std::cout<<"Not Possible\n";
		exit(0);
	}

	blocks_main = blocks_main/blocks, blocks_cache = blocks_cache/blocks;

	cs202::DoubleHashMap<int, int> cache(blocks_cache);
	cs202::LinearList<pair<int, int> > counter(blocks_cache);

	while(1){

		std::cout<<"Address Main Memory (-1 for exit): ";
		std::cin>>input;


		if(input < 0)
			exit(EXIT_SUCCESS);

		input /= blocks;

		if(input >= blocks_main){
			std::cout<<"This memory address doesn't exist\n";
			exit(EXIT_SUCCESS);
		}

		if(counter.size() == blocks_cache && !cache.has(input)){
			max = 0;
			for(int i = 0; i < counter.size(); i++){
				if(counter[i].value() > counter[max].value()){
					max = i;
				}
			}

			cache.remove(counter[max].key());
			counter.erase_pos(max);
		}

		if(!cache.has(input)){
			counter.push_back(pair<int, int>(input, 0));
			cache[input] = input;
		}

		for(int i = 0; i < counter.size(); i++){
			if(counter[i].key() != input){
				counter[i].value() += 1;
			}
			else
				counter[i].value() = 0;
		}

		std::cout<<"CacheMemory holds : CacheCounters \n";
		for(int i = 0; i < counter.size(); i++){
			
			std::cout<<"MainMemory["<<cache[counter[i].key()]<<"] \t : "<<counter[i].value()<<std::endl;
		}

	}
	return 0;
}