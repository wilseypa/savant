
#ifndef IIRBASE_SCALAR_TYPE_DEFINITION_HH
#define IIRBASE_SCALAR_TYPE_DEFINITION_HH

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
#include "IIRBase_TypeDefinition.hh"
#include "IIR_ScalarTypeDefinition.hh"

class IIRBase_ScalarTypeDefinition : public virtual IIRBase_TypeDefinition, public virtual IIR_ScalarTypeDefinition{

public:
  void                  set_left( IIR* left);
  IIR*                  get_left();
  void                  set_direction( IIR* direction);
  IIR*                  get_direction();
  void                  set_right(IIR* right);
  IIR*                  get_right();

  IIR*                  get_base_type_left();
  IIR*                  get_base_type_direction();
  IIR*                  get_base_type_right();
  IIR_TypeDefinition*   get_resolved_base_type();

  IIR *convert_tree(plugin_class_factory *factory);

  IIR_Boolean is_ascending_range();
  IIR_Boolean is_scalar_type(){ return TRUE; }
  IIR_Boolean is_resolved();
  IIR_Boolean is_locally_static();

  IIR_Boolean is_scalar_type_definition(){ return TRUE; }

  ostream &print( ostream & );
  virtual void publish_vhdl(ostream &);
  virtual void publish_vhdl_decl(ostream &);
  virtual void publish_vhdl_constraint(ostream &);
  virtual void publish_vhdl_range(ostream &);
  virtual void publish_vhdl_index(ostream &);
protected:
  
  IIRBase_ScalarTypeDefinition();
  virtual ~IIRBase_ScalarTypeDefinition() = 0;
    
private:
  
  IIR* left;
  IIR* direction;
  IIR* right;

};

#endif
