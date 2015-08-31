
#ifndef IIRBASE_GENERIC_LIST_HH
#define IIRBASE_GENERIC_LIST_HH

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
#include "IIRBase_InterfaceList.hh"
#include "IIR_GenericList.hh"

class IIR_ConstantInterfaceDeclaration;

class IIRBase_GenericList : public virtual IIRBase_InterfaceList, public virtual IIR_GenericList{

public:
  IIR_Kind get_kind() const {return IIR_GENERIC_LIST;}
  const IIR_Char *get_kind_text() const {return "IIR_GenericList";}

  void prepend( IIR_ConstantInterfaceDeclaration* element);

  void append( IIR_ConstantInterfaceDeclaration* element);

  IIR_Boolean insert_after( IIR_ConstantInterfaceDeclaration *existing_element,
				    IIR_ConstantInterfaceDeclaration* new_element);

  IIR_Boolean insert_before_element( IIR_ConstantInterfaceDeclaration *existing_element, 
				     IIR_ConstantInterfaceDeclaration* new_element);

  IIR *successor( IIR_ConstantInterfaceDeclaration* existing_element);
  IIR *predecessor( IIR_ConstantInterfaceDeclaration* element );
  IIR *first( );
  IIR *get_nth_element( IIR_Int32 );
  IIR *last();

  IIR_Int32 get_position( IIR_ConstantInterfaceDeclaration* element );

  void publish_vhdl(ostream &);
protected:
  IIRBase_GenericList();
  virtual ~IIRBase_GenericList() = 0;
    
private:
};
#endif
