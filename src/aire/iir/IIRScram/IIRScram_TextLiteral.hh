#ifndef IIRSCRAM_TEXT_LITERAL_HH
#define IIRSCRAM_TEXT_LITERAL_HH

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
//          Timothy J. McBrayer tmcbraye@ece.uc.edu
//          Malolan Chetlur     mal@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_Literal.hh"
#include "IIRBase_TextLiteral.hh"
#include "IRBasicDataTypes.hh"

class IIRScram_Declaration;
class IIRScram_Name;
class IIRScram_TypeDefinition;

class IIRScram_TextLiteral : public virtual IIRScram_Literal, public virtual IIRBase_TextLiteral{

public:
  IIRScram_TextLiteral();
  virtual ~IIRScram_TextLiteral();

  // Makes this string go to lower case.
  void _to_lower();

  IIR_Boolean _is_iir_text_literal(){ return TRUE; }

  savant::set<IIRScram_TypeDefinition> *_get_rval_set(constraint_functor *functor = 0);  

  savant::set<IIRScram_Declaration> *_symbol_lookup();
  savant::set<IIRScram_Declaration> *_symbol_lookup(constraint_functor *functor);

  // Implements "get_rval_set" for String and BitString Literals
  savant::set<IIRScram_TypeDefinition> *_get_rval_set_for_string();
  

protected:
    
private:
};

#endif
