#ifndef SCRAM_PLUGIN_CLASS_FACTORY_HH
#define SCRAM_PLUGIN_CLASS_FACTORY_HH

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

#include "savant_config.hh"
#include "plugin_class_factory.hh"
/** IIRScram implementation of the plugin class factory.  This isn't strictly
    necessary, but large portions of the code base have been refactored to work
    independent of the type of nodes they generate.  Thus IIRScram has become a
    special case of the general plugin methodology, requiring it's own class factory. */
class scram_plugin_class_factory : public plugin_class_factory {
public:
  IIR *get_new_class(IIR_Kind);

  // Various plugin related classes
  StandardPackage                               *get_standard_package();

  // Class return methods
  IIR_AboveAttribute                            *new_IIR_AboveAttribute();
  IIR_AbsoluteOperator                          *new_IIR_AbsoluteOperator();
  IIR_AccessSubtypeDefinition                   *new_IIR_AccessSubtypeDefinition();
  IIR_AccessTypeDefinition                      *new_IIR_AccessTypeDefinition();
  IIR_AcrossAttribute                           *new_IIR_AcrossAttribute();
  IIR_ActiveAttribute                           *new_IIR_ActiveAttribute();
  IIR_AdditionOperator                          *new_IIR_AdditionOperator();
  IIR_Aggregate                                 *new_IIR_Aggregate();
  IIR_AliasDeclaration                          *new_IIR_AliasDeclaration();
  IIR_Allocator                                 *new_IIR_Allocator();
  IIR_AndOperator                               *new_IIR_AndOperator();
  IIR_ArchitectureDeclaration                   *new_IIR_ArchitectureDeclaration();
  IIR_ArchitectureStatement                     *new_IIR_ArchitectureStatement();
  IIR_ArchitectureStatementList                 *new_IIR_ArchitectureStatementList();
  IIR_ArrayNatureDefinition                     *new_IIR_ArrayNatureDefinition();
  IIR_ArraySubnatureDefinition                  *new_IIR_ArraySubnatureDefinition();
  IIR_ArraySubtypeDefinition                    *new_IIR_ArraySubtypeDefinition();
  IIR_ArrayTypeDefinition                       *new_IIR_ArrayTypeDefinition();
  IIR_AscendingAttribute                        *new_IIR_AscendingAttribute();
  IIR_AssertionStatement                        *new_IIR_AssertionStatement();
  IIR_AssociationElementByExpression            *new_IIR_AssociationElementByExpression();
  IIR_AssociationElementOpen                    *new_IIR_AssociationElementOpen();
  IIR_AssociationList                           *new_IIR_AssociationList();
  IIR_AttributeDeclaration                      *new_IIR_AttributeDeclaration();
  IIR_AttributeSpecification                    *new_IIR_AttributeSpecification();
  IIR_AttributeSpecificationList                *new_IIR_AttributeSpecificationList();
  IIR_BaseAttribute                             *new_IIR_BaseAttribute();
  IIR_BitStringLiteral                          *new_IIR_BitStringLiteral();
  IIR_BlockConfiguration                        *new_IIR_BlockConfiguration();
  IIR_BlockStatement                            *new_IIR_BlockStatement();
  IIR_BranchQuantityDeclaration                 *new_IIR_BranchQuantityDeclaration();
  IIR_BreakElement                              *new_IIR_BreakElement();
  IIR_BreakStatement                            *new_IIR_BreakStatement();
  IIR_CaseStatementAlternativeByChoices         *new_IIR_CaseStatementAlternativeByChoices();
  IIR_CaseStatementAlternativeByExpression      *new_IIR_CaseStatementAlternativeByExpression();
  IIR_CaseStatementAlternativeByOthers          *new_IIR_CaseStatementAlternativeByOthers();
  IIR_CaseStatementAlternativeList              *new_IIR_CaseStatementAlternativeList();
  IIR_CaseStatement                             *new_IIR_CaseStatement();
  IIR_CharacterLiteral                          *new_IIR_CharacterLiteral();
  IIR_Choice                                    *new_IIR_Choice();
  IIR_ChoiceList                                *new_IIR_ChoiceList();
  IIR_Comment                                   *new_IIR_Comment();
  IIR_CommentList                               *new_IIR_CommentList();
  IIR_ComponentConfiguration                    *new_IIR_ComponentConfiguration();
  IIR_ComponentDeclaration                      *new_IIR_ComponentDeclaration();
  IIR_ComponentInstantiationStatement           *new_IIR_ComponentInstantiationStatement();
  IIR_ConcatenationOperator                     *new_IIR_ConcatenationOperator();
  IIR_ConcurrentAssertionStatement              *new_IIR_ConcurrentAssertionStatement();
  IIR_ConcurrentBreakStatement                  *new_IIR_ConcurrentBreakStatement();
  IIR_ConcurrentConditionalSignalAssignment     *new_IIR_ConcurrentConditionalSignalAssignment();
  IIR_ConcurrentGenerateForStatement            *new_IIR_ConcurrentGenerateForStatement();
  IIR_ConcurrentGenerateIfStatement             *new_IIR_ConcurrentGenerateIfStatement();
  IIR_ConcurrentProcedureCallStatement          *new_IIR_ConcurrentProcedureCallStatement();
  IIR_ConcurrentSelectedSignalAssignment        *new_IIR_ConcurrentSelectedSignalAssignment();
  IIR_ConditionalWaveform                       *new_IIR_ConditionalWaveform();
  IIR_ConditionalWaveformList                   *new_IIR_ConditionalWaveformList();
  IIR_ConfigurationDeclaration                  *new_IIR_ConfigurationDeclaration();
  IIR_ConfigurationItem                         *new_IIR_ConfigurationItem();
  IIR_ConfigurationItemList                     *new_IIR_ConfigurationItemList();
  IIR_ConfigurationSpecification                *new_IIR_ConfigurationSpecification();
  IIR_ContributionAttribute                     *new_IIR_ContributionAttribute();
  IIR_ConstantDeclaration                       *new_IIR_ConstantDeclaration();
  IIR_ConstantInterfaceDeclaration              *new_IIR_ConstantInterfaceDeclaration();
  IIR_DeclarationList                           *new_IIR_DeclarationList();
  IIR_DelayedAttribute                          *new_IIR_DelayedAttribute();
  IIR_DesignatorByAll                           *new_IIR_DesignatorByAll();
  IIR_DesignatorByOthers                        *new_IIR_DesignatorByOthers();
  IIR_DesignatorExplicit                        *new_IIR_DesignatorExplicit();
  IIR_Designator                                *new_IIR_Designator();
  IIR_DesignatorList                            *new_IIR_DesignatorList();
  IIR_DesignFile                                *new_IIR_DesignFile();
  IIR_DesignFileList                            *new_IIR_DesignFileList();
  IIR_DesignUnitList                            *new_IIR_DesignUnitList();
  IIR_DisconnectSpecification                   *new_IIR_DisconnectSpecification();
  IIR_DivisionOperator                          *new_IIR_DivisionOperator();
  IIR_DotAttribute                              *new_IIR_DotAttribute();
  IIR_DrivingAttribute                          *new_IIR_DrivingAttribute();
  IIR_DrivingValueAttribute                     *new_IIR_DrivingValueAttribute();
  IIR_ElementDeclaration                        *new_IIR_ElementDeclaration();
  IIR_ElementDeclarationList                    *new_IIR_ElementDeclarationList();
  IIR_Elsif                                     *new_IIR_Elsif();
  IIR_EntityClassEntry                          *new_IIR_EntityClassEntry();
  IIR_EntityClassEntryList                      *new_IIR_EntityClassEntryList();
  IIR_EntityDeclaration                         *new_IIR_EntityDeclaration();
  IIR_EntityNameList                            *new_IIR_EntityNameList();
  IIR_EnumerationLiteral                        *new_IIR_EnumerationLiteral();
  IIR_EnumerationLiteralList                    *new_IIR_EnumerationLiteralList();
  IIR_EnumerationSubtypeDefinition              *new_IIR_EnumerationSubtypeDefinition();
  IIR_EnumerationTypeDefinition                 *new_IIR_EnumerationTypeDefinition();
  IIR_EqualityOperator                          *new_IIR_EqualityOperator();
  IIR_EventAttribute                            *new_IIR_EventAttribute();
  IIR_ExitStatement                             *new_IIR_ExitStatement();
  IIR_ExponentiationOperator                    *new_IIR_ExponentiationOperator();
  IIR_FileDeclaration                           *new_IIR_FileDeclaration();
  IIR_FileInterfaceDeclaration                  *new_IIR_FileInterfaceDeclaration();
  IIR_FileTypeDefinition                        *new_IIR_FileTypeDefinition();
  IIR_FloatingPointLiteral32                    *new_IIR_FloatingPointLiteral32();
  IIR_FloatingPointLiteral64                    *new_IIR_FloatingPointLiteral64();
  IIR_FloatingPointLiteral                      *new_IIR_FloatingPointLiteral();
  IIR_FloatingSubtypeDefinition                 *new_IIR_FloatingSubtypeDefinition();
  IIR_FloatingTypeDefinition                    *new_IIR_FloatingTypeDefinition();
  IIR_ForLoopStatement                          *new_IIR_ForLoopStatement();
  IIR_FreeQuantityDeclaration                   *new_IIR_FreeQuantityDeclaration();
  IIR_FunctionCall                              *new_IIR_FunctionCall();
  IIR_FunctionDeclaration                       *new_IIR_FunctionDeclaration();
  IIR_GenericList                               *new_IIR_GenericList();
  IIR_GreaterThanOperator                       *new_IIR_GreaterThanOperator();
  IIR_GreaterThanOrEqualOperator                *new_IIR_GreaterThanOrEqualOperator();
  IIR_GroupConstituent                          *new_IIR_GroupConstituent();
  IIR_GroupDeclaration                          *new_IIR_GroupDeclaration();
  IIR_GroupTemplateDeclaration                  *new_IIR_GroupTemplateDeclaration();
  IIR_HighAttribute                             *new_IIR_HighAttribute();
  IIR_Identifier                                *new_IIR_Identifier();
  IIR_IdentifierList                            *new_IIR_IdentifierList();
  IIR_IdentityOperator                          *new_IIR_IdentityOperator();
  IIR_IfStatement                               *new_IIR_IfStatement();
  IIR_ImageAttribute                            *new_IIR_ImageAttribute();
  IIR_IncompleteTypeDefinition                  *new_IIR_IncompleteTypeDefinition();
  IIR_IndexedName                               *new_IIR_IndexedName();
  IIR_InequalityOperator                        *new_IIR_InequalityOperator();
  IIR_InstanceNameAttribute                     *new_IIR_InstanceNameAttribute();
  IIR_IntegerLiteral32                          *new_IIR_IntegerLiteral32();
  IIR_IntegerLiteral64                          *new_IIR_IntegerLiteral64();
  IIR_IntegerLiteral                            *new_IIR_IntegerLiteral();
  IIR_IntegerSubtypeDefinition                  *new_IIR_IntegerSubtypeDefinition();
  IIR_IntegerTypeDefinition                     *new_IIR_IntegerTypeDefinition();
  IIR_InterfaceList                             *new_IIR_InterfaceList();
  IIR_Label                                     *new_IIR_Label();
  IIR_LastActiveAttribute                       *new_IIR_LastActiveAttribute();
  IIR_LastEventAttribute                        *new_IIR_LastEventAttribute();
  IIR_LastValueAttribute                        *new_IIR_LastValueAttribute();
  IIR_LeftAttribute                             *new_IIR_LeftAttribute();
  IIR_LeftOfAttribute                           *new_IIR_LeftOfAttribute();
  IIR_LengthAttribute                           *new_IIR_LengthAttribute();
  IIR_LessThanOperator                          *new_IIR_LessThanOperator();
  IIR_LessThanOrEqualOperator                   *new_IIR_LessThanOrEqualOperator();
  IIR_LibraryClause                             *new_IIR_LibraryClause();
  IIR_LibraryDeclaration                        *new_IIR_LibraryDeclaration();
  IIR_LibraryUnitList                           *new_IIR_LibraryUnitList();
  IIR_Literal                                   *new_IIR_Literal();
  IIR_LTFAttribute                              *new_IIR_LTFAttribute();
  IIR_LowAttribute                              *new_IIR_LowAttribute();
  IIR_ModulusOperator                           *new_IIR_ModulusOperator();
  IIR_MultiplicationOperator                    *new_IIR_MultiplicationOperator();
  IIR_Name                                      *new_IIR_Name();
  IIR_NameList                                  *new_IIR_NameList();
  IIR_NandOperator                              *new_IIR_NandOperator();
  IIR_NatureDeclaration                         *new_IIR_NatureDeclaration();
  IIR_NatureDefinition                          *new_IIR_NatureDefinition();
  IIR_NegationOperator                          *new_IIR_NegationOperator();
  IIR_NextStatement                             *new_IIR_NextStatement();
  IIR_NorOperator                               *new_IIR_NorOperator();
  IIR_NotOperator                               *new_IIR_NotOperator();
  IIR_NullStatement                             *new_IIR_NullStatement();
  IIR_OrOperator                                *new_IIR_OrOperator();
  IIR_OthersInitialization                      *new_IIR_OthersInitialization();
  IIR_PackageBodyDeclaration                    *new_IIR_PackageBodyDeclaration();
  IIR_PackageDeclaration                        *new_IIR_PackageDeclaration();
  IIR_PathNameAttribute                         *new_IIR_PathNameAttribute();
  IIR_PhysicalLiteral                           *new_IIR_PhysicalLiteral();
  IIR_PhysicalSubtypeDefinition                 *new_IIR_PhysicalSubtypeDefinition();
  IIR_PhysicalTypeDefinition                    *new_IIR_PhysicalTypeDefinition();
  IIR_PhysicalUnit                              *new_IIR_PhysicalUnit();
  IIR_PortList                                  *new_IIR_PortList();
  IIR_PosAttribute                              *new_IIR_PosAttribute();
  IIR_PredAttribute                             *new_IIR_PredAttribute();
  IIR_ProcedureCallStatement                    *new_IIR_ProcedureCallStatement();
  IIR_ProcedureDeclaration                      *new_IIR_ProcedureDeclaration();
  IIR_ProcessStatement                          *new_IIR_ProcessStatement();
  IIR_QualifiedExpression                       *new_IIR_QualifiedExpression();
  IIR_QuantityDeclaration                       *new_IIR_QuantityDeclaration();
  IIR_QuietAttribute                            *new_IIR_QuietAttribute();
  IIR_RangeAttribute                            *new_IIR_RangeAttribute();
  IIR_RangeTypeDefinition                       *new_IIR_RangeTypeDefinition();
  IIR_RecordTypeDefinition                      *new_IIR_RecordTypeDefinition();
  IIR_ReferenceAttribute                        *new_IIR_ReferenceAttribute();
  IIR_RemainderOperator                         *new_IIR_RemainderOperator();
  IIR_ReportStatement                           *new_IIR_ReportStatement();
  IIR_ReturnStatement                           *new_IIR_ReturnStatement();
  IIR_ReverseRangeAttribute                     *new_IIR_ReverseRangeAttribute();
  IIR_RightAttribute                            *new_IIR_RightAttribute();
  IIR_RightOfAttribute                          *new_IIR_RightOfAttribute();
  IIR_ROLOperator                               *new_IIR_ROLOperator();
  IIR_ROROperator                               *new_IIR_ROROperator();
  IIR_ScalarNatureDefinition                    *new_IIR_ScalarNatureDefinition();
  IIR_SelectedNameByAll                         *new_IIR_SelectedNameByAll();
  IIR_SelectedName                              *new_IIR_SelectedName();
  IIR_SelectedWaveform                          *new_IIR_SelectedWaveform();
  IIR_SelectedWaveformList                      *new_IIR_SelectedWaveformList();
  IIR_SensitizedProcessStatement                *new_IIR_SensitizedProcessStatement();
  IIR_SequentialStatementList                   *new_IIR_SequentialStatementList();
  IIR_SharedVariableDeclaration                 *new_IIR_SharedVariableDeclaration();
  IIR_SignalAssignmentStatement                 *new_IIR_SignalAssignmentStatement();
  IIR_SignalDeclaration                         *new_IIR_SignalDeclaration();
  IIR_SignalInterfaceDeclaration                *new_IIR_SignalInterfaceDeclaration();
  IIR_Signature                                 *new_IIR_Signature();
  IIR_SimpleNameAttribute                       *new_IIR_SimpleNameAttribute();
  IIR_SimpleName                                *new_IIR_SimpleName();
  IIR_SimpleSimultaneousStatement               *new_IIR_SimpleSimultaneousStatement();
  IIR_SimultaneousElsif                         *new_IIR_SimultaneousElsif();
  IIR_SimultaneousIfStatement                   *new_IIR_SimultaneousIfStatement();
  IIR_SLAOperator                               *new_IIR_SLAOperator();
  IIR_SliceName                                 *new_IIR_SliceName();
  IIR_SLLOperator                               *new_IIR_SLLOperator();
  IIR_SourceQuantityDeclaration                 *new_IIR_SourceQuantityDeclaration();
  IIR_SRAOperator                               *new_IIR_SRAOperator();
  IIR_SRLOperator                               *new_IIR_SRLOperator();
  IIR_StableAttribute                           *new_IIR_StableAttribute();
  IIR_StringLiteral                             *new_IIR_StringLiteral();
  IIR_SubprogramDeclaration                     *new_IIR_SubprogramDeclaration();
  IIR_SubtractionOperator                       *new_IIR_SubtractionOperator();
  IIR_SubtypeDeclaration                        *new_IIR_SubtypeDeclaration();
  IIR_SuccAttribute                             *new_IIR_SuccAttribute();
  IIR_TerminalDeclaration                       *new_IIR_TerminalDeclaration();
  IIR_TerminalInterfaceDeclaration              *new_IIR_TerminalInterfaceDeclaration();
  IIR_TextLiteral                               *new_IIR_TextLiteral();
  IIR_ThroughAttribute                          *new_IIR_ThroughAttribute();
  IIR_TransactionAttribute                      *new_IIR_TransactionAttribute();
  IIR_Tuple                                     *new_IIR_Tuple();
  IIR_TypeConversion                            *new_IIR_TypeConversion();
  IIR_TypeDeclaration                           *new_IIR_TypeDeclaration();
  IIR_UnitList                                  *new_IIR_UnitList();
  IIR_UseClause                                 *new_IIR_UseClause();
  IIR_UserAttribute                             *new_IIR_UserAttribute();
  IIR_ValAttribute                              *new_IIR_ValAttribute();
  IIR_ValueAttribute                            *new_IIR_ValueAttribute();
  IIR_VariableAssignmentStatement               *new_IIR_VariableAssignmentStatement();
  IIR_VariableDeclaration                       *new_IIR_VariableDeclaration();
  IIR_VariableInterfaceDeclaration              *new_IIR_VariableInterfaceDeclaration();
  IIR_WaitStatement                             *new_IIR_WaitStatement();
  IIR_WaveformElement                           *new_IIR_WaveformElement();
  IIR_WaveformList                              *new_IIR_WaveformList();
  IIR_WhileLoopStatement                        *new_IIR_WhileLoopStatement();
  IIR_XnorOperator                              *new_IIR_XnorOperator();
  IIR_XorOperator                               *new_IIR_XorOperator();
  IIR_ZTFAttribute                              *new_IIR_ZTFAttribute();

  /** Access the singleton. */
  static plugin_class_factory *instance();

private:
  StandardPackage *new_StandardPackage();

  scram_plugin_class_factory(){}
  virtual ~scram_plugin_class_factory(){}
};
#endif
