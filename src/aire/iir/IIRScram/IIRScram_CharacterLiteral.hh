#ifndef IIRSCRAM_CHARACTER_LITERAL_HH
#define IIRSCRAM_CHARACTER_LITERAL_HH
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
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_TextLiteral.hh"
#include "IIRBase_CharacterLiteral.hh"

class IIRScram_CharacterLiteral : public virtual IIRScram_TextLiteral, public virtual IIRBase_CharacterLiteral{

public:
  IIRScram_CharacterLiteral() {}
  IIRScram_CharacterLiteral(const IIR_Char *const str, const IIR_Int32 len) {set_text( str, len ); }
  virtual ~IIRScram_CharacterLiteral();

  static IIRScram_CharacterLiteral *get( IIR_Char *new_text, IIR_Int32 new_length );
  static IIRScram_CharacterLiteral *get( const string new_text );
    
  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);

  // This method takes a C-language character and returns a VHDL character literal
  // with the ' characters on either side.
  static IIRScram_CharacterLiteral *_get_from_character( char );

protected:
private:
};
#endif
