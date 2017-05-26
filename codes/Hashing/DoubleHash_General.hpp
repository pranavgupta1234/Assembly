#ifndef DOUBLEHASHMAP_HPP_
#define DOUBLEHASHMAP_HPP_
#include <climits>                      //to get value of INT_MAX
#include "Dictionary.hpp"
#include <math.h>
#include <sstream>
#define INITIAL_VALUE 7
#define MARKER INT_MAX

namespace DH{

template<class Key, class Value>
class DoubleHashMap  : public Dictionary<Key,Value>
{
private:

    Key* key;
    Value* value;
    int size;
    Value initial_value,marker_value;
    Key initial_key,marker_key;
    std::stringstream ss;
    std::string key_in_string;
    /*
     * Function rehash:
     * Resizes the has table to the next convenient size.
     * Called when all the slots are full and a new element needs to be inserted.
     */
	void rehash();

    //hashfunction to find the value
    int hashFunc(Key key);

    //hashfunction to find offset in case of collision
    int hashFuncOffset(Key key); 

public:
    /*
     * Constructor: DoubleHashMap
     * Creates a Double Hash Hash Table with some default size.
     * NOTE: Please try to ensure that the size is a prime number for better performance.
     */
	DoubleHashMap();
    /*
     * Constructor:DoubleHashMap
     * Creates an empty Double Hash Map with the ability to hold atleast num Key value pairs.
     */
	DoubleHashMap(const int& num);
    /*
     * Constructor: Double Hash Map
     * Creates a new Hash Table which is the exact copy of the given hash table.
     **/
	DoubleHashMap(DoubleHashMap<Key, Value>& ht);
    /*
     * Destructor
     * Deletes the memory acquired by the given Hash Map.
     */
	~DoubleHashMap();
    /*
     * A convenience wrapper operator.
     * Returns a reference to the value corresponding to the given key.
     * If the key does'nt exist, then inserts the key in the table,
     * with the default value of the Value type.
     * This should enable you to write code like this:
     * DoubleHashMap<int,int> ht;
     * ht[1] = 2;
     * ht[1] = 4;
     * ht[2] = 3;
     */
	Value& operator[](const Key& key);
    /*
     * Function : has
     * Returns true if the dictionay contains the key
     * false otherwise. It is search operation
     */
    bool has(const Key& key);
    /*
     * Function : remove
     * Removes the given key and the corresponding value from the Dictionary if the key is in the dictionary.
     * Does nothing otherwise.
     */
    void remove(const Key& key);
    /*
     * Function : get
     * Returns the value associated with the given key.
     * Raises an exception if the key does'nt exist in the dictionary.
     */
    Value get(const Key& key);
    /*
     * Function : put
     * If the key does'nt exist in the dictionary, then insert the given key and value in the dictionary.
     * Otherwise change the value associated with the key to the given value.
     */
    void put(const Key& key, const Value& value);

    void printTable();

    bool isPrime(int n);

    int findNextPrime(int n);

    int sizeTable();

    void setDefaultValues(const Key& k,const Value& val,const Key& mark_k,const Value& mark_v);

    int getSize();

    Key* getKey();

    Value* getValue();
};


template<class Key, class Value>
bool DoubleHashMap<Key,Value> :: has(const Key& k){

    int probe_number = 0;
    int hashed_value = hashFunc(k);
    int offset = hashFuncOffset(k);

    while( key[hashed_value] !=initial_key and probe_number< size ) {

        if(key[hashed_value] == k){
            return true;
        }
        else{
            hashed_value = (hashed_value+offset)% size;
            probe_number++;
        }
    }

    if(probe_number== size or value[hashed_value] == initial_value){
        return false;
    }
}

template<class Key, class Value>
void DoubleHashMap<Key,Value> :: remove(const Key& k){

    int probe_number = 0;
    int hashed_value = hashFunc(k);
    int offset = hashFuncOffset(k);

    while(key[hashed_value] != initial_key and probe_number < size){

        if(key[hashed_value] == k){
            key[hashed_value] = marker_key;
            value[hashed_value] = marker_value;
        }
        else{
            hashed_value = (hashed_value+offset)%size;
            probe_number++;
        }
    }

    if(probe_number== size or value[hashed_value] == initial_value){
        return ;
    }    
    
}

template<class Key, class Value>
Value DoubleHashMap<Key,Value> :: get(const Key& k){

    int probe_number = 0;
    int hashed_value = hashFunc(k);
    int offset = hashFuncOffset(k);

    while(key[hashed_value] != initial_key and probe_number < size){

        if(key[hashed_value] == k){
            return value[hashed_value];
        }
        else{
            hashed_value = (hashed_value + offset )%size;
            probe_number++;
        }
    }

    if(hashed_value == size or value[hashed_value] == initial_value){
        return initial_value;
    }

}

template<class Key, class Value>
void DoubleHashMap<Key,Value> :: put(const Key& k, const Value& v){

    int probe_number = 0;
    int hashed_value = hashFunc(k);
    int offset = hashFuncOffset(k);

    if(!has(k)){

        while(key[hashed_value] != initial_value and key[hashed_value] != marker_key and probe_number< size ) {
            hashed_value = (hashed_value+offset)%size;
            probe_number++;
        }

        if(probe_number==size){

            //std::cout<<"Hash Table Full"<<std::endl;
            rehash();
            put(k,v);

        }
        else{

            key[hashed_value] = k;
            value[hashed_value] = v;
        }

    }else{

        while(key[hashed_value]!=k){
            hashed_value = ( hashed_value + offset) % size;
        }

        value[hashed_value] = v;

    }
}

template<class Key, class Value>
void DoubleHashMap<Key,Value> :: rehash() {
    
    int newSize = findNextPrime(size);

    Key* newKeys = new Key[newSize];
    Value* newValues = new Value[newSize];

    for(int i=0;i<newSize;i++){
        newKeys[i]= initial_key;
        newValues[i]= initial_value;
    }

    for(int i=0;i<newSize-1;i++){
        newKeys[i]= key[i];
        newValues[i] = value[i];
    }

    delete key;
    delete value;

    key = newKeys;
    value = newValues;

    Key* reHashedKeys = new Key[newSize];
    Value* reHashedValues = new Value[newSize];

    for(int i=0;i<size;i++){

        reHashedKeys[i] = key[i];
        key[i]=initial_key;
        reHashedValues[i] = value[i];
        value[i]=initial_value;
    } 

    size = newSize ;


    for(int i=0;i<size-1;i++){

        put(reHashedKeys[i],reHashedValues[i]);

    }
}

template<class Key, class Value>
DoubleHashMap<Key,Value> :: DoubleHashMap(){

    key = new Key[INITIAL_VALUE];
    value = new Value[INITIAL_VALUE];
    size = INITIAL_VALUE;

    // for(int i=0;i<size;i++){
    //     key[i]=0;
    //     value[i]=0;                      //do not initialise to some hardcoded value
    // }
}

template<class Key, class Value>
DoubleHashMap<Key,Value> :: DoubleHashMap(const int& num){

    key = new Key[num];
    value = new Value[num];
    size = num;

    // for(int i=0;i<size;i++){
    //     key[i]=0;
    //     value[i]=0;
    // }
}

template<class Key,class Value>
DoubleHashMap<Key,Value> :: DoubleHashMap(DoubleHashMap<Key,Value>& dhm){

    key = new Key[dhm.getSize()];
    value = new Value[dhm.getSize()];

    size = dhm.getSize();

    Key* k = dhm.getKey();
    Value* v = dhm.getValue();

    for(int i=0;i<dhm.getSize();i++){
        key[i]=k[i];
        value[i]=v[i];
    }
}

template<class Key,class Value>
int DoubleHashMap<Key,Value> :: getSize(){
    return size;
}

template<class Key,class Value>
Key* DoubleHashMap<Key,Value> :: getKey(){
    return key;
}

template<class Key,class Value>
Value* DoubleHashMap<Key,Value> :: getValue(){
    return value;
}

template<class Key,class Value>
DoubleHashMap<Key,Value> :: ~DoubleHashMap(){

    delete[] key;
    delete[] value;

}

template<class Key,class Value>
int DoubleHashMap<Key,Value> :: sizeTable(){
    return size;
}

template<class Key, class Value>
int DoubleHashMap<Key,Value> :: hashFunc(Key key){
        //ss.flush();           //they are not clearing the stringstream    The clear() member function is inherited from ios 
                                //and is used to clear the error state of the stream, e.g. if a file stream has the error
                                //state set to eofbit (end-of-file), then calling clear() will set the error state back to goodbit (no error).
        //ss.clear();
        ss.str("");                //this is correct way of clearing the stream
        key_in_string.erase();
        int changed_key = 0;
        ss<<key;
        key_in_string = ss.str();

        for(int i=0;i<key_in_string.size();i++){

            changed_key = changed_key + int(key_in_string[i])*pow(7,i);
        
        }

        return changed_key % INITIAL_VALUE;
}

template<class Key, class Value>
int DoubleHashMap<Key,Value> :: hashFuncOffset(Key key){
        //ss.flush();           //they are not clearing the stringstream    The clear() member function is inherited from ios 
                                //and is used to clear the error state of the stream, e.g. if a file stream has the error
                                //state set to eofbit (end-of-file), then calling clear() will set the error state back to goodbit (no error).
        //ss.clear();
        ss.str("");                //this is correct way of clearing the stream
        key_in_string.erase();
        int changed_key = 0;
        ss<<key;
        key_in_string = ss.str();

        for(int i=0;i<key_in_string.size();i++){

            changed_key = changed_key + int(key_in_string[i])*pow(7,i);
        
        }
    return size - (changed_key % size) ;
}

template<class Key, class Value>
void DoubleHashMap<Key,Value> :: printTable(){

    for(int i=0;i<size;i++){
        
        std::cout<<key[i]<<" "<<value[i]<<std::endl;            
    
    }
    std::cout<<std::endl;
}

template<class Key,class Value>
Value& DoubleHashMap<Key,Value> :: operator[](const Key& k){
    
    int probe_number = 0;
    int hashed_value = hashFunc(k);
    int offset = hashFuncOffset(k);

    if(has(k)){

        while(value[hashed_value] != initial_value and probe_number< size){
            if(key[hashed_value] == k){
                return value[hashed_value];                
            }else{
                hashed_value = (hashed_value+offset)%size;
                probe_number++;
            }

        }

    }else{

        put(k,0);

        while(key[hashed_value]!= initial_key and probe_number< size){

                if(key[hashed_value] == k){
                    return value[hashed_value];
                }else{
                    hashed_value = (hashed_value+offset)%size;
                    probe_number++;
                }
        }
    }
}

//given a number n, find the next closest prime number above n
template<class Key,class Value>
int DoubleHashMap<Key,Value> :: findNextPrime(int n){
    int nextPrime = n;
    bool found = false;

    //loop continuously until isPrime returns true for a number above n
    while (!found)
    {
        nextPrime++;
        if (isPrime(nextPrime))
            found = true;
    }

    return nextPrime;
}

//given a number n, determine if it is prime
template<class Key,class Value>
bool DoubleHashMap<Key,Value> :: isPrime(int n){
    //loop from 2 to n/2 to check for factors
    for (int i = 2; i <= n/2; i++)
    {
        if (n % i == 0)     //found a factor that isn't 1 or n, therefore not prime
            return false;
    }

    return true;
}

template<class Key,class Value>
void DoubleHashMap<Key,Value> :: setDefaultValues(const Key& k,const Value& val,const Key& mark_k,const Value& mark_v){

    marker_key = mark_k;
    marker_value = mark_v;

    for(int i=0 ; i < size ; i++){
        key[i] = k;
        value[i] = val;
    }

}

//end of namespace DH
}

#endif 