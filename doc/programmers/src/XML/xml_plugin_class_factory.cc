// Copyright (c) 2004 The University of Cincinnati.  
 // All rights reserved.
 // 
 // UC MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
 // SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 // IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
 // OR NON-INFRINGEMENT.  UC SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
 // LICENSEE AS A RESULT OF USING, RESULT OF USING, MODIFYING OR
 // DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 // 
 // By using or copying this Software, Licensee agrees to abide by the
 // intellectual property laws, and all other applicable laws of the U.S.,
 // and the terms of this license.
 // 
 // You may modify, distribute, and use the software contained in this
 // package under the terms of the "GNU LIBRARY GENERAL PUBLIC LICENSE"
 // version 2, June 1991. A copy of this license agreement can be found in
 // the file "LGPL", distributed with this archive.
 // 
 // --------------------------------------------------------------------------

#include "XMLAbsoluteOperator.hh"
#include "XMLAccessSubtypeDefinition.hh"
#include "XMLAccessTypeDefinition.hh"
#include "XMLAcrossAttribute.hh"
#include "XMLActiveAttribute.hh"
#include "XMLAdditionOperator.hh"
#include "XMLAggregate.hh"
#include "XMLAliasDeclaration.hh"
#include "XMLAllocator.hh"
#include "XMLAndOperator.hh"
#include "XMLArchitectureDeclaration.hh"
#include "XMLArchitectureStatement.hh"
#include "XMLArchitectureStatementList.hh"
#include "XMLArrayNatureDefinition.hh"
#include "XMLArraySubnatureDefinition.hh"
#include "XMLArraySubtypeDefinition.hh"
#include "XMLArrayTypeDefinition.hh"
#include "XMLAscendingAttribute.hh"
#include "XMLAssertionStatement.hh"
#include "XMLAssociationElementByExpression.hh"
#include "XMLAssociationElement.hh"
#include "XMLAssociationElementOpen.hh"
#include "XMLAssociationList.hh"
#include "XMLAttributeDeclaration.hh"
#include "XMLAttribute.hh"
#include "XMLAttributeSpecification.hh"
#include "XMLAttributeSpecificationList.hh"
#include "XMLBaseAttribute.hh"
#include "XMLBitStringLiteral.hh"
#include "XMLBlockConfiguration.hh"
#include "XMLBlockStatement.hh"
#include "XMLBranchQuantityDeclaration.hh"
#include "XMLBreakElement.hh"
#include "XMLBreakStatement.hh"
#include "XMLCaseStatementAlternativeByChoices.hh"
#include "XMLCaseStatementAlternativeByExpression.hh"
#include "XMLCaseStatementAlternativeByOthers.hh"
#include "XMLCaseStatementAlternative.hh"
#include "XMLCaseStatementAlternativeList.hh"
#include "XMLCaseStatement.hh"
#include "XMLCharacterLiteral.hh"
#include "XMLChoice.hh"
#include "XMLChoiceList.hh"
#include "XMLComment.hh"
#include "XMLCommentList.hh"
#include "XMLComponentConfiguration.hh"
#include "XMLComponentDeclaration.hh"
#include "XMLComponentInstantiationStatement.hh"
#include "XMLConcatenationOperator.hh"
#include "XMLConcurrentAssertionStatement.hh"
#include "XMLConcurrentBreakStatement.hh"
#include "XMLConcurrentConditionalSignalAssignment.hh"
#include "XMLConcurrentGenerateForStatement.hh"
#include "XMLConcurrentGenerateIfStatement.hh"
#include "XMLConcurrentProcedureCallStatement.hh"
#include "XMLConcurrentSelectedSignalAssignment.hh"
#include "XMLConcurrentStatement.hh"
#include "XMLConditionalWaveform.hh"
#include "XMLConditionalWaveformList.hh"
#include "XMLConfigurationDeclaration.hh"
#include "XMLConfigurationItem.hh"
#include "XMLConfigurationItemList.hh"
#include "XMLConfigurationSpecification.hh"
#include "XMLConstantDeclaration.hh"
#include "XMLConstantInterfaceDeclaration.hh"
#include "XMLContributionAttribute.hh"
#include "XMLDeclaration.hh"
#include "XMLDeclarationList.hh"
#include "XMLDelayedAttribute.hh"
#include "XMLDesignatorByAll.hh"
#include "XMLDesignatorByOthers.hh"
#include "XMLDesignatorExplicit.hh"
#include "XMLDesignator.hh"
#include "XMLDesignatorList.hh"
#include "XMLDesignFile.hh"
#include "XMLDesignFileList.hh"
#include "XMLDesignUnitList.hh"
#include "XMLDisconnectSpecification.hh"
#include "XMLDivisionOperator.hh"
#include "XMLDotAttribute.hh"
#include "XMLDrivingAttribute.hh"
#include "XMLDrivingValueAttribute.hh"
#include "XMLDyadicOperator.hh"
#include "XMLElementDeclaration.hh"
#include "XMLElementDeclarationList.hh"
#include "XMLElsif.hh"
#include "XMLEntityClassEntry.hh"
#include "XMLEntityClassEntryList.hh"
#include "XMLEntityDeclaration.hh"
#include "XMLEntityNameList.hh"
#include "XMLEnumerationLiteral.hh"
#include "XMLEnumerationLiteralList.hh"
#include "XMLEnumerationSubtypeDefinition.hh"
#include "XMLEnumerationTypeDefinition.hh"
#include "XMLEqualityOperator.hh"
#include "XMLEventAttribute.hh"
#include "XMLExitStatement.hh"
#include "XMLExponentiationOperator.hh"
#include "XMLExpression.hh"
#include "XMLFileDeclaration.hh"
#include "XMLFileInterfaceDeclaration.hh"
#include "XMLFileTypeDefinition.hh"
#include "XMLFloatingPointLiteral32.hh"
#include "XMLFloatingPointLiteral64.hh"
#include "XMLFloatingPointLiteral.hh"
#include "XMLFloatingSubtypeDefinition.hh"
#include "XMLFloatingTypeDefinition.hh"
#include "XMLForLoopStatement.hh"
#include "XMLFreeQuantityDeclaration.hh"
#include "XMLFunctionCall.hh"
#include "XMLFunctionDeclaration.hh"
#include "XMLGenericList.hh"
#include "XMLGreaterThanOperator.hh"
#include "XMLGreaterThanOrEqualOperator.hh"
#include "XMLGroupConstituent.hh"
#include "XMLGroupDeclaration.hh"
#include "XMLGroupTemplateDeclaration.hh"
#include "XML.hh"
#include "XMLHighAttribute.hh"
#include "XMLIdentifier.hh"
#include "XMLIdentifierList.hh"
#include "XMLIdentityOperator.hh"
#include "XMLIfStatement.hh"
#include "XMLImageAttribute.hh"
#include "XMLIncompleteTypeDefinition.hh"
#include "XMLIndexedName.hh"
#include "XMLInequalityOperator.hh"
#include "XMLInstanceNameAttribute.hh"
#include "XMLIntegerLiteral32.hh"
#include "XMLIntegerLiteral64.hh"
#include "XMLIntegerLiteral.hh"
#include "XMLIntegerSubtypeDefinition.hh"
#include "XMLIntegerTypeDefinition.hh"
#include "XMLInterfaceDeclaration.hh"
#include "XMLInterfaceList.hh"
#include "XMLLabel.hh"
#include "XMLLastActiveAttribute.hh"
#include "XMLLastEventAttribute.hh"
#include "XMLLastValueAttribute.hh"
#include "XMLLeftAttribute.hh"
#include "XMLLeftOfAttribute.hh"
#include "XMLLengthAttribute.hh"
#include "XMLLessThanOperator.hh"
#include "XMLLessThanOrEqualOperator.hh"
#include "XMLLibraryClause.hh"
#include "XMLLibraryDeclaration.hh"
#include "XMLLibraryUnit.hh"
#include "XMLLibraryUnitList.hh"
#include "XMLList.hh"
#include "XMLLiteral.hh"
#include "XMLLowAttribute.hh"
#include "XMLLTFAttribute.hh"
#include "XMLModulusOperator.hh"
#include "XMLMonadicOperator.hh"
#include "XMLMultiplicationOperator.hh"
#include "XMLName.hh"
#include "XMLNameList.hh"
#include "XMLNandOperator.hh"
#include "XMLNatureDeclaration.hh"
#include "XMLNatureDefinition.hh"
#include "XMLNegationOperator.hh"
#include "XMLNextStatement.hh"
#include "XMLNorOperator.hh"
#include "XMLNotOperator.hh"
#include "XMLNullStatement.hh"
#include "XMLObjectDeclaration.hh"
#include "XMLOrOperator.hh"
#include "XMLOthersInitialization.hh"
#include "XMLPackageBodyDeclaration.hh"
#include "XMLPackageDeclaration.hh"
#include "XMLPathNameAttribute.hh"
#include "XMLPhysicalLiteral.hh"
#include "XMLPhysicalSubtypeDefinition.hh"
#include "XMLPhysicalTypeDefinition.hh"
#include "XMLPhysicalUnit.hh"
#include "XMLPortList.hh"
#include "XMLPosAttribute.hh"
#include "XMLPredAttribute.hh"
#include "XMLProcedureCallStatement.hh"
#include "XMLProcedureDeclaration.hh"
#include "XMLProcessStatement.hh"
#include "XMLQualifiedExpression.hh"
#include "XMLQuantityDeclaration.hh"
#include "XMLQuietAttribute.hh"
#include "XMLRangeAttribute.hh"
#include "XMLRangeTypeDefinition.hh"
#include "XMLRecordTypeDefinition.hh"
#include "XMLReferenceAttribute.hh"
#include "XMLRemainderOperator.hh"
#include "XMLReportStatement.hh"
#include "XMLReturnStatement.hh"
#include "XMLReverseRangeAttribute.hh"
#include "XMLRightAttribute.hh"
#include "XMLRightOfAttribute.hh"
#include "XMLROLOperator.hh"
#include "XMLROROperator.hh"
#include "XMLScalarNatureDefinition.hh"
#include "XMLScalarTypeDefinition.hh"
#include "XMLSelectedNameByAll.hh"
#include "XMLSelectedName.hh"
#include "XMLSelectedWaveform.hh"
#include "XMLSelectedWaveformList.hh"
#include "XMLSensitizedProcessStatement.hh"
#include "XMLSequentialStatement.hh"
#include "XMLSequentialStatementList.hh"
#include "XMLSharedVariableDeclaration.hh"
#include "XMLSignalAssignmentStatement.hh"
#include "XMLSignalDeclaration.hh"
#include "XMLSignalInterfaceDeclaration.hh"
#include "XMLSignature.hh"
#include "XMLSimpleNameAttribute.hh"
#include "XMLSimpleName.hh"
#include "XMLSimpleSimultaneousStatement.hh"
#include "XMLSimultaneousElsif.hh"
#include "XMLSimultaneousIfStatement.hh"
#include "XMLSimultaneousStatement.hh"
#include "XMLSLAOperator.hh"
#include "XMLSliceName.hh"
#include "XMLSLLOperator.hh"
#include "XMLSourceQuantityDeclaration.hh"
#include "XMLSRAOperator.hh"
#include "XMLSRLOperator.hh"
#include "XMLStableAttribute.hh"
#include "XMLStatement.hh"
#include "XMLStringLiteral.hh"
#include "XMLSubprogramDeclaration.hh"
#include "XMLSubtractionOperator.hh"
#include "XMLSubtypeDeclaration.hh"
#include "XMLSuccAttribute.hh"
#include "XMLTerminalDeclaration.hh"
#include "XMLTerminalInterfaceDeclaration.hh"
#include "XMLTextLiteral.hh"
#include "XMLThroughAttribute.hh"
#include "XMLTransactionAttribute.hh"
#include "XMLTuple.hh"
#include "XMLTypeConversion.hh"
#include "XMLTypeDeclaration.hh"
#include "XMLTypeDefinition.hh"
#include "XMLUnitList.hh"
#include "XMLUseClause.hh"
#include "XMLUserAttribute.hh"
#include "XMLValAttribute.hh"
#include "XMLValueAttribute.hh"
#include "XMLVariableAssignmentStatement.hh"
#include "XMLVariableDeclaration.hh"
#include "XMLVariableInterfaceDeclaration.hh"
#include "XMLWaitStatement.hh"
#include "XMLWaveformElement.hh"
#include "XMLWaveformList.hh"
#include "XMLWhileLoopStatement.hh"
#include "XMLXnorOperator.hh"
#include "XMLXorOperator.hh"
#include "XMLZTFAttribute.hh"

#include "XMLStandardPackage.hh"
#include "savant/IRKind.hh"
#include "savant/ScramStandardPackage.hh"

// Implementation details
#include "xml_plugin_class_factory.hh"

xml_plugin_class_factory *
xml_plugin_class_factory::instance(){
  static xml_plugin_class_factory *_instance = new xml_plugin_class_factory();
  return _instance;
}

IIR*
xml_plugin_class_factory::get_new_class(IIR_Kind iir_type) {
  IIR *retv = NULL;
  switch (iir_type) {
  case IIR_ABSOLUTE_OPERATOR:
    retv = new XMLAbsoluteOperator();
    break;     

  case IIR_ACCESS_SUBTYPE_DEFINITION:
    retv = new XMLAccessSubtypeDefinition();
    break;     

  case IIR_ACCESS_TYPE_DEFINITION:
    retv = new XMLAccessTypeDefinition();
    break;     

  case IIR_ACROSS_ATTRIBUTE:
    retv = new XMLAcrossAttribute();
    break;     

  case IIR_ACTIVE_ATTRIBUTE:
    retv = new XMLActiveAttribute();
    break;     

  case IIR_ADDITION_OPERATOR:
    retv = new XMLAdditionOperator();
    break;     

  case IIR_AGGREGATE:
    retv = new XMLAggregate();
    break;     

  case IIR_ALIAS_DECLARATION:
    retv = new XMLAliasDeclaration();
    break;     

  case IIR_ALLOCATOR:
    retv = new XMLAllocator();
    break;     

  case IIR_AND_OPERATOR:
    retv = new XMLAndOperator();
    break;     

  case IIR_ARCHITECTURE_DECLARATION:
    retv = new XMLArchitectureDeclaration();
    break;     

  case IIR_ARCHITECTURE_STATEMENT:
    retv = new XMLArchitectureStatement();
    break;     

  case IIR_ARCHITECTURE_STATEMENT_LIST:
    retv = new XMLArchitectureStatementList();
    break;     

  case IIR_ARRAY_NATURE_DEFINITION:
    retv = new XMLArrayNatureDefinition();
    break;     

  case IIR_ARRAY_SUBNATURE_DEFINITION:
    retv = new XMLArraySubnatureDefinition();
    break;     

  case IIR_ARRAY_SUBTYPE_DEFINITION:
    retv = new XMLArraySubtypeDefinition();
    break;     

  case IIR_ARRAY_TYPE_DEFINITION:
    retv = new XMLArrayTypeDefinition();
    break;     

  case IIR_ASCENDING_ATTRIBUTE:
    retv = new XMLAscendingAttribute();
    break;     

  case IIR_ASSERTION_STATEMENT:
    retv = new XMLAssertionStatement();
    break;     

  case IIR_ASSOCIATION_ELEMENT_BY_EXPRESSION:
    retv = new XMLAssociationElementByExpression();
    break;     

  case IIR_ASSOCIATION_ELEMENT_BY_OPEN:
    retv = new XMLAssociationElementOpen();
    break;     

  case IIR_ASSOCIATION_LIST:
    retv = new XMLAssociationList();
    break;     

  case IIR_ATTRIBUTE_DECLARATION:
    retv = new XMLAttributeDeclaration();
    break;     

  case IIR_ATTRIBUTE_SPECIFICATION:
    retv = new XMLAttributeSpecification();
    break;     

  case IIR_ATTRIBUTE_SPECIFICATION_LIST:
    retv = new XMLAttributeSpecificationList();
    break;     

  case IIR_BASE_ATTRIBUTE:
    retv = new XMLBaseAttribute();
    break;     

  case IIR_BIT_STRING_LITERAL:
    retv = new XMLBitStringLiteral();
    break;     

  case IIR_BLOCK_CONFIGURATION:
    retv = new XMLBlockConfiguration();
    break;     

  case IIR_BLOCK_STATEMENT:
    retv = new XMLBlockStatement();
    break;     

  case IIR_BRANCH_QUANTITY_DECLARATION:
    retv = new XMLBranchQuantityDeclaration();
    break;     

  case IIR_BREAK_ELEMENT:
    retv = new XMLBreakElement();
    break;     

  case IIR_BREAK_STATEMENT:
    retv = new XMLBreakStatement();
    break;     

  case IIR_CASE_STATEMENT_ALTERNATIVE_BY_CHOICES:
    retv = new XMLCaseStatementAlternativeByChoices();
    break;     

  case IIR_CASE_STATEMENT_ALTERNATIVE_BY_EXPRESSION:
    retv = new XMLCaseStatementAlternativeByExpression();
    break;     

  case IIR_CASE_STATEMENT_ALTERNATIVE_BY_OTHERS:
    retv = new XMLCaseStatementAlternativeByOthers();
    break;     

  case IIR_CASE_STATEMENT_ALTERNATIVE_LIST:
    retv = new XMLCaseStatementAlternativeList();
    break;     

  case IIR_CASE_STATEMENT:
    retv = new XMLCaseStatement();
    break;     

  case IIR_CHARACTER_LITERAL:
    retv = new XMLCharacterLiteral();
    break;     

  case IIR_CHOICE:
    retv = new XMLChoice();
    break;     

  case IIR_CHOICE_LIST:
    retv = new XMLChoiceList();
    break;     

  case IIR_COMMENT:
    retv = new XMLComment();
    break;     

  case IIR_COMMENT_LIST:
    retv = new XMLCommentList();
    break;     

  case IIR_COMPONENT_CONFIGURATION:
    retv = new XMLComponentConfiguration();
    break;     

  case IIR_COMPONENT_DECLARATION:
    retv = new XMLComponentDeclaration();
    break;     

  case IIR_COMPONENT_INSTANTIATION_STATEMENT:
    retv = new XMLComponentInstantiationStatement();
    break;     

  case IIR_CONCATENATION_OPERATOR:
    retv = new XMLConcatenationOperator();
    break;     

  case IIR_CONCURRENT_ASSERTION_STATEMENT:
    retv = new XMLConcurrentAssertionStatement();
    break;     

  case IIR_CONCURRENT_BREAK_STATEMENT:
    retv = new XMLConcurrentBreakStatement();
    break;

  case IIR_CONCURRENT_CONDITIONAL_SIGNAL_ASSIGNMENT:
    retv = new XMLConcurrentConditionalSignalAssignment();
    break;     

  case IIR_CONCURRENT_GENERATE_FOR_STATEMENT:
    retv = new XMLConcurrentGenerateForStatement();
    break;     

  case IIR_CONCURRENT_GENERATE_IF_STATEMENT:
    retv = new XMLConcurrentGenerateIfStatement();
    break;     

  case IIR_CONCURRENT_PROCEDURE_CALL_STATEMENT:
    retv = new XMLConcurrentProcedureCallStatement();
    break;     

  case IIR_CONCURRENT_SELECTED_SIGNAL_ASSIGNMENT:
    retv = new XMLConcurrentSelectedSignalAssignment();
    break;     

  case IIR_CONDITIONAL_WAVEFORM:
    retv = new XMLConditionalWaveform();
    break;     

  case IIR_CONDITIONAL_WAVEFORM_LIST:
    retv = new XMLConditionalWaveformList();
    break;     

  case IIR_CONFIGURATION_DECLARATION:
    retv = new XMLConfigurationDeclaration();
    break;     

  case IIR_CONFIGURATION_ITEM:
    retv = new XMLConfigurationItem();
    break;     

  case IIR_CONFIGURATION_ITEM_LIST:
    retv = new XMLConfigurationItemList();
    break;     

  case IIR_CONFIGURATION_SPECIFICATION:
    retv = new XMLConfigurationSpecification();
    break;     

  case IIR_CONTRIBUTION_ATTRIBUTE:
    retv = new XMLContributionAttribute();
    break;     

  case IIR_CONSTANT_DECLARATION:
    retv = new XMLConstantDeclaration();
    break;     

  case IIR_CONSTANT_INTERFACE_DECLARATION:
    retv = new XMLConstantInterfaceDeclaration();
    break;     

  case IIR_DECLARATION_LIST:
    retv = new XMLDeclarationList();
    break;     

  case IIR_DELAYED_ATTRIBUTE:
    retv = new XMLDelayedAttribute();
    break;     

  case IIR_DESIGNATOR_BY_ALL:
    retv = new XMLDesignatorByAll();
    break;     

  case IIR_DESIGNATOR_BY_OTHERS:
    retv = new XMLDesignatorByOthers();
    break;     

  case IIR_DESIGNATOR_EXPLICIT:
    retv = new XMLDesignatorExplicit();
    break;     

  case IIR_DESIGNATOR_LIST:
    retv = new XMLDesignatorList();
    break;     

  case IIR_DESIGN_FILE:
    retv = new XMLDesignFile();
    break;     

  case IIR_DESIGN_FILE_LIST:
    retv = new XMLDesignFileList();
    break;     

  case IIR_DESIGN_UNIT_LIST:
    retv = new XMLDesignUnitList();
    break;     

  case IIR_DISCONNECT_SPECIFICATION:
    retv = new XMLDisconnectSpecification();
    break;     

  case IIR_DIVISION_OPERATOR:
    retv = new XMLDivisionOperator();
    break;     

  case IIR_DOT_ATTRIBUTE:
    retv = new XMLDotAttribute();
    break;     

  case IIR_DRIVING_ATTRIBUTE:
    retv = new XMLDrivingAttribute();
    break;     

  case IIR_DRIVING_VALUE_ATTRIBUTE:
    retv = new XMLDrivingValueAttribute();
    break;     

  case IIR_ELEMENT_DECLARATION:
    retv = new XMLElementDeclaration();
    break;     

  case IIR_ELEMENT_DECLARATION_LIST:
    retv = new XMLElementDeclarationList();
    break;     

  case IIR_ELSIF:
    retv = new XMLElsif();
    break;     

  case IIR_ENTITY_CLASS_ENTRY:
    retv = new XMLEntityClassEntry();
    break;     

  case IIR_ENTITY_CLASS_ENTRY_LIST:
    retv = new XMLEntityClassEntryList();
    break;     

  case IIR_ENTITY_DECLARATION:
    retv = new XMLEntityDeclaration();
    break;     

  case IIR_ENTITY_NAME_LIST:
    retv = new XMLEntityNameList();
    break;     

  case IIR_ENUMERATION_LITERAL:
    retv = new XMLEnumerationLiteral();
    break;     

  case IIR_ENUMERATION_LITERAL_LIST:
    retv = new XMLEnumerationLiteralList();
    break;     

  case IIR_ENUMERATION_SUBTYPE_DEFINITION:
    retv = new XMLEnumerationSubtypeDefinition();
    break;     

  case IIR_ENUMERATION_TYPE_DEFINITION:
    retv = new XMLEnumerationTypeDefinition();
    break;     

  case IIR_EQUALITY_OPERATOR:
    retv = new XMLEqualityOperator();
    break;     

  case IIR_EVENT_ATTRIBUTE:
    retv = new XMLEventAttribute();
    break;     

  case IIR_EXIT_STATEMENT:
    retv = new XMLExitStatement();
    break;     

  case IIR_EXPONENTIATION_OPERATOR:
    retv = new XMLExponentiationOperator();
    break;     

  case IIR_FILE_DECLARATION:
    retv = new XMLFileDeclaration();
    break;     

  case IIR_FILE_INTERFACE_DECLARATION:
    retv = new XMLFileInterfaceDeclaration();
    break;     

  case IIR_FILE_TYPE_DEFINITION:
    retv = new XMLFileTypeDefinition();
    break;     

  case IIR_FLOATING_POINT_LITERAL32:
    retv = new XMLFloatingPointLiteral32();
    break;     

  case IIR_FLOATING_POINT_LITERAL64:
    retv = new XMLFloatingPointLiteral64();
    break;     

  case IIR_FLOATING_POINT_LITERAL:
    retv = new XMLFloatingPointLiteral();
    break;     

  case IIR_FLOATING_SUBTYPE_DEFINITION:
    retv = new XMLFloatingSubtypeDefinition();
    break;     

  case IIR_FLOATING_TYPE_DEFINITION:
    retv = new XMLFloatingTypeDefinition();
    break;     

  case IIR_FOR_LOOP_STATEMENT:
    retv = new XMLForLoopStatement();
    break;     

  case IIR_FREE_QUANTITY_DECLARATION:
    retv = new XMLFreeQuantityDeclaration();
    break;     

  case IIR_FUNCTION_CALL:
    retv = new XMLFunctionCall();
    break;     

  case IIR_FUNCTION_DECLARATION:
    retv = new XMLFunctionDeclaration();
    break;     

  case IIR_GENERIC_LIST:
    retv = new XMLGenericList();
    break;     

  case IIR_GREATER_THAN_OPERATOR:
    retv = new XMLGreaterThanOperator();
    break;     

  case IIR_GREATER_THAN_OR_EQUAL_OPERATOR:
    retv = new XMLGreaterThanOrEqualOperator();
    break;     

  case IIR_GROUP_CONSTITUENT:
    retv = new XMLGroupConstituent();
    break;     

  case IIR_GROUP_DECLARATION:
    retv = new XMLGroupDeclaration();
    break;     

  case IIR_GROUP_TEMPLATE_DECLARATION:
    retv = new XMLGroupTemplateDeclaration();
    break;     

  case IIR_HIGH_ATTRIBUTE:
    retv = new XMLHighAttribute();
    break;     

  case IIR_IDENTIFIER:
    retv = new XMLIdentifier();
    break;     

  case IIR_IDENTIFIER_LIST:
    retv = new XMLIdentifierList();
    break;     

  case IIR_IDENTITY_OPERATOR:
    retv = new XMLIdentityOperator();
    break;     

  case IIR_IF_STATEMENT:
    retv = new XMLIfStatement();
    break;     

  case IIR_IMAGE_ATTRIBUTE:
    retv = new XMLImageAttribute();
    break;     

  case IIR_INCOMPLETE_TYPE_DEFINITION:
    retv = new XMLIncompleteTypeDefinition();
    break;     

  case IIR_INDEXED_NAME:
    retv = new XMLIndexedName();
    break;     

  case IIR_INEQUALITY_OPERATOR:
    retv = new XMLInequalityOperator();
    break;     

  case IIR_INSTANCE_NAME_ATTRIBUTE:
    retv = new XMLInstanceNameAttribute();
    break;     

  case IIR_INTEGER_LITERAL32:
    retv = new XMLIntegerLiteral32();
    break;     

  case IIR_INTEGER_LITERAL64:
    retv = new XMLIntegerLiteral64();
    break;     

  case IIR_INTEGER_LITERAL:
    retv = new XMLIntegerLiteral();
    break;     

  case IIR_INTEGER_SUBTYPE_DEFINITION:
    retv = new XMLIntegerSubtypeDefinition();
    break;     

  case IIR_INTEGER_TYPE_DEFINITION:
    retv = new XMLIntegerTypeDefinition();
    break;     

  case IIR_INTERFACE_LIST:
    retv = new XMLInterfaceList();
    break;     

  case IIR_LABEL:
    retv = new XMLLabel();
    break;     

  case IIR_LAST_ACTIVE_ATTRIBUTE:
    retv = new XMLLastActiveAttribute();
    break;     

  case IIR_LAST_EVENT_ATTRIBUTE:
    retv = new XMLLastEventAttribute();
    break;     

  case IIR_LAST_VALUE_ATTRIBUTE:
    retv = new XMLLastValueAttribute();
    break;     

  case IIR_LEFT_ATTRIBUTE:
    retv = new XMLLeftAttribute();
    break;     

  case IIR_LEFT_OF_ATTRIBUTE:
    retv = new XMLLeftOfAttribute();
    break;     

  case IIR_LENGTH_ATTRIBUTE:
    retv = new XMLLengthAttribute();
    break;     

  case IIR_LESS_THAN_OPERATOR:
    retv = new XMLLessThanOperator();
    break;     

  case IIR_LESS_THAN_OR_EQUAL_OPERATOR:
    retv = new XMLLessThanOrEqualOperator();
    break;     

  case IIR_LIBRARY_CLAUSE:
    retv = new XMLLibraryClause();
    break;     

  case IIR_LIBRARY_DECLARATION:
    retv = new XMLLibraryDeclaration();
    break;     

  case IIR_LIBRARY_UNIT_LIST:
    retv = new XMLLibraryUnitList();
    break;     

  case IIR_LITERAL:
    retv = new XMLLiteral();
    break;     

  case IIR_LTF_ATTRIBUTE:
    retv = new XMLLTFAttribute();
    break;     

  case IIR_LOW_ATTRIBUTE:
    retv = new XMLLowAttribute();
    break;     

  case IIR_MODULUS_OPERATOR:
    retv = new XMLModulusOperator();
    break;     

  case IIR_MULTIPLICATION_OPERATOR:
    retv = new XMLMultiplicationOperator();
    break;     

  case IIR_NAME:
    retv = new XMLName();
    break;     

  case IIR_NAME_LIST:
    retv = new XMLNameList();
    break;     

  case IIR_NAND_OPERATOR:
    retv = new XMLNandOperator();
    break;     

  case IIR_NATURE_DECLARATION:
    retv = new XMLNatureDeclaration();
    break;     

  case IIR_NATURE_DEFINITION:
    retv = new XMLNatureDefinition();
    break;     

  case IIR_NEGATION_OPERATOR:
    retv = new XMLNegationOperator();
    break;     

  case IIR_NEXT_STATEMENT:
    retv = new XMLNextStatement();
    break;     

  case IIR_NOR_OPERATOR:
    retv = new XMLNorOperator();
    break;     

  case IIR_NOT_OPERATOR:
    retv = new XMLNotOperator();
    break;     

  case IIR_NULL_STATEMENT:
    retv = new XMLNullStatement();
    break;     

  case IIR_OR_OPERATOR:
    retv = new XMLOrOperator();
    break;     

  case IIR_OTHERS_INITIALIZATION:
    retv = new XMLOthersInitialization();
    break;     

  case IIR_PACKAGE_BODY_DECLARATION:
    retv = new XMLPackageBodyDeclaration();
    break;     

  case IIR_PACKAGE_DECLARATION:
    retv = new XMLPackageDeclaration();
    break;     

  case IIR_PATH_NAME_ATTRIBUTE:
    retv = new XMLPathNameAttribute();
    break;     

  case IIR_PHYSICAL_LITERAL:
    retv = new XMLPhysicalLiteral();
    break;     

  case IIR_PHYSICAL_SUBTYPE_DEFINITION:
    retv = new XMLPhysicalSubtypeDefinition();
    break;     

  case IIR_PHYSICAL_TYPE_DEFINITION:
    retv = new XMLPhysicalTypeDefinition();
    break;     

  case IIR_PHYSICAL_UNIT:
    retv = new XMLPhysicalUnit();
    break;     

  case IIR_PORT_LIST:
    retv = new XMLPortList();
    break;     

  case IIR_POS_ATTRIBUTE:
    retv = new XMLPosAttribute();
    break;     

  case IIR_PRED_ATTRIBUTE:
    retv = new XMLPredAttribute();
    break;     

  case IIR_PROCEDURE_CALL_STATEMENT:
    retv = new XMLProcedureCallStatement();
    break;     

  case IIR_PROCEDURE_DECLARATION:
    retv = new XMLProcedureDeclaration();
    break;     

  case IIR_PROCESS_STATEMENT:
    retv = new XMLProcessStatement();
    break;     

  case IIR_QUALIFIED_EXPRESSION:
    retv = new XMLQualifiedExpression();
    break;     

  case IIR_QUANTITY_DECLARATION:
    retv = new XMLQuantityDeclaration();
    break;     

  case IIR_QUIET_ATTRIBUTE:
    retv = new XMLQuietAttribute();
    break;     

  case IIR_RANGE_ATTRIBUTE:
    retv = new XMLRangeAttribute();
    break;     

  case IIR_RANGE_TYPE_DEFINITION:
    retv = new XMLRangeTypeDefinition();
    break;     

  case IIR_RECORD_TYPE_DEFINITION:
    retv = new XMLRecordTypeDefinition();
    break;     

  case IIR_REFERENCE_ATTRIBUTE:
    retv = new XMLReferenceAttribute();
    break;     

  case IIR_REMAINDER_OPERATOR:
    retv = new XMLRemainderOperator();
    break;     

  case IIR_REPORT_STATEMENT:
    retv = new XMLReportStatement();
    break;     

  case IIR_RETURN_STATEMENT:
    retv = new XMLReturnStatement();
    break;     

  case IIR_REVERSE_RANGE_ATTRIBUTE:
    retv = new XMLReverseRangeAttribute();
    break;     

  case IIR_RIGHT_ATTRIBUTE:
    retv = new XMLRightAttribute();
    break;     

  case IIR_RIGHT_OF_ATTRIBUTE:
    retv = new XMLRightOfAttribute();
    break;     

  case IIR_ROL_OPERATOR:
    retv = new XMLROLOperator();
    break;     

  case IIR_ROR_OPERATOR:
    retv = new XMLROROperator();
    break;     

  case IIR_SCALAR_NATURE_DEFINITION:
    retv = new XMLScalarNatureDefinition();
    break;     

  case IIR_SELECTED_NAME_BY_ALL:
    retv = new XMLSelectedNameByAll();
    break;     

  case IIR_SELECTED_NAME:
    retv = new XMLSelectedName();
    break;     

  case IIR_SELECTED_WAVEFORM:
    retv = new XMLSelectedWaveform();
    break;     

  case IIR_SELECTED_WAVEFORM_LIST:
    retv = new XMLSelectedWaveformList();
    break;     

  case IIR_SENSITIZED_PROCESS_STATEMENT:
    retv = new XMLSensitizedProcessStatement();
    break;     

  case IIR_SEQUENTIAL_STATEMENT_LIST:
    retv = new XMLSequentialStatementList();
    break;     

  case IIR_SHARED_VARIABLE_DECLARATION:
    retv = new XMLSharedVariableDeclaration();
    break;     

  case IIR_SIGNAL_ASSIGNMENT_STATEMENT:
    retv = new XMLSignalAssignmentStatement();
    break;     

  case IIR_SIGNAL_DECLARATION:
    retv = new XMLSignalDeclaration();
    break;     

  case IIR_SIGNAL_INTERFACE_DECLARATION:
    retv = new XMLSignalInterfaceDeclaration();
    break;     

  case IIR_SIGNATURE:
    retv = new XMLSignature();
    break;     

  case IIR_SIMPLE_NAME_ATTRIBUTE:
    retv = new XMLSimpleNameAttribute();
    break;     

  case IIR_SIMPLE_NAME:
    retv = new XMLSimpleName();
    break;     

  case IIR_SIMPLE_SIMULTANEOUS_STATEMENT:
    retv = new XMLSimpleSimultaneousStatement();
    break;     

  case IIR_SIMULTANEOUS_IF_STATEMENT:
    retv = new XMLSimultaneousIfStatement();
    break;     

  case IIR_SLA_OPERATOR:
    retv = new XMLSLAOperator();
    break;     

  case IIR_SLICE_NAME:
    retv = new XMLSliceName();
    break;     

  case IIR_SLL_OPERATOR:
    retv = new XMLSLLOperator();
    break;     

  case IIR_SOURCE_QUANTITY_DECLARATION:
    retv = new XMLSourceQuantityDeclaration();
    break;     

  case IIR_SRA_OPERATOR:
    retv = new XMLSRAOperator();
    break;     

  case IIR_SRL_OPERATOR:
    retv = new XMLSRLOperator();
    break;     

  case IIR_STABLE_ATTRIBUTE:
    retv = new XMLStableAttribute();
    break;     

  case IIR_STRING_LITERAL:
    retv = new XMLStringLiteral();
    break;     

  case IIR_SUBPROGRAM_DECLARATION:
    retv = new XMLSubprogramDeclaration();
    break;     

  case IIR_SUBTRACTION_OPERATOR:
    retv = new XMLSubtractionOperator();
    break;     

  case IIR_SUBTYPE_DECLARATION:
    retv = new XMLSubtypeDeclaration();
    break;     

  case IIR_SUCC_ATTRIBUTE:
    retv = new XMLSuccAttribute();
    break;     

  case IIR_TERMINAL_DECLARATION:
    retv = new XMLTerminalDeclaration();
    break;     

  case IIR_TERMINAL_INTERFACE_DECLARATION:
    retv = new XMLTerminalInterfaceDeclaration();
    break;     

  case IIR_THROUGH_ATTRIBUTE:
    retv = new XMLThroughAttribute();
    break;     

  case IIR_TRANSACTION_ATTRIBUTE:
    retv = new XMLTransactionAttribute();
    break;     

  case IIR_TUPLE:
    retv = new XMLTuple();
    break;     

  case IIR_TYPE_CONVERSION:
    retv = new XMLTypeConversion();
    break;     

  case IIR_TYPE_DECLARATION:
    retv = new XMLTypeDeclaration();
    break;     

  case IIR_UNIT_LIST:
    retv = new XMLUnitList();
    break;     

  case IIR_USE_CLAUSE:
    retv = new XMLUseClause();
    break;     

  case IIR_USER_ATTRIBUTE:
    retv = new XMLUserAttribute();
    break;     

  case IIR_VAL_ATTRIBUTE:
    retv = new XMLValAttribute();
    break;     

  case IIR_VALUE_ATTRIBUTE:
    retv = new XMLValueAttribute();
    break;     

  case IIR_VARIABLE_ASSIGNMENT_STATEMENT:
    retv = new XMLVariableAssignmentStatement();
    break;     

  case IIR_VARIABLE_DECLARATION:
    retv = new XMLVariableDeclaration();
    break;     

  case IIR_VARIABLE_INTERFACE_DECLARATION:
    retv = new XMLVariableInterfaceDeclaration();
    break;     

  case IIR_WAIT_STATEMENT:
    retv = new XMLWaitStatement();
    break;     

  case IIR_WAVEFORM_ELEMENT:
    retv = new XMLWaveformElement();
    break;     

  case IIR_WAVEFORM_LIST:
    retv = new XMLWaveformList();
    break;     

  case IIR_WHILE_LOOP_STATEMENT:
    retv = new XMLWhileLoopStatement();
    break;     

  case IIR_XNOR_OPERATOR:
    retv = new XMLXnorOperator();
    break;     

  case IIR_XOR_OPERATOR:
    retv = new XMLXorOperator();
    break;     

  case IIR_ZTF_ATTRIBUTE:
    retv = new XMLZTFAttribute();
    break;     

  default:
    // Attempted to create an unknown type of node
    ASSERT(0);    
  }

  return retv;
}

StandardPackage *
xml_plugin_class_factory::get_standard_package() {
  static StandardPackage *instance = 
    dynamic_cast<StandardPackage *>(ScramStandardPackage::instance()->convert_tree( this ));
  return instance;
}

StandardPackage *
xml_plugin_class_factory::new_StandardPackage() {
  return new XMLStandardPackage(this);
}

IIR_AbsoluteOperator *
xml_plugin_class_factory::new_IIR_AbsoluteOperator() {
  return new XMLAbsoluteOperator();
}

IIR_AccessSubtypeDefinition *
xml_plugin_class_factory::new_IIR_AccessSubtypeDefinition() {
  return new XMLAccessSubtypeDefinition();
}

IIR_AccessTypeDefinition *
xml_plugin_class_factory::new_IIR_AccessTypeDefinition() {
  return new XMLAccessTypeDefinition();
}

IIR_AcrossAttribute *
xml_plugin_class_factory::new_IIR_AcrossAttribute() {
  return new XMLAcrossAttribute();
}

IIR_ActiveAttribute *
xml_plugin_class_factory::new_IIR_ActiveAttribute() {
  return new XMLActiveAttribute();
}

IIR_AdditionOperator *
xml_plugin_class_factory::new_IIR_AdditionOperator() {
  return new XMLAdditionOperator();
}

IIR_Aggregate *
xml_plugin_class_factory::new_IIR_Aggregate(){
  return new XMLAggregate();
}

IIR_AliasDeclaration *
xml_plugin_class_factory::new_IIR_AliasDeclaration(){
  return new XMLAliasDeclaration();
}

IIR_Allocator *
xml_plugin_class_factory::new_IIR_Allocator(){
  return new XMLAllocator();
}

IIR_AndOperator *
xml_plugin_class_factory::new_IIR_AndOperator(){
  return new XMLAndOperator();
}

IIR_ArchitectureDeclaration *
xml_plugin_class_factory::new_IIR_ArchitectureDeclaration(){
  return new XMLArchitectureDeclaration();
}

IIR_ArchitectureStatement *
xml_plugin_class_factory::new_IIR_ArchitectureStatement(){
  return new XMLArchitectureStatement();
}

IIR_ArchitectureStatementList *
xml_plugin_class_factory::new_IIR_ArchitectureStatementList(){
  return new XMLArchitectureStatementList();
}

IIR_ArrayNatureDefinition *
xml_plugin_class_factory::new_IIR_ArrayNatureDefinition(){
  return new XMLArrayNatureDefinition();
}

IIR_ArraySubnatureDefinition *
xml_plugin_class_factory::new_IIR_ArraySubnatureDefinition(){
  return new XMLArraySubnatureDefinition();
}

IIR_ArraySubtypeDefinition *
xml_plugin_class_factory::new_IIR_ArraySubtypeDefinition(){
  return new XMLArraySubtypeDefinition();
}

IIR_ArrayTypeDefinition *
xml_plugin_class_factory::new_IIR_ArrayTypeDefinition(){
  return new XMLArrayTypeDefinition();
}

IIR_AscendingAttribute *
xml_plugin_class_factory::new_IIR_AscendingAttribute(){
  return new XMLAscendingAttribute();
}

IIR_AssertionStatement *
xml_plugin_class_factory::new_IIR_AssertionStatement(){
  return new XMLAssertionStatement();
}

IIR_AssociationElementByExpression *
xml_plugin_class_factory::new_IIR_AssociationElementByExpression(){
  return new XMLAssociationElementByExpression();
}

IIR_AssociationElementOpen *
xml_plugin_class_factory::new_IIR_AssociationElementOpen(){
  return new XMLAssociationElementOpen();
}

IIR_AssociationList *
xml_plugin_class_factory::new_IIR_AssociationList(){
  return new XMLAssociationList();
}

IIR_AttributeDeclaration *
xml_plugin_class_factory::new_IIR_AttributeDeclaration(){
  return new XMLAttributeDeclaration();
}

IIR_Attribute *
xml_plugin_class_factory::new_IIR_Attribute(){
  return new XMLAttribute();
}

IIR_AttributeSpecification *
xml_plugin_class_factory::new_IIR_AttributeSpecification(){
  return new XMLAttributeSpecification();
}

IIR_AttributeSpecificationList *
xml_plugin_class_factory::new_IIR_AttributeSpecificationList(){
  return new XMLAttributeSpecificationList();
}

IIR_BaseAttribute *
xml_plugin_class_factory::new_IIR_BaseAttribute(){
  return new XMLBaseAttribute();
}

IIR_BitStringLiteral *
xml_plugin_class_factory::new_IIR_BitStringLiteral(){
  return new XMLBitStringLiteral();
}

IIR_BlockConfiguration *
xml_plugin_class_factory::new_IIR_BlockConfiguration(){
  return new XMLBlockConfiguration();
}

IIR_BlockStatement *
xml_plugin_class_factory::new_IIR_BlockStatement(){
  return new XMLBlockStatement();
}

IIR_BranchQuantityDeclaration *
xml_plugin_class_factory::new_IIR_BranchQuantityDeclaration(){
  return new XMLBranchQuantityDeclaration();
}

IIR_BreakElement *
xml_plugin_class_factory::new_IIR_BreakElement(){
  return new XMLBreakElement();
}

IIR_BreakStatement *
xml_plugin_class_factory::new_IIR_BreakStatement(){
  return new XMLBreakStatement();
}

IIR_CaseStatementAlternativeByChoices *
xml_plugin_class_factory::new_IIR_CaseStatementAlternativeByChoices() {
  return new XMLCaseStatementAlternativeByChoices();
}

IIR_CaseStatementAlternativeByExpression *
xml_plugin_class_factory::new_IIR_CaseStatementAlternativeByExpression() {
  return new XMLCaseStatementAlternativeByExpression();
}

IIR_CaseStatementAlternativeByOthers *
xml_plugin_class_factory::new_IIR_CaseStatementAlternativeByOthers() {
  return new XMLCaseStatementAlternativeByOthers();
}

IIR_CaseStatementAlternativeList *
xml_plugin_class_factory::new_IIR_CaseStatementAlternativeList() {
  return new XMLCaseStatementAlternativeList();
}

IIR_CaseStatement *
xml_plugin_class_factory::new_IIR_CaseStatement() {
  return new XMLCaseStatement();
}

IIR_CharacterLiteral *
xml_plugin_class_factory::new_IIR_CharacterLiteral() {
  return new XMLCharacterLiteral();
}

IIR_Choice *
xml_plugin_class_factory::new_IIR_Choice() {
  return new XMLChoice();
}

IIR_ChoiceList *
xml_plugin_class_factory::new_IIR_ChoiceList() {
  return new XMLChoiceList();
}

IIR_Comment *
xml_plugin_class_factory::new_IIR_Comment() {
  return new XMLComment();
}

IIR_CommentList *
xml_plugin_class_factory::new_IIR_CommentList() {
  return new XMLCommentList();
}

IIR_ComponentConfiguration *
xml_plugin_class_factory::new_IIR_ComponentConfiguration() {
  return new XMLComponentConfiguration();
}

IIR_ComponentDeclaration *
xml_plugin_class_factory::new_IIR_ComponentDeclaration() {
  return new XMLComponentDeclaration();
}

IIR_ComponentInstantiationStatement *
xml_plugin_class_factory::new_IIR_ComponentInstantiationStatement() {
  return new XMLComponentInstantiationStatement();
}

IIR_ConcatenationOperator *
xml_plugin_class_factory::new_IIR_ConcatenationOperator() {
  return new XMLConcatenationOperator();
}

IIR_ConcurrentAssertionStatement *
xml_plugin_class_factory::new_IIR_ConcurrentAssertionStatement() {
  return new XMLConcurrentAssertionStatement();
}

IIR_ConcurrentBreakStatement *
xml_plugin_class_factory::new_IIR_ConcurrentBreakStatement() {
  return new XMLConcurrentBreakStatement();
}

IIR_ConcurrentConditionalSignalAssignment *
xml_plugin_class_factory::new_IIR_ConcurrentConditionalSignalAssignment() {
  return new XMLConcurrentConditionalSignalAssignment();
}

IIR_ConcurrentGenerateForStatement *
xml_plugin_class_factory::new_IIR_ConcurrentGenerateForStatement() {
  return new XMLConcurrentGenerateForStatement();
}

IIR_ConcurrentGenerateIfStatement *
xml_plugin_class_factory::new_IIR_ConcurrentGenerateIfStatement() {
  return new XMLConcurrentGenerateIfStatement();
}

IIR_ConcurrentProcedureCallStatement *
xml_plugin_class_factory::new_IIR_ConcurrentProcedureCallStatement() {
  return new XMLConcurrentProcedureCallStatement();
}

IIR_ConcurrentSelectedSignalAssignment *
xml_plugin_class_factory::new_IIR_ConcurrentSelectedSignalAssignment() {
  return new XMLConcurrentSelectedSignalAssignment();
}

IIR_ConditionalWaveform *
xml_plugin_class_factory::new_IIR_ConditionalWaveform() {
  return new XMLConditionalWaveform();
}

IIR_ConditionalWaveformList *
xml_plugin_class_factory::new_IIR_ConditionalWaveformList() {
  return new XMLConditionalWaveformList();
}

IIR_ConfigurationDeclaration *
xml_plugin_class_factory::new_IIR_ConfigurationDeclaration() {
  return new XMLConfigurationDeclaration();
}

IIR_ConfigurationItem *
xml_plugin_class_factory::new_IIR_ConfigurationItem() {
  return new XMLConfigurationItem();
}

IIR_ConfigurationItemList *
xml_plugin_class_factory::new_IIR_ConfigurationItemList() {
  return new XMLConfigurationItemList();
}

IIR_ConfigurationSpecification *
xml_plugin_class_factory::new_IIR_ConfigurationSpecification() {
  return new XMLConfigurationSpecification();
}

IIR_ContributionAttribute *
xml_plugin_class_factory::new_IIR_ContributionAttribute() {
  return new XMLContributionAttribute();
}

IIR_ConstantDeclaration *
xml_plugin_class_factory::new_IIR_ConstantDeclaration() {
  return new XMLConstantDeclaration();
}

IIR_ConstantInterfaceDeclaration *
xml_plugin_class_factory::new_IIR_ConstantInterfaceDeclaration() {
  return new XMLConstantInterfaceDeclaration();
}

IIR_DeclarationList *
xml_plugin_class_factory::new_IIR_DeclarationList() {
  return new XMLDeclarationList();
}

IIR_DelayedAttribute *
xml_plugin_class_factory::new_IIR_DelayedAttribute() {
  return new XMLDelayedAttribute();
}

IIR_DesignatorByAll *
xml_plugin_class_factory::new_IIR_DesignatorByAll() {
  return new XMLDesignatorByAll();
}

IIR_DesignatorByOthers *
xml_plugin_class_factory::new_IIR_DesignatorByOthers() {
  return new XMLDesignatorByOthers();
}

IIR_DesignatorExplicit *
xml_plugin_class_factory::new_IIR_DesignatorExplicit() {
  return new XMLDesignatorExplicit();
}

IIR_Designator *
xml_plugin_class_factory::new_IIR_Designator() {
  return new XMLDesignator();
}

IIR_DesignatorList *
xml_plugin_class_factory::new_IIR_DesignatorList() {
  return new XMLDesignatorList();
}

IIR_DesignFile *
xml_plugin_class_factory::new_IIR_DesignFile() {
  return new XMLDesignFile();
}

IIR_DesignFileList *
xml_plugin_class_factory::new_IIR_DesignFileList() {
  return new XMLDesignFileList();
}

IIR_DesignUnitList *
xml_plugin_class_factory::new_IIR_DesignUnitList() {
  return new XMLDesignUnitList();
}

IIR_DisconnectSpecification *
xml_plugin_class_factory::new_IIR_DisconnectSpecification() {
  return new XMLDisconnectSpecification();
}

IIR_DivisionOperator *
xml_plugin_class_factory::new_IIR_DivisionOperator() {
  return new XMLDivisionOperator();
}

IIR_DotAttribute *
xml_plugin_class_factory::new_IIR_DotAttribute() {
  return new XMLDotAttribute();
}

IIR_DrivingAttribute *
xml_plugin_class_factory::new_IIR_DrivingAttribute() {
  return new XMLDrivingAttribute();
}

IIR_DrivingValueAttribute *
xml_plugin_class_factory::new_IIR_DrivingValueAttribute() {
  return new XMLDrivingValueAttribute();
}

IIR_ElementDeclaration *
xml_plugin_class_factory::new_IIR_ElementDeclaration() {
  return new XMLElementDeclaration();
}

IIR_ElementDeclarationList *
xml_plugin_class_factory::new_IIR_ElementDeclarationList() {
  return new XMLElementDeclarationList();
}

IIR_Elsif *
xml_plugin_class_factory::new_IIR_Elsif() {
  return new XMLElsif();
}

IIR_EntityClassEntry *
xml_plugin_class_factory::new_IIR_EntityClassEntry() {
  return new XMLEntityClassEntry();
}

IIR_EntityClassEntryList *
xml_plugin_class_factory::new_IIR_EntityClassEntryList() {
  return new XMLEntityClassEntryList();
}

IIR_EntityDeclaration *
xml_plugin_class_factory::new_IIR_EntityDeclaration() {
  return new XMLEntityDeclaration();
}

IIR_EntityNameList *
xml_plugin_class_factory::new_IIR_EntityNameList() {
  return new XMLEntityNameList();
}

IIR_EnumerationLiteral *
xml_plugin_class_factory::new_IIR_EnumerationLiteral() {
  return new XMLEnumerationLiteral();
}

IIR_EnumerationLiteralList *
xml_plugin_class_factory::new_IIR_EnumerationLiteralList() {
  return new XMLEnumerationLiteralList();
}

IIR_EnumerationSubtypeDefinition *
xml_plugin_class_factory::new_IIR_EnumerationSubtypeDefinition() {
  return new XMLEnumerationSubtypeDefinition();
}

IIR_EnumerationTypeDefinition *
xml_plugin_class_factory::new_IIR_EnumerationTypeDefinition() {
  return new XMLEnumerationTypeDefinition();
}

IIR_EqualityOperator *
xml_plugin_class_factory::new_IIR_EqualityOperator() {
  return new XMLEqualityOperator();
}

IIR_EventAttribute *
xml_plugin_class_factory::new_IIR_EventAttribute() {
  return new XMLEventAttribute();
}

IIR_ExitStatement *
xml_plugin_class_factory::new_IIR_ExitStatement() {
  return new XMLExitStatement();
}

IIR_ExponentiationOperator *
xml_plugin_class_factory::new_IIR_ExponentiationOperator() {
  return new XMLExponentiationOperator();
}

IIR_FileDeclaration *
xml_plugin_class_factory::new_IIR_FileDeclaration() {
  return new XMLFileDeclaration();
}

IIR_FileInterfaceDeclaration *
xml_plugin_class_factory::new_IIR_FileInterfaceDeclaration() {
  return new XMLFileInterfaceDeclaration();
}

IIR_FileTypeDefinition *
xml_plugin_class_factory::new_IIR_FileTypeDefinition() {
  return new XMLFileTypeDefinition();
}

IIR_FloatingPointLiteral32 *
xml_plugin_class_factory::new_IIR_FloatingPointLiteral32() {
  return new XMLFloatingPointLiteral32();
}

IIR_FloatingPointLiteral64 *
xml_plugin_class_factory::new_IIR_FloatingPointLiteral64() {
  return new XMLFloatingPointLiteral64();
}

IIR_FloatingPointLiteral *
xml_plugin_class_factory::new_IIR_FloatingPointLiteral() {
  return new XMLFloatingPointLiteral();
}

IIR_FloatingSubtypeDefinition *
xml_plugin_class_factory::new_IIR_FloatingSubtypeDefinition() {
  return new XMLFloatingSubtypeDefinition();
}

IIR_FloatingTypeDefinition *
xml_plugin_class_factory::new_IIR_FloatingTypeDefinition() {
  return new XMLFloatingTypeDefinition();
}

IIR_ForLoopStatement *
xml_plugin_class_factory::new_IIR_ForLoopStatement() {
  return new XMLForLoopStatement();
}

IIR_FreeQuantityDeclaration *
xml_plugin_class_factory::new_IIR_FreeQuantityDeclaration() {
  return new XMLFreeQuantityDeclaration();
}

IIR_FunctionCall *
xml_plugin_class_factory::new_IIR_FunctionCall() {
  return new XMLFunctionCall();
}

IIR_FunctionDeclaration *
xml_plugin_class_factory::new_IIR_FunctionDeclaration() {
  return new XMLFunctionDeclaration();
}

IIR_GenericList *
xml_plugin_class_factory::new_IIR_GenericList() {
  return new XMLGenericList();
}

IIR_GreaterThanOperator *
xml_plugin_class_factory::new_IIR_GreaterThanOperator() {
  return new XMLGreaterThanOperator();
}

IIR_GreaterThanOrEqualOperator *
xml_plugin_class_factory::new_IIR_GreaterThanOrEqualOperator() {
  return new XMLGreaterThanOrEqualOperator();
}

IIR_GroupConstituent *
xml_plugin_class_factory::new_IIR_GroupConstituent() {
  return new XMLGroupConstituent();
}

IIR_GroupDeclaration *
xml_plugin_class_factory::new_IIR_GroupDeclaration() {
  return new XMLGroupDeclaration();
}

IIR_GroupTemplateDeclaration *
xml_plugin_class_factory::new_IIR_GroupTemplateDeclaration() {
  return new XMLGroupTemplateDeclaration();
}

IIR_HighAttribute *
xml_plugin_class_factory::new_IIR_HighAttribute() {
  return new XMLHighAttribute();
}

IIR_Identifier *
xml_plugin_class_factory::new_IIR_Identifier() {
  return new XMLIdentifier();
}

IIR_IdentifierList *
xml_plugin_class_factory::new_IIR_IdentifierList() {
  return new XMLIdentifierList();
}

IIR_IdentityOperator *
xml_plugin_class_factory::new_IIR_IdentityOperator() {
  return new XMLIdentityOperator();
}

IIR_IfStatement *
xml_plugin_class_factory::new_IIR_IfStatement() {
  return new XMLIfStatement();
}

IIR_ImageAttribute *
xml_plugin_class_factory::new_IIR_ImageAttribute() {
  return new XMLImageAttribute();
}

IIR_IncompleteTypeDefinition *
xml_plugin_class_factory::new_IIR_IncompleteTypeDefinition() {
  return new XMLIncompleteTypeDefinition();
}

IIR_IndexedName *
xml_plugin_class_factory::new_IIR_IndexedName() {
  return new XMLIndexedName();
}

IIR_InequalityOperator *
xml_plugin_class_factory::new_IIR_InequalityOperator() {
  return new XMLInequalityOperator();
}

IIR_InstanceNameAttribute *
xml_plugin_class_factory::new_IIR_InstanceNameAttribute() {
  return new XMLInstanceNameAttribute();
}

IIR_IntegerLiteral32 *
xml_plugin_class_factory::new_IIR_IntegerLiteral32() {
  return new XMLIntegerLiteral32();
}

IIR_IntegerLiteral64 *
xml_plugin_class_factory::new_IIR_IntegerLiteral64() {
  return new XMLIntegerLiteral64();
}

IIR_IntegerLiteral *
xml_plugin_class_factory::new_IIR_IntegerLiteral() {
  return new XMLIntegerLiteral();
}

IIR_IntegerSubtypeDefinition *
xml_plugin_class_factory::new_IIR_IntegerSubtypeDefinition() {
  return new XMLIntegerSubtypeDefinition();
}

IIR_IntegerTypeDefinition *
xml_plugin_class_factory::new_IIR_IntegerTypeDefinition() {
  return new XMLIntegerTypeDefinition();
}

IIR_InterfaceList *
xml_plugin_class_factory::new_IIR_InterfaceList() {
  return new XMLInterfaceList();
}

IIR_Label *
xml_plugin_class_factory::new_IIR_Label() {
  return new XMLLabel();
}

IIR_LastActiveAttribute *
xml_plugin_class_factory::new_IIR_LastActiveAttribute() {
  return new XMLLastActiveAttribute();
}

IIR_LastEventAttribute *
xml_plugin_class_factory::new_IIR_LastEventAttribute() {
  return new XMLLastEventAttribute();
}

IIR_LastValueAttribute *
xml_plugin_class_factory::new_IIR_LastValueAttribute() {
  return new XMLLastValueAttribute();
}

IIR_LeftAttribute *
xml_plugin_class_factory::new_IIR_LeftAttribute() {
  return new XMLLeftAttribute();
}

IIR_LeftOfAttribute *
xml_plugin_class_factory::new_IIR_LeftOfAttribute() {
  return new XMLLeftOfAttribute();
}

IIR_LengthAttribute *
xml_plugin_class_factory::new_IIR_LengthAttribute() {
  return new XMLLengthAttribute();
}

IIR_LessThanOperator *
xml_plugin_class_factory::new_IIR_LessThanOperator() {
  return new XMLLessThanOperator();
}

IIR_LessThanOrEqualOperator *
xml_plugin_class_factory::new_IIR_LessThanOrEqualOperator() {
  return new XMLLessThanOrEqualOperator();
}

IIR_LibraryClause *
xml_plugin_class_factory::new_IIR_LibraryClause() {
  return new XMLLibraryClause();
}

IIR_LibraryDeclaration *
xml_plugin_class_factory::new_IIR_LibraryDeclaration() {
  return new XMLLibraryDeclaration();
}

IIR_LibraryUnitList *
xml_plugin_class_factory::new_IIR_LibraryUnitList() {
  return new XMLLibraryUnitList();
}

IIR_Literal *
xml_plugin_class_factory::new_IIR_Literal() {
  return new XMLLiteral();
}

IIR_LTFAttribute *
xml_plugin_class_factory::new_IIR_LTFAttribute() {
  return new XMLLTFAttribute();
}

IIR_LowAttribute *
xml_plugin_class_factory::new_IIR_LowAttribute() {
  return new XMLLowAttribute();
}

IIR_ModulusOperator *
xml_plugin_class_factory::new_IIR_ModulusOperator() {
  return new XMLModulusOperator();
}

IIR_MultiplicationOperator *
xml_plugin_class_factory::new_IIR_MultiplicationOperator() {
  return new XMLMultiplicationOperator();
}

IIR_Name *
xml_plugin_class_factory::new_IIR_Name() {
  return new XMLName();
}

IIR_NameList *
xml_plugin_class_factory::new_IIR_NameList() {
  return new XMLNameList();
}

IIR_NandOperator *
xml_plugin_class_factory::new_IIR_NandOperator() {
  return new XMLNandOperator();
}

IIR_NatureDeclaration *
xml_plugin_class_factory::new_IIR_NatureDeclaration() {
  return new XMLNatureDeclaration();
}

IIR_NatureDefinition *
xml_plugin_class_factory::new_IIR_NatureDefinition() {
  return new XMLNatureDefinition();
}

IIR_NegationOperator *
xml_plugin_class_factory::new_IIR_NegationOperator() {
  return new XMLNegationOperator();
}

IIR_NextStatement *
xml_plugin_class_factory::new_IIR_NextStatement() {
  return new XMLNextStatement();
}

IIR_NorOperator *
xml_plugin_class_factory::new_IIR_NorOperator() {
  return new XMLNorOperator();
}

IIR_NotOperator *
xml_plugin_class_factory::new_IIR_NotOperator() {
  return new XMLNotOperator();
}

IIR_NullStatement *
xml_plugin_class_factory::new_IIR_NullStatement() {
  return new XMLNullStatement();
}

IIR_OrOperator *
xml_plugin_class_factory::new_IIR_OrOperator() {
  return new XMLOrOperator();
}

IIR_OthersInitialization *
xml_plugin_class_factory::new_IIR_OthersInitialization() {
  return new XMLOthersInitialization();
}

IIR_PackageBodyDeclaration *
xml_plugin_class_factory::new_IIR_PackageBodyDeclaration() {
  return new XMLPackageBodyDeclaration();
}

IIR_PackageDeclaration *
xml_plugin_class_factory::new_IIR_PackageDeclaration() {
  return new XMLPackageDeclaration();
}

IIR_PathNameAttribute *
xml_plugin_class_factory::new_IIR_PathNameAttribute() {
  return new XMLPathNameAttribute();
}

IIR_PhysicalLiteral *
xml_plugin_class_factory::new_IIR_PhysicalLiteral() {
  return new XMLPhysicalLiteral();
}

IIR_PhysicalSubtypeDefinition *
xml_plugin_class_factory::new_IIR_PhysicalSubtypeDefinition() {
  return new XMLPhysicalSubtypeDefinition();
}

IIR_PhysicalTypeDefinition *
xml_plugin_class_factory::new_IIR_PhysicalTypeDefinition() {
  return new XMLPhysicalTypeDefinition();
}

IIR_PhysicalUnit *
xml_plugin_class_factory::new_IIR_PhysicalUnit() {
  return new XMLPhysicalUnit();
}

IIR_PortList *
xml_plugin_class_factory::new_IIR_PortList() {
  return new XMLPortList();
}

IIR_PosAttribute *
xml_plugin_class_factory::new_IIR_PosAttribute() {
  return new XMLPosAttribute();
}

IIR_PredAttribute *
xml_plugin_class_factory::new_IIR_PredAttribute() {
  return new XMLPredAttribute();
}

IIR_ProcedureCallStatement *
xml_plugin_class_factory::new_IIR_ProcedureCallStatement() {
  return new XMLProcedureCallStatement();
}

IIR_ProcedureDeclaration *
xml_plugin_class_factory::new_IIR_ProcedureDeclaration() {
  return new XMLProcedureDeclaration();
}

IIR_ProcessStatement *
xml_plugin_class_factory::new_IIR_ProcessStatement() {
  return new XMLProcessStatement();
}

IIR_QualifiedExpression *
xml_plugin_class_factory::new_IIR_QualifiedExpression() {
  return new XMLQualifiedExpression();
}

IIR_QuantityDeclaration *
xml_plugin_class_factory::new_IIR_QuantityDeclaration() {
  return new XMLQuantityDeclaration();
}

IIR_QuietAttribute *
xml_plugin_class_factory::new_IIR_QuietAttribute() {
  return new XMLQuietAttribute();
}

IIR_RangeAttribute *
xml_plugin_class_factory::new_IIR_RangeAttribute() {
  return new XMLRangeAttribute();
}

IIR_RangeTypeDefinition *
xml_plugin_class_factory::new_IIR_RangeTypeDefinition() {
  return new XMLRangeTypeDefinition();
}

IIR_RecordTypeDefinition *
xml_plugin_class_factory::new_IIR_RecordTypeDefinition() {
  return new XMLRecordTypeDefinition();
}

IIR_ReferenceAttribute *
xml_plugin_class_factory::new_IIR_ReferenceAttribute() {
  return new XMLReferenceAttribute();
}

IIR_RemainderOperator *
xml_plugin_class_factory::new_IIR_RemainderOperator() {
  return new XMLRemainderOperator();
}

IIR_ReportStatement *
xml_plugin_class_factory::new_IIR_ReportStatement() {
  return new XMLReportStatement();
}

IIR_ReturnStatement *
xml_plugin_class_factory::new_IIR_ReturnStatement() {
  return new XMLReturnStatement();
}

IIR_ReverseRangeAttribute *
xml_plugin_class_factory::new_IIR_ReverseRangeAttribute() {
  return new XMLReverseRangeAttribute();
}

IIR_RightAttribute *
xml_plugin_class_factory::new_IIR_RightAttribute() {
  return new XMLRightAttribute();
}

IIR_RightOfAttribute *
xml_plugin_class_factory::new_IIR_RightOfAttribute() {
  return new XMLRightOfAttribute();
}

IIR_ROLOperator *
xml_plugin_class_factory::new_IIR_ROLOperator() {
  return new XMLROLOperator();
}

IIR_ROROperator *
xml_plugin_class_factory::new_IIR_ROROperator() {
  return new XMLROROperator();
}

IIR_ScalarNatureDefinition *
xml_plugin_class_factory::new_IIR_ScalarNatureDefinition() {
  return new XMLScalarNatureDefinition();
}

IIR_SelectedNameByAll *
xml_plugin_class_factory::new_IIR_SelectedNameByAll() {
  return new XMLSelectedNameByAll();
}

IIR_SelectedName *
xml_plugin_class_factory::new_IIR_SelectedName() {
  return new XMLSelectedName();
}

IIR_SelectedWaveform *
xml_plugin_class_factory::new_IIR_SelectedWaveform() {
  return new XMLSelectedWaveform();
}

IIR_SelectedWaveformList *
xml_plugin_class_factory::new_IIR_SelectedWaveformList() {
  return new XMLSelectedWaveformList();
}

IIR_SensitizedProcessStatement *
xml_plugin_class_factory::new_IIR_SensitizedProcessStatement() {
  return new XMLSensitizedProcessStatement();
}

IIR_SequentialStatementList *
xml_plugin_class_factory::new_IIR_SequentialStatementList() {
  return new XMLSequentialStatementList();
}

IIR_SharedVariableDeclaration *
xml_plugin_class_factory::new_IIR_SharedVariableDeclaration() {
  return new XMLSharedVariableDeclaration();
}

IIR_SignalAssignmentStatement *
xml_plugin_class_factory::new_IIR_SignalAssignmentStatement() {
  return new XMLSignalAssignmentStatement();
}

IIR_SignalDeclaration *
xml_plugin_class_factory::new_IIR_SignalDeclaration() {
  return new XMLSignalDeclaration();
}

IIR_SignalInterfaceDeclaration *
xml_plugin_class_factory::new_IIR_SignalInterfaceDeclaration() {
  return new XMLSignalInterfaceDeclaration();
}

IIR_Signature *
xml_plugin_class_factory::new_IIR_Signature() {
  return new XMLSignature();
}

IIR_SimpleNameAttribute *
xml_plugin_class_factory::new_IIR_SimpleNameAttribute() {
  return new XMLSimpleNameAttribute();
}

IIR_SimpleName *
xml_plugin_class_factory::new_IIR_SimpleName() {
  return new XMLSimpleName();
}

IIR_SimpleSimultaneousStatement *
xml_plugin_class_factory::new_IIR_SimpleSimultaneousStatement() {
  return new XMLSimpleSimultaneousStatement();
}

IIR_SimultaneousElsif *
xml_plugin_class_factory::new_IIR_SimultaneousElsif() {
  return new XMLSimultaneousElsif();
}

IIR_SimultaneousIfStatement *
xml_plugin_class_factory::new_IIR_SimultaneousIfStatement() {
  return new XMLSimultaneousIfStatement();
}

IIR_SLAOperator *
xml_plugin_class_factory::new_IIR_SLAOperator() {
  return new XMLSLAOperator();
}

IIR_SliceName *
xml_plugin_class_factory::new_IIR_SliceName() {
  return new XMLSliceName();
}

IIR_SLLOperator *
xml_plugin_class_factory::new_IIR_SLLOperator() {
  return new XMLSLLOperator();
}

IIR_SourceQuantityDeclaration *
xml_plugin_class_factory::new_IIR_SourceQuantityDeclaration() {
  return new XMLSourceQuantityDeclaration();
}

IIR_SRAOperator *
xml_plugin_class_factory::new_IIR_SRAOperator() {
  return new XMLSRAOperator();
}

IIR_SRLOperator *
xml_plugin_class_factory::new_IIR_SRLOperator() {
  return new XMLSRLOperator();
}

IIR_StableAttribute *
xml_plugin_class_factory::new_IIR_StableAttribute() {
  return new XMLStableAttribute();
}

IIR_StringLiteral *
xml_plugin_class_factory::new_IIR_StringLiteral() {
  return new XMLStringLiteral();
}

IIR_SubprogramDeclaration *
xml_plugin_class_factory::new_IIR_SubprogramDeclaration() {
  return new XMLSubprogramDeclaration();
}

IIR_SubtractionOperator *
xml_plugin_class_factory::new_IIR_SubtractionOperator() {
  return new XMLSubtractionOperator();
}

IIR_SubtypeDeclaration *
xml_plugin_class_factory::new_IIR_SubtypeDeclaration() {
  return new XMLSubtypeDeclaration();
}

IIR_SuccAttribute *
xml_plugin_class_factory::new_IIR_SuccAttribute() {
  return new XMLSuccAttribute();
}

IIR_TerminalDeclaration *
xml_plugin_class_factory::new_IIR_TerminalDeclaration() {
  return new XMLTerminalDeclaration();
}

IIR_TerminalInterfaceDeclaration *
xml_plugin_class_factory::new_IIR_TerminalInterfaceDeclaration() {
  return new XMLTerminalInterfaceDeclaration();
}

IIR_TextLiteral *
xml_plugin_class_factory::new_IIR_TextLiteral() {
  return new XMLTextLiteral();
}

IIR_ThroughAttribute *
xml_plugin_class_factory::new_IIR_ThroughAttribute() {
  return new XMLThroughAttribute();
}

IIR_TransactionAttribute *
xml_plugin_class_factory::new_IIR_TransactionAttribute() {
  return new XMLTransactionAttribute();
}

IIR_Tuple *
xml_plugin_class_factory::new_IIR_Tuple() {
  return new XMLTuple();
}

IIR_TypeConversion *
xml_plugin_class_factory::new_IIR_TypeConversion() {
  return new XMLTypeConversion();
}

IIR_TypeDeclaration *
xml_plugin_class_factory::new_IIR_TypeDeclaration() {
  return new XMLTypeDeclaration();
}

IIR_UnitList *
xml_plugin_class_factory::new_IIR_UnitList() {
  return new XMLUnitList();
}

IIR_UseClause *
xml_plugin_class_factory::new_IIR_UseClause() {
  return new XMLUseClause();
}

IIR_UserAttribute *
xml_plugin_class_factory::new_IIR_UserAttribute() {
  return new XMLUserAttribute();
}

IIR_ValAttribute *
xml_plugin_class_factory::new_IIR_ValAttribute() {
  return new XMLValAttribute();
}

IIR_ValueAttribute *
xml_plugin_class_factory::new_IIR_ValueAttribute() {
  return new XMLValueAttribute();
}

IIR_VariableAssignmentStatement *
xml_plugin_class_factory::new_IIR_VariableAssignmentStatement() {
  return new XMLVariableAssignmentStatement();
}

IIR_VariableDeclaration *
xml_plugin_class_factory::new_IIR_VariableDeclaration() {
  return new XMLVariableDeclaration();
}

IIR_VariableInterfaceDeclaration *
xml_plugin_class_factory::new_IIR_VariableInterfaceDeclaration() {
  return new XMLVariableInterfaceDeclaration();
}

IIR_WaitStatement *
xml_plugin_class_factory::new_IIR_WaitStatement() {
  return new XMLWaitStatement();
}

IIR_WaveformElement *
xml_plugin_class_factory::new_IIR_WaveformElement() {
  return new XMLWaveformElement();
}

IIR_WaveformList *
xml_plugin_class_factory::new_IIR_WaveformList() {
  return new XMLWaveformList();
}

IIR_WhileLoopStatement *
xml_plugin_class_factory::new_IIR_WhileLoopStatement() {
  return new XMLWhileLoopStatement();
}

IIR_XnorOperator *
xml_plugin_class_factory::new_IIR_XnorOperator() {
  return new XMLXnorOperator();
}

IIR_XorOperator *
xml_plugin_class_factory::new_IIR_XorOperator() {
  return new XMLXorOperator();
}

IIR_ZTFAttribute *
xml_plugin_class_factory::new_IIR_ZTFAttribute() {
  return new XMLZTFAttribute();
}
