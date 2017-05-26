#include <iostream>
#include <string.h>

namespace cs202 {
    template<typename T>
    class LinearList{
      private:
        T* buffer_;
        unsigned int size_;
        unsigned int capacity_;
      public:
        // Default Constructor
        // Creates a zero sized LinearList
        LinearList();

        // Constructor with size_ as input
        LinearList(const int& isize);                   

        // Constuctor with size_ and default value as input
        LinearList(const int& isize, const T& ival);    

        // Default Destructor
        ~LinearList();                                  

        // Accessing an element of the LinearList using operator
        inline T& operator[](const int& i);         

        // Return the element in the list at position k
        inline T& at(const int& k);         

        // Appending an element to the LinearList
        // The asymptotic time complexity of this function
        // should be O(1)
        void push_back(const T& item);              

        // Returns true if LinearList is empty
        bool empty();                               

        // Returns the size_ of the LinearList
        unsigned int size();                                 

        // Returns the capacity_ of the LinearList
        unsigned int capacity();                                 

        // Fills all the elements with a default value
        void fill(const T& item);                   

        // Resizes the LinearList
        void resize(const int& n); 

        // Find the index of first occurence of an item in the list
        // Return size_ of list if item not found
        // 0-based indexing
        int find(const T& item);

        // Remove all occurences of an item in the list
        void erase(const T& item);

        // Remove the item in the list at position pos
        void erase_pos(const int& pos);

        // Insert item at position k
        void insert(const T& item, const int& k);

        // Iterator typename for LinearList
        // This should be used to traverse the LinearList
        // See std::vector<T>::iterator for more understanding
        // on how iterators work
        class iterator{                             
          private:
            T* elem_;
          public:
            iterator() : elem_(NULL){};
            iterator(T* ptr) : elem_(ptr){};
            ~iterator();
            T& operator*() {return (*elem_); }
            void operator=(T *ptr) {elem_ = ptr;}
            void operator=(iterator iter) {elem_ = iter.elem_;}
            void operator++() {elem_ += 1;}
            void operator--() {elem_ -= 1;}
            bool operator!=(T* ptr) { return elem_ != ptr? true : false;}
            bool operator==(T* ptr) { return elem_ == ptr? true : false;}
            bool operator!=(iterator iter) { return elem_ != iter.elem_? true : false;}
            bool operator==(iterator iter) { return elem_ == iter.elem_? true : false;}
            iterator operator+(int i) {elem_ + i; return this;}
            iterator operator-(int i) {elem_ + i; return this;}
        };

        //iterator begin();                       
        //iterator end();
  };


    /*template<typename T>iterator LinearList<T> :: begin(){
        iterator it(&buffer_[0]);
        return it;
    }

    /*template<typename T>iterator LinearList<T> :: end(){
        return iterator(&buffer_[size_ - 1]);
    }*/

    

    template<typename T> LinearList<T> :: LinearList(){
        buffer_=new T[1];
        size_=0;
        capacity_=1;

    }



    template<typename T> LinearList<T> :: LinearList(const int& isize){
            
            int i;
            capacity_ = isize;
            buffer_ = new T[isize];
            size_=0;
    }



    template<typename T> LinearList<T> :: LinearList(const int& isize, const T& ival){
            
            int i;
            capacity_ = isize;
            buffer_=new T[isize];
            
            for(i=0;i<isize;i++)
                buffer_[i]=ival;
            
            size_ = 0;
    }
    
    template<typename T> LinearList<T> ::  ~LinearList(){                                                     
            
            size_ = 0;
            delete[] buffer_;
    }


    template<typename T> inline T&  LinearList<T> :: operator[](const int& i){
        
        return buffer_[i];
    }


    template<typename T> T&  LinearList<T> :: at(const int& k){

        return *(buffer_ + k);
    }

    template<typename T> void  LinearList<T> :: push_back(const T& k){


        if(size_ < capacity_){

            buffer_[size_] = k;
        }
        else{
            
            resize( 2 * capacity_);
           
            buffer_[size_] = k;
        }

        size_++;
    }

    template<typename T>bool  LinearList<T> :: empty(){
        if (size_ == 0) 
            return true;
        
        else 
            return false;
    }


    template<typename T>unsigned int  LinearList<T> :: size(){

        return size_;
    }



     template<typename T>unsigned int LinearList<T> ::  capacity(){
        return capacity_;
    }

    template<typename T>void  LinearList<T> :: fill(const T& item){   
        for(int i = 0; i < capacity_; i++)
            buffer_[i]=item;

        size_ = capacity_;

    }

    template<typename T>void  LinearList<T> :: resize(const int & n){
       
        T* tmpBuffer = new T[n];
       for(int i=0; i < size_ && i < n; i++){

            tmpBuffer[i]=buffer_[i];
       }
        
        delete[] buffer_;

        buffer_= tmpBuffer;

        capacity_ = n;
    } 

    template<typename T> int LinearList<T> :: find(const T& item){    

        int i;
        for(i=0;i<size_;i++){
            if(buffer_[i]== item){
                return i;
            }   
        }

        return size_;
       
    }

    template<typename T>void  LinearList<T> :: erase(const T& item){                                                             

            for(int i = 0; i < size_; i++){
                if(buffer_[i] == item){
                    erase_pos(i);
                }

            }
    }

    template<typename T>void LinearList<T> :: erase_pos(const int &pos){                                                             

        for(int i = pos; i < size_-1; i++){      
            buffer_[i]=buffer_[i+1];
            
        }   

        size_--;
    }

    template<typename T>void  LinearList<T> :: insert(const T& item,const int& k){                                                                                       
         
        if(size_ == capacity_){
            resize(2*capacity_);
        }
        
        if(k>size_){
            buffer_[size_]=item;
            size_++;
        }
        else{
            for(int i = size_; i > k; i--){   
                buffer_[i] = buffer_[i-1];
            
            }   

            buffer_[k] = item;
        }        
    }
}
