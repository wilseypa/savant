#ifndef DL_LIST_HH
#define DL_LIST_HH

// Copyright (c) 1994-1999 The University of Cincinnati.
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF 
// THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE, OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE
// FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
// RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS
// DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the
// U.S., and the terms of this license.


// You may modify, distribute, and use the software contained in this package
// under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2,
// June 1991. A copy of this license agreement can be found in the file
// "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey            phil.wilsey@uc.edu
//          Tim McBrayer                tmcbraye@ece.uc.edu
//          Dale E. Martin              dmartin@cliftonlabs.com

#include "savant_config.hh"
#include <list>
#include <algorithm>
#include <functional>
#include <cassert>

using std::list;
using std::distance;
using std::advance;
using std::find;
using std::equal_to;
using std::bind2nd;

template <class type>
class dl_list {
  
public:
  dl_list() : elementCount(0){
    my_iterator = my_list.begin();
  }
  ~dl_list(){}
    
  int num_elements(){
    return elementCount;
  }

  int size() {
    return num_elements();
  }

  void append( type *to_append ){
    my_list.push_back( to_append );
    elementCount++;
  }

  void prepend( type* to_prepend ) {
    my_list.push_front( to_prepend );
    elementCount++;
  }

  void insert_after( const type *after_me, type* new_object ) {
    typename list<type *>::iterator found = list_find( after_me );
    assert( found != my_list.end() );
    found++;
    my_list.insert( found, new_object );
    elementCount++;
  }
    
  bool remove( const type *to_remove ) {
    bool retval = false;
    typename list<type *>::iterator found = list_find( to_remove );
    if( found != my_list.end() ){
      if( my_iterator == found ){
	my_iterator = my_list.end();
      }
      my_list.erase( found );
      retval = true;
      elementCount--;
    }
    return retval;
  }

  type *successor( const type *to_succeed ) {
    type *retval = 0;
    my_iterator = list_find( to_succeed );
    if( my_iterator != my_list.end() ){
      my_iterator++;
      if( my_iterator != my_list.end() ){
	retval = *my_iterator;
      }
    }
    return retval;
  }

  type *predecessor( const type *to_precede ) {
    type *retval = 0;
    my_iterator = list_find( to_precede );
    if( my_iterator != my_list.end() ){
      my_iterator--;
      if( my_iterator != my_list.end() ){
	retval = *my_iterator;
      }
    }
    return retval;
  }
        
  type *first() {
    type *retval = 0;
    if( !my_list.empty() ){
      my_iterator = my_list.begin();
      retval = *my_iterator;
    }
    return retval;
  }
    
  type *last() {
    type *retval = 0;
    if( !my_list.empty() ){
      my_iterator = my_list.end();
      my_iterator--;
      retval = *my_iterator;
    }
    return retval;
  }
    
  /** This returns the ordinal position in the dl_list of the object passed
      in.  Returns -1 if the element is not found in list. */
  int get_position(type* data) {
    int retval = -1;
    typename list<type *>::iterator element = list_find( data );
    if( element != my_list.end() ){
      retval = distance<typename list<type *>::iterator>( my_list.begin(), element );
    }
    
    return retval;
  }

  type *get_nth_element( int pos_to_get ){
    int i = 0;
    type *current = first();
    for( i = 0; i < pos_to_get && current != NULL; i++ ){
      current = successor( current );
    }
    return current;
  }

  dl_list<type> &
  operator=( dl_list<type> to_copy ){
    my_list.clear();
    my_list.insert( my_list.end(), to_copy.my_list.begin(), to_copy.my_list.end() );
    my_iterator = my_list.end();
    elementCount = to_copy.elementCount;

    return *this;
  }

  // Replace "to_replace" with replace with, without disturbing the rest
  // of the list.
  void _replace( type *to_replace, type *replace_with ){
    typename list<type *>::iterator found = list_find( to_replace );
    assert( found != my_list.end() );
    *found = replace_with;
  }
  
  bool in_list( type *to_find ){
    if( list_find( to_find ) == my_list.end() ){
      return false;
    }
    else{
      return true;
    }
  }

private:
  unsigned int elementCount;
  list<type *> my_list;
  typename list<type *>::iterator my_iterator;

  typename list<type *>::iterator list_find( const type *to_find ){
    typename list<type *>::iterator retval = my_list.end();
    if( !my_list.empty() ){
      if( my_iterator != my_list.end() && *my_iterator == to_find ){
	retval = my_iterator;
      }
      else{
	retval = find( my_list.begin(), 
		       my_list.end(), 
		       to_find );
      }
    }
    return retval;
  }
};

#endif
