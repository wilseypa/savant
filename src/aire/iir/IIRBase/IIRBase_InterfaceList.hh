
#ifndef IIRBASE_INTERFACE_LIST_HH
#define IIRBASE_INTERFACE_LIST_HH

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
//          Timothy J. McBrayer tmcbraye@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRBase_DeclarationList.hh"
#include "IIR_InterfaceList.hh"

class IIR_InterfaceDeclaration;

class IIRBase_InterfaceList : public virtual IIRBase_DeclarationList, public virtual IIR_InterfaceList{

public:
  IIR_Kind get_kind() const { return IIR_INTERFACE_LIST; }
  const IIR_Char *get_kind_text() const { return "IIR_InterfaceList"; }

  IIR *first();
  IIR *last();
  IIR *successor( IIR_InterfaceDeclaration * );
  IIR *predecessor( IIR_InterfaceDeclaration * );
  IIR *get_nth_element( IIR_Int32 );
  IIR_Int32 get_position( IIR_InterfaceDeclaration * );

  void append( IIR_InterfaceDeclaration * );
  void prepend( IIR_InterfaceDeclaration * );
  void insert_after( IIR_InterfaceDeclaration *, IIR_InterfaceDeclaration * );

  void publish_vhdl(ostream &);
  void publish_vhdl_decl(ostream &);
protected:
  IIRBase_InterfaceList();
  virtual ~IIRBase_InterfaceList() = 0;
    
private:
};
#endif
