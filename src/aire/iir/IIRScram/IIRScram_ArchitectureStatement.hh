#ifndef IIRSCRAM_ARCHITECTURE_STATEMENT_HH
#define IIRSCRAM_ARCHITECTURE_STATEMENT_HH

// Copyright (c) The University of Cincinnati.  
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

#include "savant_config.hh"
#include "IIRScram_Statement.hh"
#include "IIRBase_ArchitectureStatement.hh"
#include <string>

class IIRScram_AssociationList;
class IIRScram_SignalDeclaration;

class IIRScram_ArchitectureStatement : public virtual IIRScram_Statement, public virtual IIRBase_ArchitectureStatement {
public:
  IIRScram_ArchitectureStatement();
  virtual ~IIRScram_ArchitectureStatement();
  virtual IIRScram* _get_instantiated_unit() {
    _report_undefined_scram_fn("_get_instantiated_unit()");
    return NULL;
  };

  virtual IIRScram_AssociationList *_get_generic_map_aspect() {
    _report_undefined_scram_fn("_get_generic_map_aspect()");
    return NULL;
  }
  
  IIR_Boolean _is_iir_concurrent_statement() { return TRUE; }

  // This method is overriden by classes that can contain instantiate
  // statements.
  virtual void _type_check_instantiate_statements(){ }

  // This method should be overloaded by statements that contain concurrent
  // statement lists.  Currently it's overloaded for concurrent generate for
  // and concurrent generate if statements only.
  IIRScram_ArchitectureStatementList *_get_architecture_statment_list(){ return NULL; }
  
protected:  
  virtual void _resolve_guard_signal( symbol_table * );

private:
};
#endif
