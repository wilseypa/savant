
#ifndef IIRBASE_PHYSICAL_UNIT_HH
#define IIRBASE_PHYSICAL_UNIT_HH

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
//          Timothy J. McBrayer tmcbraye@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRBase_Declaration.hh"
#include "IIR_PhysicalUnit.hh"

class IIR_PhysicalUnit;
class IIR_AttributeSpecificationList;

class IIRBase_PhysicalUnit : public virtual IIRBase_Declaration,
			     public virtual IIR_PhysicalUnit{
public:
  // List Accessor(s)
  IIR_AttributeSpecificationList *get_attributes();
  void                           set_attributes(IIR_AttributeSpecificationList *new_attributes);

  IIR_Kind get_kind() const { return IIR_PHYSICAL_UNIT; }
  const IIR_Char *get_kind_text() const { return "IIR_PhysicalUnit"; }

  void set_multiplier(IIR*);
  IIR* get_multiplier();
  void set_unit_name(IIR_PhysicalUnit*);
  IIR_PhysicalUnit* get_unit_name();

  IIR *convert_tree(plugin_class_factory *factory);

  declaration_type get_declaration_type();

  IIR_Boolean is_physical_unit(){ return TRUE; }  

  IIR_Boolean is_locally_static();

  void publish_vhdl_decl(ostream &);
  void publish_vhdl(ostream &);
protected:
  IIRBase_PhysicalUnit();
  virtual ~IIRBase_PhysicalUnit() = 0;
    
private:
  // List Variable(s)
  IIR_AttributeSpecificationList *attributes;

  IIR* multiplier;
  IIR_PhysicalUnit *unit_name;
};

#endif
