/***********************************************************************
 * Header:
 *    Vector
 * Summary:
 *    This class contains the notion of an array: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the vector, set, stack, queue, deque, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       vector             : similar to std::array
 *       vector :: iterator : an iterator through the array
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>  // because I am paranoid

// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

namespace custom
{

/************************************************
 * Vector
 * A class that holds stuff
 ***********************************************/
template <class T>
class vector
{
public:
   // constructors and destructors
   vector()
   {
     numElements = 0;
     numCapacity = 0;
     data = NULL;
   }
   vector(int numElements);
   vector(int numElements, const T & t);
   vector(const vector<T> & rhs);
  ~vector();
   vector <T> & operator = (const vector<T> & rhs);
   
   // standard container interfaces
   // array treats size and max_size the same
   int  size()     const { return numElements;                 }
   int  capacity() const { return numCapacity;                 }
   bool empty()    const { return numElements == 0;}
     
   
   // array-specific interfaces
   // what would happen if I passed -1 or something greater than num?
   void clear(){numElements = 0;}
   void push_back(const T & t);
   T & operator [] (int index);
   
   T operator [] (int index) const;

   
   // the various iterator interfaces
   class iterator;
   iterator begin()      { return iterator (data); }
   iterator end()   {return iterator(data + numElements);}
   
   class const_iterator;
   const_iterator cbegin() const{return const_iterator (data);}
   const_iterator cend() const{return const_iterator (data + numElements);}

   // a debug utility to display the array
   // this gets compiled to nothing if NDEBUG is defined
   void display() const; 
   
private:
   T * data;              // dynamically allocated array of T
   int numElements;
   int numCapacity;              // both the capacity and the number of elements
   
   void resize(int newCapacity, const T & t);
   void resize(int newCapacity);
};

/**************************************************
 * VECTOR ITERATOR
 * An iterator through array
 *************************************************/
template <class T>
class vector <T> :: iterator
{
public:
   // constructors, destructors, and assignment operator
   iterator()      : p(NULL)      {              }
   iterator(T * p) : p(p)         {              }
   iterator(const iterator & rhs) { *this = rhs; }
   iterator & operator = (const iterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
   bool operator == (const iterator & rhs) const { return rhs.p == this->p; }

   // dereference operator
         T & operator * ()       { return *p; }
   const T & operator * () const { return *p; }

   // prefix increment
   iterator & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   iterator operator ++ (int postfix)
   {
      iterator tmp(*this);
      p++;
      return tmp;
   }
   
   iterator & operator -- ()
   {
      p--;
      return *this;
   }

   // postfix increment
   iterator operator -- (int postfix)
   {
      iterator tmp(*this);
      p--;
      return tmp;
   }
   
private:
   T * p;
};

/**************************************************
 * VECTOR CONST_ITERATOR
 * An iterator through vector where we can't change
 * the vector with *it
 *************************************************/
template <class T>
class vector <T> :: const_iterator
{
public:
   // constructors, destructors, and assignment operator
   const_iterator()      : p(NULL)      {              }
   const_iterator(T * p) : p(p)         {              }
   const_iterator(const const_iterator & rhs) { this->p = rhs.p; }
   const_iterator & operator = (const const_iterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const const_iterator & rhs) const { return rhs.p != this->p; }
   bool operator == (const const_iterator & rhs) const { return rhs.p == this->p; }

   // dereference operator
         T operator * ()       { return *p; }

   // prefix increment
   const_iterator & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   const_iterator operator ++ (int postfix)
   {
      vector<T> :: const_iterator tmp(*this);
      p++;
      return tmp;
   }
   
   const_iterator & operator -- ()
   {
      p--;
      return *this;
   }

   // postfix increment
   const_iterator operator -- (int postfix)
   {
      const_iterator tmp(*this);
      p--;
      return tmp;
   }
   
private:
   const T * p;
};

/*******************************************
 * VECTOR :: Assignment
 *******************************************/
template <class T>
vector <T> & vector <T> :: operator = (const vector <T> & rhs)
{
   if(&rhs == this)
     return *this;
     
   numElements = 0;
   
   if(rhs.numElements > numCapacity)
   {
     resize(rhs.numElements);
    } 
    
    numElements = rhs.numElements;
   
   for (int i = 0; i < numElements; i++)
     data[i] = rhs.data[i];

   return *this;
}
/*******************************************
 * VECTOR :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
vector <T> :: vector(const vector <T> & rhs): data(NULL), numElements(0), numCapacity(0)
{
   assert(rhs.numElements >= 0);
      
   // do nothing if there is nothing to do
   if (!rhs.empty())
   {
      *this = rhs;
   }
}

/**********************************************
 * VECTOR : NON-DEFAULT CONSTRUCTOR
 * Preallocate the array to "capacity"
 **********************************************/
template <class T>
vector <T> :: vector(int numElements): data(NULL), numElements(0), numCapacity(0) 
{  
    assert(numElements >= 0);
   
   // do nothing if there is nothing to do.
   // since we can't grow an array, this is kinda pointless
   if (numElements > 0)
   {
      resize(numElements);
      this -> numElements = numElements;
   }

}

/*****************************************
* DESTRUCTOR
****************************************/
template <class T>
vector <T> :: ~vector()
{
  assert(numCapacity >= 0);
  if(!empty())
  {
    assert(data != NULL);
    delete [] data;
  }
}

/**********************************************
 * VECTOR : NON-DEFAULT CONSTRUCTOR
 * Preallocate the array to "capacity"
 **********************************************/
template <class T>
vector <T> :: vector(int numElements, const T & t): data(NULL), numElements(0), numCapacity(0) 
{  
    assert(numElements >= 0);
   
   // do nothing if there is nothing to do.
   // since we can't grow an array, this is kinda pointless
   if (numElements > 0)
   {
      resize(numElements, t);
      this -> numElements = numElements;
   }

}

template <class T>
 T & vector <T> ::operator[] (int index)
   {
     if (index < 0 || index >= numElements)
     {
       throw "ERROR: Invalid Index";
     }
      return data[index];
   }
template <class T>
T vector <T> :: operator[] (int index) const 
   {
     if (index < 0 || index >= numElements)
     {
       throw "ERROR: Invalid Index";
     }
      return data[index];
   }

template <class T>
void vector<T> :: push_back(const T & t)
{
  assert(numElements <= numCapacity);
  if(numCapacity == 0)
  {
    resize(1);
  }
  else if (numElements == numCapacity)
  {
    resize(numCapacity * 2);
  }
  
  data[numElements++] = t;
}


/***************************************
* vector <T> :: RESIZE
* This will change the buffer size as needed.
* This will also check if the current index
* is in bounds
**************************************/
template <class T>
void vector <T> :: resize(int newCapacity) 
{
  assert(newCapacity > 0 && newCapacity > numCapacity);

// allocate the new array
  T * pNew;
  try
  {
    pNew = new T[newCapacity]; // could throw bad_alloc
  }
  catch (std::bad_alloc)
  {
    throw "ERROR: Unable to allocate a new buffer for vector";
  }

// copy over the data from the old array
  for (int i = 0; i < numElements; i++)
    pNew[i] = data[i];

// delete the old and assign the new
  if (data != NULL)
    delete [] data;
  data = pNew;
  numCapacity = newCapacity;
}

/***************************************
* vector <T> :: RESIZE
* This will change the buffer size as needed.
* This will also check if the current index
* is in bounds
**************************************/
template <class T>
void vector <T> :: resize(int newCapacity, const T & t)
{
  assert(newCapacity > 0 && newCapacity > numCapacity);

// allocate the new array
  T * pNew;
  try
  {
    pNew = new T[newCapacity]; // could throw bad_alloc
  }
  catch (std::bad_alloc)
  {
    throw "ERROR: Unable to allocate a new buffer for vector";
  }

// copy over the data from the old array
  for (int i = 0; i < numElements; i++)
    pNew[i] = data[i];
    
  for (int i = numElements; i < newCapacity; i++)
    pNew[i] = t;

// delete the old and assign the new
  if (data != NULL)
    delete [] data;
  data = pNew;
  numCapacity = newCapacity;
}


/********************************************
 * VECTOR : DISPLAY
 * A debug utility to display the contents of the array
 *******************************************/
template <class T>
void vector <T> :: display() const
{
#ifndef NDEBUG
   std::cerr << "vector<T>::display()\n";
   std::cerr << "\tnum = " << numElements << "\n";
   for (int i = 0; i < numElements; i++)
      std::cerr << "\tdata[" << i << "] = " << data[i] << "\n";
#endif // NDEBUG
}

}; // namespace custom 

#endif // VECTOR_H

