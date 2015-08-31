
#ifndef IIR_PACKAGE_DECLARATION_HH
#define IIR_PACKAGE_DECLARATION_HH

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
#include "IIR_LibraryUnit.hh"

class IIR_PackageBodyDeclaration;
class IIR_DeclarationList;

class IIR_PackageDeclaration : public virtual IIR_LibraryUnit{

public:
  virtual ~IIR_PackageDeclaration() {}
    
  // List accessor(s)
  virtual IIR_DeclarationList           *get_package_declarative_part() = 0;
  virtual void                          set_package_declarative_part(IIR_DeclarationList *) = 0;

  virtual IIR_PackageBodyDeclaration *get_package_body() = 0;
  virtual void set_package_body( IIR_PackageBodyDeclaration * ) = 0;
};
#endif
