#ifndef IIRSCRAM_DECLARATION_LIST_HH
#define IIRSCRAM_DECLARATION_LIST_HH
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
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_List.hh"
#include "IIRBase_DeclarationList.hh"

class IIRScram_AttributeSpecification;
class IIRScram_List;
class IIRScram_Name;
class IIRScram_StatementList;
class IIRScram_TextLiteral;

class IIRScram_DeclarationList : public virtual IIRScram_List, public virtual IIRBase_DeclarationList{

public:
  IIRScram_DeclarationList() {}
  virtual ~IIRScram_DeclarationList();
    
  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);
  
  /** This method looks through the list, finds the configuration
      specifications, and does the appropriate type checking on them.  The
      statement list passed in is so that labels can be found if needed. */
  void _type_check_configuration_specifications( IIRScram_List *statement_list );

  /** This method looks through the list, finds the disconnection
      specifications, and does the appropriate type checking on them. */
  void _type_check_disconnection_specifications( );

  /** This method looks through the list, finds the attribute
      specifications, and does the appropriate type checking on them.  The
      statement list passed in is so that labels can be found if needed. */
  void _type_check_attribute_specifications( IIRScram_List *statement_list );

  /** This method assumes this list is a list of context items (use clauses
      and library clauses) and makes the appropriate stuff visible in the
      symbol table passed in. */
  void _make_visible_as_context_list( symbol_table * );

  /** This method applies the method passed in to each element, and builds
      a newly allocated list of the members that returned true. */
  IIRScram_DeclarationList *_build_constrained_list( IIR_Boolean (IIRScram::*constraint_function)() );

  IIRScram *_clone();

protected:
private:
};
#endif
