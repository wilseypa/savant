
#ifndef IIRSCRAM_CASE_STATEMENT_HH
#define IIRSCRAM_CASE_STATEMENT_HH

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
//          Umesh Kumar V. Rajasekaran

// You may modify, distribute, and use the software contained in this package
// under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2,
// June 1991. A copy of this license agreement can be found in the file
// "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey	phil.wilsey@uc.edu
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Timothy J. McBrayer tmcbraye@ece.uc.edu
//          Malolan Chetlur     mal@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_SequentialStatement.hh"
#include "IIRBase_CaseStatement.hh"

template <class type> class set;
class IIRScram_List;

class IIRScram_CaseStatement : public virtual IIRScram_SequentialStatement, public virtual IIRBase_CaseStatement{
public:
  IIRScram_CaseStatement();
  virtual ~IIRScram_CaseStatement();

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);

  
  IIR_Boolean _type_check_return_statements( savant::set<IIRScram_TypeDefinition> *, 
					     IIRScram_SubprogramDeclaration * );
  
  void _type_check();

  IIRScram                              *_get_expression();
  IIRScram                              *_get_case_statement_expression();
  IIRScram_CaseStatementAlternativeList *_get_case_statement_alternatives();

  void _set_case_statement_expression( IIRScram * );
  IIRScram *_clone();

protected:    
private:
  // Handle error reporting in a function for both expressions and
  // alternatives.
  IIRScram *_handle_reconciliation( savant::set<IIRScram_TypeDefinition> *rval_set,
                                    IIRScram *node_in_consideration,
                                    char *error_part );
};
#endif
