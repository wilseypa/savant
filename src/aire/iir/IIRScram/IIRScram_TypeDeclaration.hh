#ifndef IIRSCRAM_TYPE_DECLARATION_HH
#define IIRSCRAM_TYPE_DECLARATION_HH
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
//          Krishnan Subramani  skrish@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu
//          Malolan Chetlur     mal@ece.uc.edu
//          Radharamanan Radhakrishnan  ramanan@ece.uc.edu
//          Swaminathan Subramanian ssubrama@ececs.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRBase_TypeDeclaration.hh"
#include "IIRScram_Declaration.hh"

class IIRScram_AttributeSpecification;
class IIRScram_AttributeSpecificationList;

/**
   The extension base for type declarations.
*/
class IIRScram_TypeDeclaration : public virtual IIRScram_Declaration, public virtual IIRBase_TypeDeclaration{

public:
  IIRScram_TypeDeclaration();
  virtual ~IIRScram_TypeDeclaration();

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);


  IIR_Boolean _attach_attribute( IIRScram_AttributeSpecification * );

  IIRScram_AttributeSpecificationList* _get_attribute_specification_list();

  virtual void _type_check();

  IIR_Boolean _designates_incomplete_type();
  IIR_Boolean _can_be_in_same_region( IIRScram_Declaration * );

  IIR_Boolean _is_readable(){ return TRUE; }
  IIR_Boolean _is_writable(){ return FALSE; }
  IIR_Int32 get_num_indexes();

  // The following methods apply to incomplete type declarations.  After
  // the parser has found the definition of an incomplete type, these methods
  // can be called on the incomplete type to get the full definition.
  IIRScram_TypeDefinition *_get_fully_defined_type(){
    return _fully_defined_type;
  }

  void _set_fully_defined_type( IIRScram_TypeDefinition *my_real_type ){
    _fully_defined_type = my_real_type;
  }

  void _come_into_scope( symbol_table *sym_tab );
  void _come_out_of_scope( symbol_table *sym_tab );

  virtual IIRScram *_clone();


  IIRScram_TypeDefinition *_get_type_definition();
protected:    
private:
  IIRScram_TypeDefinition *                     _fully_defined_type;
};
#endif
