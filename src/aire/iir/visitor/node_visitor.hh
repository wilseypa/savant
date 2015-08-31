
#ifndef NODE_VISITOR_HH
#define NODE_VISITOR_HH

// Copyright (c) 1999-2000 The University of Cincinnati.  
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

// Authors: Philip A. Wilsey	phil.wilsey@uc.edu
//---------------------------------------------------------------------------

#include "savant_config.hh"
#include "visitor_argument_type.hh"
#include "visitor_return_type.hh"

class IIR;

/** This class contains the interface definition for visitors to the IIR
    intermediate form package \Ref{IIR}.  All visitor methods in this
    package are declared pure virtual so any visitor type derived from this
    class must provide an implementation for each.

    An important aspect of this visitor pattern is that it supports
    parameter transmission.  Each method has two arguments, the first is a
    pointer to the IIR object related to this visitation and the second is
    an general {\tt visitor_argument_type*} argument that is provided for
    use by any instantiated visitor object; each method also has a return
    signature {\tt visitor_return_type*} that the visitor can use to
    return data up the call chain. 

    @see visitor_argument_type
    @see visitor_return_type
    @see IIR */
class node_visitor {

public: 

  /** Visitor method for objects of type IIR_AbsoluteOperator.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_AbsoluteOperator(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_AccessSubtypeDefinition.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_AccessSubtypeDefinition(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_AccessTypeDefinition.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_AccessTypeDefinition(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ActiveAttribute.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ActiveAttribute(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_AdditionOperator.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_AdditionOperator(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_Aggregate.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_Aggregate(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_AliasDeclaration.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_AliasDeclaration(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_Allocator.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_Allocator(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_AndOperator.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_AndOperator(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ArchitectureDeclaration.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ArchitectureDeclaration(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ArchitectureStatementList.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ArchitectureStatementList(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ArraySubtypeDefinition.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ArraySubtypeDefinition(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ArrayTypeDefinition.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ArrayTypeDefinition(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_AscendingAttribute.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_AscendingAttribute(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_AssertionStatement.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_AssertionStatement(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_AssociationElementByExpression.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_AssociationElementByExpression(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_AssociationElementOpen.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_AssociationElementOpen(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_AssociationList.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_AssociationList(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_AttributeDeclaration.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_AttributeDeclaration(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_AttributeSpecification.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_AttributeSpecification(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_AttributeSpecificationList.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_AttributeSpecificationList(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_BaseAttribute.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_BaseAttribute(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_BitStringLiteral.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_BitStringLiteral(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_BlockConfiguration.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_BlockConfiguration(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_BlockStatement.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_BlockStatement(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_CaseStatement.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_CaseStatement(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_CaseStatementAlternativeByChoices.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_CaseStatementAlternativeByChoices(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_CaseStatementAlternativeByExpression.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_CaseStatementAlternativeByExpression(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_CaseStatementAlternativeByOthers.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_CaseStatementAlternativeByOthers(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_CaseStatementAlternativeList.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_CaseStatementAlternativeList(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_CharacterLiteral.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_CharacterLiteral(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_Choice.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_Choice(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ChoiceList.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ChoiceList(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_Comment.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_Comment(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_CommentList.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_CommentList(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ComponentConfiguration.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ComponentConfiguration(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ComponentDeclaration.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ComponentDeclaration(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ComponentInstantiationStatement.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ComponentInstantiationStatement(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ConcatenationOperator.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ConcatenationOperator(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ConcurrentAssertionStatement.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ConcurrentAssertionStatement(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ConcurrentConditionalSignalAssignment.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ConcurrentConditionalSignalAssignment(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ConcurrentGenerateForStatement.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ConcurrentGenerateForStatement(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ConcurrentGenerateIfStatement.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ConcurrentGenerateIfStatement(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ConcurrentProcedureCallStatement.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ConcurrentProcedureCallStatement(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ConcurrentSelectedSignalAssignment.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ConcurrentSelectedSignalAssignment(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ConditionalWaveform.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ConditionalWaveform(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ConditionalWaveformList.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ConditionalWaveformList(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ConfigurationDeclaration.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ConfigurationDeclaration(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ConfigurationItem.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ConfigurationItem(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ConfigurationItemList.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ConfigurationItemList(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ConfigurationSpecification.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ConfigurationSpecification(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ConstantDeclaration.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ConstantDeclaration(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ConstantInterfaceDeclaration.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ConstantInterfaceDeclaration(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_DeclarationList.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_DeclarationList(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_DelayedAttribute.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_DelayedAttribute(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_DesignFile.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_DesignFile(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_DesignFileList.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_DesignFileList(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_DesignUnitList.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_DesignUnitList(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_DesignatorByAll.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_DesignatorByAll(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_DesignatorByOthers.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_DesignatorByOthers(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_DesignatorExplicit.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_DesignatorExplicit(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_DesignatorList.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_DesignatorList(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_DisconnectSpecification.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_DisconnectSpecification(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_DivisionOperator.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_DivisionOperator(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_DrivingAttribute.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_DrivingAttribute(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_DrivingValueAttribute.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_DrivingValueAttribute(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ElementDeclaration.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ElementDeclaration(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ElementDeclarationList.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ElementDeclarationList(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_Elsif.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_Elsif(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_EntityClassEntry.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_EntityClassEntry(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_EntityClassEntryList.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_EntityClassEntryList(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_EntityDeclaration.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_EntityDeclaration(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_EntityNameList.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_EntityNameList(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_EnumerationLiteral.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_EnumerationLiteral(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_EnumerationLiteralList.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_EnumerationLiteralList(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_EnumerationSubtypeDefinition.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_EnumerationSubtypeDefinition(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_EnumerationTypeDefinition.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_EnumerationTypeDefinition(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_EqualityOperator.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_EqualityOperator(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_EventAttribute.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_EventAttribute(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ExitStatement.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ExitStatement(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ExponentiationOperator.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ExponentiationOperator(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_FileDeclaration.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_FileDeclaration(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_FileInterfaceDeclaration.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_FileInterfaceDeclaration(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_FileTypeDefinition.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_FileTypeDefinition(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_FloatingPointLiteral.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_FloatingPointLiteral(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_FloatingPointLiteral32.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_FloatingPointLiteral32(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_FloatingPointLiteral64.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_FloatingPointLiteral64(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_FloatingSubtypeDefinition.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_FloatingSubtypeDefinition(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_FloatingTypeDefinition.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_FloatingTypeDefinition(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ForLoopStatement.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ForLoopStatement(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_FunctionCall.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_FunctionCall(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_FunctionDeclaration.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_FunctionDeclaration(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_GenericList.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_GenericList(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_GreaterThanOperator.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_GreaterThanOperator(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_GreaterThanOrEqualOperator.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_GreaterThanOrEqualOperator(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_GroupConstituent.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_GroupConstituent(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_GroupDeclaration.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_GroupDeclaration(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_GroupTemplateDeclaration.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_GroupTemplateDeclaration(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_HighAttribute.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_HighAttribute(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_Identifier.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_Identifier(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_IdentifierList.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_IdentifierList(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_IdentityOperator.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_IdentityOperator(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_IfStatement.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_IfStatement(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ImageAttribute.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ImageAttribute(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_IndexedName.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_IndexedName(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_InequalityOperator.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_InequalityOperator(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_InstanceNameAttribute.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_InstanceNameAttribute(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_IntegerLiteral.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_IntegerLiteral(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_IntegerLiteral32.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_IntegerLiteral32(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_IntegerLiteral64.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_IntegerLiteral64(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_IntegerSubtypeDefinition.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_IntegerSubtypeDefinition(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_IntegerTypeDefinition.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_IntegerTypeDefinition(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_InterfaceList.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_InterfaceList(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_Label.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_Label(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_LastActiveAttribute.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_LastActiveAttribute(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_LastEventAttribute.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_LastEventAttribute(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_LastValueAttribute.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_LastValueAttribute(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_LeftAttribute.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_LeftAttribute(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_LeftOfAttribute.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_LeftOfAttribute(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_LengthAttribute.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_LengthAttribute(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_LessThanOperator.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_LessThanOperator(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_LessThanOrEqualOperator.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_LessThanOrEqualOperator(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_LibraryClause.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_LibraryClause(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_LibraryDeclaration.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_LibraryDeclaration(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_LibraryUnitList.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_LibraryUnitList(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_Literal.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_Literal(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_LowAttribute.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_LowAttribute(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ModulusOperator.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ModulusOperator(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_MultiplicationOperator.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_MultiplicationOperator(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_Name.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_Name(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_NameList.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_NameList(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_NandOperator.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_NandOperator(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_NegationOperator.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_NegationOperator(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_NextStatement.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_NextStatement(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_NorOperator.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_NorOperator(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_NotOperator.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_NotOperator(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_NullStatement.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_NullStatement(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_OrOperator.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_OrOperator(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_OthersInitialization.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_OthersInitialization(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_PackageBodyDeclaration.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_PackageBodyDeclaration(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_PackageDeclaration.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_PackageDeclaration(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_PathNameAttribute.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_PathNameAttribute(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_PhysicalLiteral.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_PhysicalLiteral(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_PhysicalSubtypeDefinition.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_PhysicalSubtypeDefinition(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_PhysicalTypeDefinition.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_PhysicalTypeDefinition(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_PhysicalUnit.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_PhysicalUnit(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_PortList.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_PortList(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_PosAttribute.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_PosAttribute(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_PredAttribute.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_PredAttribute(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ProcedureCallStatement.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ProcedureCallStatement(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ProcedureDeclaration.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ProcedureDeclaration(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ProcessStatement.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ProcessStatement(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_QualifiedExpression.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_QualifiedExpression(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_QuietAttribute.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_QuietAttribute(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ROLOperator.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ROLOperator(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ROROperator.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ROROperator(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_RangeAttribute.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_RangeAttribute(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_RangeTypeDefinition.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_RangeTypeDefinition(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_RecordTypeDefinition.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_RecordTypeDefinition(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_RemainderOperator.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_RemainderOperator(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ReportStatement.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ReportStatement(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ReturnStatement.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ReturnStatement(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ReverseRangeAttribute.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ReverseRangeAttribute(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_RightAttribute.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_RightAttribute(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_RightOfAttribute.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_RightOfAttribute(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_SLAOperator.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_SLAOperator(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_SLLOperator.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_SLLOperator(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_SRAOperator.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_SRAOperator(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_SRLOperator.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_SRLOperator(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_SelectedName.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_SelectedName(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_SelectedNameByAll.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_SelectedNameByAll(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_SelectedWaveform.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_SelectedWaveform(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_SelectedWaveformList.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_SelectedWaveformList(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_SensitizedProcessStatement.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_SensitizedProcessStatement(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_SequentialStatementList.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_SequentialStatementList(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_SharedVariableDeclaration.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_SharedVariableDeclaration(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_SignalAssignmentStatement.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_SignalAssignmentStatement(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_SignalDeclaration.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_SignalDeclaration(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_SignalInterfaceDeclaration.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_SignalInterfaceDeclaration(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_Signature.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_Signature(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_SimpleName.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_SimpleName(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_SimpleNameAttribute.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_SimpleNameAttribute(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_SliceName.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_SliceName(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_StableAttribute.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_StableAttribute(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_StringLiteral.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_StringLiteral(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_SubprogramDeclaration.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_SubprogramDeclaration(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_SubtractionOperator.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_SubtractionOperator(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_SubtypeDeclaration.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_SubtypeDeclaration(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_SuccAttribute.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_SuccAttribute(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_TransactionAttribute.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_TransactionAttribute(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_Tuple.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_Tuple(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_TypeConversion.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_TypeConversion(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_TypeDeclaration.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_TypeDeclaration(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_UnitList.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_UnitList(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_UseClause.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_UseClause(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_UserAttribute.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_UserAttribute(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ValAttribute.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ValAttribute(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_ValueAttribute.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_ValueAttribute(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_VariableAssignmentStatement.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_VariableAssignmentStatement(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_VariableDeclaration.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_VariableDeclaration(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_VariableInterfaceDeclaration.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_VariableInterfaceDeclaration(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_WaitStatement.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_WaitStatement(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_WaveformElement.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_WaveformElement(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_WaveformList.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_WaveformList(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_WhileLoopStatement.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_WhileLoopStatement(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_XnorOperator.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_XnorOperator(IIR *node, visitor_argument_type *arg) = 0;


  /** Visitor method for objects of type IIR_XorOperator.
      @return container for any return value wanted by the visitor.
      @param node a pointer to the \Ref{AIRE-IIR} object related to this
      visitation 
      @param arg container for any argument wanted by the visitor.
  */
  virtual visitor_return_type *visit_IIR_XorOperator(IIR *node, visitor_argument_type *arg) = 0;


  /// Constructor.
  node_visitor() {};

  /** The destructor is pure virtual to define this as an abstract and to
      prevent direct instantiation. 
  */
  virtual ~node_visitor() = 0;

};

#endif
