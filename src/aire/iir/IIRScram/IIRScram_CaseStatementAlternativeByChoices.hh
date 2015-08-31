
#ifndef IIRSCRAM_CASE_STATEMENT_ALTERNATIVE_BY_CHOICES_HH
#define IIRSCRAM_CASE_STATEMENT_ALTERNATIVE_BY_CHOICES_HH

// Copyright (c) 1996-2002 The University of Cincinnati.  
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

// Authors: Philip A. Wilsey    philip.wilsey@ieee.org
//          Dale E. Martin      dmartin@cliftonlabs.com
//          Timothy J. McBrayer
//          Umesh Kumar V. Rajasekaran
//          Narayanan Thondugulam

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_CaseStatementAlternative.hh"
#include "IIRBase_CaseStatementAlternativeByChoices.hh"

class IIRScram_TypeDefinition;
class IIRScram_List;
class IIRScram_ChoiceList;

class IIRScram_CaseStatementAlternativeByChoices : public virtual IIRScram_CaseStatementAlternative, public virtual IIRBase_CaseStatementAlternativeByChoices{
  
public:
  IIRScram_CaseStatementAlternativeByChoices();
  virtual ~IIRScram_CaseStatementAlternativeByChoices();

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);
  
  void _type_check( savant::set<IIRScram_TypeDefinition> * );
  savant::set<IIRScram_TypeDefinition> *_get_rval_set(constraint_functor *functor=0); 
  
  
  IIRScram              *_clone();
  IIRScram_ChoiceList   *_get_choices();

protected:
private:

};

#endif
