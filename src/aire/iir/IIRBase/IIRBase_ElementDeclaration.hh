
#ifndef IIRBASE_ELEMENT_DECLARATION_HH
#define IIRBASE_ELEMENT_DECLARATION_HH

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

#include "savant_config.hh"
#include "IIRBase_ObjectDeclaration.hh"
#include "IIR_ElementDeclaration.hh"


class IIRBase_ElementDeclaration : public virtual IIRBase_ObjectDeclaration, public virtual IIR_ElementDeclaration{

public:
  IIR_Kind get_kind() const {return IIR_ELEMENT_DECLARATION;}
  const IIR_Char *get_kind_text() const {return "IIR_ElementDeclaration";}
  IIR_Boolean is_element(){ return TRUE; }

  declaration_type get_declaration_type(){ return ELEMENT; }

  savant::set<IIR_Declaration> *find_declarations( IIR_Name *to_find );
  void publish_vhdl_decl(ostream &);
protected:
  IIRBase_ElementDeclaration();
  virtual ~IIRBase_ElementDeclaration() = 0;
    
private:
};
#endif
