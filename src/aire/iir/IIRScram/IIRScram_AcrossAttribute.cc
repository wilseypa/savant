
// Copyright (c) The University of Cincinnati.  All rights reserved.

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

#include "IIRScram_AcrossAttribute.hh"
#include "IIRScram_Declaration.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_NatureDeclaration.hh"
#include "IIRScram_NatureDefinition.hh"
#include "IIRScram_ScalarNatureDefinition.hh"
#include "IIRScram_TextLiteral.hh"
#include "IIRScram_TypeDefinition.hh"

#include "error_func.hh"

#include "resolution_func.hh"
#include "set.hh"
#include "StandardPackage.hh"

using std::cerr;
using std::endl;

IIRScram_TypeDefinition*
IIRScram_AcrossAttribute::_get_subtype() {
  savant::set<IIRScram_Declaration>* nature_decl_set;
  IIRScram_Declaration* nature_decl;
  IIRScram_TypeDefinition *type_def;
  
  nature_decl_set = _get_prefix()->_symbol_lookup();
  if (nature_decl_set->size() == 0) {
    return NULL;
  }
  nature_decl = nature_decl_set->getElement();
  if (nature_decl->get_kind() == IIR_NATURE_DECLARATION) {
    type_def = dynamic_cast<IIRScram_TypeDefinition *>((dynamic_cast<IIRScram_ScalarNatureDefinition *>
               (dynamic_cast<IIRScram_NatureDeclaration*>(nature_decl)->get_nature()))->IIRBase_ScalarNatureDefinition::get_across());
    if (type_def != NULL) {
      return type_def;
    }
    else {
      cerr <<"Invalid Across type for Nature "<<endl;
      return NULL;
    }
  }
  else {
    cerr << " |" << _get_attribute_name()
         << "| - may only be applied to natures " << endl;
    return NULL;
  }
}
