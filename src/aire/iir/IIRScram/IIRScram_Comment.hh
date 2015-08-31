#ifndef IIRSCRAM_COMMENT_HH
#define IIRSCRAM_COMMENT_HH

// Copyright (c) 1996-2003 The University of Cincinnati.  
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

// Authors: Philip A. Wilsey	philip.wilsey@ieee.org
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Malolan Chetlur     
//          Umesh Kumar V. Rajasekaran
//          Narayanan Thondugulam

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_TextLiteral.hh"
#include "IIRBase_Comment.hh"

class IIRScram_CommentList;

/* Each VHDL comment line is captured in a separate IIR_Comment node.
   Typically these will be collected into a list and attached to the design
   unit in which they are found.  */
class IIRScram_Comment : public virtual IIRScram_TextLiteral,
			 public virtual IIRBase_Comment{
public:
  IIRScram_Comment() {}
  virtual ~IIRScram_Comment() {}

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);


  static IIRScram_Comment *get( IIR_Char *text, IIR_Int32 text_length );
protected:
    
private:
};
#endif
