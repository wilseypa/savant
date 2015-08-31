
#ifndef IIRBASE_SIGNATURE_HH
#define IIRBASE_SIGNATURE_HH

// Copyright (c) 1996-2003 The University of Cincinnati.  
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

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Malolan Chetlur     

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRBase_TypeDefinition.hh"
#include "IIR_Signature.hh"

class IIR_DesignatorList;

class IIRBase_Signature : public virtual IIRBase_TypeDefinition, public virtual IIR_Signature{

public:
  // List Accessor(s)
  IIR_DesignatorList    *get_argument_type_list();
  void                  set_argument_type_list(IIR_DesignatorList *new_argument_type_list);

  IIR_Kind get_kind() const {return IIR_SIGNATURE;}
  const IIR_Char *get_kind_text() const {return "IIR_Signature";}

  void set_return_type( IIR_TypeDefinition* return_type);
  IIR_TypeDefinition* get_return_type();

  IIR *convert_tree(plugin_class_factory *factory);

  void publish_vhdl(ostream &);
protected:
  IIRBase_Signature();
  virtual ~IIRBase_Signature() = 0;
    
private:
  // List Variable(s)
  IIR_DesignatorList *argument_type_list;
  IIR_TypeDefinition* return_type;
};

#endif
