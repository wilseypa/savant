#ifndef IIRBASE_PROCEDURE_RETURN_TYPE_DEFINITION_HH
#define IIRBASE_PROCEDURE_RETURN_TYPE_DEFINITION_HH

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
#include "IIRBase.hh"
#include "IIRBase_TypeDefinition.hh"

class IIRBase_ProcedureDeclaration;
class IIRBase_FunctionDeclaration;

class IIRBase_ProcedureReturnTypeDefinition : public virtual IIRBase_TypeDefinition{

public:
  IIRBase_ProcedureReturnTypeDefinition(){};
  ~IIRBase_ProcedureReturnTypeDefinition(){};

  //@{ These should never get called, but they're pure virtual so they
  // have to be overloaded.
  IIR_Kind get_kind() const { return _IIR_ERROR; }
  const char *get_kind_text() const { return "IIR_ProcedureReturnTypeDefinition"; }

  void _set_resolution_function( IIRBase_FunctionDeclaration * ){ ASSERT( 0 ); }
  //@}


  IIR_FunctionDeclaration *get_resolution_function(){ return 0; }

private:
};

#endif
