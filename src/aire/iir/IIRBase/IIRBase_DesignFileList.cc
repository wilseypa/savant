
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
//          Narayanan Thondugulam

//---------------------------------------------------------------------------

#include "savant.hh"
#include "IIR_DesignFile.hh"
#include "IIRBase_DesignFileList.hh"

IIRBase_DesignFileList::IIRBase_DesignFileList(){}

IIRBase_DesignFileList::~IIRBase_DesignFileList(){}

IIR *
IIRBase_DesignFileList::successor( IIR_DesignFile *to_succeed ){
  if( to_succeed != NULL ){
    ASSERT( to_succeed->get_kind() == IIR_DESIGN_FILE );
  }
  IIR *retval = IIR_List::successor( (IIR *)to_succeed );
  if( retval != NULL ){
    ASSERT( retval->get_kind() == IIR_DESIGN_FILE ); 
  }
  return retval;
}

IIR *
IIRBase_DesignFileList::predecessor( IIR_DesignFile *to_precede ){
  if( to_precede != NULL ){
    ASSERT( to_precede->get_kind() == IIR_DESIGN_FILE );
  }
  IIR *retval = IIR_List::predecessor( (IIR *)to_precede );
  if( retval != NULL ){
    ASSERT( retval->get_kind() == IIR_DESIGN_FILE );
  }
  return retval;
}

IIR *
IIRBase_DesignFileList::first( ){
  IIR *retval = IIR_List::first( );
  if( retval != NULL ){
    ASSERT( retval->get_kind() == IIR_DESIGN_FILE );
  }
  return retval;
}

void 
IIRBase_DesignFileList::append( IIR_DesignFile *to_append ){
  ASSERT( to_append->get_kind() == IIR_DESIGN_FILE );
  IIR_List::append( (IIR *)to_append );
}

void
IIRBase_DesignFileList::prepend( IIR_DesignFile *to_prepend ){
  ASSERT( to_prepend->get_kind() == IIR_DESIGN_FILE );
  IIR_List::prepend( (IIR *)to_prepend );
}

