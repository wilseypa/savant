
#ifndef IIRBASE_COMMENT_HH
#define IIRBASE_COMMENT_HH

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
#include "IIR_Comment.hh"
#include "IIRBase_TextLiteral.hh"

/* Each VHDL comment line is captured in a separate IIR_Comment node.
   Typically these will be collected into a list and attached to the design
   unit in which they are found.  */
class IIRBase_Comment : public virtual IIRBase_TextLiteral, public virtual IIR_Comment{

public:
  IIR_Kind get_kind() const {return IIR_COMMENT;}
  const IIR_Char *get_kind_text() const {return "IIR_Comment";}

  IIR_Char *get_text();
  IIR_Int32 get_text_length();

  void set_element( IIR_Int32 subscript, IIR_Char value );
  IIR_Char& operator[]( IIR_Int32 subscript );

  void set_text( IIR_Char *txt, IIR_Int32 text_len );

  void release();

  IIR *convert_tree(plugin_class_factory *factory);

  void publish_vhdl(ostream &);
protected:
  IIRBase_Comment();
  virtual ~IIRBase_Comment() = 0;
    
  IIR_Char *text;
  IIR_Int32 text_length;

private:
  void _check_bounds( IIR_Int32 );

};
#endif
