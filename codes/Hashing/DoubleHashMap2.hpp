#ifndef DOUBLEHASHMAP_HPP_
#define DOUBLEHASHMAP_HPP_

#include <climits>

int NIL = INT_MAX;
int MARKER = INT_MIN;

#include "seqLinearList.hpp"
#include "Dictionary.hpp"
#include <math.h>

namespace cs202
{
    int findPrime(const int& num){
        bool isPrime;
        int i;

        if(i <= 1){
            return 2;
        }

        for(i = num; ; i++){
            isPrime = true;

            for(int j = 2; j <= sqrt(i) && isPrime; j++){
                if(i%j == 0)
                    isPrime = false;
            }

            if(isPrime)
                break;
        }

        return i;
    }

    template<class Key, class Value>
    class DoubleHashMap  : public Dictionary<Key,Value>
    {
        LinearList<pair<Key, Value> > _hashTable;
        int _size;
        /*
         * Function rehash:
         * Resizes the has table to the next convenient size.
         * Called when all the slots are full and a new element needs to be inserted.
         */
    	void rehash();
        /*
         * Function hashFunction:
         * When search is true, it returns index of the key in map
         * When search is false, it return appropriate index for the key in map
         */
        int hashFunction(const Key& key, bool search);
        
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
    };

    template<class Key, class Value>
    DoubleHashMap<Key, Value>::DoubleHashMap(){
        _size = 11;
        _hashTable.resize(_size);
        _hashTable.fill(pair<Key, Value>(NIL, NIL));
    }

    template<class Key, class Value>
    DoubleHashMap<Key, Value>::DoubleHashMap(const int& num){
        
        _size = findPrime(num);
        _hashTable.resize(_size);
        _hashTable.fill(pair<Key, Value>(NIL, NIL));
    }

    template<class Key, class Value>
    DoubleHashMap<Key, Value>::DoubleHashMap(DoubleHashMap<Key, Value>& ht){
        _size = ht._size;
        _hashTable.resize(_size);

        for(int i = 0; i < _size; i++)
            _hashTable[i] = ht._hashTable[i];
    }

    template<class Key, class Value>
    DoubleHashMap<Key, Value>::~DoubleHashMap(){
        _size = 0;
    }

    template<class Key, class Value>
    Value& DoubleHashMap<Key, Value>::operator[](const Key& key){
    
        int index = hashFunction(key, true);

        //When the key does not exist.
        if(index == NIL){
            index = hashFunction(key, false);

            //When hash map is full.
            if(index == NIL){

                rehash();
                index = hashFunction(key, false);         
            }

            _hashTable[index] = pair<Key, Value>(key, NIL);
        }

        return _hashTable[index].value();
           
    }

    template<class Key, class Value>
    int DoubleHashMap<Key, Value>::hashFunction(const Key& key, bool search){

        Key parameter = search? key : NIL; 
        int index = key % _size;
        int i = 1;
        int offset = (_size/2) - (key % (_size/2));

        while(_hashTable[index].key() != parameter && i < _size){
            
            //search is true and key is NIL then key does not exits
            if(search && _hashTable[index].key() == NIL)
                return NIL;

            //search is false and index->key is marker then key can be inserted at index
            if(!search && _hashTable[index].key() == MARKER)
                break;
            
            index = (index + offset) % _size;
            i++;
        }

        if(i == _size)
            return NIL;

        return index;
    }

    template<class Key, class Value>
    bool DoubleHashMap<Key, Value>::has(const Key& key){

        int index = hashFunction(key, true);

        if(index == NIL)
            return false;

        return true;
    }

    template<class Key, class Value>
    void DoubleHashMap<Key, Value>::remove(const Key& key){

        int index = hashFunction(key, true);

        if(index != NIL){
            _hashTable[index] = pair<Key, Value>(MARKER, NIL);
        }
    }

    template<class Key, class Value>
    Value DoubleHashMap<Key, Value>::get(const Key& key){

        int index = hashFunction(key, true);

        if(index != NIL)
            return _hashTable[index].value();
        else
            throw "** Key not found!";
    }

    template<class Key, class Value>
    void DoubleHashMap<Key, Value>::put(const Key& key, const Value& value){

        int index = hashFunction(key, true);

        //When key exists.
        if(index != NIL){
            _hashTable[index].value() = value;
            return;
        }

        index = hashFunction(key, false);

        //When hash map is full.
        if(index == NIL){
            rehash();
            index = hashFunction(key, false);           
        }

        _hashTable[index] = pair<Key, Value>(key, value);
    }

    template<class Key, class Value>
    void DoubleHashMap<Key, Value>::rehash(){

        int newSize = findPrime(_size + 1);
        
        LinearList<pair<Key, Value> > tmpHash(_size);
        tmpHash.fill(pair<Key, Value>(NIL, NIL));

        for(int i = 0; i < _size; i++){
            if(_hashTable[i].key() != (Key)NIL){
                tmpHash[i] = _hashTable[i];
            }
        }

        _size = newSize;

        _hashTable.resize(_size);
        _hashTable.fill(pair<Key, Value>(NIL, NIL));

        while(!tmpHash.empty()){
            if(tmpHash[0].key() != NIL)
                put(tmpHash[0].key(), tmpHash[0].value());
          
            tmpHash.erase_pos(0);
        }

    }
}

#endif 