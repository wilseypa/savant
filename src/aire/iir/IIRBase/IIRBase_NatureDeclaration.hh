
#ifndef IIRBASE_NATURE_DECLARATION_HH
#define IIRBASE_NATURE_DECLARATION_HH

// Copyright (c) 2002 The University of Cincinnati.
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
 
// Authors: Sivakumar Gowrisankar             gowriss@ececs.uc.edu
//          Vinod Chamarty                    chamarv@ececs.uc.edu
//          Vasudevan Shanmugasundaram
//          Kathiresan Nellayappan
 
//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIR_NatureDeclaration.hh"
#include "IIRBase_Declaration.hh"
#include "IRBasicDataTypes.hh"

class IIR_AttributeSpecificationList;
class IIR_NatureDefinition;
class IIR_TypeDefinition;

class IIRBase_NatureDeclaration : public virtual IIRBase_Declaration, public virtual IIR_NatureDeclaration {

public:
  // List Accessor(s)
  IIR_AttributeSpecificationList  *get_attributes();
  void                            set_attributes(IIR_AttributeSpecificationList *new_attributes);

  IIR_Kind get_kind() const {return IIR_NATURE_DECLARATION;}
  const IIR_Char *get_kind_text() const {return "IIR_NatureDeclaration";}

  /** Set the Nature of the terminal */
  void set_nature(IIR_NatureDefinition* nature);

  /** Get nature of the terminal */
  IIR_NatureDefinition *get_nature();

  IIR *convert_tree(plugin_class_factory *factory);

  IIR_Boolean is_array_type();

  /** Returns the nature of the subtype */ 
  IIR_TypeDefinition *get_subtype();

  /** Returns the reference terminal */
  IIR_TerminalDeclaration* get_reference_terminal();

  /** Set the reference terminal */
  void set_reference_terminal(IIR_TerminalDeclaration*);

  declaration_type get_declaration_type();

  IIR_TypeDefinition *get_final_subtype();
  
  void publish_vhdl_decl(ostream &vhdl_out);

protected : 

  IIRBase_NatureDeclaration();
  virtual ~IIRBase_NatureDeclaration()= 0;

private:
  // List Variable(s)
  IIR_AttributeSpecificationList  *attributes;

  IIR_NatureDefinition* nature;
  IIR_TerminalDeclaration* reference_terminal;
};

#endif
