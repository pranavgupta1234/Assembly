/*
 * Dictionary.hpp
*/
#ifndef DICTIONARY_HPP_
#define DICTIONARY_HPP_


template<class Key, class Value>
class Dictionary;

template<class Key, class Value>
class pair{

    Key _key;
    Value _value;

    public:

        pair(){}    
        
        pair(const Key& key, const Value& value){
            _key = key;
            _value = value;
        }

        void operator=(const pair& p){
            _key = p._key;
            _value = p._value;
        }

        bool operator==(const pair& p){
            return (_key == p._key)? true : false;
        }

        Key& key(){
            return _key;
        }

        Value& value(){
            return _value;
        }
};

template<class Key, class Value>
class Dictionary
{
public:

    // = 0 implies pure virtual i.e definition of these function must be present in the derived class
    /*
     * Destructor. Should release all the memory acquired by the dictionary.
     */
	virtual ~Dictionary(){};
    /*
     * Function : has
     * Returns true if the dictionay contains the key
     * false otherwise. It is search operation
     */
	virtual bool has(const Key& key) = 0;
    /*
     * Function : remove
     * Removes the given key and the corresponding value from the Dictionary if the key is in the dictionary.
     * Does nothing otherwise.
     */
	virtual void remove(const Key& key) = 0;
    /*
     * Function : get
     * Returns the value associated with the given key.
     * Raises an exception if the key does'nt exist in the dictionary.
     */
	virtual Value get(const Key& key) = 0;
    /*
     * Function : put
     * If the key does'nt exist in the dictionary, then insert the given key and value in the dictionary.
     * Otherwise change the value associated with the key to the given value.
     */
	virtual void put(const Key& key, const Value& value) = 0;
};

#endif /* DICTIONARY_HPP_ */
