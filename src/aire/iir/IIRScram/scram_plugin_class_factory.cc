
// Copyright (c) Clifton Labs, Inc.  All rights reserved.

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


#include "IIRScram_AboveAttribute.hh"
#include "IIRScram_AbsoluteOperator.hh"
#include "IIRScram_AccessSubtypeDefinition.hh"
#include "IIRScram_AccessTypeDefinition.hh"
#include "IIRScram_AcrossAttribute.hh"
#include "IIRScram_ActiveAttribute.hh"
#include "IIRScram_AdditionOperator.hh"
#include "IIRScram_Aggregate.hh"
#include "IIRScram_AliasDeclaration.hh"
#include "IIRScram_Allocator.hh"
#include "IIRScram_AndOperator.hh"
#include "IIRScram_ArchitectureDeclaration.hh"
#include "IIRScram_ArchitectureStatement.hh"
#include "IIRScram_ArchitectureStatementList.hh"
#include "IIRScram_ArrayNatureDefinition.hh"
#include "IIRScram_ArraySubnatureDefinition.hh"
#include "IIRScram_ArraySubtypeDefinition.hh"
#include "IIRScram_ArrayTypeDefinition.hh"
#include "IIRScram_AscendingAttribute.hh"
#include "IIRScram_AssertionStatement.hh"
#include "IIRScram_AssociationElementByExpression.hh"
#include "IIRScram_AssociationElement.hh"
#include "IIRScram_AssociationElementOpen.hh"
#include "IIRScram_AssociationList.hh"
#include "IIRScram_AttributeDeclaration.hh"
#include "IIRScram_Attribute.hh"
#include "IIRScram_AttributeSpecification.hh"
#include "IIRScram_AttributeSpecificationList.hh"
#include "IIRScram_BaseAttribute.hh"
#include "IIRScram_BitStringLiteral.hh"
#include "IIRScram_BlockConfiguration.hh"
#include "IIRScram_BlockStatement.hh"
#include "IIRScram_BranchQuantityDeclaration.hh"
#include "IIRScram_BreakElement.hh"
#include "IIRScram_BreakStatement.hh"
#include "IIRScram_CaseStatementAlternativeByChoices.hh"
#include "IIRScram_CaseStatementAlternativeByExpression.hh"
#include "IIRScram_CaseStatementAlternativeByOthers.hh"
#include "IIRScram_CaseStatementAlternativeList.hh"
#include "IIRScram_CaseStatement.hh"
#include "IIRScram_CharacterLiteral.hh"
#include "IIRScram_Choice.hh"
#include "IIRScram_ChoiceList.hh"
#include "IIRScram_Comment.hh"
#include "IIRScram_CommentList.hh"
#include "IIRScram_ComponentConfiguration.hh"
#include "IIRScram_ComponentDeclaration.hh"
#include "IIRScram_ComponentInstantiationStatement.hh"
#include "IIRScram_ConcatenationOperator.hh"
#include "IIRScram_ConcurrentAssertionStatement.hh"
#include "IIRScram_ConcurrentBreakStatement.hh"
#include "IIRScram_ConcurrentConditionalSignalAssignment.hh"
#include "IIRScram_ConcurrentGenerateForStatement.hh"
#include "IIRScram_ConcurrentGenerateIfStatement.hh"
#include "IIRScram_ConcurrentProcedureCallStatement.hh"
#include "IIRScram_ConcurrentSelectedSignalAssignment.hh"
#include "IIRScram_ConcurrentStatement.hh"
#include "IIRScram_ConditionalWaveform.hh"
#include "IIRScram_ConditionalWaveformList.hh"
#include "IIRScram_ConfigurationDeclaration.hh"
#include "IIRScram_ConfigurationItem.hh"
#include "IIRScram_ConfigurationItemList.hh"
#include "IIRScram_ConfigurationSpecification.hh"
#include "IIRScram_ConstantDeclaration.hh"
#include "IIRScram_ConstantInterfaceDeclaration.hh"
#include "IIRScram_ContributionAttribute.hh"
#include "IIRScram_Declaration.hh"
#include "IIRScram_DeclarationList.hh"
#include "IIRScram_DelayedAttribute.hh"
#include "IIRScram_DesignatorByAll.hh"
#include "IIRScram_DesignatorByOthers.hh"
#include "IIRScram_DesignatorExplicit.hh"
#include "IIRScram_Designator.hh"
#include "IIRScram_DesignatorList.hh"
#include "IIRScram_DesignFile.hh"
#include "IIRScram_DesignFileList.hh"
#include "IIRScram_DesignUnitList.hh"
#include "IIRScram_DisconnectSpecification.hh"
#include "IIRScram_DivisionOperator.hh"
#include "IIRScram_DotAttribute.hh"
#include "IIRScram_DrivingAttribute.hh"
#include "IIRScram_DrivingValueAttribute.hh"
#include "IIRScram_DyadicOperator.hh"
#include "IIRScram_ElementDeclaration.hh"
#include "IIRScram_ElementDeclarationList.hh"
#include "IIRScram_Elsif.hh"
#include "IIRScram_EntityClassEntry.hh"
#include "IIRScram_EntityClassEntryList.hh"
#include "IIRScram_EntityDeclaration.hh"
#include "IIRScram_EntityNameList.hh"
#include "IIRScram_EnumerationLiteral.hh"
#include "IIRScram_EnumerationLiteralList.hh"
#include "IIRScram_EnumerationSubtypeDefinition.hh"
#include "IIRScram_EnumerationTypeDefinition.hh"
#include "IIRScram_EqualityOperator.hh"
#include "IIRScram_EventAttribute.hh"
#include "IIRScram_ExitStatement.hh"
#include "IIRScram_ExponentiationOperator.hh"
#include "IIRScram_Expression.hh"
#include "IIRScram_FileDeclaration.hh"
#include "IIRScram_FileInterfaceDeclaration.hh"
#include "IIRScram_FileTypeDefinition.hh"
#include "IIRScram_FloatingPointLiteral32.hh"
#include "IIRScram_FloatingPointLiteral64.hh"
#include "IIRScram_FloatingPointLiteral.hh"
#include "IIRScram_FloatingSubtypeDefinition.hh"
#include "IIRScram_FloatingTypeDefinition.hh"
#include "IIRScram_ForLoopStatement.hh"
#include "IIRScram_FreeQuantityDeclaration.hh"
#include "IIRScram_FunctionCall.hh"
#include "IIRScram_FunctionDeclaration.hh"
#include "IIRScram_GenericList.hh"
#include "IIRScram_GreaterThanOperator.hh"
#include "IIRScram_GreaterThanOrEqualOperator.hh"
#include "IIRScram_GroupConstituent.hh"
#include "IIRScram_GroupDeclaration.hh"
#include "IIRScram_GroupTemplateDeclaration.hh"
#include "IIRScram.hh"
#include "IIRScram_HighAttribute.hh"
#include "IIRScram_Identifier.hh"
#include "IIRScram_IdentifierList.hh"
#include "IIRScram_IdentityOperator.hh"
#include "IIRScram_IfStatement.hh"
#include "IIRScram_ImageAttribute.hh"
#include "IIRScram_IncompleteTypeDefinition.hh"
#include "IIRScram_IndexedName.hh"
#include "IIRScram_InequalityOperator.hh"
#include "IIRScram_InstanceNameAttribute.hh"
#include "IIRScram_IntegerLiteral32.hh"
#include "IIRScram_IntegerLiteral64.hh"
#include "IIRScram_IntegerLiteral.hh"
#include "IIRScram_IntegerSubtypeDefinition.hh"
#include "IIRScram_IntegerTypeDefinition.hh"
#include "IIRScram_InterfaceDeclaration.hh"
#include "IIRScram_InterfaceList.hh"
#include "IIRScram_Label.hh"
#include "IIRScram_LastActiveAttribute.hh"
#include "IIRScram_LastEventAttribute.hh"
#include "IIRScram_LastValueAttribute.hh"
#include "IIRScram_LeftAttribute.hh"
#include "IIRScram_LeftOfAttribute.hh"
#include "IIRScram_LengthAttribute.hh"
#include "IIRScram_LessThanOperator.hh"
#include "IIRScram_LessThanOrEqualOperator.hh"
#include "IIRScram_LibraryClause.hh"
#include "IIRScram_LibraryDeclaration.hh"
#include "IIRScram_LibraryUnit.hh"
#include "IIRScram_LibraryUnitList.hh"
#include "IIRScram_List.hh"
#include "IIRScram_Literal.hh"
#include "IIRScram_LowAttribute.hh"
#include "IIRScram_LTFAttribute.hh"
#include "IIRScram_ModulusOperator.hh"
#include "IIRScram_MonadicOperator.hh"
#include "IIRScram_MultiplicationOperator.hh"
#include "IIRScram_Name.hh"
#include "IIRScram_NameList.hh"
#include "IIRScram_NandOperator.hh"
#include "IIRScram_NatureDeclaration.hh"
#include "IIRScram_NatureDefinition.hh"
#include "IIRScram_NegationOperator.hh"
#include "IIRScram_NextStatement.hh"
#include "IIRScram_NorOperator.hh"
#include "IIRScram_NotOperator.hh"
#include "IIRScram_NullStatement.hh"
#include "IIRScram_ObjectDeclaration.hh"
#include "IIRScram_OrOperator.hh"
#include "IIRScram_OthersInitialization.hh"
#include "IIRScram_PackageBodyDeclaration.hh"
#include "IIRScram_PackageDeclaration.hh"
#include "IIRScram_PathNameAttribute.hh"
#include "IIRScram_PhysicalLiteral.hh"
#include "IIRScram_PhysicalSubtypeDefinition.hh"
#include "IIRScram_PhysicalTypeDefinition.hh"
#include "IIRScram_PhysicalUnit.hh"
#include "IIRScram_PortList.hh"
#include "IIRScram_PosAttribute.hh"
#include "IIRScram_PredAttribute.hh"
#include "IIRScram_ProcedureCallStatement.hh"
#include "IIRScram_ProcedureDeclaration.hh"
#include "IIRScram_ProcessStatement.hh"
#include "IIRScram_QualifiedExpression.hh"
#include "IIRScram_QuantityDeclaration.hh"
#include "IIRScram_QuietAttribute.hh"
#include "IIRScram_RangeAttribute.hh"
#include "IIRScram_RangeTypeDefinition.hh"
#include "IIRScram_RecordTypeDefinition.hh"
#include "IIRScram_ReferenceAttribute.hh"
#include "IIRScram_RemainderOperator.hh"
#include "IIRScram_ReportStatement.hh"
#include "IIRScram_ReturnStatement.hh"
#include "IIRScram_ReverseRangeAttribute.hh"
#include "IIRScram_RightAttribute.hh"
#include "IIRScram_RightOfAttribute.hh"
#include "IIRScram_ROLOperator.hh"
#include "IIRScram_ROROperator.hh"
#include "IIRScram_ScalarNatureDefinition.hh"
#include "IIRScram_ScalarTypeDefinition.hh"
#include "IIRScram_SelectedNameByAll.hh"
#include "IIRScram_SelectedName.hh"
#include "IIRScram_SelectedWaveform.hh"
#include "IIRScram_SelectedWaveformList.hh"
#include "IIRScram_SensitizedProcessStatement.hh"
#include "IIRScram_SequentialStatement.hh"
#include "IIRScram_SequentialStatementList.hh"
#include "IIRScram_SharedVariableDeclaration.hh"
#include "IIRScram_SignalAssignmentStatement.hh"
#include "IIRScram_SignalDeclaration.hh"
#include "IIRScram_SignalInterfaceDeclaration.hh"
#include "IIRScram_Signature.hh"
#include "IIRScram_SimpleNameAttribute.hh"
#include "IIRScram_SimpleName.hh"
#include "IIRScram_SimpleSimultaneousStatement.hh"
#include "IIRScram_SimultaneousElsif.hh"
#include "IIRScram_SimultaneousIfStatement.hh"
#include "IIRScram_SimultaneousStatement.hh"
#include "IIRScram_SLAOperator.hh"
#include "IIRScram_SliceName.hh"
#include "IIRScram_SLLOperator.hh"
#include "IIRScram_SourceQuantityDeclaration.hh"
#include "IIRScram_SRAOperator.hh"
#include "IIRScram_SRLOperator.hh"
#include "IIRScram_StableAttribute.hh"
#include "IIRScram_Statement.hh"
#include "IIRScram_StringLiteral.hh"
#include "IIRScram_SubprogramDeclaration.hh"
#include "IIRScram_SubtractionOperator.hh"
#include "IIRScram_SubtypeDeclaration.hh"
#include "IIRScram_SuccAttribute.hh"
#include "IIRScram_TerminalDeclaration.hh"
#include "IIRScram_TerminalInterfaceDeclaration.hh"
#include "IIRScram_TextLiteral.hh"
#include "IIRScram_ThroughAttribute.hh"
#include "IIRScram_TransactionAttribute.hh"
#include "IIRScram_Tuple.hh"
#include "IIRScram_TypeConversion.hh"
#include "IIRScram_TypeDeclaration.hh"
#include "IIRScram_TypeDefinition.hh"
#include "IIRScram_UnitList.hh"
#include "IIRScram_UseClause.hh"
#include "IIRScram_UserAttribute.hh"
#include "IIRScram_ValAttribute.hh"
#include "IIRScram_ValueAttribute.hh"
#include "IIRScram_VariableAssignmentStatement.hh"
#include "IIRScram_VariableDeclaration.hh"
#include "IIRScram_VariableInterfaceDeclaration.hh"
#include "IIRScram_WaitStatement.hh"
#include "IIRScram_WaveformElement.hh"
#include "IIRScram_WaveformList.hh"
#include "IIRScram_WhileLoopStatement.hh"
#include "IIRScram_XnorOperator.hh"
#include "IIRScram_XorOperator.hh"
#include "IIRScram_ZTFAttribute.hh"

#include "ScramStandardPackage.hh"
#include "IRKind.hh"

// Implementation details
#include "scram_plugin_class_factory.hh"

IIR*
scram_plugin_class_factory::get_new_class(IIR_Kind iir_type) {
  IIR *retv = NULL;
  switch (iir_type) {
  case IIR_ABOVE_ATTRIBUTE:
    retv = new IIRScram_AboveAttribute();
    break;     

  case IIR_ABSOLUTE_OPERATOR:
    retv = new IIRScram_AbsoluteOperator();
    break;     

  case IIR_ACCESS_SUBTYPE_DEFINITION:
    retv = new IIRScram_AccessSubtypeDefinition();
    break;     

  case IIR_ACCESS_TYPE_DEFINITION:
    retv = new IIRScram_AccessTypeDefinition();
    break;     

  case IIR_ACROSS_ATTRIBUTE:
    retv = new IIRScram_AcrossAttribute();
    break;     

  case IIR_ACTIVE_ATTRIBUTE:
    retv = new IIRScram_ActiveAttribute();
    break;     

  case IIR_ADDITION_OPERATOR:
    retv = new IIRScram_AdditionOperator();
    break;     

  case IIR_AGGREGATE:
    retv = new IIRScram_Aggregate();
    break;     

  case IIR_ALIAS_DECLARATION:
    retv = new IIRScram_AliasDeclaration();
    break;     

  case IIR_ALLOCATOR:
    retv = new IIRScram_Allocator();
    break;     

  case IIR_AND_OPERATOR:
    retv = new IIRScram_AndOperator();
    break;     

  case IIR_ARCHITECTURE_DECLARATION:
    retv = new IIRScram_ArchitectureDeclaration();
    break;     

  case IIR_ARCHITECTURE_STATEMENT:
    retv = new IIRScram_ArchitectureStatement();
    break;     

  case IIR_ARCHITECTURE_STATEMENT_LIST:
    retv = new IIRScram_ArchitectureStatementList();
    break;     

  case IIR_ARRAY_NATURE_DEFINITION:
    retv = new IIRScram_ArrayNatureDefinition();
    break;     

  case IIR_ARRAY_SUBNATURE_DEFINITION:
    retv = new IIRScram_ArraySubnatureDefinition();
    break;     

  case IIR_ARRAY_SUBTYPE_DEFINITION:
    retv = new IIRScram_ArraySubtypeDefinition();
    break;     

  case IIR_ARRAY_TYPE_DEFINITION:
    retv = new IIRScram_ArrayTypeDefinition();
    break;     

  case IIR_ASCENDING_ATTRIBUTE:
    retv = new IIRScram_AscendingAttribute();
    break;     

  case IIR_ASSERTION_STATEMENT:
    retv = new IIRScram_AssertionStatement();
    break;     

  case IIR_ASSOCIATION_ELEMENT_BY_EXPRESSION:
    retv = new IIRScram_AssociationElementByExpression();
    break;     

  case IIR_ASSOCIATION_ELEMENT_BY_OPEN:
    retv = new IIRScram_AssociationElementOpen();
    break;     

  case IIR_ASSOCIATION_LIST:
    retv = new IIRScram_AssociationList();
    break;     

  case IIR_ATTRIBUTE_DECLARATION:
    retv = new IIRScram_AttributeDeclaration();
    break;     

  case IIR_ATTRIBUTE_SPECIFICATION:
    retv = new IIRScram_AttributeSpecification();
    break;     

  case IIR_ATTRIBUTE_SPECIFICATION_LIST:
    retv = new IIRScram_AttributeSpecificationList();
    break;     

  case IIR_BASE_ATTRIBUTE:
    retv = new IIRScram_BaseAttribute();
    break;     

  case IIR_BIT_STRING_LITERAL:
    retv = new IIRScram_BitStringLiteral();
    break;     

  case IIR_BLOCK_CONFIGURATION:
    retv = new IIRScram_BlockConfiguration();
    break;     

  case IIR_BLOCK_STATEMENT:
    retv = new IIRScram_BlockStatement();
    break;     

  case IIR_BRANCH_QUANTITY_DECLARATION:
    retv = new IIRScram_BranchQuantityDeclaration();
    break;     

  case IIR_BREAK_ELEMENT:
    retv = new IIRScram_BreakElement();
    break;     

  case IIR_BREAK_STATEMENT:
    retv = new IIRScram_BreakStatement();
    break;     

  case IIR_CASE_STATEMENT_ALTERNATIVE_BY_CHOICES:
    retv = new IIRScram_CaseStatementAlternativeByChoices();
    break;     

  case IIR_CASE_STATEMENT_ALTERNATIVE_BY_EXPRESSION:
    retv = new IIRScram_CaseStatementAlternativeByExpression();
    break;     

  case IIR_CASE_STATEMENT_ALTERNATIVE_BY_OTHERS:
    retv = new IIRScram_CaseStatementAlternativeByOthers();
    break;     

  case IIR_CASE_STATEMENT_ALTERNATIVE_LIST:
    retv = new IIRScram_CaseStatementAlternativeList();
    break;     

  case IIR_CASE_STATEMENT:
    retv = new IIRScram_CaseStatement();
    break;     

  case IIR_CHARACTER_LITERAL:
    retv = new IIRScram_CharacterLiteral();
    break;     

  case IIR_CHOICE:
    retv = new IIRScram_Choice();
    break;     

  case IIR_CHOICE_LIST:
    retv = new IIRScram_ChoiceList();
    break;     

  case IIR_COMMENT:
    retv = new IIRScram_Comment();
    break;     

  case IIR_COMMENT_LIST:
    retv = new IIRScram_CommentList();
    break;     

  case IIR_COMPONENT_CONFIGURATION:
    retv = new IIRScram_ComponentConfiguration();
    break;     

  case IIR_COMPONENT_DECLARATION:
    retv = new IIRScram_ComponentDeclaration();
    break;     

  case IIR_COMPONENT_INSTANTIATION_STATEMENT:
    retv = new IIRScram_ComponentInstantiationStatement();
    break;     

  case IIR_CONCATENATION_OPERATOR:
    retv = new IIRScram_ConcatenationOperator();
    break;     

  case IIR_CONCURRENT_ASSERTION_STATEMENT:
    retv = new IIRScram_ConcurrentAssertionStatement();
    break;     

  case IIR_CONCURRENT_BREAK_STATEMENT:
    retv = new IIRScram_ConcurrentBreakStatement();
    break;

  case IIR_CONCURRENT_CONDITIONAL_SIGNAL_ASSIGNMENT:
    retv = new IIRScram_ConcurrentConditionalSignalAssignment();
    break;     

  case IIR_CONCURRENT_GENERATE_FOR_STATEMENT:
    retv = new IIRScram_ConcurrentGenerateForStatement();
    break;     

  case IIR_CONCURRENT_GENERATE_IF_STATEMENT:
    retv = new IIRScram_ConcurrentGenerateIfStatement();
    break;     

  case IIR_CONCURRENT_PROCEDURE_CALL_STATEMENT:
    retv = new IIRScram_ConcurrentProcedureCallStatement();
    break;     

  case IIR_CONCURRENT_SELECTED_SIGNAL_ASSIGNMENT:
    retv = new IIRScram_ConcurrentSelectedSignalAssignment();
    break;     

  case IIR_CONDITIONAL_WAVEFORM:
    retv = new IIRScram_ConditionalWaveform();
    break;     

  case IIR_CONDITIONAL_WAVEFORM_LIST:
    retv = new IIRScram_ConditionalWaveformList();
    break;     

  case IIR_CONFIGURATION_DECLARATION:
    retv = new IIRScram_ConfigurationDeclaration();
    break;     

  case IIR_CONFIGURATION_ITEM:
    retv = new IIRScram_ConfigurationItem();
    break;     

  case IIR_CONFIGURATION_ITEM_LIST:
    retv = new IIRScram_ConfigurationItemList();
    break;     

  case IIR_CONFIGURATION_SPECIFICATION:
    retv = new IIRScram_ConfigurationSpecification();
    break;     

  case IIR_CONTRIBUTION_ATTRIBUTE:
    retv = new IIRScram_ContributionAttribute();
    break;     

  case IIR_CONSTANT_DECLARATION:
    retv = new IIRScram_ConstantDeclaration();
    break;     

  case IIR_CONSTANT_INTERFACE_DECLARATION:
    retv = new IIRScram_ConstantInterfaceDeclaration();
    break;     

  case IIR_DECLARATION_LIST:
    retv = new IIRScram_DeclarationList();
    break;     

  case IIR_DELAYED_ATTRIBUTE:
    retv = new IIRScram_DelayedAttribute();
    break;     

  case IIR_DESIGNATOR_BY_ALL:
    retv = new IIRScram_DesignatorByAll();
    break;     

  case IIR_DESIGNATOR_BY_OTHERS:
    retv = new IIRScram_DesignatorByOthers();
    break;     

  case IIR_DESIGNATOR_EXPLICIT:
    retv = new IIRScram_DesignatorExplicit();
    break;     

  case IIR_DESIGNATOR_LIST:
    retv = new IIRScram_DesignatorList();
    break;     

  case IIR_DESIGN_FILE:
    retv = new IIRScram_DesignFile();
    break;     

  case IIR_DESIGN_FILE_LIST:
    retv = new IIRScram_DesignFileList();
    break;     

  case IIR_DESIGN_UNIT_LIST:
    retv = new IIRScram_DesignUnitList();
    break;     

  case IIR_DISCONNECT_SPECIFICATION:
    retv = new IIRScram_DisconnectSpecification();
    break;     

  case IIR_DIVISION_OPERATOR:
    retv = new IIRScram_DivisionOperator();
    break;     

  case IIR_DOT_ATTRIBUTE:
    retv = new IIRScram_DotAttribute();
    break;     

  case IIR_DRIVING_ATTRIBUTE:
    retv = new IIRScram_DrivingAttribute();
    break;     

  case IIR_DRIVING_VALUE_ATTRIBUTE:
    retv = new IIRScram_DrivingValueAttribute();
    break;     

  case IIR_ELEMENT_DECLARATION:
    retv = new IIRScram_ElementDeclaration();
    break;     

  case IIR_ELEMENT_DECLARATION_LIST:
    retv = new IIRScram_ElementDeclarationList();
    break;     

  case IIR_ELSIF:
    retv = new IIRScram_Elsif();
    break;     

  case IIR_ENTITY_CLASS_ENTRY:
    retv = new IIRScram_EntityClassEntry();
    break;     

  case IIR_ENTITY_CLASS_ENTRY_LIST:
    retv = new IIRScram_EntityClassEntryList();
    break;     

  case IIR_ENTITY_DECLARATION:
    retv = new IIRScram_EntityDeclaration();
    break;     

  case IIR_ENTITY_NAME_LIST:
    retv = new IIRScram_EntityNameList();
    break;     

  case IIR_ENUMERATION_LITERAL:
    retv = new IIRScram_EnumerationLiteral();
    break;     

  case IIR_ENUMERATION_LITERAL_LIST:
    retv = new IIRScram_EnumerationLiteralList();
    break;     

  case IIR_ENUMERATION_SUBTYPE_DEFINITION:
    retv = new IIRScram_EnumerationSubtypeDefinition();
    break;     

  case IIR_ENUMERATION_TYPE_DEFINITION:
    retv = new IIRScram_EnumerationTypeDefinition();
    break;     

  case IIR_EQUALITY_OPERATOR:
    retv = new IIRScram_EqualityOperator();
    break;     

  case IIR_EVENT_ATTRIBUTE:
    retv = new IIRScram_EventAttribute();
    break;     

  case IIR_EXIT_STATEMENT:
    retv = new IIRScram_ExitStatement();
    break;     

  case IIR_EXPONENTIATION_OPERATOR:
    retv = new IIRScram_ExponentiationOperator();
    break;     

  case IIR_FILE_DECLARATION:
    retv = new IIRScram_FileDeclaration();
    break;     

  case IIR_FILE_INTERFACE_DECLARATION:
    retv = new IIRScram_FileInterfaceDeclaration();
    break;     

  case IIR_FILE_TYPE_DEFINITION:
    retv = new IIRScram_FileTypeDefinition();
    break;     

  case IIR_FLOATING_POINT_LITERAL32:
    retv = new IIRScram_FloatingPointLiteral32();
    break;     

  case IIR_FLOATING_POINT_LITERAL64:
    retv = new IIRScram_FloatingPointLiteral64();
    break;     

  case IIR_FLOATING_POINT_LITERAL:
    retv = new IIRScram_FloatingPointLiteral();
    break;     

  case IIR_FLOATING_SUBTYPE_DEFINITION:
    retv = new IIRScram_FloatingSubtypeDefinition();
    break;     

  case IIR_FLOATING_TYPE_DEFINITION:
    retv = new IIRScram_FloatingTypeDefinition();
    break;     

  case IIR_FOR_LOOP_STATEMENT:
    retv = new IIRScram_ForLoopStatement();
    break;     

  case IIR_FREE_QUANTITY_DECLARATION:
    retv = new IIRScram_FreeQuantityDeclaration();
    break;     

  case IIR_FUNCTION_CALL:
    retv = new IIRScram_FunctionCall();
    break;     

  case IIR_FUNCTION_DECLARATION:
    retv = new IIRScram_FunctionDeclaration();
    break;     

  case IIR_GENERIC_LIST:
    retv = new IIRScram_GenericList();
    break;     

  case IIR_GREATER_THAN_OPERATOR:
    retv = new IIRScram_GreaterThanOperator();
    break;     

  case IIR_GREATER_THAN_OR_EQUAL_OPERATOR:
    retv = new IIRScram_GreaterThanOrEqualOperator();
    break;     

  case IIR_GROUP_CONSTITUENT:
    retv = new IIRScram_GroupConstituent();
    break;     

  case IIR_GROUP_DECLARATION:
    retv = new IIRScram_GroupDeclaration();
    break;     

  case IIR_GROUP_TEMPLATE_DECLARATION:
    retv = new IIRScram_GroupTemplateDeclaration();
    break;     

  case IIR_HIGH_ATTRIBUTE:
    retv = new IIRScram_HighAttribute();
    break;     

  case IIR_IDENTIFIER:
    retv = new IIRScram_Identifier();
    break;     

  case IIR_IDENTIFIER_LIST:
    retv = new IIRScram_IdentifierList();
    break;     

  case IIR_IDENTITY_OPERATOR:
    retv = new IIRScram_IdentityOperator();
    break;     

  case IIR_IF_STATEMENT:
    retv = new IIRScram_IfStatement();
    break;     

  case IIR_IMAGE_ATTRIBUTE:
    retv = new IIRScram_ImageAttribute();
    break;     

  case IIR_INCOMPLETE_TYPE_DEFINITION:
    retv = new IIRScram_IncompleteTypeDefinition();
    break;     

  case IIR_INDEXED_NAME:
    retv = new IIRScram_IndexedName();
    break;     

  case IIR_INEQUALITY_OPERATOR:
    retv = new IIRScram_InequalityOperator();
    break;     

  case IIR_INSTANCE_NAME_ATTRIBUTE:
    retv = new IIRScram_InstanceNameAttribute();
    break;     

  case IIR_INTEGER_LITERAL32:
    retv = new IIRScram_IntegerLiteral32();
    break;     

  case IIR_INTEGER_LITERAL64:
    retv = new IIRScram_IntegerLiteral64();
    break;     

  case IIR_INTEGER_LITERAL:
    retv = new IIRScram_IntegerLiteral();
    break;     

  case IIR_INTEGER_SUBTYPE_DEFINITION:
    retv = new IIRScram_IntegerSubtypeDefinition();
    break;     

  case IIR_INTEGER_TYPE_DEFINITION:
    retv = new IIRScram_IntegerTypeDefinition();
    break;     

  case IIR_INTERFACE_LIST:
    retv = new IIRScram_InterfaceList();
    break;     

  case IIR_LABEL:
    retv = new IIRScram_Label();
    break;     

  case IIR_LAST_ACTIVE_ATTRIBUTE:
    retv = new IIRScram_LastActiveAttribute();
    break;     

  case IIR_LAST_EVENT_ATTRIBUTE:
    retv = new IIRScram_LastEventAttribute();
    break;     

  case IIR_LAST_VALUE_ATTRIBUTE:
    retv = new IIRScram_LastValueAttribute();
    break;     

  case IIR_LEFT_ATTRIBUTE:
    retv = new IIRScram_LeftAttribute();
    break;     

  case IIR_LEFT_OF_ATTRIBUTE:
    retv = new IIRScram_LeftOfAttribute();
    break;     

  case IIR_LENGTH_ATTRIBUTE:
    retv = new IIRScram_LengthAttribute();
    break;     

  case IIR_LESS_THAN_OPERATOR:
    retv = new IIRScram_LessThanOperator();
    break;     

  case IIR_LESS_THAN_OR_EQUAL_OPERATOR:
    retv = new IIRScram_LessThanOrEqualOperator();
    break;     

  case IIR_LIBRARY_CLAUSE:
    retv = new IIRScram_LibraryClause();
    break;     

  case IIR_LIBRARY_DECLARATION:
    retv = new IIRScram_LibraryDeclaration();
    break;     

  case IIR_LIBRARY_UNIT_LIST:
    retv = new IIRScram_LibraryUnitList();
    break;     

  case IIR_LITERAL:
    retv = new IIRScram_Literal();
    break;     

  case IIR_LTF_ATTRIBUTE:
    retv = new IIRScram_LTFAttribute();
    break;     

  case IIR_LOW_ATTRIBUTE:
    retv = new IIRScram_LowAttribute();
    break;     

  case IIR_MODULUS_OPERATOR:
    retv = new IIRScram_ModulusOperator();
    break;     

  case IIR_MULTIPLICATION_OPERATOR:
    retv = new IIRScram_MultiplicationOperator();
    break;     

  case IIR_NAME:
    retv = new IIRScram_Name();
    break;     

  case IIR_NAME_LIST:
    retv = new IIRScram_NameList();
    break;     

  case IIR_NAND_OPERATOR:
    retv = new IIRScram_NandOperator();
    break;     

  case IIR_NATURE_DECLARATION:
    retv = new IIRScram_NatureDeclaration();
    break;     

  case IIR_NATURE_DEFINITION:
    retv = new IIRScram_NatureDefinition();
    break;     

  case IIR_NEGATION_OPERATOR:
    retv = new IIRScram_NegationOperator();
    break;     

  case IIR_NEXT_STATEMENT:
    retv = new IIRScram_NextStatement();
    break;     

  case IIR_NOR_OPERATOR:
    retv = new IIRScram_NorOperator();
    break;     

  case IIR_NOT_OPERATOR:
    retv = new IIRScram_NotOperator();
    break;     

  case IIR_NULL_STATEMENT:
    retv = new IIRScram_NullStatement();
    break;     

  case IIR_OR_OPERATOR:
    retv = new IIRScram_OrOperator();
    break;     

  case IIR_OTHERS_INITIALIZATION:
    retv = new IIRScram_OthersInitialization();
    break;     

  case IIR_PACKAGE_BODY_DECLARATION:
    retv = new IIRScram_PackageBodyDeclaration();
    break;     

  case IIR_PACKAGE_DECLARATION:
    retv = new IIRScram_PackageDeclaration();
    break;     

  case IIR_PATH_NAME_ATTRIBUTE:
    retv = new IIRScram_PathNameAttribute();
    break;     

  case IIR_PHYSICAL_LITERAL:
    retv = new IIRScram_PhysicalLiteral();
    break;     

  case IIR_PHYSICAL_SUBTYPE_DEFINITION:
    retv = new IIRScram_PhysicalSubtypeDefinition();
    break;     

  case IIR_PHYSICAL_TYPE_DEFINITION:
    retv = new IIRScram_PhysicalTypeDefinition();
    break;     

  case IIR_PHYSICAL_UNIT:
    retv = new IIRScram_PhysicalUnit();
    break;     

  case IIR_PORT_LIST:
    retv = new IIRScram_PortList();
    break;     

  case IIR_POS_ATTRIBUTE:
    retv = new IIRScram_PosAttribute();
    break;     

  case IIR_PRED_ATTRIBUTE:
    retv = new IIRScram_PredAttribute();
    break;     

  case IIR_PROCEDURE_CALL_STATEMENT:
    retv = new IIRScram_ProcedureCallStatement();
    break;     

  case IIR_PROCEDURE_DECLARATION:
    retv = new IIRScram_ProcedureDeclaration();
    break;     

  case IIR_PROCESS_STATEMENT:
    retv = new IIRScram_ProcessStatement();
    break;     

  case IIR_QUALIFIED_EXPRESSION:
    retv = new IIRScram_QualifiedExpression();
    break;     

  case IIR_QUANTITY_DECLARATION:
    retv = new IIRScram_QuantityDeclaration();
    break;     

  case IIR_QUIET_ATTRIBUTE:
    retv = new IIRScram_QuietAttribute();
    break;     

  case IIR_RANGE_ATTRIBUTE:
    retv = new IIRScram_RangeAttribute();
    break;     

  case IIR_RANGE_TYPE_DEFINITION:
    retv = new IIRScram_RangeTypeDefinition();
    break;     

  case IIR_RECORD_TYPE_DEFINITION:
    retv = new IIRScram_RecordTypeDefinition();
    break;     

  case IIR_REFERENCE_ATTRIBUTE:
    retv = new IIRScram_ReferenceAttribute();
    break;     

  case IIR_REMAINDER_OPERATOR:
    retv = new IIRScram_RemainderOperator();
    break;     

  case IIR_REPORT_STATEMENT:
    retv = new IIRScram_ReportStatement();
    break;     

  case IIR_RETURN_STATEMENT:
    retv = new IIRScram_ReturnStatement();
    break;     

  case IIR_REVERSE_RANGE_ATTRIBUTE:
    retv = new IIRScram_ReverseRangeAttribute();
    break;     

  case IIR_RIGHT_ATTRIBUTE:
    retv = new IIRScram_RightAttribute();
    break;     

  case IIR_RIGHT_OF_ATTRIBUTE:
    retv = new IIRScram_RightOfAttribute();
    break;     

  case IIR_ROL_OPERATOR:
    retv = new IIRScram_ROLOperator();
    break;     

  case IIR_ROR_OPERATOR:
    retv = new IIRScram_ROROperator();
    break;     

  case IIR_SCALAR_NATURE_DEFINITION:
    retv = new IIRScram_ScalarNatureDefinition();
    break;     

  case IIR_SELECTED_NAME_BY_ALL:
    retv = new IIRScram_SelectedNameByAll();
    break;     

  case IIR_SELECTED_NAME:
    retv = new IIRScram_SelectedName();
    break;     

  case IIR_SELECTED_WAVEFORM:
    retv = new IIRScram_SelectedWaveform();
    break;     

  case IIR_SELECTED_WAVEFORM_LIST:
    retv = new IIRScram_SelectedWaveformList();
    break;     

  case IIR_SENSITIZED_PROCESS_STATEMENT:
    retv = new IIRScram_SensitizedProcessStatement();
    break;     

  case IIR_SEQUENTIAL_STATEMENT_LIST:
    retv = new IIRScram_SequentialStatementList();
    break;     

  case IIR_SHARED_VARIABLE_DECLARATION:
    retv = new IIRScram_SharedVariableDeclaration();
    break;     

  case IIR_SIGNAL_ASSIGNMENT_STATEMENT:
    retv = new IIRScram_SignalAssignmentStatement();
    break;     

  case IIR_SIGNAL_DECLARATION:
    retv = new IIRScram_SignalDeclaration();
    break;     

  case IIR_SIGNAL_INTERFACE_DECLARATION:
    retv = new IIRScram_SignalInterfaceDeclaration();
    break;     

  case IIR_SIGNATURE:
    retv = new IIRScram_Signature();
    break;     

  case IIR_SIMPLE_NAME_ATTRIBUTE:
    retv = new IIRScram_SimpleNameAttribute();
    break;     

  case IIR_SIMPLE_NAME:
    retv = new IIRScram_SimpleName();
    break;     

  case IIR_SIMPLE_SIMULTANEOUS_STATEMENT:
    retv = new IIRScram_SimpleSimultaneousStatement();
    break;     

  case IIR_SIMULTANEOUS_IF_STATEMENT:
    retv = new IIRScram_SimultaneousIfStatement();
    break;     

  case IIR_SLA_OPERATOR:
    retv = new IIRScram_SLAOperator();
    break;     

  case IIR_SLICE_NAME:
    retv = new IIRScram_SliceName();
    break;     

  case IIR_SLL_OPERATOR:
    retv = new IIRScram_SLLOperator();
    break;     

  case IIR_SOURCE_QUANTITY_DECLARATION:
    retv = new IIRScram_SourceQuantityDeclaration();
    break;     

  case IIR_SRA_OPERATOR:
    retv = new IIRScram_SRAOperator();
    break;     

  case IIR_SRL_OPERATOR:
    retv = new IIRScram_SRLOperator();
    break;     

  case IIR_STABLE_ATTRIBUTE:
    retv = new IIRScram_StableAttribute();
    break;     

  case IIR_STRING_LITERAL:
    retv = new IIRScram_StringLiteral();
    break;     

  case IIR_SUBPROGRAM_DECLARATION:
    retv = new IIRScram_SubprogramDeclaration();
    break;     

  case IIR_SUBTRACTION_OPERATOR:
    retv = new IIRScram_SubtractionOperator();
    break;     

  case IIR_SUBTYPE_DECLARATION:
    retv = new IIRScram_SubtypeDeclaration();
    break;     

  case IIR_SUCC_ATTRIBUTE:
    retv = new IIRScram_SuccAttribute();
    break;     

  case IIR_TERMINAL_DECLARATION:
    retv = new IIRScram_TerminalDeclaration();
    break;     

  case IIR_TERMINAL_INTERFACE_DECLARATION:
    retv = new IIRScram_TerminalInterfaceDeclaration();
    break;     

  case IIR_THROUGH_ATTRIBUTE:
    retv = new IIRScram_ThroughAttribute();
    break;     

  case IIR_TRANSACTION_ATTRIBUTE:
    retv = new IIRScram_TransactionAttribute();
    break;     

  case IIR_TUPLE:
    retv = new IIRScram_Tuple();
    break;     

  case IIR_TYPE_CONVERSION:
    retv = new IIRScram_TypeConversion();
    break;     

  case IIR_TYPE_DECLARATION:
    retv = new IIRScram_TypeDeclaration();
    break;     

  case IIR_UNIT_LIST:
    retv = new IIRScram_UnitList();
    break;     

  case IIR_USE_CLAUSE:
    retv = new IIRScram_UseClause();
    break;     

  case IIR_USER_ATTRIBUTE:
    retv = new IIRScram_UserAttribute();
    break;     

  case IIR_VAL_ATTRIBUTE:
    retv = new IIRScram_ValAttribute();
    break;     

  case IIR_VALUE_ATTRIBUTE:
    retv = new IIRScram_ValueAttribute();
    break;     

  case IIR_VARIABLE_ASSIGNMENT_STATEMENT:
    retv = new IIRScram_VariableAssignmentStatement();
    break;     

  case IIR_VARIABLE_DECLARATION:
    retv = new IIRScram_VariableDeclaration();
    break;     

  case IIR_VARIABLE_INTERFACE_DECLARATION:
    retv = new IIRScram_VariableInterfaceDeclaration();
    break;     

  case IIR_WAIT_STATEMENT:
    retv = new IIRScram_WaitStatement();
    break;     

  case IIR_WAVEFORM_ELEMENT:
    retv = new IIRScram_WaveformElement();
    break;     

  case IIR_WAVEFORM_LIST:
    retv = new IIRScram_WaveformList();
    break;     

  case IIR_WHILE_LOOP_STATEMENT:
    retv = new IIRScram_WhileLoopStatement();
    break;     

  case IIR_XNOR_OPERATOR:
    retv = new IIRScram_XnorOperator();
    break;     

  case IIR_XOR_OPERATOR:
    retv = new IIRScram_XorOperator();
    break;     

  case IIR_ZTF_ATTRIBUTE:
    retv = new IIRScram_ZTFAttribute();
    break;     

  default:
    // Attempted to create an unknown type of node
    ASSERT(0);    
  }

  return retv;
}

StandardPackage *
scram_plugin_class_factory::get_standard_package() {
  return ScramStandardPackage::instance();
}

StandardPackage *
scram_plugin_class_factory::new_StandardPackage() {
 // return new ScramStandardPackage();
 // Shouldn't we return a static instance of ScramStandardPackage? Ruda
 return ScramStandardPackage::instance(); //DRH
}

IIR_AboveAttribute *
scram_plugin_class_factory::new_IIR_AboveAttribute() {
  return new IIRScram_AboveAttribute();
}

IIR_AbsoluteOperator *
scram_plugin_class_factory::new_IIR_AbsoluteOperator() {
  return new IIRScram_AbsoluteOperator();
}

IIR_AccessSubtypeDefinition *
scram_plugin_class_factory::new_IIR_AccessSubtypeDefinition() {
  return new IIRScram_AccessSubtypeDefinition();
}

IIR_AccessTypeDefinition *
scram_plugin_class_factory::new_IIR_AccessTypeDefinition() {
  return new IIRScram_AccessTypeDefinition();
}

IIR_AcrossAttribute *
scram_plugin_class_factory::new_IIR_AcrossAttribute() {
  return new IIRScram_AcrossAttribute();
}

IIR_ActiveAttribute *
scram_plugin_class_factory::new_IIR_ActiveAttribute() {
  return new IIRScram_ActiveAttribute();
}

IIR_AdditionOperator *
scram_plugin_class_factory::new_IIR_AdditionOperator() {
  return new IIRScram_AdditionOperator();
}

IIR_Aggregate *
scram_plugin_class_factory::new_IIR_Aggregate(){
  return new IIRScram_Aggregate();
}

IIR_AliasDeclaration *
scram_plugin_class_factory::new_IIR_AliasDeclaration(){
  return new IIRScram_AliasDeclaration();
}

IIR_Allocator *
scram_plugin_class_factory::new_IIR_Allocator(){
  return new IIRScram_Allocator();
}

IIR_AndOperator *
scram_plugin_class_factory::new_IIR_AndOperator(){
  return new IIRScram_AndOperator();
}

IIR_ArchitectureDeclaration *
scram_plugin_class_factory::new_IIR_ArchitectureDeclaration(){
  return new IIRScram_ArchitectureDeclaration();
}

IIR_ArchitectureStatement *
scram_plugin_class_factory::new_IIR_ArchitectureStatement(){
  return new IIRScram_ArchitectureStatement();
}

IIR_ArchitectureStatementList *
scram_plugin_class_factory::new_IIR_ArchitectureStatementList(){
  return new IIRScram_ArchitectureStatementList();
}

IIR_ArrayNatureDefinition *
scram_plugin_class_factory::new_IIR_ArrayNatureDefinition(){
  return new IIRScram_ArrayNatureDefinition();
}

IIR_ArraySubnatureDefinition *
scram_plugin_class_factory::new_IIR_ArraySubnatureDefinition(){
  return new IIRScram_ArraySubnatureDefinition();
}

IIR_ArraySubtypeDefinition *
scram_plugin_class_factory::new_IIR_ArraySubtypeDefinition(){
  return new IIRScram_ArraySubtypeDefinition();
}

IIR_ArrayTypeDefinition *
scram_plugin_class_factory::new_IIR_ArrayTypeDefinition(){
  return new IIRScram_ArrayTypeDefinition();
}

IIR_AscendingAttribute *
scram_plugin_class_factory::new_IIR_AscendingAttribute(){
  return new IIRScram_AscendingAttribute();
}

IIR_AssertionStatement *
scram_plugin_class_factory::new_IIR_AssertionStatement(){
  return new IIRScram_AssertionStatement();
}

IIR_AssociationElementByExpression *
scram_plugin_class_factory::new_IIR_AssociationElementByExpression(){
  return new IIRScram_AssociationElementByExpression();
}

IIR_AssociationElementOpen *
scram_plugin_class_factory::new_IIR_AssociationElementOpen(){
  return new IIRScram_AssociationElementOpen();
}

IIR_AssociationList *
scram_plugin_class_factory::new_IIR_AssociationList(){
  return new IIRScram_AssociationList();
}

IIR_AttributeDeclaration *
scram_plugin_class_factory::new_IIR_AttributeDeclaration(){
  return new IIRScram_AttributeDeclaration();
}

IIR_AttributeSpecification *
scram_plugin_class_factory::new_IIR_AttributeSpecification(){
  return new IIRScram_AttributeSpecification();
}

IIR_AttributeSpecificationList *
scram_plugin_class_factory::new_IIR_AttributeSpecificationList(){
  return new IIRScram_AttributeSpecificationList();
}

IIR_BaseAttribute *
scram_plugin_class_factory::new_IIR_BaseAttribute(){
  return new IIRScram_BaseAttribute();
}

IIR_BitStringLiteral *
scram_plugin_class_factory::new_IIR_BitStringLiteral(){
  return new IIRScram_BitStringLiteral();
}

IIR_BlockConfiguration *
scram_plugin_class_factory::new_IIR_BlockConfiguration(){
  return new IIRScram_BlockConfiguration();
}

IIR_BlockStatement *
scram_plugin_class_factory::new_IIR_BlockStatement(){
  return new IIRScram_BlockStatement();
}

IIR_BranchQuantityDeclaration *
scram_plugin_class_factory::new_IIR_BranchQuantityDeclaration(){
  return new IIRScram_BranchQuantityDeclaration();
}

IIR_BreakElement *
scram_plugin_class_factory::new_IIR_BreakElement(){
  return new IIRScram_BreakElement();
}

IIR_BreakStatement *
scram_plugin_class_factory::new_IIR_BreakStatement(){
  return new IIRScram_BreakStatement();
}

IIR_CaseStatementAlternativeByChoices *
scram_plugin_class_factory::new_IIR_CaseStatementAlternativeByChoices() {
  return new IIRScram_CaseStatementAlternativeByChoices();
}

IIR_CaseStatementAlternativeByExpression *
scram_plugin_class_factory::new_IIR_CaseStatementAlternativeByExpression() {
  return new IIRScram_CaseStatementAlternativeByExpression();
}

IIR_CaseStatementAlternativeByOthers *
scram_plugin_class_factory::new_IIR_CaseStatementAlternativeByOthers() {
  return new IIRScram_CaseStatementAlternativeByOthers();
}

IIR_CaseStatementAlternativeList *
scram_plugin_class_factory::new_IIR_CaseStatementAlternativeList() {
  return new IIRScram_CaseStatementAlternativeList();
}

IIR_CaseStatement *
scram_plugin_class_factory::new_IIR_CaseStatement() {
  return new IIRScram_CaseStatement();
}

IIR_CharacterLiteral *
scram_plugin_class_factory::new_IIR_CharacterLiteral() {
  return new IIRScram_CharacterLiteral();
}

IIR_Choice *
scram_plugin_class_factory::new_IIR_Choice() {
  return new IIRScram_Choice();
}

IIR_ChoiceList *
scram_plugin_class_factory::new_IIR_ChoiceList() {
  return new IIRScram_ChoiceList();
}

IIR_Comment *
scram_plugin_class_factory::new_IIR_Comment() {
  return new IIRScram_Comment();
}

IIR_CommentList *
scram_plugin_class_factory::new_IIR_CommentList() {
  return new IIRScram_CommentList();
}

IIR_ComponentConfiguration *
scram_plugin_class_factory::new_IIR_ComponentConfiguration() {
  return new IIRScram_ComponentConfiguration();
}

IIR_ComponentDeclaration *
scram_plugin_class_factory::new_IIR_ComponentDeclaration() {
  return new IIRScram_ComponentDeclaration();
}

IIR_ComponentInstantiationStatement *
scram_plugin_class_factory::new_IIR_ComponentInstantiationStatement() {
  return new IIRScram_ComponentInstantiationStatement();
}

IIR_ConcatenationOperator *
scram_plugin_class_factory::new_IIR_ConcatenationOperator() {
  return new IIRScram_ConcatenationOperator();
}

IIR_ConcurrentAssertionStatement *
scram_plugin_class_factory::new_IIR_ConcurrentAssertionStatement() {
  return new IIRScram_ConcurrentAssertionStatement();
}

IIR_ConcurrentBreakStatement *
scram_plugin_class_factory::new_IIR_ConcurrentBreakStatement() {
  return new IIRScram_ConcurrentBreakStatement();
}

IIR_ConcurrentConditionalSignalAssignment *
scram_plugin_class_factory::new_IIR_ConcurrentConditionalSignalAssignment() {
  return new IIRScram_ConcurrentConditionalSignalAssignment();
}

IIR_ConcurrentGenerateForStatement *
scram_plugin_class_factory::new_IIR_ConcurrentGenerateForStatement() {
  return new IIRScram_ConcurrentGenerateForStatement();
}

IIR_ConcurrentGenerateIfStatement *
scram_plugin_class_factory::new_IIR_ConcurrentGenerateIfStatement() {
  return new IIRScram_ConcurrentGenerateIfStatement();
}

IIR_ConcurrentProcedureCallStatement *
scram_plugin_class_factory::new_IIR_ConcurrentProcedureCallStatement() {
  return new IIRScram_ConcurrentProcedureCallStatement();
}

IIR_ConcurrentSelectedSignalAssignment *
scram_plugin_class_factory::new_IIR_ConcurrentSelectedSignalAssignment() {
  return new IIRScram_ConcurrentSelectedSignalAssignment();
}

IIR_ConditionalWaveform *
scram_plugin_class_factory::new_IIR_ConditionalWaveform() {
  return new IIRScram_ConditionalWaveform();
}

IIR_ConditionalWaveformList *
scram_plugin_class_factory::new_IIR_ConditionalWaveformList() {
  return new IIRScram_ConditionalWaveformList();
}

IIR_ConfigurationDeclaration *
scram_plugin_class_factory::new_IIR_ConfigurationDeclaration() {
  return new IIRScram_ConfigurationDeclaration();
}

IIR_ConfigurationItem *
scram_plugin_class_factory::new_IIR_ConfigurationItem() {
  return new IIRScram_ConfigurationItem();
}

IIR_ConfigurationItemList *
scram_plugin_class_factory::new_IIR_ConfigurationItemList() {
  return new IIRScram_ConfigurationItemList();
}

IIR_ConfigurationSpecification *
scram_plugin_class_factory::new_IIR_ConfigurationSpecification() {
  return new IIRScram_ConfigurationSpecification();
}

IIR_ContributionAttribute *
scram_plugin_class_factory::new_IIR_ContributionAttribute() {
  return new IIRScram_ContributionAttribute();
}

IIR_ConstantDeclaration *
scram_plugin_class_factory::new_IIR_ConstantDeclaration() {
  return new IIRScram_ConstantDeclaration();
}

IIR_ConstantInterfaceDeclaration *
scram_plugin_class_factory::new_IIR_ConstantInterfaceDeclaration() {
  return new IIRScram_ConstantInterfaceDeclaration();
}

IIR_DeclarationList *
scram_plugin_class_factory::new_IIR_DeclarationList() {
  return new IIRScram_DeclarationList();
}

IIR_DelayedAttribute *
scram_plugin_class_factory::new_IIR_DelayedAttribute() {
  return new IIRScram_DelayedAttribute();
}

IIR_DesignatorByAll *
scram_plugin_class_factory::new_IIR_DesignatorByAll() {
  return new IIRScram_DesignatorByAll();
}

IIR_DesignatorByOthers *
scram_plugin_class_factory::new_IIR_DesignatorByOthers() {
  return new IIRScram_DesignatorByOthers();
}

IIR_DesignatorExplicit *
scram_plugin_class_factory::new_IIR_DesignatorExplicit() {
  return new IIRScram_DesignatorExplicit();
}

IIR_Designator *
scram_plugin_class_factory::new_IIR_Designator() {
  return new IIRScram_Designator();
}

IIR_DesignatorList *
scram_plugin_class_factory::new_IIR_DesignatorList() {
  return new IIRScram_DesignatorList();
}

IIR_DesignFile *
scram_plugin_class_factory::new_IIR_DesignFile() {
  return new IIRScram_DesignFile();
}

IIR_DesignFileList *
scram_plugin_class_factory::new_IIR_DesignFileList() {
  return new IIRScram_DesignFileList();
}

IIR_DesignUnitList *
scram_plugin_class_factory::new_IIR_DesignUnitList() {
  return new IIRScram_DesignUnitList();
}

IIR_DisconnectSpecification *
scram_plugin_class_factory::new_IIR_DisconnectSpecification() {
  return new IIRScram_DisconnectSpecification();
}

IIR_DivisionOperator *
scram_plugin_class_factory::new_IIR_DivisionOperator() {
  return new IIRScram_DivisionOperator();
}

IIR_DotAttribute *
scram_plugin_class_factory::new_IIR_DotAttribute() {
  return new IIRScram_DotAttribute();
}

IIR_DrivingAttribute *
scram_plugin_class_factory::new_IIR_DrivingAttribute() {
  return new IIRScram_DrivingAttribute();
}

IIR_DrivingValueAttribute *
scram_plugin_class_factory::new_IIR_DrivingValueAttribute() {
  return new IIRScram_DrivingValueAttribute();
}

IIR_ElementDeclaration *
scram_plugin_class_factory::new_IIR_ElementDeclaration() {
  return new IIRScram_ElementDeclaration();
}

IIR_ElementDeclarationList *
scram_plugin_class_factory::new_IIR_ElementDeclarationList() {
  return new IIRScram_ElementDeclarationList();
}

IIR_Elsif *
scram_plugin_class_factory::new_IIR_Elsif() {
  return new IIRScram_Elsif();
}

IIR_EntityClassEntry *
scram_plugin_class_factory::new_IIR_EntityClassEntry() {
  return new IIRScram_EntityClassEntry();
}

IIR_EntityClassEntryList *
scram_plugin_class_factory::new_IIR_EntityClassEntryList() {
  return new IIRScram_EntityClassEntryList();
}

IIR_EntityDeclaration *
scram_plugin_class_factory::new_IIR_EntityDeclaration() {
  return new IIRScram_EntityDeclaration();
}

IIR_EntityNameList *
scram_plugin_class_factory::new_IIR_EntityNameList() {
  return new IIRScram_EntityNameList();
}

IIR_EnumerationLiteral *
scram_plugin_class_factory::new_IIR_EnumerationLiteral() {
  return new IIRScram_EnumerationLiteral();
}

IIR_EnumerationLiteralList *
scram_plugin_class_factory::new_IIR_EnumerationLiteralList() {
  return new IIRScram_EnumerationLiteralList();
}

IIR_EnumerationSubtypeDefinition *
scram_plugin_class_factory::new_IIR_EnumerationSubtypeDefinition() {
  return new IIRScram_EnumerationSubtypeDefinition();
}

IIR_EnumerationTypeDefinition *
scram_plugin_class_factory::new_IIR_EnumerationTypeDefinition() {
  return new IIRScram_EnumerationTypeDefinition();
}

IIR_EqualityOperator *
scram_plugin_class_factory::new_IIR_EqualityOperator() {
  return new IIRScram_EqualityOperator();
}

IIR_EventAttribute *
scram_plugin_class_factory::new_IIR_EventAttribute() {
  return new IIRScram_EventAttribute();
}

IIR_ExitStatement *
scram_plugin_class_factory::new_IIR_ExitStatement() {
  return new IIRScram_ExitStatement();
}

IIR_ExponentiationOperator *
scram_plugin_class_factory::new_IIR_ExponentiationOperator() {
  return new IIRScram_ExponentiationOperator();
}

IIR_FileDeclaration *
scram_plugin_class_factory::new_IIR_FileDeclaration() {
  return new IIRScram_FileDeclaration();
}

IIR_FileInterfaceDeclaration *
scram_plugin_class_factory::new_IIR_FileInterfaceDeclaration() {
  return new IIRScram_FileInterfaceDeclaration();
}

IIR_FileTypeDefinition *
scram_plugin_class_factory::new_IIR_FileTypeDefinition() {
  return new IIRScram_FileTypeDefinition();
}

IIR_FloatingPointLiteral32 *
scram_plugin_class_factory::new_IIR_FloatingPointLiteral32() {
  return new IIRScram_FloatingPointLiteral32();
}

IIR_FloatingPointLiteral64 *
scram_plugin_class_factory::new_IIR_FloatingPointLiteral64() {
  return new IIRScram_FloatingPointLiteral64();
}

IIR_FloatingPointLiteral *
scram_plugin_class_factory::new_IIR_FloatingPointLiteral() {
  return new IIRScram_FloatingPointLiteral();
}

IIR_FloatingSubtypeDefinition *
scram_plugin_class_factory::new_IIR_FloatingSubtypeDefinition() {
  return new IIRScram_FloatingSubtypeDefinition();
}

IIR_FloatingTypeDefinition *
scram_plugin_class_factory::new_IIR_FloatingTypeDefinition() {
  return new IIRScram_FloatingTypeDefinition();
}

IIR_ForLoopStatement *
scram_plugin_class_factory::new_IIR_ForLoopStatement() {
  return new IIRScram_ForLoopStatement();
}

IIR_FreeQuantityDeclaration *
scram_plugin_class_factory::new_IIR_FreeQuantityDeclaration() {
  return new IIRScram_FreeQuantityDeclaration();
}

IIR_FunctionCall *
scram_plugin_class_factory::new_IIR_FunctionCall() {
  return new IIRScram_FunctionCall();
}

IIR_FunctionDeclaration *
scram_plugin_class_factory::new_IIR_FunctionDeclaration() {
  return new IIRScram_FunctionDeclaration();
}

IIR_GenericList *
scram_plugin_class_factory::new_IIR_GenericList() {
  return new IIRScram_GenericList();
}

IIR_GreaterThanOperator *
scram_plugin_class_factory::new_IIR_GreaterThanOperator() {
  return new IIRScram_GreaterThanOperator();
}

IIR_GreaterThanOrEqualOperator *
scram_plugin_class_factory::new_IIR_GreaterThanOrEqualOperator() {
  return new IIRScram_GreaterThanOrEqualOperator();
}

IIR_GroupConstituent *
scram_plugin_class_factory::new_IIR_GroupConstituent() {
  return new IIRScram_GroupConstituent();
}

IIR_GroupDeclaration *
scram_plugin_class_factory::new_IIR_GroupDeclaration() {
  return new IIRScram_GroupDeclaration();
}

IIR_GroupTemplateDeclaration *
scram_plugin_class_factory::new_IIR_GroupTemplateDeclaration() {
  return new IIRScram_GroupTemplateDeclaration();
}

IIR_HighAttribute *
scram_plugin_class_factory::new_IIR_HighAttribute() {
  return new IIRScram_HighAttribute();
}

IIR_Identifier *
scram_plugin_class_factory::new_IIR_Identifier() {
  return new IIRScram_Identifier();
}

IIR_IdentifierList *
scram_plugin_class_factory::new_IIR_IdentifierList() {
  return new IIRScram_IdentifierList();
}

IIR_IdentityOperator *
scram_plugin_class_factory::new_IIR_IdentityOperator() {
  return new IIRScram_IdentityOperator();
}

IIR_IfStatement *
scram_plugin_class_factory::new_IIR_IfStatement() {
  return new IIRScram_IfStatement();
}

IIR_ImageAttribute *
scram_plugin_class_factory::new_IIR_ImageAttribute() {
  return new IIRScram_ImageAttribute();
}

IIR_IncompleteTypeDefinition *
scram_plugin_class_factory::new_IIR_IncompleteTypeDefinition() {
  return new IIRScram_IncompleteTypeDefinition();
}

IIR_IndexedName *
scram_plugin_class_factory::new_IIR_IndexedName() {
  return new IIRScram_IndexedName();
}

IIR_InequalityOperator *
scram_plugin_class_factory::new_IIR_InequalityOperator() {
  return new IIRScram_InequalityOperator();
}

IIR_InstanceNameAttribute *
scram_plugin_class_factory::new_IIR_InstanceNameAttribute() {
  return new IIRScram_InstanceNameAttribute();
}

IIR_IntegerLiteral32 *
scram_plugin_class_factory::new_IIR_IntegerLiteral32() {
  return new IIRScram_IntegerLiteral32();
}

IIR_IntegerLiteral64 *
scram_plugin_class_factory::new_IIR_IntegerLiteral64() {
  return new IIRScram_IntegerLiteral64();
}

IIR_IntegerLiteral *
scram_plugin_class_factory::new_IIR_IntegerLiteral() {
  return new IIRScram_IntegerLiteral();
}

IIR_IntegerSubtypeDefinition *
scram_plugin_class_factory::new_IIR_IntegerSubtypeDefinition() {
  return new IIRScram_IntegerSubtypeDefinition();
}

IIR_IntegerTypeDefinition *
scram_plugin_class_factory::new_IIR_IntegerTypeDefinition() {
  return new IIRScram_IntegerTypeDefinition();
}

IIR_InterfaceList *
scram_plugin_class_factory::new_IIR_InterfaceList() {
  return new IIRScram_InterfaceList();
}

IIR_Label *
scram_plugin_class_factory::new_IIR_Label() {
  return new IIRScram_Label();
}

IIR_LastActiveAttribute *
scram_plugin_class_factory::new_IIR_LastActiveAttribute() {
  return new IIRScram_LastActiveAttribute();
}

IIR_LastEventAttribute *
scram_plugin_class_factory::new_IIR_LastEventAttribute() {
  return new IIRScram_LastEventAttribute();
}

IIR_LastValueAttribute *
scram_plugin_class_factory::new_IIR_LastValueAttribute() {
  return new IIRScram_LastValueAttribute();
}

IIR_LeftAttribute *
scram_plugin_class_factory::new_IIR_LeftAttribute() {
  return new IIRScram_LeftAttribute();
}

IIR_LeftOfAttribute *
scram_plugin_class_factory::new_IIR_LeftOfAttribute() {
  return new IIRScram_LeftOfAttribute();
}

IIR_LengthAttribute *
scram_plugin_class_factory::new_IIR_LengthAttribute() {
  return new IIRScram_LengthAttribute();
}

IIR_LessThanOperator *
scram_plugin_class_factory::new_IIR_LessThanOperator() {
  return new IIRScram_LessThanOperator();
}

IIR_LessThanOrEqualOperator *
scram_plugin_class_factory::new_IIR_LessThanOrEqualOperator() {
  return new IIRScram_LessThanOrEqualOperator();
}

IIR_LibraryClause *
scram_plugin_class_factory::new_IIR_LibraryClause() {
  return new IIRScram_LibraryClause();
}

IIR_LibraryDeclaration *
scram_plugin_class_factory::new_IIR_LibraryDeclaration() {
  return new IIRScram_LibraryDeclaration();
}

IIR_LibraryUnitList *
scram_plugin_class_factory::new_IIR_LibraryUnitList() {
  return new IIRScram_LibraryUnitList();
}

IIR_Literal *
scram_plugin_class_factory::new_IIR_Literal() {
  return new IIRScram_Literal();
}

IIR_LTFAttribute *
scram_plugin_class_factory::new_IIR_LTFAttribute() {
  return new IIRScram_LTFAttribute();
}

IIR_LowAttribute *
scram_plugin_class_factory::new_IIR_LowAttribute() {
  return new IIRScram_LowAttribute();
}

IIR_ModulusOperator *
scram_plugin_class_factory::new_IIR_ModulusOperator() {
  return new IIRScram_ModulusOperator();
}

IIR_MultiplicationOperator *
scram_plugin_class_factory::new_IIR_MultiplicationOperator() {
  return new IIRScram_MultiplicationOperator();
}

IIR_Name *
scram_plugin_class_factory::new_IIR_Name() {
  return new IIRScram_Name();
}

IIR_NameList *
scram_plugin_class_factory::new_IIR_NameList() {
  return new IIRScram_NameList();
}

IIR_NandOperator *
scram_plugin_class_factory::new_IIR_NandOperator() {
  return new IIRScram_NandOperator();
}

IIR_NatureDeclaration *
scram_plugin_class_factory::new_IIR_NatureDeclaration() {
  return new IIRScram_NatureDeclaration();
}

IIR_NatureDefinition *
scram_plugin_class_factory::new_IIR_NatureDefinition() {
  return new IIRScram_NatureDefinition();
}

IIR_NegationOperator *
scram_plugin_class_factory::new_IIR_NegationOperator() {
  return new IIRScram_NegationOperator();
}

IIR_NextStatement *
scram_plugin_class_factory::new_IIR_NextStatement() {
  return new IIRScram_NextStatement();
}

IIR_NorOperator *
scram_plugin_class_factory::new_IIR_NorOperator() {
  return new IIRScram_NorOperator();
}

IIR_NotOperator *
scram_plugin_class_factory::new_IIR_NotOperator() {
  return new IIRScram_NotOperator();
}

IIR_NullStatement *
scram_plugin_class_factory::new_IIR_NullStatement() {
  return new IIRScram_NullStatement();
}

IIR_OrOperator *
scram_plugin_class_factory::new_IIR_OrOperator() {
  return new IIRScram_OrOperator();
}

IIR_OthersInitialization *
scram_plugin_class_factory::new_IIR_OthersInitialization() {
  return new IIRScram_OthersInitialization();
}

IIR_PackageBodyDeclaration *
scram_plugin_class_factory::new_IIR_PackageBodyDeclaration() {
  return new IIRScram_PackageBodyDeclaration();
}

IIR_PackageDeclaration *
scram_plugin_class_factory::new_IIR_PackageDeclaration() {
  return new IIRScram_PackageDeclaration();
}

IIR_PathNameAttribute *
scram_plugin_class_factory::new_IIR_PathNameAttribute() {
  return new IIRScram_PathNameAttribute();
}

IIR_PhysicalLiteral *
scram_plugin_class_factory::new_IIR_PhysicalLiteral() {
  return new IIRScram_PhysicalLiteral();
}

IIR_PhysicalSubtypeDefinition *
scram_plugin_class_factory::new_IIR_PhysicalSubtypeDefinition() {
  return new IIRScram_PhysicalSubtypeDefinition();
}

IIR_PhysicalTypeDefinition *
scram_plugin_class_factory::new_IIR_PhysicalTypeDefinition() {
  return new IIRScram_PhysicalTypeDefinition();
}

IIR_PhysicalUnit *
scram_plugin_class_factory::new_IIR_PhysicalUnit() {
  return new IIRScram_PhysicalUnit();
}

IIR_PortList *
scram_plugin_class_factory::new_IIR_PortList() {
  return new IIRScram_PortList();
}

IIR_PosAttribute *
scram_plugin_class_factory::new_IIR_PosAttribute() {
  return new IIRScram_PosAttribute();
}

IIR_PredAttribute *
scram_plugin_class_factory::new_IIR_PredAttribute() {
  return new IIRScram_PredAttribute();
}

IIR_ProcedureCallStatement *
scram_plugin_class_factory::new_IIR_ProcedureCallStatement() {
  return new IIRScram_ProcedureCallStatement();
}

IIR_ProcedureDeclaration *
scram_plugin_class_factory::new_IIR_ProcedureDeclaration() {
  return new IIRScram_ProcedureDeclaration();
}

IIR_ProcessStatement *
scram_plugin_class_factory::new_IIR_ProcessStatement() {
  return new IIRScram_ProcessStatement();
}

IIR_QualifiedExpression *
scram_plugin_class_factory::new_IIR_QualifiedExpression() {
  return new IIRScram_QualifiedExpression();
}

IIR_QuantityDeclaration *
scram_plugin_class_factory::new_IIR_QuantityDeclaration() {
  return new IIRScram_QuantityDeclaration();
}

IIR_QuietAttribute *
scram_plugin_class_factory::new_IIR_QuietAttribute() {
  return new IIRScram_QuietAttribute();
}

IIR_RangeAttribute *
scram_plugin_class_factory::new_IIR_RangeAttribute() {
  return new IIRScram_RangeAttribute();
}

IIR_RangeTypeDefinition *
scram_plugin_class_factory::new_IIR_RangeTypeDefinition() {
  return new IIRScram_RangeTypeDefinition();
}

IIR_RecordTypeDefinition *
scram_plugin_class_factory::new_IIR_RecordTypeDefinition() {
  return new IIRScram_RecordTypeDefinition();
}

IIR_ReferenceAttribute *
scram_plugin_class_factory::new_IIR_ReferenceAttribute() {
  return new IIRScram_ReferenceAttribute();
}

IIR_RemainderOperator *
scram_plugin_class_factory::new_IIR_RemainderOperator() {
  return new IIRScram_RemainderOperator();
}

IIR_ReportStatement *
scram_plugin_class_factory::new_IIR_ReportStatement() {
  return new IIRScram_ReportStatement();
}

IIR_ReturnStatement *
scram_plugin_class_factory::new_IIR_ReturnStatement() {
  return new IIRScram_ReturnStatement();
}

IIR_ReverseRangeAttribute *
scram_plugin_class_factory::new_IIR_ReverseRangeAttribute() {
  return new IIRScram_ReverseRangeAttribute();
}

IIR_RightAttribute *
scram_plugin_class_factory::new_IIR_RightAttribute() {
  return new IIRScram_RightAttribute();
}

IIR_RightOfAttribute *
scram_plugin_class_factory::new_IIR_RightOfAttribute() {
  return new IIRScram_RightOfAttribute();
}

IIR_ROLOperator *
scram_plugin_class_factory::new_IIR_ROLOperator() {
  return new IIRScram_ROLOperator();
}

IIR_ROROperator *
scram_plugin_class_factory::new_IIR_ROROperator() {
  return new IIRScram_ROROperator();
}

IIR_ScalarNatureDefinition *
scram_plugin_class_factory::new_IIR_ScalarNatureDefinition() {
  return new IIRScram_ScalarNatureDefinition();
}

IIR_SelectedNameByAll *
scram_plugin_class_factory::new_IIR_SelectedNameByAll() {
  return new IIRScram_SelectedNameByAll();
}

IIR_SelectedName *
scram_plugin_class_factory::new_IIR_SelectedName() {
  return new IIRScram_SelectedName();
}

IIR_SelectedWaveform *
scram_plugin_class_factory::new_IIR_SelectedWaveform() {
  return new IIRScram_SelectedWaveform();
}

IIR_SelectedWaveformList *
scram_plugin_class_factory::new_IIR_SelectedWaveformList() {
  return new IIRScram_SelectedWaveformList();
}

IIR_SensitizedProcessStatement *
scram_plugin_class_factory::new_IIR_SensitizedProcessStatement() {
  return new IIRScram_SensitizedProcessStatement();
}

IIR_SequentialStatementList *
scram_plugin_class_factory::new_IIR_SequentialStatementList() {
  return new IIRScram_SequentialStatementList();
}

IIR_SharedVariableDeclaration *
scram_plugin_class_factory::new_IIR_SharedVariableDeclaration() {
  return new IIRScram_SharedVariableDeclaration();
}

IIR_SignalAssignmentStatement *
scram_plugin_class_factory::new_IIR_SignalAssignmentStatement() {
  return new IIRScram_SignalAssignmentStatement();
}

IIR_SignalDeclaration *
scram_plugin_class_factory::new_IIR_SignalDeclaration() {
  return new IIRScram_SignalDeclaration();
}

IIR_SignalInterfaceDeclaration *
scram_plugin_class_factory::new_IIR_SignalInterfaceDeclaration() {
  return new IIRScram_SignalInterfaceDeclaration();
}

IIR_Signature *
scram_plugin_class_factory::new_IIR_Signature() {
  return new IIRScram_Signature();
}

IIR_SimpleNameAttribute *
scram_plugin_class_factory::new_IIR_SimpleNameAttribute() {
  return new IIRScram_SimpleNameAttribute();
}

IIR_SimpleName *
scram_plugin_class_factory::new_IIR_SimpleName() {
  return new IIRScram_SimpleName();
}

IIR_SimpleSimultaneousStatement *
scram_plugin_class_factory::new_IIR_SimpleSimultaneousStatement() {
  return new IIRScram_SimpleSimultaneousStatement();
}

IIR_SimultaneousElsif *
scram_plugin_class_factory::new_IIR_SimultaneousElsif() {
  return new IIRScram_SimultaneousElsif();
}

IIR_SimultaneousIfStatement *
scram_plugin_class_factory::new_IIR_SimultaneousIfStatement() {
  return new IIRScram_SimultaneousIfStatement();
}

IIR_SLAOperator *
scram_plugin_class_factory::new_IIR_SLAOperator() {
  return new IIRScram_SLAOperator();
}

IIR_SliceName *
scram_plugin_class_factory::new_IIR_SliceName() {
  return new IIRScram_SliceName();
}

IIR_SLLOperator *
scram_plugin_class_factory::new_IIR_SLLOperator() {
  return new IIRScram_SLLOperator();
}

IIR_SourceQuantityDeclaration *
scram_plugin_class_factory::new_IIR_SourceQuantityDeclaration() {
  return new IIRScram_SourceQuantityDeclaration();
}

IIR_SRAOperator *
scram_plugin_class_factory::new_IIR_SRAOperator() {
  return new IIRScram_SRAOperator();
}

IIR_SRLOperator *
scram_plugin_class_factory::new_IIR_SRLOperator() {
  return new IIRScram_SRLOperator();
}

IIR_StableAttribute *
scram_plugin_class_factory::new_IIR_StableAttribute() {
  return new IIRScram_StableAttribute();
}

IIR_StringLiteral *
scram_plugin_class_factory::new_IIR_StringLiteral() {
  return new IIRScram_StringLiteral();
}

IIR_SubprogramDeclaration *
scram_plugin_class_factory::new_IIR_SubprogramDeclaration() {
  return new IIRScram_SubprogramDeclaration();
}

IIR_SubtractionOperator *
scram_plugin_class_factory::new_IIR_SubtractionOperator() {
  return new IIRScram_SubtractionOperator();
}

IIR_SubtypeDeclaration *
scram_plugin_class_factory::new_IIR_SubtypeDeclaration() {
  return new IIRScram_SubtypeDeclaration();
}

IIR_SuccAttribute *
scram_plugin_class_factory::new_IIR_SuccAttribute() {
  return new IIRScram_SuccAttribute();
}

IIR_TerminalDeclaration *
scram_plugin_class_factory::new_IIR_TerminalDeclaration() {
  return new IIRScram_TerminalDeclaration();
}

IIR_TerminalInterfaceDeclaration *
scram_plugin_class_factory::new_IIR_TerminalInterfaceDeclaration() {
  return new IIRScram_TerminalInterfaceDeclaration();
}

IIR_TextLiteral *
scram_plugin_class_factory::new_IIR_TextLiteral() {
  return new IIRScram_TextLiteral();
}

IIR_ThroughAttribute *
scram_plugin_class_factory::new_IIR_ThroughAttribute() {
  return new IIRScram_ThroughAttribute();
}

IIR_TransactionAttribute *
scram_plugin_class_factory::new_IIR_TransactionAttribute() {
  return new IIRScram_TransactionAttribute();
}

IIR_Tuple *
scram_plugin_class_factory::new_IIR_Tuple() {
  return new IIRScram_Tuple();
}

IIR_TypeConversion *
scram_plugin_class_factory::new_IIR_TypeConversion() {
  return new IIRScram_TypeConversion();
}

IIR_TypeDeclaration *
scram_plugin_class_factory::new_IIR_TypeDeclaration() {
  return new IIRScram_TypeDeclaration();
}

IIR_UnitList *
scram_plugin_class_factory::new_IIR_UnitList() {
  return new IIRScram_UnitList();
}

IIR_UseClause *
scram_plugin_class_factory::new_IIR_UseClause() {
  return new IIRScram_UseClause();
}

IIR_UserAttribute *
scram_plugin_class_factory::new_IIR_UserAttribute() {
  return new IIRScram_UserAttribute();
}

IIR_ValAttribute *
scram_plugin_class_factory::new_IIR_ValAttribute() {
  return new IIRScram_ValAttribute();
}

IIR_ValueAttribute *
scram_plugin_class_factory::new_IIR_ValueAttribute() {
  return new IIRScram_ValueAttribute();
}

IIR_VariableAssignmentStatement *
scram_plugin_class_factory::new_IIR_VariableAssignmentStatement() {
  return new IIRScram_VariableAssignmentStatement();
}

IIR_VariableDeclaration *
scram_plugin_class_factory::new_IIR_VariableDeclaration() {
  return new IIRScram_VariableDeclaration();
}

IIR_VariableInterfaceDeclaration *
scram_plugin_class_factory::new_IIR_VariableInterfaceDeclaration() {
  return new IIRScram_VariableInterfaceDeclaration();
}

IIR_WaitStatement *
scram_plugin_class_factory::new_IIR_WaitStatement() {
  return new IIRScram_WaitStatement();
}

IIR_WaveformElement *
scram_plugin_class_factory::new_IIR_WaveformElement() {
  return new IIRScram_WaveformElement();
}

IIR_WaveformList *
scram_plugin_class_factory::new_IIR_WaveformList() {
  return new IIRScram_WaveformList();
}

IIR_WhileLoopStatement *
scram_plugin_class_factory::new_IIR_WhileLoopStatement() {
  return new IIRScram_WhileLoopStatement();
}

IIR_XnorOperator *
scram_plugin_class_factory::new_IIR_XnorOperator() {
  return new IIRScram_XnorOperator();
}

IIR_XorOperator *
scram_plugin_class_factory::new_IIR_XorOperator() {
  return new IIRScram_XorOperator();
}

IIR_ZTFAttribute *
scram_plugin_class_factory::new_IIR_ZTFAttribute() {
  return new IIRScram_ZTFAttribute();
}

plugin_class_factory *
scram_plugin_class_factory::instance(){
  static plugin_class_factory *factory = new scram_plugin_class_factory();
  return factory;
}
