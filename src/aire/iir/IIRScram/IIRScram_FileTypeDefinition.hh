#ifndef IIRSCRAM_FILE_TYPE_DEFINITION_HH
#define IIRSCRAM_FILE_TYPE_DEFINITION_HH

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
#include "IIRScram_TypeDefinition.hh"
#include "IIRBase_FileTypeDefinition.hh"

class IIRScram_FunctionDeclaration;
class IIRScram_TypeDeclaration;

class IIRScram_FileTypeDefinition : public virtual IIRScram_TypeDefinition, public virtual IIRBase_FileTypeDefinition{

public:
  IIRScram_FileTypeDefinition() {}
  virtual ~IIRScram_FileTypeDefinition();
    
  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);

  /** This function builds the implicit declarations associated with
      file types.  It also adds the declarations to the symbol table
      and to the type's list of implicit_declarations. */
  void  _come_into_scope( symbol_table *, IIRScram_TypeDeclaration * );

  IIR_Boolean is_locally_static(){ return TRUE; }

  void _set_resolution_function( IIRScram_FunctionDeclaration * );

protected:
private:
  IIRScram_TypeDefinition *_get_type_mark();
};
#endif
