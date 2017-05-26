/*  Author : Indresh Kumar Gupta
    Purpose : Implementation of linked list data structure
    Version : 1.2

*/
/*
 * queue.hpp
 *
 * functionality of a singly linked-list
 *
 * define your methods in coherence with the following
 * function signatures
 * 
 * 
 */

#ifndef LIST_HPP
#define LIST_HPP 1

namespace cs202
{   
    template<class T>
    class list;

    template<class T>
    class node{
        public:
            friend list<T>;
            T data;
            node* next;
    };

    template<class T>
    class list
    {
        private:

            node<T> *_start;
            node<T> *_end;
            int _length;  
        public:
            /*
             * Primary contructor.
             * Should construct an empty list.
             * Size of the created list should be zero.
             */
            list();
            /*
             * Seondary constructor.
             * Creates a new list which is a copy of the provided list.
             */
            list(const list<T> & x);
            /*
             * Destructor.
             * Frees all the memory acquired by the list.
             */
            ~list();
            /*
             * adds value at the end of the list.
             */
            void append(const T& value);
            /*
             * Returns the length of the list.
             */
            inline int length();
            /*
             * Returns a boolean indicating whether the list is empty.
             */
            inline bool empty();
            /*
             * Adds a value to the front of the list.
             */
            void cons(const T& value);
            /*
             * Removes the first occurence of the value from list.
             */
            void remove(const T & x);
            /*
             * Appends the given list x at the end of the current list.
             */
            void append(list<T>& x);

            void display();

            T front();

            T rear();

            node<T>* getIterator(){
                return _start;
            }
    };

    template<class T>
    list<T>::list(){
        _start = NULL;
        _end = NULL;
        _length = 0;
    }

    template<class T>
    list<T>::list(const list<T> & x){
        _start = x._start;
        _end = x._end;
        _length = x._length;
    }

    template<class T>
    list<T>::~list(){
        node<T> *tmp = NULL;
        while(_start){
            tmp = _start;
            _start = _start->next;
            delete tmp;
        }
    }

    template<class T>
    void list<T>::append(const T& value){
        node<T> *tmp = new node<T>;
        tmp->data = value;
        tmp->next = NULL;

        if(empty()){
            _start = tmp;
            _end = tmp;
        }
        else{
            _end->next = tmp;
            _end = tmp;
        }

        _length++;
    }

    template<class T>
    inline int list<T>::length(){
        return _length;
    }

    template<class T>
    inline bool list<T>::empty(){
        return _length == 0 ? true : false;
    }    

    template<class T>
    void list<T>::cons(const T& value){
        node<T> *tmp = new node<T>;
        tmp->data = value;
        tmp->next = NULL;

        if(empty()){
            _start = tmp;
            _end = tmp;
        }
        else{
            tmp->next = _start;
            _start = tmp;
        }

        _length++;   
    }

    template<class T>
    void list<T>::remove(const T & x){

        if(empty())
            return;

        if(_start->data == x){
            node<T> *tmp = _start;
            if(_start == _end)
                _end = _start->next;
            _start = _start->next;
            _length--;
            delete tmp;
        }
        else{
            node<T> *traverse = _start;
            node<T> *previous = _start;
            while(traverse){
                if(traverse->data == x){
                    if(traverse == _end)
                        _end = previous;

                    previous->next = traverse->next;
                    _length--;
                    delete traverse;
                    return;
                }
                previous = traverse;
                traverse = traverse->next;
            }
        }
    }

    template<class T>
    void list<T>::append(list<T>& x){
        
        if(!empty()){
            if(!x.empty()){
                _end->next = x._start;
                _end = x._end;
            }
        }
        else{
            _start = x._start;
            _end = x._end;
        }
        _length += x._length;
    }

    template<class T>
    void list<T>::display(){
        node<T> *traverse = _start;
        while(traverse){
            std::cout<<traverse->data<<std::endl;
            traverse = traverse->next;
        }
    }

    template<class T>
    T list<T>::front(){
        if(!empty())
            return _start->data;
    }

    template<class T>
    T list<T>::rear(){
        if(!empty())
            return _end->data;
    }    
}

#endif