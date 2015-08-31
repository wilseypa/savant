
#ifndef IIRBASE_FILE_DECLARATION_HH
#define IIRBASE_FILE_DECLARATION_HH

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
#include "IIR_FileDeclaration.hh"

class IIRBase_FileDeclaration : public virtual IIRBase_ObjectDeclaration, public virtual IIR_FileDeclaration{

public:
  IIR_Kind get_kind() const {return IIR_FILE_DECLARATION;}
  const IIR_Char *get_kind_text() const {return "IIR_FileDeclaration";}

  void set_file_open_expression(IIR* file_open_expression);
  IIR* get_file_open_expression();
  void set_file_logical_name(IIR* file_logical_name);
  IIR* get_file_logical_name();

  IIR *convert_tree(plugin_class_factory *factory);
  
  declaration_type get_declaration_type();

  IIR_Boolean is_file(){ return TRUE; }
  void publish_vhdl_decl(ostream &);
protected:
  IIRBase_FileDeclaration();
  virtual ~IIRBase_FileDeclaration() = 0;
    
private:
  IIR* file_open_expression;
  IIR* file_logical_name;
};
#endif
