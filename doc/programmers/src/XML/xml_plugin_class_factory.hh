#ifndef XML_PLUGIN_CLASS_FACTORY_HH
#define XML_PLUGIN_CLASS_FACTORY_HH
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
#include "savant/plugin_class_factory.hh"
//class IIR_AssociationElement;
//class IIR_CaseStatementAlternative;

class xml_plugin_class_factory : public plugin_class_factory {
public:

  virtual xml_plugin_class_factory *instance();
  virtual StandardPackage *get_standard_package();

  /** Returns a standard package.  This is a special case, since we need to create a standard package in a few places
      but there isn't a IIR_Kind associated with it. */
  virtual StandardPackage                               *new_StandardPackage();

  /** @name Create nodes
      Methods for creating specific nodes
  */
  //@{
  /** Returns the new class based on the passed in IIR_Kind type. */
  virtual IIR* get_new_class(IIR_Kind);

  virtual IIR_AbsoluteOperator                          *new_IIR_AbsoluteOperator();
  virtual IIR_AccessSubtypeDefinition                   *new_IIR_AccessSubtypeDefinition();
  virtual IIR_AccessTypeDefinition                      *new_IIR_AccessTypeDefinition();
  virtual IIR_AcrossAttribute                           *new_IIR_AcrossAttribute();
  virtual IIR_ActiveAttribute                           *new_IIR_ActiveAttribute();
  virtual IIR_AdditionOperator                          *new_IIR_AdditionOperator();
  virtual IIR_Aggregate                                 *new_IIR_Aggregate();
  virtual IIR_AliasDeclaration                          *new_IIR_AliasDeclaration();
  virtual IIR_Allocator                                 *new_IIR_Allocator();
  virtual IIR_AndOperator                               *new_IIR_AndOperator();
  virtual IIR_ArchitectureDeclaration                   *new_IIR_ArchitectureDeclaration();
  virtual IIR_ArchitectureStatement                     *new_IIR_ArchitectureStatement();
  virtual IIR_ArchitectureStatementList                 *new_IIR_ArchitectureStatementList();
  virtual IIR_ArrayNatureDefinition                     *new_IIR_ArrayNatureDefinition();
  virtual IIR_ArraySubnatureDefinition                  *new_IIR_ArraySubnatureDefinition();
  virtual IIR_ArraySubtypeDefinition                    *new_IIR_ArraySubtypeDefinition();
  virtual IIR_ArrayTypeDefinition                       *new_IIR_ArrayTypeDefinition();
  virtual IIR_AscendingAttribute                        *new_IIR_AscendingAttribute();
  virtual IIR_AssertionStatement                        *new_IIR_AssertionStatement();
  virtual IIR_AssociationElementByExpression            *new_IIR_AssociationElementByExpression();
  //  virtual IIR_AssociationElement                        *new_IIR_AssociationElement();
  virtual IIR_AssociationElementOpen                    *new_IIR_AssociationElementOpen();
  virtual IIR_AssociationList                           *new_IIR_AssociationList();
  virtual IIR_AttributeDeclaration                      *new_IIR_AttributeDeclaration();
  virtual IIR_Attribute                                 *new_IIR_Attribute();
  virtual IIR_AttributeSpecification                    *new_IIR_AttributeSpecification();
  virtual IIR_AttributeSpecificationList                *new_IIR_AttributeSpecificationList();
  virtual IIR_BaseAttribute                             *new_IIR_BaseAttribute();
  virtual IIR_BitStringLiteral                          *new_IIR_BitStringLiteral();
  virtual IIR_BlockConfiguration                        *new_IIR_BlockConfiguration();
  virtual IIR_BlockStatement                            *new_IIR_BlockStatement();
  virtual IIR_BranchQuantityDeclaration                 *new_IIR_BranchQuantityDeclaration();
  virtual IIR_BreakElement                              *new_IIR_BreakElement();
  virtual IIR_BreakStatement                            *new_IIR_BreakStatement();
  virtual IIR_CaseStatementAlternativeByChoices         *new_IIR_CaseStatementAlternativeByChoices();
  virtual IIR_CaseStatementAlternativeByExpression      *new_IIR_CaseStatementAlternativeByExpression();
  virtual IIR_CaseStatementAlternativeByOthers          *new_IIR_CaseStatementAlternativeByOthers();
  //  virtual IIR_CaseStatementAlternative                  *new_IIR_CaseStatementAlternative();
  virtual IIR_CaseStatementAlternativeList              *new_IIR_CaseStatementAlternativeList();
  virtual IIR_CaseStatement                             *new_IIR_CaseStatement();
  virtual IIR_CharacterLiteral                          *new_IIR_CharacterLiteral();
  virtual IIR_Choice                                    *new_IIR_Choice();
  virtual IIR_ChoiceList                                *new_IIR_ChoiceList();
  virtual IIR_Comment                                   *new_IIR_Comment();
  virtual IIR_CommentList                               *new_IIR_CommentList();
  virtual IIR_ComponentConfiguration                    *new_IIR_ComponentConfiguration();
  virtual IIR_ComponentDeclaration                      *new_IIR_ComponentDeclaration();
  virtual IIR_ComponentInstantiationStatement           *new_IIR_ComponentInstantiationStatement();
  virtual IIR_ConcatenationOperator                     *new_IIR_ConcatenationOperator();
  virtual IIR_ConcurrentAssertionStatement              *new_IIR_ConcurrentAssertionStatement();
  virtual IIR_ConcurrentBreakStatement                  *new_IIR_ConcurrentBreakStatement();
  virtual IIR_ConcurrentConditionalSignalAssignment     *new_IIR_ConcurrentConditionalSignalAssignment();
  virtual IIR_ConcurrentGenerateForStatement            *new_IIR_ConcurrentGenerateForStatement();
  virtual IIR_ConcurrentGenerateIfStatement             *new_IIR_ConcurrentGenerateIfStatement();
  virtual IIR_ConcurrentProcedureCallStatement          *new_IIR_ConcurrentProcedureCallStatement();
  virtual IIR_ConcurrentSelectedSignalAssignment        *new_IIR_ConcurrentSelectedSignalAssignment();
  virtual IIR_ConditionalWaveform                       *new_IIR_ConditionalWaveform();
  virtual IIR_ConditionalWaveformList                   *new_IIR_ConditionalWaveformList();
  virtual IIR_ConfigurationDeclaration                  *new_IIR_ConfigurationDeclaration();
  virtual IIR_ConfigurationItem                         *new_IIR_ConfigurationItem();
  virtual IIR_ConfigurationItemList                     *new_IIR_ConfigurationItemList();
  virtual IIR_ConfigurationSpecification                *new_IIR_ConfigurationSpecification();
  virtual IIR_ContributionAttribute                     *new_IIR_ContributionAttribute();
  virtual IIR_ConstantDeclaration                       *new_IIR_ConstantDeclaration();
  virtual IIR_ConstantInterfaceDeclaration              *new_IIR_ConstantInterfaceDeclaration();
  virtual IIR_DeclarationList                           *new_IIR_DeclarationList();
  virtual IIR_DelayedAttribute                          *new_IIR_DelayedAttribute();
  virtual IIR_DesignatorByAll                           *new_IIR_DesignatorByAll();
  virtual IIR_DesignatorByOthers                        *new_IIR_DesignatorByOthers();
  virtual IIR_DesignatorExplicit                        *new_IIR_DesignatorExplicit();
  virtual IIR_Designator                                *new_IIR_Designator();
  virtual IIR_DesignatorList                            *new_IIR_DesignatorList();
  virtual IIR_DesignFile                                *new_IIR_DesignFile();
  virtual IIR_DesignFileList                            *new_IIR_DesignFileList();
  virtual IIR_DesignUnitList                            *new_IIR_DesignUnitList();
  virtual IIR_DisconnectSpecification                   *new_IIR_DisconnectSpecification();
  virtual IIR_DivisionOperator                          *new_IIR_DivisionOperator();
  virtual IIR_DotAttribute                              *new_IIR_DotAttribute();
  virtual IIR_DrivingAttribute                          *new_IIR_DrivingAttribute();
  virtual IIR_DrivingValueAttribute                     *new_IIR_DrivingValueAttribute();
  virtual IIR_ElementDeclaration                        *new_IIR_ElementDeclaration();
  virtual IIR_ElementDeclarationList                    *new_IIR_ElementDeclarationList();
  virtual IIR_Elsif                                     *new_IIR_Elsif();
  virtual IIR_EntityClassEntry                          *new_IIR_EntityClassEntry();
  virtual IIR_EntityClassEntryList                      *new_IIR_EntityClassEntryList();
  virtual IIR_EntityDeclaration                         *new_IIR_EntityDeclaration();
  virtual IIR_EntityNameList                            *new_IIR_EntityNameList();
  virtual IIR_EnumerationLiteral                        *new_IIR_EnumerationLiteral();
  virtual IIR_EnumerationLiteralList                    *new_IIR_EnumerationLiteralList();
  virtual IIR_EnumerationSubtypeDefinition              *new_IIR_EnumerationSubtypeDefinition();
  virtual IIR_EnumerationTypeDefinition                 *new_IIR_EnumerationTypeDefinition();
  virtual IIR_EqualityOperator                          *new_IIR_EqualityOperator();
  virtual IIR_EventAttribute                            *new_IIR_EventAttribute();
  virtual IIR_ExitStatement                             *new_IIR_ExitStatement();
  virtual IIR_ExponentiationOperator                    *new_IIR_ExponentiationOperator();
  virtual IIR_FileDeclaration                           *new_IIR_FileDeclaration();
  virtual IIR_FileInterfaceDeclaration                  *new_IIR_FileInterfaceDeclaration();
  virtual IIR_FileTypeDefinition                        *new_IIR_FileTypeDefinition();
  virtual IIR_FloatingPointLiteral32                    *new_IIR_FloatingPointLiteral32();
  virtual IIR_FloatingPointLiteral64                    *new_IIR_FloatingPointLiteral64();
  virtual IIR_FloatingPointLiteral                      *new_IIR_FloatingPointLiteral();
  virtual IIR_FloatingSubtypeDefinition                 *new_IIR_FloatingSubtypeDefinition();
  virtual IIR_FloatingTypeDefinition                    *new_IIR_FloatingTypeDefinition();
  virtual IIR_ForLoopStatement                          *new_IIR_ForLoopStatement();
  virtual IIR_FreeQuantityDeclaration                   *new_IIR_FreeQuantityDeclaration();
  virtual IIR_FunctionCall                              *new_IIR_FunctionCall();
  virtual IIR_FunctionDeclaration                       *new_IIR_FunctionDeclaration();
  virtual IIR_GenericList                               *new_IIR_GenericList();
  virtual IIR_GreaterThanOperator                       *new_IIR_GreaterThanOperator();
  virtual IIR_GreaterThanOrEqualOperator                *new_IIR_GreaterThanOrEqualOperator();
  virtual IIR_GroupConstituent                          *new_IIR_GroupConstituent();
  virtual IIR_GroupDeclaration                          *new_IIR_GroupDeclaration();
  virtual IIR_GroupTemplateDeclaration                  *new_IIR_GroupTemplateDeclaration();
  virtual IIR_HighAttribute                             *new_IIR_HighAttribute();
  virtual IIR_Identifier                                *new_IIR_Identifier();
  virtual IIR_IdentifierList                            *new_IIR_IdentifierList();
  virtual IIR_IdentityOperator                          *new_IIR_IdentityOperator();
  virtual IIR_IfStatement                               *new_IIR_IfStatement();
  virtual IIR_ImageAttribute                            *new_IIR_ImageAttribute();
  virtual IIR_IncompleteTypeDefinition                  *new_IIR_IncompleteTypeDefinition();
  virtual IIR_IndexedName                               *new_IIR_IndexedName();
  virtual IIR_InequalityOperator                        *new_IIR_InequalityOperator();
  virtual IIR_InstanceNameAttribute                     *new_IIR_InstanceNameAttribute();
  virtual IIR_IntegerLiteral32                          *new_IIR_IntegerLiteral32();
  virtual IIR_IntegerLiteral64                          *new_IIR_IntegerLiteral64();
  virtual IIR_IntegerLiteral                            *new_IIR_IntegerLiteral();
  virtual IIR_IntegerSubtypeDefinition                  *new_IIR_IntegerSubtypeDefinition();
  virtual IIR_IntegerTypeDefinition                     *new_IIR_IntegerTypeDefinition();
  virtual IIR_InterfaceList                             *new_IIR_InterfaceList();
  virtual IIR_Label                                     *new_IIR_Label();
  virtual IIR_LastActiveAttribute                       *new_IIR_LastActiveAttribute();
  virtual IIR_LastEventAttribute                        *new_IIR_LastEventAttribute();
  virtual IIR_LastValueAttribute                        *new_IIR_LastValueAttribute();
  virtual IIR_LeftAttribute                             *new_IIR_LeftAttribute();
  virtual IIR_LeftOfAttribute                           *new_IIR_LeftOfAttribute();
  virtual IIR_LengthAttribute                           *new_IIR_LengthAttribute();
  virtual IIR_LessThanOperator                          *new_IIR_LessThanOperator();
  virtual IIR_LessThanOrEqualOperator                   *new_IIR_LessThanOrEqualOperator();
  virtual IIR_LibraryClause                             *new_IIR_LibraryClause();
  virtual IIR_LibraryDeclaration                        *new_IIR_LibraryDeclaration();
  virtual IIR_LibraryUnitList                           *new_IIR_LibraryUnitList();
  virtual IIR_Literal                                   *new_IIR_Literal();
  virtual IIR_LowAttribute                              *new_IIR_LowAttribute();
  virtual IIR_LTFAttribute                              *new_IIR_LTFAttribute();
  virtual IIR_ModulusOperator                           *new_IIR_ModulusOperator();
  virtual IIR_MultiplicationOperator                    *new_IIR_MultiplicationOperator();
  virtual IIR_Name                                      *new_IIR_Name();
  virtual IIR_NameList                                  *new_IIR_NameList();
  virtual IIR_NandOperator                              *new_IIR_NandOperator();
  virtual IIR_NatureDeclaration                         *new_IIR_NatureDeclaration();
  virtual IIR_NatureDefinition                          *new_IIR_NatureDefinition();
  virtual IIR_NegationOperator                          *new_IIR_NegationOperator();
  virtual IIR_NextStatement                             *new_IIR_NextStatement();
  virtual IIR_NorOperator                               *new_IIR_NorOperator();
  virtual IIR_NotOperator                               *new_IIR_NotOperator();
  virtual IIR_NullStatement                             *new_IIR_NullStatement();
  virtual IIR_OrOperator                                *new_IIR_OrOperator();
  virtual IIR_OthersInitialization                      *new_IIR_OthersInitialization();
  virtual IIR_PackageBodyDeclaration                    *new_IIR_PackageBodyDeclaration();
  virtual IIR_PackageDeclaration                        *new_IIR_PackageDeclaration();
  virtual IIR_PathNameAttribute                         *new_IIR_PathNameAttribute();
  virtual IIR_PhysicalLiteral                           *new_IIR_PhysicalLiteral();
  virtual IIR_PhysicalSubtypeDefinition                 *new_IIR_PhysicalSubtypeDefinition();
  virtual IIR_PhysicalTypeDefinition                    *new_IIR_PhysicalTypeDefinition();
  virtual IIR_PhysicalUnit                              *new_IIR_PhysicalUnit();
  virtual IIR_PortList                                  *new_IIR_PortList();
  virtual IIR_PosAttribute                              *new_IIR_PosAttribute();
  virtual IIR_PredAttribute                             *new_IIR_PredAttribute();
  virtual IIR_ProcedureCallStatement                    *new_IIR_ProcedureCallStatement();
  virtual IIR_ProcedureDeclaration                      *new_IIR_ProcedureDeclaration();
  virtual IIR_ProcessStatement                          *new_IIR_ProcessStatement();
  virtual IIR_QualifiedExpression                       *new_IIR_QualifiedExpression();
  virtual IIR_QuantityDeclaration                       *new_IIR_QuantityDeclaration();
  virtual IIR_QuietAttribute                            *new_IIR_QuietAttribute();
  virtual IIR_RangeAttribute                            *new_IIR_RangeAttribute();
  virtual IIR_RangeTypeDefinition                       *new_IIR_RangeTypeDefinition();
  virtual IIR_RecordTypeDefinition                      *new_IIR_RecordTypeDefinition();
  virtual IIR_ReferenceAttribute                        *new_IIR_ReferenceAttribute();
  virtual IIR_RemainderOperator                         *new_IIR_RemainderOperator();
  virtual IIR_ReportStatement                           *new_IIR_ReportStatement();
  virtual IIR_ReturnStatement                           *new_IIR_ReturnStatement();
  virtual IIR_ReverseRangeAttribute                     *new_IIR_ReverseRangeAttribute();
  virtual IIR_RightAttribute                            *new_IIR_RightAttribute();
  virtual IIR_RightOfAttribute                          *new_IIR_RightOfAttribute();
  virtual IIR_ROLOperator                               *new_IIR_ROLOperator();
  virtual IIR_ROROperator                               *new_IIR_ROROperator();
  virtual IIR_ScalarNatureDefinition                    *new_IIR_ScalarNatureDefinition();
  virtual IIR_SelectedNameByAll                         *new_IIR_SelectedNameByAll();
  virtual IIR_SelectedName                              *new_IIR_SelectedName();
  virtual IIR_SelectedWaveform                          *new_IIR_SelectedWaveform();
  virtual IIR_SelectedWaveformList                      *new_IIR_SelectedWaveformList();
  virtual IIR_SensitizedProcessStatement                *new_IIR_SensitizedProcessStatement();
  virtual IIR_SequentialStatementList                   *new_IIR_SequentialStatementList();
  virtual IIR_SharedVariableDeclaration                 *new_IIR_SharedVariableDeclaration();
  virtual IIR_SignalAssignmentStatement                 *new_IIR_SignalAssignmentStatement();
  virtual IIR_SignalDeclaration                         *new_IIR_SignalDeclaration();
  virtual IIR_SignalInterfaceDeclaration                *new_IIR_SignalInterfaceDeclaration();
  virtual IIR_Signature                                 *new_IIR_Signature();
  virtual IIR_SimpleNameAttribute                       *new_IIR_SimpleNameAttribute();
  virtual IIR_SimpleName                                *new_IIR_SimpleName();
  virtual IIR_SimpleSimultaneousStatement               *new_IIR_SimpleSimultaneousStatement();
  virtual IIR_SimultaneousElsif                         *new_IIR_SimultaneousElsif();
  virtual IIR_SimultaneousIfStatement                   *new_IIR_SimultaneousIfStatement();
  virtual IIR_SLAOperator                               *new_IIR_SLAOperator();
  virtual IIR_SliceName                                 *new_IIR_SliceName();
  virtual IIR_SLLOperator                               *new_IIR_SLLOperator();
  virtual IIR_SourceQuantityDeclaration                 *new_IIR_SourceQuantityDeclaration();
  virtual IIR_SRAOperator                               *new_IIR_SRAOperator();
  virtual IIR_SRLOperator                               *new_IIR_SRLOperator();
  virtual IIR_StableAttribute                           *new_IIR_StableAttribute();
  virtual IIR_StringLiteral                             *new_IIR_StringLiteral();
  virtual IIR_SubprogramDeclaration                     *new_IIR_SubprogramDeclaration();
  virtual IIR_SubtractionOperator                       *new_IIR_SubtractionOperator();
  virtual IIR_SubtypeDeclaration                        *new_IIR_SubtypeDeclaration();
  virtual IIR_SuccAttribute                             *new_IIR_SuccAttribute();
  virtual IIR_TerminalDeclaration                       *new_IIR_TerminalDeclaration();
  virtual IIR_TerminalInterfaceDeclaration              *new_IIR_TerminalInterfaceDeclaration();
  virtual IIR_TextLiteral                               *new_IIR_TextLiteral();
  virtual IIR_ThroughAttribute                          *new_IIR_ThroughAttribute();
  virtual IIR_TransactionAttribute                      *new_IIR_TransactionAttribute();
  virtual IIR_Tuple                                     *new_IIR_Tuple();
  virtual IIR_TypeConversion                            *new_IIR_TypeConversion();
  virtual IIR_TypeDeclaration                           *new_IIR_TypeDeclaration();
  virtual IIR_UnitList                                  *new_IIR_UnitList();
  virtual IIR_UseClause                                 *new_IIR_UseClause();
  virtual IIR_UserAttribute                             *new_IIR_UserAttribute();
  virtual IIR_ValAttribute                              *new_IIR_ValAttribute();
  virtual IIR_ValueAttribute                            *new_IIR_ValueAttribute();
  virtual IIR_VariableAssignmentStatement               *new_IIR_VariableAssignmentStatement();
  virtual IIR_VariableDeclaration                       *new_IIR_VariableDeclaration();
  virtual IIR_VariableInterfaceDeclaration              *new_IIR_VariableInterfaceDeclaration();
  virtual IIR_WaitStatement                             *new_IIR_WaitStatement();
  virtual IIR_WaveformElement                           *new_IIR_WaveformElement();
  virtual IIR_WaveformList                              *new_IIR_WaveformList();
  virtual IIR_WhileLoopStatement                        *new_IIR_WhileLoopStatement();
  virtual IIR_XnorOperator                              *new_IIR_XnorOperator();
  virtual IIR_XorOperator                               *new_IIR_XorOperator();
  virtual IIR_ZTFAttribute                              *new_IIR_ZTFAttribute();
  //@}
};

#endif
