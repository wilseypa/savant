
// Copyright (c) 2003 The University of Cincinnati.  
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR
// NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
// LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the U.S., and
// the terms of this license.

// You may modify, distribute, and use the software contained in this package
// under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2, June
// 1991. A copy of this license agreement can be found in the file "LGPL",
// distributed with this archive.

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org

//---------------------------------------------------------------------------

#include "IIRBase_ArchitectureStatement.hh"

IIRBase_ArchitectureStatement::IIRBase_ArchitectureStatement(){}

IIRBase_ArchitectureStatement::~IIRBase_ArchitectureStatement(){}

void 
IIRBase_ArchitectureStatement::set_guard_signal( IIR_SignalDeclaration * ){
  _report_undefined_fn("set_guard_signal( IIR_Declaration * )");
}

void
IIRBase_ArchitectureStatement::set_declarative_region( IIR *outerRegion ){
  enclosingRegion = outerRegion;
}

IIR *
IIRBase_ArchitectureStatement::get_declarative_region(){
  return enclosingRegion;
}
