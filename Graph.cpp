#include <iostream>
#include "Graph.h"

using std::cout;
using std::endl;
using std::exception;
using std::invalid_argument;

// Constructor - DO NOT MODIFY
Graph::Graph(int n) {
  if (n <= 0)
    throw invalid_argument("Graph::Graph(): number of vertices must be positive");

  _rows = new EntryList*[n];
  for (int i = 0; i < n; i++) {
    _rows[i] = new EntryList();
  }
  _numVert = n;
  _numEdge = 0;
}

Graph::Graph(const Graph& G) {
  cout << "Graph, copy constructor..." << endl;

  //copying the passed in _rows
  _rows = new EntryList*[G._numVert];
  for (int i = 0; i < G._numVert; i++){
    _rows[i] = new EntryList(*(G._rows[i]));
  }

  //updating the value of the member variables
  _numVert = G._numVert;
  _numEdge = G._numEdge;
  
  
}

const Graph& Graph::operator=(const Graph& rhs) {

  cout << "Graph, the assignment operator is called..." << endl;

  //checks for self-assignment
  if (this != &rhs){
    delete [] _rows;

    //initializing a new array and copying
    _rows = new EntryList*[rhs._numVert];
    for (int i = 0; i < rhs._numVert; i++){
      _rows[i] = new EntryList(*(rhs._rows[i]));
    }

    //updating the size
    _numVert = rhs._numVert;
    _numEdge = rhs._numEdge;


  }
  

}

Graph::~Graph() {

  //destructor
  if (_rows != nullptr){
    for (int i = 0; i < numVert(); i++) {
      delete _rows[i];
    }
    delete [] _rows;
  }
}

// Number of vertices - DO NOT MODIFY
int Graph::numVert() const {
  return _numVert;
}

// Number of edges - DO NOT MODIFY
int Graph::numEdge() const {
  return _numEdge;
}

void Graph::addEdge(int u, int v, weight_t x) {

  //if out of bound
  if ((u < 0) or (u > _numVert)) { 
    throw invalid_argument("An exception was thrown from addEdge()");
  }
  else{
    //if there is a match, call the insert() in EntryList
    EntryList:: Entry insertThis(v, x);
    for (int i = 0; i < _numVert; i++){
      if (i == u){
	_rows[i] -> insert(insertThis);
	_numEdge ++; //incrementing the number of edges
      }
    }
  }
  
}

bool Graph::removeEdge(int u, int v) {
  bool flag = false;

  //out of bound
  if ((u < 0) or (u > _numVert)) {
    throw invalid_argument("An exception was thrown from addEdge()");
  }
  else{
    
    //create and entry object and if match is found call remove() in EntryList
    EntryList::Entry removeThis;
    for (int i = 0; i < _numVert; i++){
      if (i == u){
	flag = _rows[i] -> remove(v, removeThis);
	_numEdge --; //decrementing the number of edges
      }
      
    }
  }

  return flag;
  
}

  


// Dump the graph - DO NOT MODIFY
void Graph::dump() const {

  cout << "Dump of graph (numVert = " << _numVert
       << ", numEdge = " << _numEdge << ")" << endl;

  for (int i = 0; i < _numVert; i++) {
    cout << "Row " << i << ": \n";
    _rows[i]->dump();
  }
}


Graph::EgIterator::EgIterator(Graph *Gptr, bool enditr) {

  _Gptr = Gptr;
  
  if (_Gptr == nullptr){
    _itr = EntryList::Iterator(); // creates uninitialized iterator
  }

  else{

    bool flag;
    int num;
    
    if (enditr == false){
      num = 0;
      flag = false;
      while (num < _Gptr->numVert() and flag != true) {
	
	if (_Gptr -> _rows[num] -> size() == 0){
	  num ++; //if nothing exists
	}
	else {
	  //jump out of the loop
	  flag = true;
	}
      }
      //insert the begin()
      _itr = _Gptr -> _rows[num] -> begin();
      //update _row
      _row = num;
    }

    else{
      //from the back end
      num = _Gptr->numVert() - 1; //end value
      flag = false;
      
      while (num >= 0 and flag != true) {
	
	if (_Gptr -> _rows[num] -> size() == 0){
          num --; //if nothing exists, decrement the count
        }
        else {
          flag = true; //jump out of the loop if array exists
        }
      }
      //insert the end()
      _itr = _Gptr -> _rows[num] -> end();
      // update _row
      _row = num;
    }
  }
}
  
tuple<int,int,weight_t> Graph::EgIterator::operator*() {

  //invalid 
  if (_Gptr == nullptr){
    throw invalid_argument("Invalid Argument");
  }
  
  //making object of entry type to access getWeight() and getVertex()
  EntryList::Entry obj = *_itr;
  weight_t _weight = obj.getWeight();
  int _vertex = obj.getVertex();

  //returning (u,v,w)
  return tuple<int, int, weight_t>(_row, _vertex, _weight);
}

bool Graph::EgIterator::operator!=(const EgIterator& rhs) {
  
  bool myFlag = false;
  
  if (_Gptr != rhs._Gptr or _itr != rhs._itr) {
    myFlag = true;
  }
  return myFlag;
}

void Graph::EgIterator::operator++(int dummy) {
  
  //if the graph is empty
  if(_Gptr->numVert() == 0) {
    throw invalid_argument("Graph is empty.." );
  } else {

    EntryList::Iterator recentItr(_Gptr->_rows[_row], _Gptr->_rows[_row]->size() - 1);

    bool flag;
    int count;

    
    if (recentItr == _itr) {

      count = _Gptr->numVert() - 1; //last numVert value
      flag = false;

      while (count >= 0 and flag != true) {

	//size if zero
        if (_Gptr -> _rows[count] -> size() == 0){
          count --; //decrementing the index
        }
        else {
          flag = true; //jump out of the loop
        }
      }

      if (_row == count) {
	_itr = _Gptr->_rows[_row]->end(); //to the very end of the _row
      } else {
	count = 0;
	count = _row + 1;
	flag = false;
	
	while (count < _Gptr->numVert() and flag != true) {

	  if (_Gptr -> _rows[count] -> size() == 0){
	    count ++; //overlook if the size is zero
	  }
	  else {
	    flag = true; //set the while loop to fail
	  }
	}

	//set the begin()
	_itr = _Gptr -> _rows[count] -> begin(); 
	//row is updated
	_row = count;
      }

    }
    else {
      _itr++; //incrementing the iterator
    }
  } 

}

Graph::EgIterator Graph::egBegin() {

  //begin
  return EgIterator(this, 0);
}
 
Graph::EgIterator Graph::egEnd() {

  //end
  return EgIterator(this, 1);
}
 
Graph::NbIterator::NbIterator(Graph *Gptr, int v, bool enditr) {

  _Gptr = Gptr;
  _row = v;
  
  if (_Gptr == nullptr){
    _itr = EntryList::Iterator(); // creates uninitialized iterator
  }

  else{
    if (enditr == false){
      //marking begin in the beginning of the _array with objects
      _itr = _Gptr -> _rows[_row] -> begin();
}
    else{
      //marking end at the end of the _array with objects
      _itr = _Gptr -> _rows[_row] -> end();
    }
  }
  
 }

bool Graph::NbIterator::operator!=(const NbIterator& rhs) {

  //comparison
  bool flag = false;
  if (_row != rhs._row or _Gptr != rhs._Gptr){
    flag = true;
  }
  return flag;

}

void Graph::NbIterator::operator++(int dummy) {
  //incrementing the iterator
  _itr++;
}

pair<int,weight_t> Graph::NbIterator::operator*() {


  if (_itr == nullptr){
      throw invalid_argument("iterator is null...");
    }
  
  //declaring object of the entry type to access getWeight() and getVertex()
  EntryList::Entry object = (*_itr);
  weight_t _weight = object.getWeight();
  int _vertex = object.getVertex();

  //returning (v, w)
  return pair<int, weight_t>(_vertex, _weight); 
}

Graph::NbIterator Graph::nbBegin(int v) {

  //checking the bound
  if (v < 0){
    throw invalid_argument("Invalid Argument");
  }

  //begin
  return NbIterator(this, v);
}

Graph::NbIterator Graph::nbEnd(int v) {

  //checking the bound
  if (v < 0){
    throw invalid_argument("Invalid Argument");
  }

  //end
  return NbIterator(this, v);
}
