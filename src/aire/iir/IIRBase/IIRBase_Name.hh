
#ifndef IIRBASE_NAME_HH
#define IIRBASE_NAME_HH

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
#include "IIRBase.hh"
#include "IIR_Name.hh"

class IIR_Identifier;
class IIR_LibraryDeclaration;

class IIRBase_Name : public virtual IIRBase, public virtual IIR_Name{
public:
  IIR_Kind get_kind() const {return IIR_NAME;}
  const IIR_Char *get_kind_text() const {return "IIR_Name";}

  static IIR **lookup( IIR_Identifier *identifier,
                       IIR_Int32      &number_of_matches,
                       IIR            *&first_match);

  static IIR **lookup( IIR_Name    *name,
                       IIR_Int32   &number_of_matches,
                       IIR         *&first_match);
  
  void set_prefix( IIR *prefix );
  IIR *get_prefix();

  void set_suffix( IIR *suffix );
  IIR *get_suffix();

  IIR *convert_tree(plugin_class_factory *factory);
  
  IIR_Boolean is_name() { return TRUE; };
  IIR_Boolean is_signal();
  IIR_Boolean is_object(); 
  IIR_Boolean is_variable();

  IIR_SignalKind get_signal_kind();

  void set_subtype( IIR_TypeDefinition * );

  /** This method returns the prefix as an IIR_TextLiteral...  (this
      SHOULD always be possible...) */
  IIR_TextLiteral *get_prefix_string();

  /** Find the first prefix.  It should be a library.  Return it. */
  virtual IIR_LibraryDeclaration *get_library_declaration(){ return 0; }

  IIR_Boolean is_locally_static();

  ostream &print( ostream & os );
protected:
  IIRBase_Name();
  virtual ~IIRBase_Name() = 0;
    
private:
  IIR *prefix;

};
#endif
