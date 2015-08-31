
#ifndef IIRBASE_SIGNAL_INTERFACE_DECLARATION_HH
#define IIRBASE_SIGNAL_INTERFACE_DECLARATION_HH

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
#include "IIRBase_InterfaceDeclaration.hh"
#include "IIR_SignalInterfaceDeclaration.hh"

class IIRBase_SignalInterfaceDeclaration : public virtual IIRBase_InterfaceDeclaration, public virtual IIR_SignalInterfaceDeclaration{
public:
  IIR_Kind get_kind() const {return IIR_SIGNAL_INTERFACE_DECLARATION;}
  const IIR_Char *get_kind_text() const {return "IIR_SignalInterfaceDeclaration";}

  void set_signal_kind( IIR_SignalKind signal_kind);
  IIR_SignalKind get_signal_kind();

  IIR *convert_tree(plugin_class_factory *factory);

  IIR_Boolean is_signal(){ return TRUE; }

  declaration_type get_declaration_type();
  void publish_vhdl_decl(ostream &);
protected:
  
  IIRBase_SignalInterfaceDeclaration();
  virtual ~IIRBase_SignalInterfaceDeclaration() = 0;
    
private:
  
  IIR_SignalKind signal_kind;

};

#endif
