#include <iostream>
#include "EntryList.h"
#include "Graph.h"

using namespace std;


int main(){

   EntryList entryList;                                                                            
   EntryList::Entry entry;                                                                      
                                                                                            
   cout << "size: " << entryList.size() << ", capacity: " << entryList.capacity() << endl;                
   entryList.dump();                                                                               
   cout << endl;                                                                            
                                                                                            
   for (int i = 1; i < 26; i++) {                                                           
     entryList.insert( EntryList::Entry((i*10)%5, i) );                                            
   }                                                                                        
                                                                                            
   cout << "size: " << entryList.size() << ", capacity: " << entryList.capacity() << endl;                
   entryList.dump();                                                                               
   cout << endl;                                                                            
                                                                                            
   for (int i = 1; i < 26; i+=3) {                                                          
     entryList.remove(i, entry);                                                                       
   }                                                                                        
                                                                                            
   cout << "size: " << entryList.size() << ", capacity: " << entryList.capacity() << endl;                
   entryList.dump();                                                                               
   cout << endl;                                                                            
                                                                                            
                                                                                            
   for (int i = 3; i < 26; i+=3) {                                                          
     entryList.update( EntryList::Entry(i, 3*i) );                                                 
   }                                                                                        
                                                                                            
   cout << "size: " << entryList.size() << ", capacity: " << entryList.capacity() << endl;                
   entryList.dump();                                                                               
   cout << endl;                                                                            
                                                                                            
   for (int i = 3; i < 26; i*=3) {                                                          
     entryList.remove(i, entry);                                                                       
   }

   cout << "size: " << entryList.size() << ", capacity: " << entryList.capacity() << endl;                
   entryList.dump();                                                                               
   cout << endl;                                                                            
                                                                                            
   cout << "\nPrint using iterator:\n";                                                     
   for (auto itr = entryList.begin(); itr != entryList.end(); itr++) {                                    
     cout << *itr << endl;                                                                  
   }                                                                                        
                                                                                            
   
  Graph G(5) ;

   // adding edges                                                    
   G.addEdge(3,4,11);
   G.addEdge(1,4,12);
   G.addEdge(0,3,13);
   G.addEdge(0,4,14);
   G.addEdge(0,1,15);
   G.addEdge(1,2,16);
   G.addEdge(2,4,17);
                                                                        
   G.dump();

   Graph::NbIterator nit ;

   for (int i = 0; i < G.numVert(); i++) {
     cout << "\nThe neighbors of vertex " << i << " are:\n" ;
     for (nit = G.nbBegin(i); nit != G.nbEnd(i) ; nit++) {
       cout << "(" << (*nit).first << ", " << (*nit).second << ")" << " " ;
     }
     cout << endl ;
   }


   Graph::EgIterator eit ;
   std::tuple<int,int,int> edge ;

   cout << "\nnumVert = " << G.numVert() << ", numEdge = " << G.numEdge() << endl;
   cout << "The edges in the graph are:\n" ;
   for (eit = G.egBegin() ; eit != G.egEnd() ; eit++) {

     edge = *eit ;   // get current edge

     cout << "(" << get<0>(edge) << ", "
          << get<1>(edge) << ", "
          << get<2>(edge) << ") " ;

   }
   cout << endl ;

   cout << "\nRemove edges (3,4), (0,4), and (1,2)...\n";
   G.removeEdge(3,4);
   G.removeEdge(0,4);
   G.removeEdge(1,2);

   cout << "\nnumVert = " << G.numVert() << ", numEdge = " << G.numEdge() << endl;
   cout << "The edges in the graph are:\n" ;
   for (eit = G.egBegin() ; eit != G.egEnd() ; eit++) {
     edge = *eit ;                                                     
     cout << "(" << get<0>(edge) << ", "
          << get<1>(edge) << ", "
          << get<2>(edge) << ") " ;

   }
   cout << endl ;
     

     
  return 0;                                                                                

}
