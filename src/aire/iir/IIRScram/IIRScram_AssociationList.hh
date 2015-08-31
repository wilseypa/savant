
#ifndef IIRSCRAM_ASSOCIATION_LIST_HH
#define IIRSCRAM_ASSOCIATION_LIST_HH

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
//          Timothy J. McBrayer tmcrbaye@ece.uc.edu
//          Malolan Chetlur     mal@ece.uc.edu
//          Narayanan Thondugulam nthondug@ece.uc.edu

//---------------------------------------------------------------------------
#include "savant_config.hh"
#include "IIRScram_List.hh"
#include "IIRBase_AssociationList.hh"

class IIRScram_AssociationElement;
class IIRScram_ComponentInstantiationStatement;
class IIRScram_Declaration;
class IIRScram_DeclarationList;
class IIRScram_DesignatorList;
class IIRScram_IndexedName;
class IIRScram_InterfaceDeclaration;
class IIRScram_InterfaceList;
class IIRScram_Name;

class IIRScram_AssociationList : public virtual IIRScram_List, public virtual IIRBase_AssociationList{

public:
  IIRScram_AssociationList() {}

  /// Accept visitations \Ref{_accept_visitor}.
  visitor_return_type* _accept_visitor(node_visitor *, visitor_argument_type *);

  void append( IIRScram_AssociationElement * );
  void prepend( IIRScram_AssociationElement * );

  IIR *get_nth_element( int );
  void _replace( IIRScram_AssociationElement *to_replace, IIRScram_AssociationElement *replace_with );

  void _resolve_and_order( IIRScram_InterfaceList *formal_list,
			   IIRScram_InterfaceList *local_list,
			   IIRScram               *line_info );
  
  IIR_Boolean _check_valid_arguments( IIRScram_InterfaceList    *formal_list,
				      IIRScram_InterfaceList    *local_list);

  /** This method takes an interface list, and fills in all of the default
      values for associations that weren't specified.  It will generate
      error messages when errors occur. */
  void _fill_in_defaults( IIRScram *line_info, IIRScram_InterfaceList *formal_list );

  /**
     Used by
     IIRScram_ComponentInstantiationStatement#_build_default_entity_aspect
     to build the default maps, as per the rules on pg 80 of the '93 LRM.
  */
  void _build_default_map( IIRScram_ComponentInstantiationStatement *err_info,
			   IIRScram_InterfaceList *formal_list,
			   IIRScram_InterfaceList *actual_list );
  
  IIRScram *_clone();
  
  virtual ~IIRScram_AssociationList();
    
private:
  /** This method is responsible for checking to see if this list matches the
      interface list passed in, OR, for resolving a mathing list.  If this
      method is called with an incorrect interface list and the boolean argument
      is TRUE, it should abort. */
  IIR_Boolean _check_or_resolve( IIRScram_InterfaceList         *formal_list,
				 IIRScram_InterfaceList         *local_list,
				 IIR_Boolean                    resolve = TRUE );  
  
  /** This method checks the positional part of an argument list.  It only
      blows up on errors if the second parameter is TRUE.  It returns -1 if
      an argument didn't match. */
  IIR_Int32 _process_positional_part( IIRScram_InterfaceList *, IIR_Boolean resolve = TRUE );

  IIRScram_InterfaceDeclaration *_find_declaration_in_formal( IIRScram_AssociationElement * );
  IIRScram_Declaration *_find_declaration( IIRScram_Name *to_find, IIRScram_DeclarationList *list );
  IIRScram *_find_formal_designator( IIRScram *formal_part );
  IIRScram_Declaration *_find_formal_declaration( IIRScram *formal_designator,
                                                  IIRScram_InterfaceList *formal_list  );
  IIRScram *_find_actual_designator( IIRScram *actual_part );

  bool _find_formal_types( IIRScram_AssociationElement *current_association,		  
			   IIRScram *actual_part, 
			   IIRScram *actual_designator,
			   IIRScram *formal_part,
			   IIRScram *formal_designator,
			   IIRScram_Declaration *formal_declaration,
			   savant::set<IIRScram_TypeDefinition> *add_types_to_me );

  IIRScram_Name *_get_formal_designator_from_indexed_name( IIRScram_IndexedName * );
  IIRScram *_get_actual_designator_from_indexed_name( IIRScram_IndexedName * );
};
#endif
