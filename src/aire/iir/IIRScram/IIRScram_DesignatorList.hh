
#ifndef IIRSCRAM_DESIGNATORLIST_HH
#define IIRSCRAM_DESIGNATORLIST_HH

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

// You may modify, distribute, and use the software contained in this package
// under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE" version 2,
// June 1991. A copy of this license agreement can be found in the file
// "LGPL", distributed with this archive.

// Authors: Philip A. Wilsey	phil.wilsey@uc.edu
//          Dale E. Martin	dmartin@cliftonlabs.com
//          Timothy J. McBrayer tmcbraye@ece.uc.edu
//          Malolan Chetlur     mal@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu
//          Krishnan Subramani  skrish@ece.uc.edu

//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "IIRScram_List.hh"
#include "IIRBase_DesignatorList.hh"

class IIRScram_DesignatorList;
class IIRScram_Label;
class IIRScram_StatementList;
class IIRScram_TextLiteral;

class IIRScram_DesignatorList : public virtual IIRScram_List, public virtual IIRBase_DesignatorList{
public:
  IIRScram_DesignatorList() {}
  virtual ~IIRScram_DesignatorList();
    
  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);
  

  void _type_check_as_instantiation_list( IIRScram *instantiated_unit, 
					  IIRScram_List *,
					  IIRScram *configuration );

  // This method walks the designator list, looking for a label for an
  // instantiate statement that instantiates "instantiated_unit".  When
  // finding one, it returns the label.
  IIRScram_Label *_process_instantiate_statement( IIRScram_Declaration *instantiated_unit,
                                                  IIRScram *statement );

protected:
private:
  void _process_by_all_or_others( IIRScram_Declaration *instantiated_unit,
				  IIRScram_List *,
				  IIR_Boolean by_all,
				  IIRScram *configuration );

  void _process_explicit_list( IIRScram_Declaration *instantiated_unit, 
			       IIRScram_List *,
			       IIRScram *configuration );    
};
#endif
