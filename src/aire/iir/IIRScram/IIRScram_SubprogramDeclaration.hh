#ifndef IIRSCRAM_SUBPROGRAM_DECLARATION_HH
#define IIRSCRAM_SUBPROGRAM_DECLARATION_HH

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
//          Radharamanan Radhakrishnan  ramanan@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_Declaration.hh"
#include "IIRBase_SubprogramDeclaration.hh"

class IIRScram_AttributeSpecificationList;
class IIRScram_Declaration;
class IIRScram_DeclarationList;
class IIRScram_InterfaceList;
class IIRScram_SequentialStatementList;
class IIRScram_TypeDefinition;

class IIRScram_SubprogramDeclaration : public virtual IIRScram_Declaration, public virtual IIRBase_SubprogramDeclaration{

public:
  IIRScram_SubprogramDeclaration();
  ~IIRScram_SubprogramDeclaration();

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);

  /** See header of IIRScram_Declaration for description. */
  bool _check_param( IIRScram_TypeDefinition *type_def, int arg_num );

  /** This method type checks all of the return statements in this
      subprogram.  It recursively descends the statements within the
      declaration as well.  The return value tells us if at least one
      return was encountered. */
  IIR_Boolean _type_check_return_statements( IIRScram_TypeDefinition *context_set );
  
  virtual void _type_check();

  /** This method adds the declaration to the symbol table, _after_ the
      declarator and interface have been parsed, and _after_ the
      "_contains_body" flag has been set, if needed.  This is necessary
      because the symbol table needs to know the full signature to
      determine the hiding and that kind of stuff. */
  void _add_declaration();

  /** This method returns the type definition of the parameter passed in.
      For the first parameter, pass in 0.  If the number passed in is
      greater than the number of parameters, a NULL is returned. */
  IIRScram_TypeDefinition *_get_type_of_param(int);
  
  IIR_Boolean _is_implicit_operator();
  IIR_Boolean _is_overloadable(){ return TRUE; }
  
  /** This method takes two subprogram declarations and compares their
      return values and signatures (ONLY - not parameter names or anything
      like that), and returns a boolean value indicating whether or not
      they are equivalent. */
  static IIR_Boolean _compare_signatures( IIRScram_SubprogramDeclaration *,
					  IIRScram_SubprogramDeclaration *);
  
  IIR_Boolean _is_homograph_of( IIRScram_Declaration * );
  IIR_Boolean _can_be_in_same_region( IIRScram_Declaration * );

  void _make_interface_visible( symbol_table * );

  IIRScram_AttributeSpecificationList* _get_attribute_specification_list();

  IIR_Int32 _num_required_args();

  IIRScram_List *_get_statement_list();

  // Wrappers for IIRBase functions
  IIRScram_InterfaceList *              _get_interface_declarations();
  IIRScram_SequentialStatementList *    _get_subprogram_body();
  IIRScram_DeclarationList *            _get_subprogram_declarations();

protected:    
private:
};
#endif

