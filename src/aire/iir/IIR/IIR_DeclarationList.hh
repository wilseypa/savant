
#ifndef IIR_DECLARATION_LIST_HH
#define IIR_DECLARATION_LIST_HH

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
#include "IIR_List.hh"
#include "set.hh"

class IIR_Name;
class IIR_Declaration;
class IIR_TextLiteral;

class IIR_DeclarationList : public virtual IIR_List{

public:
  virtual ~IIR_DeclarationList() {}
  
  virtual void append( IIR_Declaration * ) = 0;
  virtual void prepend( IIR_Declaration * ) = 0;

  virtual IIR *successor( IIR_Declaration * ) = 0;
  virtual IIR *predecessor( IIR_Declaration * ) = 0;

  virtual IIR *first() = 0;
  virtual IIR *last() = 0;

  virtual IIR *get_nth_element( IIR_Int32 ) = 0;

  virtual savant::set<IIR_Declaration> *find_declarations( IIR_Name *  ) { return NULL; }
  virtual savant::set<IIR_Declaration> *find_declarations( IIR_TextLiteral * ) { return NULL; }

  /**
     Makes the declarative region of all of the elements in this list point
     to the new region passed in.
  */
  virtual void set_declarative_region( IIR * ) = 0;
};
#endif
