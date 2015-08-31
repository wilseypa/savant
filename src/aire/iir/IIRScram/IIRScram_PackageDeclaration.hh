#ifndef IIRSCRAM_PACKAGE_DECLARATION_HH
#define IIRSCRAM_PACKAGE_DECLARATION_HH

// Copyright (c) 1996-2000 The University of Cincinnati.  
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
//          Krishnan Subramani  skrish@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu
//          Radharamanan Radhakrishnan  ramanan@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_LibraryUnit.hh"
#include "IIRBase_PackageDeclaration.hh"

class IIRScram_Declaration;
class IIRScram_Name;

/**
   Extension base for package declarations.
*/
class IIRScram_PackageDeclaration : public virtual IIRScram_LibraryUnit, public virtual IIRBase_PackageDeclaration{
public:
  IIRScram_PackageDeclaration();
  ~IIRScram_PackageDeclaration();
  
  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);


  /**
     Presumably, we don't need to add package declarations into the code
     generator table.  However, in some cases (like attribute names
     package.something) this method will be called, so we're stubbing it out
     as an empty call.
  */
  IIRScram_Declaration *_get_package_declaration();

  void _add_to_declarative_region( savant::set<IIRScram_Declaration> * );
  void _make_interface_visible(symbol_table *);

  void _type_check();

  // Wrappers for IIRBase functions
  IIRScram_DeclarationList         *_get_package_declarative_part();

protected:
private:
};
#endif
