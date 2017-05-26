/*
 * ChainedMap.hpp
 *
 */
#ifndef CHAINEDMAP_HPP_
#define CHAINEDMAP_HPP_
#define INITIAL_SIZE 13
 #include "Dictionary.hpp"

namespace CM
{

template<class Key,class Value> class ChainedMap;

template<class Key, class Value>
class HashTableNode{
    friend ChainedMap<Key,Value>;
    private:
        Key key;
        Value value;
        HashTableNode<Key,Value> * link;
};

template<class Key, class Value>
//syntax for derived classes (ie Chained Map inherits Dictionary)
class ChainedMap  : public Dictionary<Key,Value>

{

private:

    HashTableNode<Key,Value>** node;
    /*
     * Function rehash:
     * Resizes the hash table to the next convenient size.
     * Called when all the slots are full and a new element needs to be inserted.
     */
	void rehash();

    //hash function must not be accessible so private
    int hashFunc(Key key){
        return key % INITIAL_SIZE;
    }

public:
    /*
     * Constructor: ChainedMap
     * Creates a Chained Hash Table with some default size.
     * NOTE: Please try to ensure that the size is a prime number for better performance.
     */
	ChainedMap();
    /*
     * Constructor:ChainedMap
     * Creates an empty Chained Map with the ability to hold atleast num Key value pairs.
     */
	ChainedMap(const int& num);
    /*
     * Constructor: Chained Map
     * Creates a new Hash Table which is the exact copy of the given hash table.
     **/
	ChainedMap(ChainedMap<Key, Value>& ht);
    /*
     * Destructor
     * Deletes the memory acquired by the given Hash Map.
     */
	~ChainedMap();
    /*
     * A convenience wrapper operator.
     * Returns a reference to the value corresponding to the given key.
     * If the key does'nt exist, then inserts the key in the table,
     * with the default value of the Value type.
     * This should enable you to write code like this:
     * ChainedHashMap<int,int> ht;
     * ht[1] = 2;
     * ht[1] = 4;
     * ht[2] = 3;
     */
	Value& operator[](const Key& key);

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

};

template<class Key, class Value>
bool ChainedMap<Key,Value> :: has(const Key& key){ 
    
    int hashed_value = hashFunc(key);

    //get the head of list
    HashTableNode<Key,Value>* head = node[hashed_value];

    while(head!=NULL){

        if(head->key == key){
            return true;
        }

        head = head -> link;
    }

    return false;

}

template<class Key, class Value>
void ChainedMap<Key,Value> :: remove(const Key& key){

    int hashed_value = hashFunc(key);
    
    //node[hashed_value] is where head lies

     if(node[hashed_value]!=NULL){

        HashTableNode<Key,Value>* temp_head = node[hashed_value];
        HashTableNode<Key,Value>* prev;

        if(node[hashed_value]->key == key){

            HashTableNode<Key,Value>* to_be_deleted = node[hashed_value] ->link;            
            node[hashed_value] = node[hashed_value] -> link;
            //delete deleted the value present at the address supplied to it
            delete to_be_deleted;

            return ;
        }

        while(temp_head-> key != key){
            prev = temp_head;
            temp_head = temp_head->link;
        }
        prev->link = temp_head->link;
    }
}

template<class Key, class Value>
Value ChainedMap<Key,Value> :: get(const Key& key){

    int hashed_value = hashFunc(key);
    
    //get the head of list
    HashTableNode<Key,Value>* head = node[hashed_value];    

    while(head!=NULL){

        if( head-> key == key){
            return head -> value;
        }
    }
}

template<class Key, class Value>
void ChainedMap<Key,Value> :: put(const Key& key, const Value& value){

    int hashed_value = hashFunc(key);

    HashTableNode<Key,Value>* newHashTableNode = new HashTableNode<Key,Value>();
    newHashTableNode-> key = key;
    newHashTableNode-> value = value;
    newHashTableNode ->link = node[hashed_value];
    node[hashed_value] = newHashTableNode;
}

template<class Key,class Value>
ChainedMap<Key,Value> :: ChainedMap(){
    node = new HashTableNode<Key,Value>*[INITIAL_SIZE];
    for(int i=0;i<INITIAL_SIZE;i++){
        node[i]=NULL;
    }
}

template<class Key,class Value>
ChainedMap<Key,Value> :: ChainedMap(const int& num){
    node = new HashTableNode<Key,Value>*[num];
    for(int i=0;i<num;i++){
        node[i]=NULL;
    }
}

template<class Key,class Value>
ChainedMap<Key,Value> :: ~ChainedMap(){
    for(int i=0;i<INITIAL_SIZE;i++){

        //get links to the linked lists one by one
        HashTableNode<Key,Value>* temp = node[i];

        while(temp!=NULL){
            HashTableNode<Key,Value>* prev = temp;
            temp = temp -> link;
            delete prev;
        }
    }

    //finally erase the list which holds reference to all heads of list
    delete[] node;
}

template<class Key,class Value>
Value& ChainedMap<Key,Value> :: operator[](const Key& key){

    int hashed_value = hashFunc(key);
    
    //get the head of list
    HashTableNode<Key,Value>* head = node[hashed_value];

    while(head != NULL){
        if(head -> key == key){
            return head->value;
        }
        head = head -> link;
    }
}

template<class Key,class Value>
void ChainedMap<Key,Value> :: printTable(){

    for(int i=0;i<INITIAL_SIZE;i++){

        HashTableNode<Key,Value>* head = node[i];

        std::cout<<"Table Index "<<i<<std::endl;

        while(head!=NULL){

            std::cout<<head->key<<" -> "<<head -> value<<std::endl;

            head = head -> link;
        }

        std::cout<<std::endl;
    }
}

//end of namespace cs202
}

#endif /* CHAINEDMAP_HPP_ */