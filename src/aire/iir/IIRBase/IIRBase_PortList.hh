
#ifndef IIRBASE_PORT_LIST_HH
#define IIRBASE_PORT_LIST_HH

// Copyright (c) 1996-2003 The University of Cincinnati.  
// All rights reserved.

// UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
// OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
// LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING OR
// DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.

// By using or copying this Software, Licensee agrees to abide by the
// intellectual property laws, and all other applicable laws of the U.S.,
// and the terms of this license.

// You may modify, distribute, and use the software contained in this
// package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
// version 2, June 1991. A copy of this license agreement can be found in
// the file "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Timothy J. McBrayer 

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRBase_InterfaceList.hh"
#include "IIR_PortList.hh"

class IIR_SignalInterfaceDeclaration;
class IIR_TerminalInterfaceDeclaration;

class IIRBase_PortList : public virtual IIRBase_InterfaceList, public virtual IIR_PortList{

public:
  IIR_Kind get_kind() const { return IIR_PORT_LIST; }
  const IIR_Char *get_kind_text() const { return "IIR_PortList"; }

  void prepend( IIR_InterfaceDeclaration * );
  void append( IIR_InterfaceDeclaration * );

  void insert_after( IIR_InterfaceDeclaration *,
                     IIR_InterfaceDeclaration * );

  IIR_Boolean insert_before_element( IIR_InterfaceDeclaration *,
				     IIR_InterfaceDeclaration * );

  IIR *successor( IIR_InterfaceDeclaration * );
  IIR *predecessor( IIR_InterfaceDeclaration * );
  IIR *first( );
  IIR *last();
  IIR_Int32 get_position( IIR_InterfaceDeclaration * );

  void publish_vhdl(ostream &);
protected:
  IIRBase_PortList();
  virtual ~IIRBase_PortList() = 0;
    
private:

};
#endif
