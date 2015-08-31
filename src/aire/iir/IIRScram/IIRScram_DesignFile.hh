
#ifndef IIRSCRAM_DESIGN_FILE_HH
#define IIRSCRAM_DESIGN_FILE_HH

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
//          Timothy J. McBrayer 
//          Malolan Chetlur     
//          Umesh Kumar V. Rajasekaran
//          Narayanan Thondugulam
//          Radharamanan Radhakrishnan

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "savant.hh"
#include "IIRScram.hh"
#include "IIRBase_DesignFile.hh"
#include "dl_list.hh"
#include "scram.hh"

class IIRScram_ArchitectureDeclaration;
class IIRScram_CommentList;
class IIRScram_DesignFileList;
class IIRScram_LibraryDeclaration;
class IIRScram_LibraryUnitList;
class plugin_class_factory;
class StandardPackage;
class library_manager;

/** The extension base of the node Design File node. */
class IIRScram_DesignFile : public virtual IIRScram, public virtual IIRBase_DesignFile{
public:
  IIRScram_DesignFile();
  virtual ~IIRScram_DesignFile();

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);


  /** Returns a handle to the work library that we were created with. */ 
  IIRScram_LibraryDeclaration *_get_work_library();

  /** Sets the file name to the string passed in. */
  void _set_file_name( const string &new_file_name );
  
  symbol_table                  *_get_symbol_table();

  // Wrappers for IIRBase functions
  IIRScram *                    _get_name();
  IIRScram_LibraryUnitList *    _get_library_units();
  IIRScram_CommentList *        _get_comments();

protected:   
private:
};
#endif
