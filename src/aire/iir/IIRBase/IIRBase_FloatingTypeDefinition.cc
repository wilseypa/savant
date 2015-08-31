
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

#include "IIRBase_FloatingTypeDefinition.hh"

#include "IIR_DesignFile.hh"
#include "IIR_FloatingSubtypeDefinition.hh"
#include "IIR_FloatingTypeDefinition.hh"
#include "IIR_TypeDefinition.hh"

#include "StandardPackage.hh"

IIRBase_FloatingTypeDefinition::IIRBase_FloatingTypeDefinition() {}
IIRBase_FloatingTypeDefinition::~IIRBase_FloatingTypeDefinition() {}

IIR_TypeDefinition *
IIRBase_FloatingTypeDefinition::check_special_compatible( IIR_TypeDefinition *to_check ){
  IIR_FloatingTypeDefinition *package_real = 
    dynamic_cast<IIR_FloatingTypeDefinition *>(to_check->get_design_file()->get_standard_package()->get_savant_universal_real());

  if(((this == package_real) && 
      (dynamic_cast<IIR_FloatingTypeDefinition *>(to_check) != NULL) ) ||
     dynamic_cast<IIR_FloatingTypeDefinition *>(to_check) == package_real ){
    return package_real;
  }
  else{
    return NULL;
  }
}
