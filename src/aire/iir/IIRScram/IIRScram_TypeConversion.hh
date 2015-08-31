#ifndef IIRSCRAM_TYPE_CONVERSION_HH
#define IIRSCRAM_TYPE_CONVERSION_HH

// Copyright (c) 1996-2003 The University of Cincinnati.  
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
// OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
// LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING OR
// DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the U.S.,
// and the terms of this license.

// You may modify, distribute, and use the software contained in this
// package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
// version 2, June 1991. A copy of this license agreement can be found in
// the file "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Malolan Chetlur    
//          Umesh Kumar V. Rajasekaran
//          Radharamanan Radhakrishnan
//          Krishnan Subramani  

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_Expression.hh"
#include "IIRBase_TypeConversion.hh"

class IIRScram_TypeConversion : public virtual IIRScram_Expression,
				public virtual IIRBase_TypeConversion{

public:
  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);


  void _type_check( savant::set<IIRScram_TypeDefinition> * ){}
  savant::set<IIRScram_TypeDefinition> *_get_rval_set(constraint_functor *functor = 0 );

  IIRScram_Declaration *_find_formal_declaration();

  IIRScram_TypeDefinition *_get_type_mark();
  IIRScram * _get_expression();

protected:

private:
  IIR_Int32 _stmt_node_index;

};
#endif
