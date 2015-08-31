
#ifndef IIRSCRAM_PROCESS_STATEMENT_HH
#define IIRSCRAM_PROCESS_STATEMENT_HH

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
//          Narayanan Thondugulam
//          Swaminathan Subramanian

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_ConcurrentStatement.hh"
#include "IIRBase_ProcessStatement.hh"

class IIRScram_Name;
class IIRScram_SequentialStatementList;
class IIRScram_WaitStatement;

class IIRScram_ProcessStatement : public virtual IIRScram_ConcurrentStatement,
				  public virtual IIRBase_ProcessStatement{
public:
  IIRScram_ProcessStatement();
  virtual ~IIRScram_ProcessStatement();
    
  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);

  /** Publshes the warped state class for this process. */
  void _add_declarations_in_initializations();

  virtual void _type_check();
  IIRScram *_clone();

  IIRScram_SequentialStatementList *    _get_process_statement_part();
  // Wrappers for IIRBase functions
  IIRScram_DeclarationList *            _get_process_declarative_part();

protected:
private:

};
#endif
