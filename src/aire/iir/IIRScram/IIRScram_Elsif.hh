#ifndef IIRSCRAM_ELSIF_HH
#define IIRSCRAM_ELSIF_HH

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
//          Malolan Chetlur     mal@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_Tuple.hh"
#include "IIRBase_Elsif.hh"
#include "dl_list.hh"

class IIRScram_DesignatorList;
class IIRScram_List;
class IIRScram_ProcedureCallStatement;
class IIRScram_SequentialStatementList;
class IIRScram_SubprogramDeclaration;
class IIRScram_TypeDefinition;
class IIRScram_WaitStatement;

class IIRScram_Elsif : public virtual IIRScram_Tuple, public virtual IIRBase_Elsif{
public:
  IIRScram_Elsif();
  virtual ~IIRScram_Elsif();

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);

  void _type_check( savant::set<IIRScram_TypeDefinition> * );
  IIR_Boolean _type_check_return_statements( savant::set<IIRScram_TypeDefinition> *,
			     IIRScram_SubprogramDeclaration *subprogram_decl );
    
  IIRScram *_clone();

  // Wrappers for IIRBase functions
  IIRScram_SequentialStatementList *    _get_then_sequence_of_statements();
  IIRScram *                            _get_condition();
  IIRScram_Elsif *                      _get_else_clause();

protected:
private:
};
#endif
