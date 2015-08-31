
#ifndef IIRSCRAM_ENUMERATION_LITERAL_HH
#define IIRSCRAM_ENUMERATION_LITERAL_HH

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
//          Timothy J. McBrayer 
//          Malolan Chetlur     
//          Krishnan Subramani  
//          Umesh Kumar V. Rajasekaran
//          Narayanan Thondugulam
//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_Declaration.hh"
#include "IIRBase_EnumerationLiteral.hh"

class IIRScram_List;
class IIRScram_TypeDefinition;

class IIRScram_EnumerationLiteral : public virtual IIRScram_Declaration, public virtual IIRBase_EnumerationLiteral{

public:
  IIRScram_EnumerationLiteral();
  virtual ~IIRScram_EnumerationLiteral();
    
  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);


  savant::set<IIRScram_TypeDefinition> *_get_rval_set(constraint_functor *functor = 0);
  savant::set<IIRScram_Declaration> *_symbol_lookup();
  IIRScram *_rval_to_decl( IIRScram_TypeDefinition * );
  void _type_check( savant::set<IIRScram_TypeDefinition> * );
  IIRScram *_clone();

  IIR_Boolean _is_enumeration_literal() { return TRUE; }
  IIR_Boolean _is_iir_enumeration_literal(){ return TRUE; }
  IIR_Boolean is_locally_static() { return TRUE;}
  IIR_Boolean _is_overloadable(){ return TRUE; }
  IIR_Boolean _is_readable(){ return TRUE; }
  IIR_Boolean _is_writable(){ return FALSE; }
  IIR_Boolean _is_homograph_of( IIRScram_Declaration * );

  // an empty function to prevent incorrect error message.
  void _add_declarations_in_initializations() {};

  IIRScram_AttributeSpecificationList*  _get_attribute_specification_list();

  // Wrappers for IIRBase functions
  IIRScram_AttributeSpecificationList * _get_attributes();

protected:
private:
};
#endif
