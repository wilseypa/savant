#ifndef IIRSCRAM_ALIAS_DECLARATION_HH
#define IIRSCRAM_ALIAS_DECLARATION_HH

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
//          Timothy J. McBrayer tmcrbaye@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Malolan Chetlur     mal@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu

//--------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_Declaration.hh"
#include "IIRBase_AliasDeclaration.hh"

class IIRScram_TypeDefinition;
class IIRScram_List;
class IIRScram_DesignatorList;
class IIRScram_AliasDeclaration;
class IIRScram_AttributeSpecificationList;

class IIRScram_AliasDeclaration : public virtual IIRScram_Declaration, public virtual IIRBase_AliasDeclaration{

public:
  IIRScram_AliasDeclaration() { _my_clone = NULL; }

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);

  // See IIRScram_Declaration for internal documentation for these methods.
  IIR_Boolean is_object();

  IIRScram_TypeDefinition *_get_type_of_element( int );
  IIR_Int32 get_num_indexes();
  void _type_check();

  IIR_Boolean _is_readable();
  IIR_Boolean _is_writable();

  const IIR_Char* _get_mangling_prefix();

  IIRScram_AttributeSpecificationList* _get_attribute_specification_list(); 

  /** For some reason, sometimes the code generate wants a fresh clone
     generated.  */
  void _clear_clone(){ _my_clone = 0; }

  IIRScram *_clone();

  void _come_into_scope( symbol_table * );
  void _come_out_of_scope( symbol_table * );

  IIRScram *_get_name();

protected:
  virtual ~IIRScram_AliasDeclaration();
    
private:
  IIRScram_AliasDeclaration *_my_clone;
};
#endif
