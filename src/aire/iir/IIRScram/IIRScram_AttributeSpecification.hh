#ifndef IIRSCRAM_ATTRIBUTE_SPECIFICATION_HH
#define IIRSCRAM_ATTRIBUTE_SPECIFICATION_HH

// Copyright (c) 1996-2000 The University of Cincinnati.  
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

// Authors: Philip A. Wilsey	phil.wilsey@uc.edu
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Timothy J. McBrayer tmcbraye@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_Declaration.hh"
#include "IIRBase_AttributeSpecification.hh"

class IIRScram_DeclarationList;
class IIRScram_TypeDefinition;

class IIRScram_AttributeSpecification : public virtual IIRScram_Declaration, public virtual IIRBase_AttributeSpecification{

public:
  IIRScram_AttributeSpecification();
  virtual ~IIRScram_AttributeSpecification();

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);


  void _type_check( IIRScram_DeclarationList *declarative_region );

  IIR_Boolean _is_specification(){ return TRUE; }
  IIR_Boolean _can_be_in_same_region( IIRScram_Declaration * );

  void _set_entity_constraint( constraint_functor *functor ){
    _my_functor = functor;
  }

  constraint_functor *_get_entity_constraint() {
    return _my_functor;
  }

  IIR_Boolean                   _is_iir_attribute_specification(){ return TRUE; }
  IIRScram_Identifier           *_get_entity_class();
  IIRScram_DesignatorList       *_get_entity_name_list();
  IIRScram                      *_get_value();
  IIRScram_Declaration          *_get_declaration();

private:
  constraint_functor            *_my_functor;
};
#endif
