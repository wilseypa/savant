
#ifndef IIRBASE_ENTITY_CLASS_ENTRY_HH
#define IIRBASE_ENTITY_CLASS_ENTRY_HH

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
#include "IIRBase_Tuple.hh"
#include "IIR_EntityClassEntry.hh"


class IIRBase_EntityClassEntry : public virtual IIRBase_Tuple, public virtual IIR_EntityClassEntry{

public:
  IIR_Kind get_kind() const {return IIR_ENTITY_CLASS_ENTRY;}
  const IIR_Char *get_kind_text() const {return "IIR_EntityClassEntry";}

  void  set_entity_kind( IIR_Kind entity_kind );
  IIR_Kind get_entity_kind();

  void  set_boxed( IIR_Boolean is_boxed );
  IIR_Boolean get_boxed();

  IIR *convert_tree(plugin_class_factory *factory);

  void publish_vhdl(ostream &);
protected:
  IIRBase_EntityClassEntry();
  virtual ~IIRBase_EntityClassEntry() = 0;
    
private:
  IIR_Kind my_entity_kind;
  IIR_Boolean my_is_boxed;
};
#endif
