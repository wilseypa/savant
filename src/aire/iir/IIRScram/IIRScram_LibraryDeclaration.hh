#ifndef IIRSCRAM_LIBRARY_DECLARATION_HH
#define IIRSCRAM_LIBRARY_DECLARATION_HH
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
//          Malolan Chetlur     mal@ece.uc.edu
//          Timothy J. McBrayer tmcbraye@ece.uc.edu
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_Declaration.hh"
#include "IIRBase_LibraryDeclaration.hh"

class IIRScram_LibraryUnitList;
class IIRScram_List;
class IIRScram_Name;
class IIRScram_TypeDefinition;

/**
   The extension base for library declarations.
 */
class IIRScram_LibraryDeclaration : public virtual IIRScram_Declaration, public virtual IIRBase_LibraryDeclaration{

public:
  IIRScram_LibraryDeclaration();
  virtual ~IIRScram_LibraryDeclaration();

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);

  IIR_Boolean _is_iir_library_declaration(){ return TRUE; }


  void _add_to_declarative_region( savant::set<IIRScram_Declaration> * );

  // Wrappers for IIRBase functions
  IIRScram_LibraryUnitList *    _get_primary_units();
protected:
private:
};
#endif
