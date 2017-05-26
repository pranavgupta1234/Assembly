#ifndef CHAINEDMAP_HPP_
#define CHAINEDMAP_HPP_
#define INITIAL_SIZE 13
#include "Dictionary.hpp"
#include <math.h>
#include <sstream>
#include <string>

namespace CM
{

template<class Key,class Value> class ChainedMap;

template<class Key, class Value>
class HashTableNode{
    friend ChainedMap<Key,Value>;
    private:
        Key key;
        Value value;
        HashTableNode<Key,Value> *link;
};

template<class Key, class Value>
//syntax for derived classes (ie Chained Map inherits Dictionary)
class ChainedMap  : public Dictionary<Key,Value>

{

private:

    HashTableNode<Key,Value>** node;
    std::stringstream ss;
    std::string key_in_string;
    int size;                                   //denotes size of hash table at any instant

    //keeps track of length of chain at each node
    int* length;
    /*
     * Function rehash:
     * Resizes the hash table to the next convenient size.
     * Called when all the slots are full and a new element needs to be inserted.
     */
	void rehash();

    //hash function must not be accessible so private
    int hashFunc(Key key){
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

        return changed_key % size;
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

    int getSize();

    int* getLength();

    HashTableNode<Key,Value>** getNodesList();

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
            length[hashed_value]--;
            return ;
        }

        while(temp_head-> key != key){
            prev = temp_head;
            temp_head = temp_head->link;
        }
        prev->link = temp_head->link;
        length[hashed_value]--;
    }
}

template<class Key, class Value>
Value ChainedMap<Key,Value> :: get(const Key& key){

    int hashed_value = hashFunc(key);
    std::cout<<hashed_value<<std::endl;

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

    if(!has(key)){

        if(length[hashed_value] > size/2 + 1){
            rehash();
            put(key,value);
        }

        HashTableNode<Key,Value>* newHashTableNode = new HashTableNode<Key,Value>();
        newHashTableNode-> key = key;
        newHashTableNode-> value = value;
        newHashTableNode ->link = node[hashed_value];
        node[hashed_value] = newHashTableNode;

        //increment length in the list;
        length[hashed_value]++;   
    }
}

template<class Key,class Value>
void ChainedMap<Key,Value> :: rehash(){

    //declare a new table with twice size
    int* temp_len = new int[2*size];

    //initialise all with zero
    for(int i=0;i<2*size;i++){
        temp_len[i]=0;
    }

    //copy the previous lengths
    for(int i=0;i<size;i++){
        temp_len[i]=length[i];
    }

    //erase all previous values
    delete[] length;

    //reassign to new array
    length = temp_len;

    //free the temporary memory
    //delete temp_len;

    //std::cout<<"rehashed"<<std::endl;


    HashTableNode<Key,Value>** temp_node = new HashTableNode<Key,Value>*[2*size];

    for(int i=0;i<2*size;i++){
        temp_node[i] = NULL;
    }

    //copies whole linked list hashed table
    for(int i=0;i<size;i++){

        temp_node[i] = node[i];
        HashTableNode<Key,Value>* reHashNode = node[i];

        while( reHashNode!= NULL){

            HashTableNode<Key,Value>* newReHashTableNode = new HashTableNode<Key,Value>();
            newReHashTableNode-> key = reHashNode-> key;
            newReHashTableNode-> value = reHashNode -> value;
            newReHashTableNode ->link = temp_node[i];
            temp_node[i] = newReHashTableNode;
            reHashNode = reHashNode -> link;

        } 
    }

    delete node;

    node = new HashTableNode<Key,Value>*[2*size];

    for(int i=0;i<2*size;i++){
        node[i] = NULL;
    }

    size = 2*size;              //update size of the table before rehashing

    for(int i=0;i<size;i++){
        length[i]=0;
    }

    //start rehashing into original from the copied one
    for(int i=0 ; i < size/2 ; i++){

        HashTableNode<Key,Value>* readyToRehash = temp_node[i];
        
        while(readyToRehash != NULL){
            put(readyToRehash->key,readyToRehash->value);
            readyToRehash = readyToRehash -> link;
        }

    }

}

template<class Key,class Value>
ChainedMap<Key,Value> :: ChainedMap(){
    node = new HashTableNode<Key,Value>*[INITIAL_SIZE];
    for(int i=0;i<INITIAL_SIZE;i++){
        node[i]=NULL;
    }

    size = INITIAL_SIZE;

    //take initial 0 length for all lists
    length = new int[INITIAL_SIZE];

    //initialise all of them with zero
    for(int i=0;i<INITIAL_SIZE;i++){
        length[i]=0;
    }

}

template<class Key,class Value>
ChainedMap<Key,Value> :: ChainedMap(const int& num){
    node = new HashTableNode<Key,Value>*[num];
    for(int i=0;i<num;i++){
        node[i]=NULL;
    }

    size = num;

    //take initial 0 length for all lists
    length = new int[num];

    //initialise all of them with zero
    for(int i=0;i<INITIAL_SIZE;i++){
        length[i]=0;
    }

}

template<class Key,class Value>
ChainedMap<Key,Value> :: ChainedMap(ChainedMap<Key,Value>& cm){
    node = new HashTableNode<Key,Value>*[cm.getSize()];
    
    for(int i=0;i<cm.getSize();i++){
        node[i]=NULL;
    }

    size = cm.getSize();

    //take initial 0 length for all lists
    length = new int[cm.getSize()];

    //get all lengths
    int* l = cm.getLength();
    //get nodes pointer list
    HashTableNode<Key,Value>** n;
    n = cm.getNodesList();

    //copy all lengths
    for(int i=0;i<cm.getSize();i++){
        length[i]=l[i];
    }

    for(int i=0;i<cm.getSize();i++){
        node[i] = n[i];
        HashTableNode<Key,Value>* temp_node = n[i];

        while(temp_node != NULL){
            if(!has(temp_node->key)){
                HashTableNode<Key,Value>* copyNode = new HashTableNode<Key,Value>();
                copyNode -> key = temp_node -> key;
                copyNode -> value = temp_node -> value;
                copyNode -> link = node[i];
                node[i] = copyNode;
                temp_node = temp_node -> link;
            }else{
                temp_node = temp_node -> link;
            }
        }
    }
}

template<class Key,class Value>
int ChainedMap<Key,Value> :: getSize(){
    return size;
}

template<class Key,class Value>
int* ChainedMap<Key,Value> :: getLength(){
    return length;
}

template<class Key,class Value>
HashTableNode<Key,Value>** ChainedMap<Key,Value> :: getNodesList(){
    return node;
}

template<class Key,class Value>
ChainedMap<Key,Value> :: ~ChainedMap(){
    for(int i=0;i<size;i++){

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
    delete[] length;
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

    for(int i=0;i<size;i++){

        HashTableNode<Key,Value>* head = node[i];

        std::cout<<"Table Index "<<i<<" with linked list of length "<<length[i]<<std::endl;

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