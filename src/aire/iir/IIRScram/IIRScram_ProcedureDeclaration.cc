// Copyright (c) 1996-2000 The FUNCTIONniversity of Cincinnati.  
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
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu
//          Malolan Chetlur     mal@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu
//	    Magnus Danielson	cfmd@swipnet.se

//---------------------------------------------------------------------------

#include "IIRScram_InterfaceList.hh"
#include "IIRScram_ProcedureDeclaration.hh"
#include "IIRScram_SequentialStatementList.hh"
#include "IIRScram_ProcedureReturnTypeDefinition.hh"
#include "IIRScram_TextLiteral.hh"

visitor_return_type *
IIRScram_ProcedureDeclaration::_accept_visitor( node_visitor *visitor, 
						visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_ProcedureDeclaration(this, arg);
}

IIR_TypeDefinition *
IIRScram_ProcedureDeclaration::get_subtype(){
  IIR_TypeDefinition *type = get_procedure_return_type();
  copy_location(this, type);
  return type;
}

IIR_TypeDefinition *
IIRScram_ProcedureDeclaration::get_procedure_return_type(){
  static IIRScram_ProcedureReturnTypeDefinition _procedure_return_type;
  return &_procedure_return_type;
}
