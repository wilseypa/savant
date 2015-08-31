
#ifndef RESOLUTION_FUNC_HH
#define RESOLUTION_FUNC_HH

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

namespace savant {
  template <class type> class set;
}

class IIRScram_TypeDefinition;
class IIRScram_Name;
class IIRScram_IndexedName;
class IIRScram_DeclarationList;
class IIRScram_Signature;
class IIRScram_Declaration;
class IIRScram_TypeDeclaration;
class IIRScram_ProcedureDeclaration;
class IIRScram_ScalarTypeDefinition;
class IIRScram_AssociationList;
class IIRScram_InterfaceList;
class IIRScram_SubprogramDeclaration;
class IIRScram_EnumerationLiteral;
class IIRScram_Aggregate;
class IIRScram_Label;
class IIRScram_TextLiteral;
class IIRScram_Identifier;
class IIRScram;
class symbol_table;

class IIR;
class IIR_Aggregate;
class IIR_AssociationList;
class IIR_Declaration;
class IIR_DeclarationList;
class IIR_EnumerationLiteral;
class IIR_Identifier;
class IIR_IndexedName;
class IIR_InterfaceList;
class IIR_Label;
class IIR_Name;
class IIR_ProcedureDeclaration;
class IIR_ScalarTypeDefinition;
class IIR_Signature;
class IIR_SubprogramDeclaration;
class IIR_TextLiteral;
class IIR_TypeDeclaration;
class IIR_TypeDefinition;

#include "savant_config.hh"
#include "savant.hh"
#include "IRBasicDataTypes.hh"

template <class type> class dl_list;
class constraint_functor;

/** This method checks to see if a set has only one member.  If it does,
    then it returns the single declaration.  If it has zero members, it
    complains that symbol name_for_error is undeclared (if it is provided.)
    If there is more than one declaration in this set, it returns a NULL
    pointer. (and doesn't complain, as more context is probably need to
    figure it out which one it needs.) */
IIRScram_Declaration *
resolve_if_one( savant::set<IIRScram_Declaration> *set_to_resolve,
		IIRScram_Name *name_for_error = NULL );

/** This function takes a set of subprogram declarations, (optionally) a
    set of possible return types for those declarations, and a list of
    arguments.  It modifies the set of subprogram declarations in that it
    REMOVES any declarations that are not valid based on return type and
    arguments. */
void 
resolve_subprogram_decls(savant::set<IIRScram_Declaration>              *possible_subprogram_decls,
			 IIRScram_AssociationList                       *arguments,
			 const savant::set<IIRScram_TypeDefinition>     *possible_return_types = NULL);

/** This method is as described above.  However, it takes it's list of
    arguments with the rvals "pre-computed"... */
void 
resolve_subprogram_decls( savant::set<IIRScram_Declaration>             *possible_subprogram_decls,
			  dl_list<IIRScram_TypeDefinition>              *parameter_rval_list,
			  savant::set<IIRScram_TypeDefinition>          *possible_return_types );

void 
resolve_subprogram_decls( savant::set<IIRScram_Declaration>     *possible_subprogram_decls,
			  IIRScram_Signature                    *signature);


/** This method takes a set of declarations, and produce the set of r_vals
    for it...  The memory returned needs to be deleted! */
savant::set<IIRScram_TypeDefinition> *
decl_set_to_typedef_set( savant::set<IIRScram_Declaration> *decl_set,
			 constraint_functor *functor = 0 );

/** This method takes a set of declarations, and a set of type definitions,
    and attempts to figure out which definitions in the lval set are
    compatible across an assignment with the type definitions on the right
    hand side.  Both sets are modified - they are reduced to only the
    compatible assignments. */
void 
reconcile_sets( savant::set<IIRScram_Declaration>       *decls, 
		savant::set<IIRScram_TypeDefinition>    *rval_set);

void 
reconcile_sets( savant::set<IIRScram_TypeDefinition>    *lval_set, 
		savant::set<IIRScram_TypeDefinition>    *rval_set);

/** This function takes the set given, and reduces it to the "deepest"
    scoped item that's in it. */
void 
reduce_scope( savant::set<IIRScram_Declaration> *declaration_set );

/** This method is used by the parser.  It looks at an aggregate it has
built, and decides whether it should remain an aggregate, or if it should
convert it to a more simple expression.  ( x ) doesn't need to be an
aggregate.  ( x => y ) does.  ( others => '1' ) does too. */
IIRScram *reduce_aggregate( IIRScram_Aggregate *aggregate );

IIRScram *reduce_association_list( IIRScram_AssociationList * );

/** This method is used by the parser to "unroll" choices in an aggregate
    initialization ( 0 | 1 | 2 => '1' ) becomes ( 0 => '1', 1 => '1', 2 =>
    '1' ); It also properly builds IIRScram_OthersInitialization if
    necessary. */
void 
process_aggregate_with_choices( IIRScram *formal_part, IIRScram *actual_part, IIRScram_Aggregate *retval );

/** This function checks a declaration's identifier against the ending name
    found at the end of a declaration, and reports an error if they don't
    match.  The last argument is the string literal of the type we're
    looking at.  So, we can generate the error message "foo doesn't match
    entity name bar".  We'd pass in "entity". */
void 
check_name( IIR_TextLiteral *, IIR_Name *, const char *declaration_type );

void 
check_name( IIR_TextLiteral *, IIR_TextLiteral *, const char *declaration_type );

void 
check_name( IIR_Label *, IIR_Name *, const char *declaration_type );


/** This method builds a default port map or generic map for this
    configurationSpecification or a componentInstantiationStatement, or a
    component configuration.  Since it is used by several different
    classes, it really belongs in neither.  So, it's just a normal
    function.*/
void build_default_map( IIRScram_InterfaceList   *formal_list, 
			IIRScram_InterfaceList   *actual_list, 
			IIRScram_AssociationList &default_map);


IIR_TypeDeclaration *
find_incomplete_type_declaration( IIR_Identifier *type_name );

#endif

