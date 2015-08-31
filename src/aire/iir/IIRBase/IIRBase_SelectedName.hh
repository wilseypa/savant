
#ifndef IIRBASE_SELECTED_NAME_HH
#define IIRBASE_SELECTED_NAME_HH

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

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRBase_Name.hh"
#include "IIR_SelectedName.hh"

class IIRBase_SelectedName : public virtual IIRBase_Name, public virtual IIR_SelectedName{
public:

  IIR_Kind get_kind() const {return IIR_SELECTED_NAME;}

  const IIR_Char *get_kind_text() const {return "IIR_SelectedName";}

  void set_suffix( IIR *suffix );
  IIR *get_suffix();

  IIR *convert_tree(plugin_class_factory *factory);

  IIR_Boolean is_resolved();
  IIR_Boolean is_signal();
  IIR_Boolean is_entity_declaration();
  IIR_Boolean is_object();
  IIR_Boolean is_type();
  IIR_Boolean is_variable();
  
  IIR_SignalKind get_signal_kind();
  IIR_TypeDefinition *get_subtype();

  ostream &print( ostream & );
  
  IIR_Declaration *get_prefix_declaration();
  void publish_vhdl(ostream &);
protected:
  
  IIRBase_SelectedName();
  virtual ~IIRBase_SelectedName() = 0;
    
private:
  IIR *suffix;
};

#endif
