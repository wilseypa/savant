
#ifndef IIRBASE_OBJECT_DECLARATION_HH
#define IIRBASE_OBJECT_DECLARATION_HH

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
#include "IIR_ObjectDeclaration.hh"

class IIR_TypeDefinition;
class IIR_AttributeSpecificationList;

class IIRBase_ObjectDeclaration : public virtual IIRBase_Declaration,
				  public virtual IIR_ObjectDeclaration{

public:
  // List Accessor(s)
  IIR_AttributeSpecificationList        *get_attributes();
  void                                  set_attributes(IIR_AttributeSpecificationList *new_attributes);

  IIR *get_value() { return NULL; }
  void set_value(IIR *);
  /**
     Sets the subtype for this object.  If the subtype's declaration is 0,
     then the subtype will be modified to point to this declaration as it's
     own.
  */
  void set_subtype(IIR_TypeDefinition* subtype);

  IIR *convert_tree(plugin_class_factory *factory);

  IIR_Boolean is_object(){ return TRUE; }
 
  IIR_SignalKind get_signal_kind();

  IIR_TypeDefinition *get_subtype() { return IIRBase::get_subtype(); }

  /** This method is for objects that are instances of records, to find the
      pieces within them... */
  savant::set<IIR_Declaration> *find_declarations( IIR_Name *);

  IIR_Boolean is_locally_static(){ return false; }

  void publish_vhdl_range( ostream & );
  virtual void publish_vhdl_subtype_indication(ostream &);
  virtual void publish_vhdl_subtype_indication_with_expression(ostream &);
  virtual void publish_vhdl_signal_kind(ostream &);
  virtual void publish_vhdl_expression(ostream &);
protected:
  IIRBase_ObjectDeclaration();
  virtual ~IIRBase_ObjectDeclaration() = 0;
    
private:
  // List Variable(s)
  IIR_AttributeSpecificationList *attributes;
};
#endif
