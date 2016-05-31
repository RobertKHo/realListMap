// $Id: listmap.tcc,v 1.1 2015-02-12 11:22:36-08 - - $
//Robert Ho rokho@ucsc.edu
//Daniel Urrutia deurruti@ucsc.edu
#include "listmap.h"
#include "trace.h"

//
/////////////////////////////////////////////////////////////////
// Operations on listmap::node.
/////////////////////////////////////////////////////////////////
//

//
// listmap::node::node (link*, link*, const value_type&)
//
template <typename Key, typename Value, class Less>
listmap<Key,Value,Less>::node::node (node* next, node* prev,
                                     const value_type& value):
            link (next, prev), value (value) {


}



//
/////////////////////////////////////////////////////////////////
// Operations on listmap.
/////////////////////////////////////////////////////////////////
//

//
// listmap::~listmap()
//
template <typename Key, typename Value, class Less>
listmap<Key,Value,Less>::~listmap() {
   TRACE ('l', (void*) this);
   while(not empty()) erase(begin());
}

//
// listmap::empty()
//
template <typename Key, typename Value, class Less>
bool listmap<Key,Value,Less>::empty() const {
   return anchor_.next == &anchor_;
}

//
// listmap::iterator listmap::begin()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::begin() {
   return iterator (anchor_.next);
}

template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::cbegin() const{
   return iterator (anchor_.next);
}

//
// listmap::iterator listmap::end()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::end() {
   return iterator (anchor());
}

template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::cend() const{
   return iterator (anchor());
}


//
// iterator listmap::insert (const value_type&)
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator 
listmap<Key,Value,Less>::insert (const value_type& pair) {
   TRACE ('l', &pair << "->" << pair);  
   Less less;
   listmap<Key,Value,Less>::iterator itor = begin();
   listmap<Key,Value,Less>::iterator final = end();

   //iterate over the map to find insertion point 
   while(itor != final and less(itor->first,pair.first)){ 
      ++itor; 
   }

   //check for case of equal key  
   if(itor != final and not less(pair.first,itor->first)){ 
      itor->second = pair.second;
      return itor;
   }
   node* temp = new node(itor.where,itor.where->prev,pair);
   //case where anchor is the only thing in map
   itor.where->prev = temp;
   //update the next field of itor.where->prev to point at the new node
   temp->prev->next = temp; 
   return iterator(temp);
}

//
// listmap::find(const key_type&)
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::find (const key_type& that) {
   TRACE ('l', that);
   listmap<Key,Value,Less>::iterator itor = begin();
   listmap<Key,Value,Less>::iterator final = end();
   while( itor != final and itor.where->value.first != that){ 
      ++itor;
   }
   if(itor != final){
      cout<< that << " = " << itor.where->value.second << endl;
   }else{
      cout<< that <<": key not found"<<endl;
   }
   return itor;
}
//
//iterator listmap::find_value(const value_type&)
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::find_value (const mapped_type& that) {
   listmap<Key,Value,Less>::iterator itor = begin();
   listmap<Key,Value,Less>::iterator final = end();
   for (; itor != final; ++itor) {
      if(itor.where->value.second == that){
         cout << itor.where->value.first << " = "
              << itor.where->value.second << endl;
      }
   }
   return itor;
}
//
// iterator listmap::erase (iterator position)
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::erase (iterator position) {
   TRACE ('l', &*position);


   //if there is a node at position delete the node
   if(position.where != nullptr){
      position.where->prev->next = position.where->next;
      position.where->next->prev = position.where->prev;
      delete position.where;
   }

   return iterator();
}


//void listmap::iterator::erase()
template <typename Key, typename Value, class Less>
void listmap<Key,Value,Less>::iterator::erase() {
   if (where != nullptr){
      where->prev->next = where->next;
      where->next->prev = where->prev;  
      delete where;
  }   
}


template  <typename Type,class Less=xless<Type>>
void compare(const Type& left, const Type& right){
   Less less;
   cout << boolalpha; 
   bool is_less = less(left,right);
   bool is_equal = not less(left,right) and not less(right,left);
   bool is_greater = not is_less and not is_equal; 
   cout << left << " < " << right << " = " << is_less << endl;
   cout << left << " == " << right << " = " << is_equal << endl;
   cout << left << " > " << right << " = " << is_greater << endl;
   cout << endl;

}

template <typename Key, typename Value, class Less>
typename listmap<Key, Value,Less>::iterator
listmap<Key,Value,Less>::print_pairs(){
   listmap<Key,Value,Less>::iterator itor = begin();
   listmap<Key,Value,Less>::iterator final = end();
   for (; itor != final; ++itor) {
      cout << itor.where->value.first << " = "
           << itor.where->value.second << endl;
   }
   return itor;    
}
//
/////////////////////////////////////////////////////////////////
// Operations on listmap::iterator.
/////////////////////////////////////////////////////////////////
//

//
// listmap::value_type& listmap::iterator::operator*()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::value_type&
listmap<Key,Value,Less>::iterator::operator*() {
   TRACE ('l', where);

   //
   return where->value;
}

//
// listmap::value_type* listmap::iterator::operator->()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::value_type*
listmap<Key,Value,Less>::iterator::operator->() {
   TRACE ('l', where);
   return &(where->value);
}

//
// listmap::iterator& listmap::iterator::operator++()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator&
listmap<Key,Value,Less>::iterator::operator++() {
   TRACE ('l', where);
   where = where->next;
   return *this;
}

//
// listmap::iterator& listmap::iterator::operator--()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator&
listmap<Key,Value,Less>::iterator::operator--() {
   TRACE ('l', where);
   where = where->prev;
   return *this;
}


//
// bool listmap::iterator::operator== (const iterator&)
//
template <typename Key, typename Value, class Less>
inline bool listmap<Key,Value,Less>::iterator::operator==
            (const iterator& that) const {
   return this->where == that.where;
}

//
// bool listmap::iterator::operator!= (const iterator&)
//
template <typename Key, typename Value, class Less>
inline bool listmap<Key,Value,Less>::iterator::operator!=
            (const iterator& that) const {
   return this->where != that.where;
}

