#ifndef IIRSCRAM_CASE_STATEMENT_ALTERNATIVE_HH
#define IIRSCRAM_CASE_STATEMENT_ALTERNATIVE_HH

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

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Timothy J. McBrayer 
//          Malolan Chetlur     
//          Umesh Kumar V. Rajasekaran
//          Narayanan Thondugulam
//          Ardhendu Singh
//          Krishnan Subramani

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_Tuple.hh"
#include "IIRBase_CaseStatementAlternative.hh"
#include "dl_list.hh"

class IIRScram_WaitStatement;
class IIRScram_TypeDefinition;
class IIRScram_SubprogramDeclaration;
class IIRScram_SequentialStatementList;

class IIRScram_CaseStatementAlternative : public virtual IIRScram_Tuple, public virtual IIRBase_CaseStatementAlternative{

public:
  IIRScram_CaseStatementAlternative();
  virtual ~IIRScram_CaseStatementAlternative();

  IIR_Boolean _type_check_return_statements( savant::set<IIRScram_TypeDefinition> *,
					     IIRScram_SubprogramDeclaration * );

  IIR_Boolean _is_iir_case_statement_alternative() {return TRUE;};

  IIRScram_SequentialStatementList *_get_sequence_of_statements();

  virtual void _clone( IIRScram * );
  IIRScram *_clone();

protected:
    

private:

};
#endif
