#ifndef CONTAINER_HH
#define CONTAINER_HH

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
//          Tim McBrayer                tmcbraye@thor.ece.uc.edu

#include "savant_config.hh"
#ifndef NULL
#define NULL 0
#endif

// container template class for misc use in lists, queues, and such.

template <class type>
class container {




public:
  
  container() {object = NULL; previous = NULL; next = NULL;};
  ~container() {};
  
  container(type* s) {object = s; previous = NULL; next = NULL;};
  
  void link_next(container<type>* s) {next = s;};
  void link_previous(container<type>* s) {previous = s;};
  
  container<type>* next_container() {return next;};
  container<type>* previous_container() {return previous;};
  
  type* return_object() {return object;};

private:
  
  type* object;
  container<type>* previous;
  container<type>* next;
  
};

#endif
