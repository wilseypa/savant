#ifndef IIRSCRAM_ACCESS_SUBTYPE_DEFINITION_HH
#define IIRSCRAM_ACCESS_SUBTYPE_DEFINITION_HH

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
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Malolan Chetlur     mal@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_AccessTypeDefinition.hh"
#include "IIRBase_AccessSubtypeDefinition.hh"

class IIRScram_AccessSubtypeDefinition;
class visitor_argument_type;
class node_visitor;
class IIRScram_TypeDefinition;

class IIRScram_AccessSubtypeDefinition : public virtual IIRScram_AccessTypeDefinition,
					 public virtual IIRBase_AccessSubtypeDefinition{
public:
  IIRScram_AccessSubtypeDefinition() {}
  virtual ~IIRScram_AccessSubtypeDefinition();

  static IIRScram_AccessSubtypeDefinition *get( IIRScram_TypeDefinition *designated_type);

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);


  virtual IIRScram *_clone();
  virtual void _clone( IIRScram * );

  IIRScram_TypeDefinition *_get_designated_subtype();

protected:     
private:
};
#endif
