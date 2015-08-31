
#ifndef IIRBASE_INTERFACE_DECLARATION_HH
#define IIRBASE_INTERFACE_DECLARATION_HH

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
#include "IIRBase_ObjectDeclaration.hh"
#include "IIR_InterfaceDeclaration.hh"

class IIRBase_InterfaceDeclaration : public virtual IIRBase_ObjectDeclaration,
				     public virtual IIR_InterfaceDeclaration{
public:
  void set_mode(IIR_Mode mode);
  IIR_Mode get_mode();

  void set_value(IIR* value);
  IIR* get_value();

  IIR *convert_tree(plugin_class_factory *factory);
  IIR_Boolean is_interface() { return TRUE; };
  IIR_Boolean is_object() { return TRUE;}

  ostream &print( ostream & );
  void publish_vhdl_mode(ostream &);
protected:
  
  IIRBase_InterfaceDeclaration();
  virtual ~IIRBase_InterfaceDeclaration() = 0;
    
private:

  IIR* value;
  IIR_Mode mode;

};
#endif
