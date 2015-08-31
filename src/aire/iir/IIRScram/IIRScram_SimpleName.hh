#ifndef IIRSCRAM_SIMPLE_NAME_HH
#define IIRSCRAM_SIMPLE_NAME_HH
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
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_Name.hh"
#include "IIRBase_SimpleName.hh"

class IIRScram_Declaration;
class IIRScram_Identifier;
class IIRScram_TextLiteral;
class IIRScram_TypeDefinition;

class IIRScram_SimpleName : public virtual IIRScram_Name, public virtual IIRBase_SimpleName{

public:
  IIRScram_SimpleName() {}
  virtual ~IIRScram_SimpleName();    

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);


  savant::set<IIRScram_Declaration> *_symbol_lookup();
  savant::set<IIRScram_Declaration> *_symbol_lookup( savant::set<IIRScram_Declaration> * );

  savant::set<IIRScram_TypeDefinition> *_get_rval_set(constraint_functor *functor = 0);

  IIRScram_TypeDefinition *_determine_rval_in_set( savant::set<IIRScram_TypeDefinition> *search_in,
                                                   IIRScram_TypeDefinition *looking_for );

  IIRScram_Declaration *_determine_decl_in_set( savant::set<IIRScram_Declaration> *search_in,
                                                IIRScram_TypeDefinition *looking_for );

  IIRScram *_rval_to_decl( IIRScram_TypeDefinition *);
  IIRScram *_decl_to_decl( IIRScram_Declaration * );

  IIRScram *_rval_to_decl( IIRScram_TypeDefinition *, IIRScram_TypeDefinition * );
  IIRScram *_rval_to_decl( IIRScram_Declaration *, IIRScram_TypeDefinition * );
  
  void _type_check( savant::set<IIRScram_TypeDefinition> * );
  IIRScram_TextLiteral *_get_string();

  const string convert_to_library_name();

  IIRScram *_clone();

protected:
private:

  // This method looks at what this name is about to resolve to and decides
  // if it should be returning a function call instead.  So, it will return
  // either a function call, or the declaration passed in.
  IIRScram *_convert_to_function_call( IIRScram_Declaration * );
};
#endif
