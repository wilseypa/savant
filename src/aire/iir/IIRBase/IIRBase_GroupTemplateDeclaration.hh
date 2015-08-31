
#ifndef IIRBASE_GROUP_TEMPLATE_DECLARATION_HH
#define IIRBASE_GROUP_TEMPLATE_DECLARATION_HH

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
//          Malolan Chetlur     mal@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRBase_Declaration.hh"
#include "IIR_GroupTemplateDeclaration.hh"

class IIR_EntityClassEntryList;
class IIRBase_GroupTemplateDeclaration : public virtual IIRBase_Declaration, public virtual IIR_GroupTemplateDeclaration{

public:
  // List Accessor(s)
  IIR_EntityClassEntryList *get_entity_class_entry_list();
  void                     set_entity_class_entry_list(IIR_EntityClassEntryList *new_entity_class_entry_list);

  IIR_Kind get_kind() const {return IIR_GROUP_TEMPLATE_DECLARATION;}
  const IIR_Char *get_kind_text() const {return "IIR_GroupTemplateDeclaration";}

  IIR *convert_tree(plugin_class_factory *factory);

  declaration_type get_declaration_type(){ return GROUP_TEMPLATE; }
  void publish_vhdl_decl(ostream &);
protected:
  IIRBase_GroupTemplateDeclaration();
  virtual ~IIRBase_GroupTemplateDeclaration() = 0;
    
private:
  // List Variable(s)
  IIR_EntityClassEntryList *entity_class_entry_list;

};
#endif
