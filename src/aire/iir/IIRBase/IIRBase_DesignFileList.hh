
#ifndef IIRBASE_DESIGN_FILE_LIST_HH
#define IIRBASE_DESIGN_FILE_LIST_HH

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

#include "savant_config.hh"
#include "IIRBase_List.hh"
#include "IIR_DesignFileList.hh"

class IIR_DesignFile;

class IIRBase_DesignFileList : public virtual IIRBase_List, public virtual IIR_DesignFileList{

public:
  IIR_Kind get_kind() const {return IIR_DESIGN_FILE_LIST;}
  const IIR_Char *get_kind_text() const {return "IIR_DesignFileList";}

  void prepend( IIR_DesignFile *);
  void append( IIR_DesignFile * );
  IIR *successor( IIR_DesignFile * );
  IIR *predecessor( IIR_DesignFile * );
  IIR *first( );

protected:
  IIRBase_DesignFileList();
  virtual ~IIRBase_DesignFileList() = 0;
    
private:
};
#endif
