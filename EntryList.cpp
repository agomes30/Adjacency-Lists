#include "EntryList.h"
#include <algorithm>
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

  cout << "The copy constructor is called..." << endl;
  _array = new Entry[rhs._capacity];

  for (int i = 0; i < rhs._capacity; i++){
    _array[i] = rhs._array[i];
  }

  //updating the size and the cpaacity
  _size = rhs._size;
  _capacity = rhs._capacity;
  
}

const EntryList& EntryList::operator=(const EntryList& rhs) {

  cout << "The assignment operator is called..." << endl;
  
  // checks for self-assignment
  if (this != &rhs){
    //deleting the current object
    delete [] _array;
    
    //initializing a new array and copying
    _array = new Entry[rhs._capacity];
    for (int i = 0; i < rhs._capacity; i++){
    _array[i] = rhs._array[i];
    }
    //updating the size
    _size = rhs._size;
    _capacity = rhs._capacity;
  }
  return *this;

}
  
EntryList::~EntryList() {
  //"The destructor is called..."
  if (_array != nullptr){
    delete [] _array;
  }
}

bool EntryList::insert(const Entry& e) {
  
  bool match = update(e);
  if (match)
    return false;    
  
   
  //checking for expansion
  if (_size == _capacity){
    _capacity = _capacity * 2; //double the previous size
    Entry *_temp = new Entry[_capacity]; // new temporary array
    for (int i = 0; i <  _size; i++){
      _temp[i] = _array[i]; //copying values to new array
    }
    delete [] _array; // freeing old array 
    _array = _temp; // now _array points to new array
  }
 
  //inserting the passed in object to the array
  _array[_size] = e;
  //updating the size
  _size ++;


  //sorting the array
  Entry temp;  
  for (int i = _size - 1; i >= 0; i--){
    for (int j = (_size - 1) - i; j > 0; j--){
      if (_array[j]._vertex < _array[j-1]._vertex){
	
	temp = _array[j-1];
	_array[j-1] = _array[j];
	_array[j] = temp;
      }
    }
  }
  
  return true;
}

  
bool EntryList::update(const Entry& e) {

  //setting the current vertex to the passed in vertex
  bool temp = false;
  for (int i = 0; i < _size; i++){
      if (_array[i]._vertex == e._vertex){
	_array[i] = e;
	temp = true;
      }
    }
  return temp;

}

bool EntryList::getEntry(int vertex, Entry &ret) {

  //ret holds the object element
  bool temp = false;
  for (int i = 0; i < _size; i++){
    if (vertex == _array[i]._vertex){
      ret = _array[i];
      temp = true;
    }
    return temp;
  }

}


bool EntryList::remove(int vertex, Entry &ret) {
  bool temp = false;
  int counter = 0;
  
  
  for (int i = 0; i < _size; i++){
    //if a match is found to be removed
    if (vertex == _array[i]._vertex){
      counter ++;
      temp = true;
      _size --;
    }
    //array[i] gets the value of the next element in the array onwards
    if (counter > 0){
      _array[i] = _array[i+1];   
    }
  }

  
  if (temp){ //if removed
    if ((_size < _capacity / 4) and (_capacity / 2 >= DEFAULT_SIZE)){
      //checking for expansion                                                 
      _capacity = _capacity / 2; //double the previous size
      Entry *_temp = new Entry[_capacity]; // new temporary array                 
      for (int i = 0; i <  _size; i++){
	_temp[i] = _array[i]; //copying values to new array
      }
      delete [] _array; // freeing old array                                   
      _array = _temp; // now _array points to new array                        
    }  
  }
  
  return temp;
}

EntryList::Entry& EntryList::at(int indx) const {

  //throw exception if out of bound
  if (indx < 0 and indx >= _size)
    throw range_error("An exception was thrown from at()");
  else{
    return _array[indx];
  }
}

// dump data structure - DO NOT MODIFY
void EntryList::dump() {
  for (int i = 0; i < _size; i++) {
    cout << "  " << _array[i] << endl;
  }
}

EntryList::Iterator::Iterator(EntryList *EList, int indx) {

  //setting the initial value for _ELptr and _indx to the passed in value
  _ELptr = EList;
  _indx = indx;

}

bool EntryList::Iterator::operator!=(const EntryList::Iterator& rhs) {

  //for comparison
  bool flag = false;
  if ((_indx != rhs._indx) or (_ELptr != rhs._ELptr))
    flag = true;
  return flag;

}

bool EntryList::Iterator::operator==(const EntryList::Iterator& rhs) {

  //for comparison
  bool flag = false;
  if ((_indx == rhs._indx) and (_ELptr == rhs._ELptr))
    flag = true;
  return flag;
  
}

void EntryList::Iterator::operator++(int dummy) {

  //incrementing the _indx 
  if ((_indx >= 0) and (_indx < _ELptr -> size()))
    _indx ++;
}

EntryList::Entry EntryList::Iterator::operator*() {

  //returning the particular object at that index
  return _ELptr -> at(_indx);
}

EntryList::Iterator EntryList::begin() {

  //initial iterator
  return Iterator(this, 0);
  
}

EntryList::Iterator EntryList::end() {

  //end iterator
  return Iterator(this, _size);
  
}

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
/*
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


   for (int i = 2; i < 13; i+=2) {
     el.update( EntryList::Entry(i, 2*i) );
   }

   cout << "size: " << el.size() << ", capacity: " << el.capacity() << endl;
   el.dump();
   cout << endl;

   for (int i = 3; i < 13; i*=2) {
     el.remove(i, e);
   }

   cout << "size: " << el.size() << ", capacity: " << el.capacity() << endl;
   el.dump();
   cout << endl;

   cout << "\nPrint using iterator:\n";
   for (auto itr = el.begin(); itr != el.end(); itr++) {
     cout << *itr << endl;
   }

   return 0;
 }
*/
