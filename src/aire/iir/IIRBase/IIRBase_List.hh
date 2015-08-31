
#ifndef IIRBASE_LIST_HH
#define IIRBASE_LIST_HH

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
#include "IIR_List.hh"
#include "IIRBase.hh"

class IIRBase_List : public virtual IIRBase, public virtual IIR_List {
public:
  /** This function performs the conversion of one tree into another.  At this 
      level it walks through the list, calling clone_tree on the contents */
  virtual IIR *convert_tree(plugin_class_factory *factory);

  IIR_Boolean is_resolved();
    
  ostream &print( ostream &os );

  void publish_vhdl_decl( ostream &os ){
    publish_vhdl_decl( os, NULL );
  }

  void publish_vhdl_decl(ostream &, const char *separator );

  void publish_vhdl(ostream &, const char *separator );

  void publish_vhdl( ostream & );

protected:
  IIRBase_List();
  virtual ~IIRBase_List() = 0;

//   IIRBase_List &operator=( IIRBase_List &toCopy ){
//     dl_list<IIR>::operator=( toCopy );
//     return *this;
//   }

private:
};
#endif
