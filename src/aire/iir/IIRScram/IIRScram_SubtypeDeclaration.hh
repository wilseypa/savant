#ifndef IIRSCRAM_SUBTYPE_DECLARATION_HH
#define IIRSCRAM_SUBTYPE_DECLARATION_HH
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
//          Malolan Chetlur     mal@ece.uc.edu
//          Timothy J. McBrayer tmcbraye@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu
//          Swaminathan Subramanian ssubrama@ececs.uc.edu

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_Declaration.hh"
#include "IIRBase_SubtypeDeclaration.hh"

class IIRScram_AttributeSpecificationList;
class IIRScram_List;
class IIRScram_TypeDefinition;

/**
   The extension base for subtype declarations.
 */
class IIRScram_SubtypeDeclaration : public virtual IIRScram_Declaration, public virtual IIRBase_SubtypeDeclaration{
public:
  IIRScram_SubtypeDeclaration();
  ~IIRScram_SubtypeDeclaration();

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);


  IIRScram_AttributeSpecificationList* _get_attribute_specification_list();

  IIR_Boolean is_subtype_declaration(){ return TRUE; }
  IIR_Boolean _is_readable(){ return TRUE; }
  virtual IIRScram *_clone();

  virtual void _type_check();

  /**
     Presumably, we don't need to add subtype declarations into the code
     generator table.  However, in some cases (like attribute names
     subtype'something) this method will be called, so we're stubbing it out
     as an empty call.
  */
  IIR_Int32 get_num_indexes();

  // Wrappers for IIRBase functions
  IIRScram_AttributeSpecificationList * _get_attributes();

protected:
private:
};
#endif

