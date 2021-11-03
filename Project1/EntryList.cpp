/****************************************************************
Author:      MAHMOOD UL MOHASIN AZIZ
File:        EntryList.cpp
Project:     Project 1
Date:        02/18/2020
Section:     05, CMSC 341
Email:       rg66173@umbc.edu
Description:
****************************************************************/
#include "EntryList.h"

using std::cout;
using std::endl;
using std::range_error;

// Constructor - DO NOT MODIFY
EntryList::EntryList() {
  _array = new Entry[DEFAULT_SIZE];
  _capacity = DEFAULT_SIZE;
  _size = 0;
}

EntryList::EntryList(const EntryList& rhs) {
  
  _array = new Entry[rhs._capacity];

  for(int i = 0; i < rhs._capacity; i++) {
    _array[i] = rhs._array[i];
  }
  _size = rhs._size;
  _capacity = rhs._capacity;
}

const EntryList& EntryList::operator=(const EntryList& rhs) {

  if(&rhs != this) {

    delete [] _array;

    _array = new Entry[rhs._capacity];
    
    for(int i = 0; i < rhs._capacity; i++) {
      _array[i] = rhs._array[i];
    }
    _size = rhs._size;
    _capacity = rhs._capacity;
    
  }
  return *this;
}
  
EntryList::~EntryList() {

  if (_array) {
    delete [] _array;
  }
  
}

bool EntryList::insert(const Entry& e) {

  bool retBool = false;
  bool myBool;

  Entry * _newArray;

  if (_size < _capacity) {

    myBool = update(e);

    // array resizing.
    if((_size <= (_capacity/4)) && (_capacity > DEFAULT_SIZE)) {

	_capacity = (_capacity / 2);

	_newArray = new Entry[_capacity];
	for (int i = 0; i < _capacity/2; i++) {
	  _newArray[i] = _array[i];
	}
	
	delete [] _array;
	_array = _newArray;
    }
    
    if(!myBool) {
      _array[_size] = e;
      _size++;
      retBool = true;
    }
    
  } else {

    _capacity = _capacity * 2;
    _newArray = new Entry[_capacity];
    for (int i = 0; i < _capacity/2; i++) {
      _newArray[i] = _array[i];
    }
    
    delete [] _array;
    
    _array = _newArray;
    _array[_size] = e;
    _size++;
    retBool = true;
  }
  
  if (_size > 0) {
    // sorting.                                                                                   
    Entry object;
    for(int i = (_size - 1); i >= 0; i--) {
      for(int j = (_size - 1) - i; j > 0 ; j--) {
	if (_array[j]._vertex < _array[j-1]._vertex) {
	  object = _array[j-1];
	  _array[j-1] = _array[j];
	  _array[j] = object;
	}
      }
    }
  }
  return retBool;
}

bool EntryList::update(const Entry& e) {

  bool myBool = false;
  
  for(int i = 0; i < _capacity; i++) {
    if(_array[i]._vertex == e._vertex) {
      _array[i] = e;
      myBool = true;
    }
  }
  return myBool;
}

bool EntryList::getEntry(int vertex, Entry &ret) {

  bool newBool = false;
  for(int i = 0; i < _capacity; i++) {
    if (vertex == ret._vertex) {
      newBool = true;
    }
  }
  return newBool;
}

bool EntryList::remove(int vertex, Entry &ret) {

  bool remove = false;

  for(int i = vertex; i < _capacity; i++) {

    if (_array[i]._vertex == vertex) {
      _size--;
      ret = _array[i];
    }
    _array[i] = _array[i+1];
    remove = true;
  }
  
  return remove;
}

/*
EntryList::Entry& EntryList::at(int indx) const {
}
*/
// dump data structure - DO NOT MODIFY
void EntryList::dump() {
  for (int i = 0; i < _size; i++) {
    cout << "  " << _array[i] << endl;
  }
}
/*
EntryList::Iterator::Iterator(EntryList *EList, int indx) {
}

bool EntryList::Iterator::operator!=(const EntryList::Iterator& rhs) {
}

bool EntryList::Iterator::operator==(const EntryList::Iterator& rhs) {
}

void EntryList::Iterator::operator++(int dummy) {
}

EntryList::Entry EntryList::Iterator::operator*() {
}

EntryList::Iterator EntryList::begin() {
}

EntryList::Iterator EntryList::end() {
}
*/
// Insertion operator for Entry objects - DO NOT MODIFY
ostream& operator<<(ostream& sout, const EntryList::Entry& e) {
  sout << e._vertex << ": " << e._weight;
  return sout;
}

// A convenient way to write test code for a single class is to write
// a main() function at the bottom of the .cpp file.  Just be sure to
// comment-out main() once you are done testing!

// Following is example test code.  There is no guarantee that it is
// complete -- you are responsbile for thoroughly testing your code.
// In particular, passing these tests does not mean your
// implementation will pass all grading tests.

int main() {
   EntryList el;
   EntryList::Entry e;

   cout << "size: " << el.size() << ", capacity: " << el.capacity() << endl;
   el.dump();
   cout << endl;
   
   for (int i = 1; i < 13; i++) {
     el.insert( EntryList::Entry((i*5)%13, i) );
   }

   cout << "size: " << el.size() << ", capacity: " << el.capacity() << endl;
   el.dump();
   cout << endl;
   
   for (int i = 1; i < 13; i+=2) {
     el.remove(i, e);
   }
   cout << "size: " << el.size() << ", capacity: " << el.capacity() << endl;
   el.dump();
   cout << endl;


//   for (int i = 2; i < 13; i+=2) {
//     el.update( EntryList::Entry(i, 2*i) );
//   }

//   cout << "size: " << el.size() << ", capacity: " << el.capacity() << endl;
//   el.dump();
//   cout << endl;

//   for (int i = 3; i < 13; i*=2) {
//     el.remove(i, e);
//   }

//   cout << "size: " << el.size() << ", capacity: " << el.capacity() << endl;
//   el.dump();
//   cout << endl;

// cout << "\nPrint using iterator:\n";
// for (auto itr = el.begin(); itr != el.end(); itr++) {
//   cout << *itr << endl;
// }

   return 0; 
}
