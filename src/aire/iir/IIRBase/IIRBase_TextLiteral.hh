
#ifndef IIRBASE_TEXTLITERAL_HH
#define IIRBASE_TEXTLITERAL_HH

// Copyright (c) The University of Cincinnati.  
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

#include "savant_config.hh"
#include "IIRBase_Literal.hh"
#include "IIR_TextLiteral.hh"
#include "IIRBase_String.hh"
#include "hash_table.hh"

class IIR_Name;

class IIRBase_TextLiteral : public virtual IIRBase_Literal,
			    public virtual IIR_TextLiteral{

public:
  IIR_Char *get_text();
  IIR_Int32 get_text_length();

  IIR_Char &operator[]( IIR_Int32 subscript );

  /** Compares text literals. */
  static int cmp(IIR_TextLiteral *, IIR_TextLiteral *);
  static int cmp(IIR_TextLiteral *, const char *);
  static int cmp(IIR_TextLiteral *, IIR_Name *);

  /** This method converts an IIR_Identifier into a C++ string. */
  const string convert_to_string();
  const string convert_to_library_name();

  IIR *convert_tree(plugin_class_factory *factory);
 
  IIR_Boolean is_text_literal() { return TRUE; }

  IIR_TextLiteral *get_prefix_string(){ return this; }

  ostream &print( ostream & );

  void publish_vhdl(ostream &);
protected:
  IIRBase_TextLiteral();
  virtual ~IIRBase_TextLiteral() = 0;

  IIRBase_String *text;
    
  void check_bounds( IIR_Int32 subscript );

  // This method is intended for use on NEW objects only...  (Otherwise,
  // it will leak - and an assertion will fail)
  void set_text( const IIR_Char *const, const IIR_Int32 );
private:  
  static hash_table<IIRBase_String> &get_string_table();
};

#endif
