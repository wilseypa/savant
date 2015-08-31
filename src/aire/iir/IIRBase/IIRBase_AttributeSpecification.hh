
#ifndef IIRBASE_ATTRIBUTE_SPECIFICATION_HH
#define IIRBASE_ATTRIBUTE_SPECIFICATION_HH

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
//          Timothy J. McBrayer tmcrbaye@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRBase_Declaration.hh"
#include "IIR_AttributeSpecification.hh"

class IIR_Identifier;
class IIR_DesignatorList;
class IIR_Declaration;

class IIRBase_AttributeSpecification : public virtual IIRBase_Declaration, public virtual IIR_AttributeSpecification{

public:
  // List Accessor(s)
  IIR_DesignatorList *get_entity_name_list();
  void               set_entity_name_list(IIR_DesignatorList *new_entity_name_list);

  IIR_Kind get_kind() const {return IIR_ATTRIBUTE_SPECIFICATION;}
  const IIR_Char *get_kind_text() const {return "IIR_AttributeSpecification";}

  void set_value(IIR*);
  IIR *get_value();

  void set_entity_class(IIR_Identifier *);
  IIR_Identifier *get_entity_class();

  IIR *convert_tree(plugin_class_factory *factory);

  /** This holds the the declaration of the attribute that is being
      specified... */
  void set_declaration( IIR_Declaration *);
  IIR_Declaration *get_declaration();

  IIR_TypeDefinition *get_subtype();

  declaration_type get_declaration_type();
  void publish_vhdl_decl(ostream &);
protected:
  IIRBase_AttributeSpecification();
  virtual ~IIRBase_AttributeSpecification() = 0;
    
private:
  // List Variable(s)
  IIR_DesignatorList *entity_name_list;

  IIR *value;
  IIR_Identifier *entity_class;
  IIR_Declaration *attribute_declaration;
};
#endif
