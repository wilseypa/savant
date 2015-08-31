#ifndef IIRSCRAM_FUNCTION_DECLARATION_HH
#define IIRSCRAM_FUNCTION_DECLARATION_HH
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
//          Umesh Kumar V. Rajasekaran urajasek@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_SubprogramDeclaration.hh"
#include "IIRBase_FunctionDeclaration.hh"

class IIRScram_Name;
class IIRScram_TypeDefinition;

class IIRScram_FunctionDeclaration : public virtual IIRScram_SubprogramDeclaration, public virtual IIRBase_FunctionDeclaration{
public:
  IIRScram_FunctionDeclaration() {}
  virtual ~IIRScram_FunctionDeclaration();

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);


  /** We can have array valued functions. */
  IIRScram_TypeDefinition *_get_type_of_element( int );
  IIR_Int32 get_num_indexes();
  
  IIR_Boolean _is_readable(){ return TRUE; }
  IIR_Boolean _is_writable(){ return FALSE; }
  IIRScram *_clone();

  /** This method looks at the function declaration and determines if it
      could be a conversion function based on the rules in 4.3.2.1 of
      the '93 LRM. */
  IIR_Boolean _could_be_conversion_function( );

  /** This function has been used as a conversion function.  Now go type
     check it to be sure that it meets all of the criteria of such a
     function.  Generates errors if there are any, silent otherwise.
  */
  virtual void _type_check_resolution_function( IIRScram_TypeDefinition *subtype_indication );

  IIRScram_DeclarationList *    _get_subprogram_declarations();
  IIRScram_TypeDefinition*      _get_return_type();

protected:    
private:
};
#endif

