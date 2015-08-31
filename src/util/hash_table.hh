
#ifndef HASH_TABLE_HH
#define HASH_TABLE_HH

// Copyright (c) 1993-1999 The University of Cincinnati.
// All rights reserved. 

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF 
// THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE, OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE
// FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
// RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS
// DERIVATIVES.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
// THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE, OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE
// FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
// RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS
// DERIVATIVES.

// Authors: Philip A. Wilsey    phil.wilsey@uc.edu
//          Dale E. Martin      dmartin@cliftonlabs.com
//          Timothy J. McBrayer tmcbraye@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include <iostream>
#include <cstring>
#include "savant.hh"
#include "dl_list.hh"
#include "savant.hh"

/** Template based bucket hashing class.  Hashes on input string.
    The template Type defines the type of the constructed bucket for
    each entry.
    
    Requirements on Type:
    void set_key(char *key): initializes text key in Type
    int test_key(char *key): returns strcmp(key,x) where x is
    internal pointer to text string
    Type constructor assumed to require no arguments
*/

template <class Type>
class hash_table {
    
public:
  /**
    Look up "text" in the hash table.
  */
  Type *hash_look( const char * const text ){
    return hash_look( text, strlen(text) );
  }

  /**
     Look up the non-NULL terminated "text" in the hash table, using
     "length" as the length of the key.
  */
  Type *hash_look( const char *const text, const int length ) {
    int key;
    int i;
    Type *wk;

    key = 0;
  
    // calculate a hash value...
    for (i = 0; i < length; i++) {
      key = (key << 3) + text[i];
    }

    key = (key & 0x7fffffff) % ht_size;

    for (wk=ht[key].first();
	 wk!=NULL && wk->test_key( text, length );
	 wk=ht[key].successor(wk)) {}
    
    if (wk == NULL) {
      wk = new Type();
      wk->set_key( text, length );
      ht[key].append(wk);
    }
    
    return wk;
  }

  /**
     Constructor

     @param table_size The initial table size of this hash table.
     Currently it's the final size as well as the table won't grow.
  */
  hash_table(int table_size = 4093) : ht_size(table_size) {
    ht = new dl_list<Type>[ht_size];
  }
    
  ~hash_table(){
    delete [] ht;
  };

  /**
     Clear the hash table.
  */
  void reset(){
    int i;
    for(i = 0 ; i < ht_size; i++){
      ht[i].destroy_containers();
    }
  }

  /**
     Get the size of the hash_table.  This isn't the number of elements in
     the table, it's the number of slots.
  */
  const int get_size() const {
    return ht_size;
  }

  /**
     Looks up the entry at the index passed in.  If the index isn't within
     the bounds of the table a runtime error is generated.
  */
  dl_list<Type>* get_entry(int entry_number) const {
    ASSERT ( (entry_number >= 0) && (entry_number <= ht_size) );
    return (ht + entry_number);
  }

  /**
     This method returns the whole table as a list.  The list needs to be
     deleted when finished.  This can be an expensive operation.  If the
     hash table is empty, an empty list will be returned.
  */
  dl_list<Type> *convert_to_list() const {
    dl_list<Type> *retval = new dl_list<Type>;
    int i;
    for( i = 0; i < ht_size; i++ ){
      Type *current = ht[i].first();
      while( current != NULL ){
	retval->append( current );
	current = ht[i].successor( current );
      }
    }
    return retval;
  }

private:
  const int ht_size;
  dl_list<Type> *ht;
};

// template <class Type>
// inline
// Type *
// hash_table<Type>::hash_look(){return NULL;}


#endif
