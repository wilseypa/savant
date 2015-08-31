
#ifndef IIRBASE_PHYSICAL_TYPE_DEFINITION_HH
#define IIRBASE_PHYSICAL_TYPE_DEFINITION_HH

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
#include "IIRBase_ScalarTypeDefinition.hh"
#include "IIR_PhysicalTypeDefinition.hh"

class IIR_PhysicalUnit;
class IIR_UnitList;

class IIRBase_PhysicalTypeDefinition : public virtual IIRBase_ScalarTypeDefinition,
				       public virtual IIR_PhysicalTypeDefinition{
public:
  // List Accessor(s)
  IIR_UnitList *get_units();
  void         set_units(IIR_UnitList *new_units);

  IIR_Kind get_kind() const { return IIR_PHYSICAL_TYPE_DEFINITION; }
  const IIR_Char *get_kind_text() const { return "IIR_PhysicalTypeDefinition"; }

  void set_primary_unit(IIR_PhysicalUnit*);
  IIR_PhysicalUnit *get_primary_unit();

  IIR *convert_tree(plugin_class_factory *factory);

  void publish_vhdl_type_decl(ostream &);
protected:
  IIRBase_PhysicalTypeDefinition();
  virtual ~IIRBase_PhysicalTypeDefinition() = 0;
    
private:
  // List Variable(s)
  IIR_UnitList *units;

  // This is different from the spec-- bus is as discussed with J. Willis.
  IIR_PhysicalUnit *primary_unit;
};
#endif
