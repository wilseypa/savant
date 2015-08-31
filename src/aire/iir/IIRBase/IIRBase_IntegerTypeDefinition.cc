
// Copyright (c) 1996-1999 The University of Cincinnati.  
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

//---------------------------------------------------------------------------

#include "IIRBase_IntegerTypeDefinition.hh"

#include "IIR_DesignFile.hh"
#include "IIR_IntegerSubtypeDefinition.hh"
#include "IIR_TypeDefinition.hh"

#include "StandardPackage.hh"

IIRBase_IntegerTypeDefinition::IIRBase_IntegerTypeDefinition() {}
IIRBase_IntegerTypeDefinition::~IIRBase_IntegerTypeDefinition() {}

IIR_TypeDefinition *
IIRBase_IntegerTypeDefinition::check_special_compatible( IIR_TypeDefinition *to_check ){
  StandardPackage *package = to_check->get_design_file()->get_standard_package();
  // Note that it things like array indexes can be subtypes of universal
  // integer so we'll cut to the chase and simply check base types.
  IIR_TypeDefinition *package_base_type = 
    dynamic_cast<IIR_TypeDefinition *>(package->get_savant_universal_integer())->get_bottom_base_type();

  if( (to_check->get_bottom_base_type() == package_base_type) ||
      (( get_bottom_base_type() == package_base_type) &&
       dynamic_cast<IIR_IntegerTypeDefinition *>(to_check) != NULL ) ) {
    return dynamic_cast<IIR_TypeDefinition *>(package->get_savant_universal_integer());
  }
  else{
    return NULL;
  }
}
  
