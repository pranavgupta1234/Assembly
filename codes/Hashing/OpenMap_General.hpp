#ifndef OPENMAP_HPP_
#define OPENMAP_HPP_
#include "Dictionary.hpp"
#include <climits>
#include <sstream>
#include <math.h>

#define INITIAL_VALUE 3
#define MARKER INT_MAX

namespace OM
{

template<class Key, class Value>
class OpenMap  : public Dictionary<Key,Value>
{

private:

    Key* key;
    Value* value;
    int size;
    Value initial_value,marker_key;
    Key initial_key,marker_value;
    std::stringstream ss;
    std::string key_in_string;
    /*
     * Function rehash:
     * Resizes the has table to the next convenient size.
     * Called when all the slots are full and a new element needs to be inserted.
     */
	void rehash();

    //hash function must not be accessible so private
    int hashFunc(Key key);

public:
    
    /*
     * Constructor: OpenMap
     * Creates a Open Hash Table with some default size.
     * NOTE: Please try to ensure that the size is a prime number for better performance.
     */
	
    OpenMap();
    /*
     * Constructor:OpenMap
     * Creates an empty Open Map with the ability to hold atleast num Key value pairs.
     */
	
    OpenMap(const int& num);
    /*
     * Constructor: Open Map
     * Creates a new Hash Table which is the exact copy of the given hash table.
     **/
	OpenMap(OpenMap<Key, Value>& ht);
    /*
     * Destructor
     * Deletes the memory acquired by the given Hash Map.
     */
	~OpenMap();
    /*
     * A convenience wrapper operator.
     * Returns a reference to the value corresponding to the given key.
     * If the key does'nt exist, then inserts the key in the table,
     * with the default value of the Value type.
     * This should enable you to write code like this:
     * OpenMap<int,int> ht;
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

    void setDefaultValues(const Key& k,const Value& value,const Key& marker_key,const Value& marker_value);

    int getSize();

    Key* getKey();

    Value* getValue();

};

template<class Key, class Value>
bool OpenMap<Key,Value> :: has(const Key& k){

    int probe_number = 0;
    int hashed_value = hashFunc(k);

    while( key[hashed_value] != initial_key and probe_number< size ) {

        if(key[hashed_value] == k){
            return true;
        }
        else{
            hashed_value = (hashed_value+1)% size;
            probe_number++;
        }
    }

    if(probe_number== size or value[hashed_value] == initial_value){
        return false;
    }
}

template<class Key, class Value>
void OpenMap<Key,Value> :: remove(const Key& k){

    int probe_number = 0;
    int hashed_value = hashFunc(k);

    while(key[hashed_value] != initial_key and probe_number < size){

        if(key[hashed_value] == k){
            key[hashed_value] = marker_key;
            value[hashed_value] = marker_value;
        }
        else{
            hashed_value = (hashed_value+1)%size;
            probe_number++;
        }
    }

    if(probe_number== size or value[hashed_value] == initial_value){
        return ;
    }    
    
}

template<class Key, class Value>
Value OpenMap<Key,Value> :: get(const Key& k){

    int probe_number = 0;
    int hashed_value = hashFunc(k);

    while(key[hashed_value] != initial_key and probe_number < size){

        if(key[hashed_value] == k){
            return value[hashed_value];
        }
        else{
            hashed_value = (hashed_value +1)%size;
            probe_number++;
        }
    }

    if(hashed_value == size or value[hashed_value] == initial_value){
        return initial_value;
    }

}

template<class Key, class Value>
void OpenMap<Key,Value> :: put(const Key& k, const Value& v){

    int probe_number = 0;
    int hashed_value = hashFunc(k);

    if(!has(k)){

        while(key[hashed_value] != initial_key and key[hashed_value] != marker_key and probe_number< size ) {
            hashed_value = (hashed_value+1)%size;
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
            hashed_value = (hashed_value+1)% size;
            //std::cout<<"Hii";
        }

        value[hashed_value] = v;

    }
}

template<class Key, class Value>
void OpenMap<Key,Value> :: rehash() {

    int newSize = size + 1;

    Key* newKeys = new Key[newSize];
    Value* newValues = new Value[newSize];

    for(int i=0;i<newSize;i++){
        newKeys[i]=initial_key;
        newValues[i]=initial_value;
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
OpenMap<Key,Value> :: OpenMap(){

    key = new Key[INITIAL_VALUE];
    value = new Value[INITIAL_VALUE];
    size = INITIAL_VALUE;

/*    for(int i=0;i<size;i++){
        key[i]=0;
        value[i]=0;
    }*/
}

template<class Key, class Value>
OpenMap<Key,Value> :: OpenMap(const int& num){

    key = new Key[num];
    value = new Value[num];
    size = num;

/*    for(int i=0;i<size;i++){
        key[i]=0;
        value[i]=0;
    }*/
}

template<class Key, class Value>
OpenMap<Key,Value> :: OpenMap(OpenMap<Key,Value>& ht){

    key = new Key[ht.getSize()];
    value = new Value[ht.getSize()];
    size = ht.getSize();

    Key* k = ht.getKey();
    Value* v = ht.getValue();

    for(int i=0;i<ht.getSize();i++){
        key[i]=k[i];
        value[i]=v[i];
    }
}

template<class Key,class Value>
Key* OpenMap<Key,Value> :: getKey(){
    return key;
} 

template<class Key,class Value>
Value* OpenMap<Key,Value> :: getValue(){
    return value;
} 

template<class Key,class Value>
int OpenMap<Key,Value> :: getSize(){
    return size;
}

template<class Key,class Value>
OpenMap<Key,Value> :: ~OpenMap(){

    delete[] key;
    delete[] value;

}

template<class Key, class Value>
int OpenMap<Key,Value> :: hashFunc(Key key){
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
void OpenMap<Key,Value> :: printTable(){

    for(int i=0;i<size;i++){
        std::cout<<key[i]<<" "<<value[i]<<std::endl;
    }
    std::cout<<std::endl;
}

template<class Key,class Value>
Value& OpenMap<Key,Value> :: operator[](const Key& k){
    
    int probe_number = 0;
    int hashed_value = hashFunc(k);

    if(has(k)){

        while(value[hashed_value] != initial_value and probe_number< size){
            if(key[hashed_value] == k){
                return value[hashed_value];                
            }else{
                hashed_value = (hashed_value+1)%size;
                probe_number++;
            }

        }

    }else{

        put(k,0);

        while(key[hashed_value]!= initial_key and probe_number< size){

                if(key[hashed_value] == k){
                    return value[hashed_value];
                }else{
                    hashed_value = (hashed_value+1)%size;
                    probe_number++;
                }
        }
    }
}

template<class Key,class Value>
void OpenMap<Key,Value> :: setDefaultValues(const Key& k,const Value& val,const Key& mark_key,const Value& mark_value){

    marker_value = mark_value;
    marker_key = mark_key;

    for(int i=0 ; i < size ; i++){
        key[i] = k;
        value[i] = val;
    }

}

//end of namespace OM
}

#endif 