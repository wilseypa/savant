
#ifndef IIRBASE_TYPE_DEFINITION_HH
#define IIRBASE_TYPE_DEFINITION_HH

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
#include "IIR_TypeDefinition.hh"
#include "IIRBase.hh"

class IIR_Declaration;
class IIR_ScalarTypeDefinition;

class IIRBase_TypeDefinition : public virtual IIRBase, public virtual IIR_TypeDefinition {
public:
  void set_base_type(IIR_TypeDefinition *);
  IIR_TypeDefinition *get_base_type();
  IIR_TypeDefinition *get_resolved_base_type();

  // These are added here, because we think they'll become part of the
  // standard.  "get_declaration()" was promised many moons ago.
  IIR_Declaration *get_declaration();
  virtual void set_declaration( IIR_Declaration *);

  IIR_TypeDefinition *get_type_mark();
  void set_type_mark( IIR_TypeDefinition * );

  IIR *convert_tree(plugin_class_factory *factory);

  IIR_Boolean is_element();
  IIR_Boolean is_resolved() { return TRUE; }
  IIR_Boolean is_anonymous();
  IIR_Boolean is_subtype();

  IIR_Boolean is_unconstrained_array_type(){ return FALSE; }
  IIR_Boolean is_incomplete_type_definition(){ return FALSE; }
  IIR_Boolean is_subtype_decl();

  IIR_Boolean is_access_type()     { return FALSE; }
  IIR_Boolean is_array_type()      { return FALSE; }
  IIR_Boolean is_enumeration_type(){ return FALSE; }
  IIR_Boolean is_file_type()       { return FALSE; }
  IIR_Boolean is_record_type()     { return FALSE; }
  IIR_Boolean is_scalar_type()     { return FALSE; }

  IIR_TypeDefinition            *get_subtype() { return this; }
  IIR_ScalarTypeDefinition      *get_resolved_index_subtype();
  void                          set_index_subtype(IIR_ScalarTypeDefinition *);

  /** If this is an array type (or an access to an array type?), returns
      it's element subtype.  Otherwise, it complains and aborts! */
  //Follows IIRScram_TypeDefinition for use in plugin development - DRH/Ruda M
  virtual IIRBase_TypeDefinition        *_get_element_subtype(); 
  IIR_TypeDefinition            *get_element_subtype();
  void                          set_element_subtype(IIR_TypeDefinition *);

  // A scalar subtype may return NULL as it's left even if it has a range
  // constraint.  These methods will travel down to the first base type
  // that has a left defined.  Similarly for right and direction.
  IIR* get_base_type_left();
  IIR* get_base_type_direction();
  IIR* get_base_type_right();

  /** This method returns a pointer to the most constrained common
   subtype of "this" type, and the one passed in.  It returns NULL if
   the types are not compatible at all. */
  IIR_TypeDefinition *is_compatible( IIR_TypeDefinition * );
  IIR_TypeDefinition *check_special_compatible( IIR_TypeDefinition * );

  IIR_TypeDefinition *get_bottom_base_type();

  savant::set<IIR_Declaration> *find_declarations( IIR_Name * );
  savant::set<IIR_Declaration> *find_declarations( IIR_TextLiteral * );

  ostream &print( ostream & );

  IIR_TextLiteral *get_declarator();
  virtual void publish_vhdl(ostream &);

  /**
     By default resoltion functions will be null.  This method is
     overridden in applicable places.
  */
  IIR_FunctionDeclaration *get_resolution_function(){ return 0; }

protected:
  
  IIRBase_TypeDefinition();
  virtual ~IIRBase_TypeDefinition() = 0;
    
private:
  IIR_TypeDefinition            *my_base_type;
  IIR_Declaration               *my_declaration;
  IIR_TypeDefinition            *my_type_mark;
};

#endif
