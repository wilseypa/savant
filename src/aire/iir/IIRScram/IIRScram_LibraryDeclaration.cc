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
//          Malolan Chetlur     mal@ece.uc.edu
//          Timothy J. McBrayer tmcbraye@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------

#include "IIRScram_ConfigurationDeclaration.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_EntityDeclaration.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_LibraryDeclaration.hh"
#include "IIRScram_LibraryUnit.hh"
#include "IIRScram_LibraryUnitList.hh"
#include "IIRScram_Name.hh"
#include "IIRScram_PackageDeclaration.hh"

#include <clutils/FileManager.h>

#include "error_func.hh"
#include "resolution_func.hh"
#include "set.hh"
#include "StandardPackage.hh"
#include "library_manager.hh"

extern char *design_library_name;

IIRScram_LibraryDeclaration::IIRScram_LibraryDeclaration() {
  set_primary_units(new IIRScram_LibraryUnitList());
}

IIRScram_LibraryDeclaration::~IIRScram_LibraryDeclaration() {
  //Release the list memory
  delete get_primary_units();
}

void 
IIRScram_LibraryDeclaration::_add_to_declarative_region( savant::set<IIRScram_Declaration> *set_to_add ){
  IIRScram_Declaration::_add_to_declarative_region( _get_primary_units(), set_to_add );
}

visitor_return_type *
IIRScram_LibraryDeclaration::_accept_visitor( node_visitor *visitor,
					      visitor_argument_type *arg ){
  ASSERT(visitor != NULL);
  return visitor->visit_IIR_LibraryDeclaration(this, arg);
}

// IIRBase Function Wrapper(s)
IIRScram_LibraryUnitList *
IIRScram_LibraryDeclaration::_get_primary_units() {
  return dynamic_cast<IIRScram_LibraryUnitList *>(get_primary_units());
}
