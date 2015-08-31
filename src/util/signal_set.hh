#ifndef SIGNALSET_HH
#define SIGNALSET_HH
// Copyright (c) 1999 The University of Cincinnati.
// All rights reserved. 

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF 
// THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE, OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE
// FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
// MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the
// U.S., and the terms of this license.


// You may modify, distribute, and use the software contained in this package
// under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2,
// June 1991. A copy of this license agreement can be found in the file
// "LGPL", distributed with this archive.

// Author:  Timothy J. McBrayer     tmcbraye@ecscs.uc.edu

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "set.hh"
#include "IIR_IndexedName.hh"
#include "IIR_IntegerLiteral.hh"

template <class type>
class signal_set : public savant::set<type> {
  // This class maintains a distinct set of heterogeneous data,
  // specicically tailored to Tim's output cone partitioning for process
  // combination.  Currently, two types of data can be stored: popinters
  // to signal declarations, and indexed_names.  The actual pointers for
  // SigDecls will be unique, so comparisons between them for existance,
  // etc., can just use the pointers.  IndexedNames are assumed to be
  // (possibly multi-dimensional) array indices of SigDecls.  These match
  // if a) their SigDecl pointers match, and b) all the indices in order
  // match.  If the indicies don't have a valid _get_value method, this'll
  // need more work.  More work will also be needed to support records,
  // aliases, etc.

  // Currently, this is derived from Dale's set class.  It overloads find,
  // and adds add(signal_set<type>) and intersects(), which just returns
  // true if the parameter set intersects with the set.
public:
  signal_set() {};
  ~signal_set() {};
  void add( signal_set<type>* );
  virtual void add( type* );
  bool intersects( signal_set<type>& );
  bool intersects( type* );

private:
  virtual int find( type * );
};


template <class type>
inline void 
signal_set<type>::add( signal_set<type> *set_to_add ){
  type *current = set_to_add->get_element();
  while( current != NULL ){
    // Cast to force finding method in base class
    ((set<IIR_Declaration>*)this)->add( current );
    current = set_to_add->get_next_element();
  }
}


template <class type>
inline void 
signal_set<type>::add( type *to_add ){
  savant::set<type>::add( to_add );
}


template <class type>
inline int
signal_set<type>::find( type *to_find ) {
  int i;

  const IIR_Kind curkind = to_find->get_kind();
  for ( i = 0; i < num; i++ ) {
    if ( curkind == data_array[i]->get_kind() ) {
      if ( curkind == IIR_SIGNAL_DECLARATION ||
	   curkind == IIR_SIGNAL_INTERFACE_DECLARATION ) {
	if ( data_array[i] == to_find ) {
	  return i;
	}
      }
      else if ( curkind == IIR_INDEXED_NAME ) {
	IIR_IndexedName *left, *right;
	left = (IIR_IndexedName*)data_array[i];
	right = (IIR_IndexedName*)to_find;
	if ( left == right ) {
	  return i;
	}
	else if ( left->get_suffix()->get_kind() == IIR_INTEGER_LITERAL &&
	     right->get_suffix()->get_kind() == IIR_INTEGER_LITERAL ) {
	  if ( ((IIR_IntegerLiteral*)left->get_suffix())->_get_value() ==
	       ((IIR_IntegerLiteral*)right->get_suffix())->_get_value()) {
	    signal_set<IIR_Declaration> lhsset;
	    bool result;
	    ASSERT( left->get_prefix()->_is_iir_declaration() && 
		    right->get_prefix()->_is_iir_declaration() );
	    // Cast to force finding method in base class
	    lhsset.add( (IIR_Declaration *)left->get_prefix() );
	    result = lhsset.in_set( (IIR_Declaration *)right->get_prefix() );
	    if ( result == true ) {
	      return i;
	    }
	  }
	}
	else {
	  cerr << "ERROR: unexpected index type(s) " 
	       << left -> get_kind_text() << " and " 
	       << right->get_kind_text() << " in set_intersect.\n";
	}
      }
    }
    else if (curkind == IIR_INDEXED_NAME &&
	     (data_array[i]->get_kind() == IIR_SIGNAL_DECLARATION ||
	      data_array[i]->get_kind() == IIR_SIGNAL_INTERFACE_DECLARATION)) {
      IIR_Declaration *decl;
      decl = (IIR_Declaration*)((IIR_IndexedName*)to_find)->get_prefix();
      if ( (decl->get_kind() == IIR_SIGNAL_DECLARATION ||
	    decl->get_kind() == IIR_SIGNAL_INTERFACE_DECLARATION )
	   && !IIR_TextLiteral::_cmp( decl->get_declarator(),
				      data_array[i]->get_declarator())) {
	return i;
      }
    }
    else if (( curkind == IIR_SIGNAL_DECLARATION ||
	       curkind == IIR_SIGNAL_INTERFACE_DECLARATION ) &&
	     data_array[i]->get_kind() == IIR_INDEXED_NAME ) {
      IIR_Declaration *decl;
      decl = (IIR_Declaration*)((IIR_IndexedName*)data_array[i])->get_prefix();
      if (( decl->get_kind() == IIR_SIGNAL_DECLARATION ||
	    decl->get_kind() == IIR_SIGNAL_INTERFACE_DECLARATION ) &&
	  !IIR_TextLiteral::_cmp( decl->get_declarator(),
				  to_find->get_declarator())) {
	return i;
      }
    }
  }
  return -1;
}


template <class type>
inline bool 
signal_set<type>::intersects( signal_set<type> &to_find ) {
  type *data = to_find.get_element();
  while ( data != NULL ) {
    if ( in_set( data )) {
      return true;
    }
    data = to_find.get_next_element();
  }
  return false;
}


template <class type>
inline bool 
signal_set<type>::intersects( type *to_find ) {
  signal_set<type> temporary;
  temporary.add( to_find );
  return intersects( temporary );
}

#endif
