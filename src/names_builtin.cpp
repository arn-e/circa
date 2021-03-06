// Copyright (c) Andrew Fischer. See LICENSE file for license terms.

// This file was generated using name_tool.py

#include "common_headers.h"
#include "names_builtin.h"

namespace circa {

const char* builtin_symbol_to_string(int name)
{
    if (name >= sym_LastBuiltinName)
        return NULL;

    switch (name) {
    case sym_None: return "None";
    case sym_Invalid: return "Invalid";
    case sym_File: return "File";
    case sym_Newline: return "Newline";
    case sym_Out: return "Out";
    case sym_Unknown: return "Unknown";
    case sym_Repeat: return "Repeat";
    case sym_Success: return "Success";
    case sym_Failure: return "Failure";
    case sym_FileNotFound: return "FileNotFound";
    case sym_NotEnoughInputs: return "NotEnoughInputs";
    case sym_TooManyInputs: return "TooManyInputs";
    case sym_ExtraOutputNotFound: return "ExtraOutputNotFound";
    case sym_Default: return "Default";
    case sym_ByDemand: return "ByDemand";
    case sym_Unevaluated: return "Unevaluated";
    case sym_InProgress: return "InProgress";
    case sym_Lazy: return "Lazy";
    case sym_Consumed: return "Consumed";
    case sym_Uncaptured: return "Uncaptured";
    case sym_Return: return "Return";
    case sym_Continue: return "Continue";
    case sym_Break: return "Break";
    case sym_Discard: return "Discard";
    case sym_Control: return "Control";
    case sym_ExitLevelFunction: return "ExitLevelFunction";
    case sym_ExitLevelLoop: return "ExitLevelLoop";
    case sym_HighestExitLevel: return "HighestExitLevel";
    case sym_ExtraReturn: return "ExtraReturn";
    case sym_Name: return "Name";
    case sym_Primary: return "Primary";
    case sym_Anonymous: return "Anonymous";
    case sym_InfixOperator: return "InfixOperator";
    case sym_FunctionName: return "FunctionName";
    case sym_TypeName: return "TypeName";
    case sym_TermName: return "TermName";
    case sym_Keyword: return "Keyword";
    case sym_Whitespace: return "Whitespace";
    case sym_UnknownIdentifier: return "UnknownIdentifier";
    case sym_LookupAny: return "LookupAny";
    case sym_LookupType: return "LookupType";
    case sym_LookupFunction: return "LookupFunction";
    case sym_LookupModule: return "LookupModule";
    case sym_Untyped: return "Untyped";
    case sym_UniformListType: return "UniformListType";
    case sym_AnonStructType: return "AnonStructType";
    case sym_StructType: return "StructType";
    case sym_NativePatch: return "NativePatch";
    case sym_PatchBlock: return "PatchBlock";
    case sym_Bootstrapping: return "Bootstrapping";
    case sym_Done: return "Done";
    case sym_StorageTypeNull: return "StorageTypeNull";
    case sym_StorageTypeInt: return "StorageTypeInt";
    case sym_StorageTypeFloat: return "StorageTypeFloat";
    case sym_StorageTypeBool: return "StorageTypeBool";
    case sym_StorageTypeString: return "StorageTypeString";
    case sym_StorageTypeList: return "StorageTypeList";
    case sym_StorageTypeOpaquePointer: return "StorageTypeOpaquePointer";
    case sym_StorageTypeTerm: return "StorageTypeTerm";
    case sym_StorageTypeType: return "StorageTypeType";
    case sym_StorageTypeHandle: return "StorageTypeHandle";
    case sym_StorageTypeHashtable: return "StorageTypeHashtable";
    case sym_StorageTypeObject: return "StorageTypeObject";
    case tok_Identifier: return "tok_Identifier";
    case tok_ColonString: return "tok_ColonString";
    case tok_Integer: return "tok_Integer";
    case tok_HexInteger: return "tok_HexInteger";
    case tok_Float: return "tok_Float";
    case tok_String: return "tok_String";
    case tok_Color: return "tok_Color";
    case tok_Bool: return "tok_Bool";
    case tok_LParen: return "tok_LParen";
    case tok_RParen: return "tok_RParen";
    case tok_LBrace: return "tok_LBrace";
    case tok_RBrace: return "tok_RBrace";
    case tok_LBracket: return "tok_LBracket";
    case tok_RBracket: return "tok_RBracket";
    case tok_Comma: return "tok_Comma";
    case tok_At: return "tok_At";
    case tok_Dot: return "tok_Dot";
    case tok_DotAt: return "tok_DotAt";
    case tok_Star: return "tok_Star";
    case tok_Question: return "tok_Question";
    case tok_Slash: return "tok_Slash";
    case tok_DoubleSlash: return "tok_DoubleSlash";
    case tok_Plus: return "tok_Plus";
    case tok_Minus: return "tok_Minus";
    case tok_LThan: return "tok_LThan";
    case tok_LThanEq: return "tok_LThanEq";
    case tok_GThan: return "tok_GThan";
    case tok_GThanEq: return "tok_GThanEq";
    case tok_Percent: return "tok_Percent";
    case tok_Colon: return "tok_Colon";
    case tok_DoubleColon: return "tok_DoubleColon";
    case tok_DoubleEquals: return "tok_DoubleEquals";
    case tok_NotEquals: return "tok_NotEquals";
    case tok_Equals: return "tok_Equals";
    case tok_PlusEquals: return "tok_PlusEquals";
    case tok_MinusEquals: return "tok_MinusEquals";
    case tok_StarEquals: return "tok_StarEquals";
    case tok_SlashEquals: return "tok_SlashEquals";
    case tok_ColonEquals: return "tok_ColonEquals";
    case tok_RightArrow: return "tok_RightArrow";
    case tok_LeftArrow: return "tok_LeftArrow";
    case tok_Ampersand: return "tok_Ampersand";
    case tok_DoubleAmpersand: return "tok_DoubleAmpersand";
    case tok_DoubleVerticalBar: return "tok_DoubleVerticalBar";
    case tok_Semicolon: return "tok_Semicolon";
    case tok_TwoDots: return "tok_TwoDots";
    case tok_Ellipsis: return "tok_Ellipsis";
    case tok_TripleLThan: return "tok_TripleLThan";
    case tok_TripleGThan: return "tok_TripleGThan";
    case tok_Pound: return "tok_Pound";
    case tok_Def: return "tok_Def";
    case tok_Type: return "tok_Type";
    case tok_UnusedName1: return "tok_UnusedName1";
    case tok_UnusedName2: return "tok_UnusedName2";
    case tok_UnusedName3: return "tok_UnusedName3";
    case tok_If: return "tok_If";
    case tok_Else: return "tok_Else";
    case tok_Elif: return "tok_Elif";
    case tok_For: return "tok_For";
    case tok_State: return "tok_State";
    case tok_Return: return "tok_Return";
    case tok_In: return "tok_In";
    case tok_True: return "tok_True";
    case tok_False: return "tok_False";
    case tok_Namespace: return "tok_Namespace";
    case tok_Include: return "tok_Include";
    case tok_And: return "tok_And";
    case tok_Or: return "tok_Or";
    case tok_Not: return "tok_Not";
    case tok_Discard: return "tok_Discard";
    case tok_Null: return "tok_Null";
    case tok_Break: return "tok_Break";
    case tok_Continue: return "tok_Continue";
    case tok_Switch: return "tok_Switch";
    case tok_Case: return "tok_Case";
    case tok_While: return "tok_While";
    case tok_Require: return "tok_Require";
    case tok_Package: return "tok_Package";
    case tok_Section: return "tok_Section";
    case tok_Whitespace: return "tok_Whitespace";
    case tok_Newline: return "tok_Newline";
    case tok_Comment: return "tok_Comment";
    case tok_Eof: return "tok_Eof";
    case tok_Unrecognized: return "tok_Unrecognized";
    case op_NoOp: return "op_NoOp";
    case op_Pause: return "op_Pause";
    case op_SetNull: return "op_SetNull";
    case op_InlineCopy: return "op_InlineCopy";
    case op_CallBlock: return "op_CallBlock";
    case op_DynamicCall: return "op_DynamicCall";
    case op_ClosureCall: return "op_ClosureCall";
    case op_FireNative: return "op_FireNative";
    case op_CaseBlock: return "op_CaseBlock";
    case op_ForLoop: return "op_ForLoop";
    case op_ExitPoint: return "op_ExitPoint";
    case op_Return: return "op_Return";
    case op_Continue: return "op_Continue";
    case op_Break: return "op_Break";
    case op_Discard: return "op_Discard";
    case op_FinishFrame: return "op_FinishFrame";
    case op_FinishLoop: return "op_FinishLoop";
    case op_ErrorNotEnoughInputs: return "op_ErrorNotEnoughInputs";
    case op_ErrorTooManyInputs: return "op_ErrorTooManyInputs";
    case sym_LoopProduceOutput: return "LoopProduceOutput";
    case sym_FlatOutputs: return "FlatOutputs";
    case sym_OutputsToList: return "OutputsToList";
    case sym_Multiple: return "Multiple";
    case sym_Cast: return "Cast";
    case sym_DynamicMethodOutput: return "DynamicMethodOutput";
    case sym_FirstStatIndex: return "FirstStatIndex";
    case stat_TermsCreated: return "stat_TermsCreated";
    case stat_TermPropAdded: return "stat_TermPropAdded";
    case stat_TermPropAccess: return "stat_TermPropAccess";
    case stat_InternedNameLookup: return "stat_InternedNameLookup";
    case stat_InternedNameCreate: return "stat_InternedNameCreate";
    case stat_Copy_PushedInputNewFrame: return "stat_Copy_PushedInputNewFrame";
    case stat_Copy_PushedInputMultiNewFrame: return "stat_Copy_PushedInputMultiNewFrame";
    case stat_Copy_PushFrameWithInputs: return "stat_Copy_PushFrameWithInputs";
    case stat_Copy_ListDuplicate: return "stat_Copy_ListDuplicate";
    case stat_Copy_LoopCopyRebound: return "stat_Copy_LoopCopyRebound";
    case stat_Cast_ListCastElement: return "stat_Cast_ListCastElement";
    case stat_Cast_PushFrameWithInputs: return "stat_Cast_PushFrameWithInputs";
    case stat_Cast_FinishFrame: return "stat_Cast_FinishFrame";
    case stat_Touch_ListCast: return "stat_Touch_ListCast";
    case stat_ValueCreates: return "stat_ValueCreates";
    case stat_ValueCopies: return "stat_ValueCopies";
    case stat_ValueCast: return "stat_ValueCast";
    case stat_ValueCastDispatched: return "stat_ValueCastDispatched";
    case stat_ValueTouch: return "stat_ValueTouch";
    case stat_ListsCreated: return "stat_ListsCreated";
    case stat_ListsGrown: return "stat_ListsGrown";
    case stat_ListSoftCopy: return "stat_ListSoftCopy";
    case stat_ListHardCopy: return "stat_ListHardCopy";
    case stat_DictHardCopy: return "stat_DictHardCopy";
    case stat_StringCreate: return "stat_StringCreate";
    case stat_StringDuplicate: return "stat_StringDuplicate";
    case stat_StringResizeInPlace: return "stat_StringResizeInPlace";
    case stat_StringResizeCreate: return "stat_StringResizeCreate";
    case stat_StringSoftCopy: return "stat_StringSoftCopy";
    case stat_StringToStd: return "stat_StringToStd";
    case stat_StepInterpreter: return "stat_StepInterpreter";
    case stat_InterpreterCastOutputFromFinishedFrame: return "stat_InterpreterCastOutputFromFinishedFrame";
    case stat_BlockNameLookups: return "stat_BlockNameLookups";
    case stat_PushFrame: return "stat_PushFrame";
    case stat_LoopFinishIteration: return "stat_LoopFinishIteration";
    case stat_LoopWriteOutput: return "stat_LoopWriteOutput";
    case stat_WriteTermBytecode: return "stat_WriteTermBytecode";
    case stat_DynamicCall: return "stat_DynamicCall";
    case stat_FinishDynamicCall: return "stat_FinishDynamicCall";
    case stat_DynamicMethodCall: return "stat_DynamicMethodCall";
    case stat_SetIndex: return "stat_SetIndex";
    case stat_SetField: return "stat_SetField";
    case sym_LastStatIndex: return "LastStatIndex";
    case sym_LastBuiltinName: return "LastBuiltinName";
    default: return NULL;
    }
}

int builtin_symbol_from_string(const char* str)
{
    switch (str[0]) {
    default: return -1;
    case 'A':
    switch (str[1]) {
    default: return -1;
    case 'n':
    switch (str[2]) {
    default: return -1;
    case 'o':
    switch (str[3]) {
    default: return -1;
    case 'n':
    switch (str[4]) {
    default: return -1;
    case 'y':
        if (strcmp(str + 5, "mous") == 0)
            return sym_Anonymous;
        break;
    case 'S':
        if (strcmp(str + 5, "tructType") == 0)
            return sym_AnonStructType;
        break;
    }
    }
    }
    }
    case 'C':
    switch (str[1]) {
    default: return -1;
    case 'a':
        if (strcmp(str + 2, "st") == 0)
            return sym_Cast;
        break;
    case 'o':
    switch (str[2]) {
    default: return -1;
    case 'n':
    switch (str[3]) {
    default: return -1;
    case 's':
        if (strcmp(str + 4, "umed") == 0)
            return sym_Consumed;
        break;
    case 't':
    switch (str[4]) {
    default: return -1;
    case 'i':
        if (strcmp(str + 5, "nue") == 0)
            return sym_Continue;
        break;
    case 'r':
        if (strcmp(str + 5, "ol") == 0)
            return sym_Control;
        break;
    }
    }
    }
    }
    case 'B':
    switch (str[1]) {
    default: return -1;
    case 'y':
        if (strcmp(str + 2, "Demand") == 0)
            return sym_ByDemand;
        break;
    case 'r':
        if (strcmp(str + 2, "eak") == 0)
            return sym_Break;
        break;
    case 'o':
        if (strcmp(str + 2, "otstrapping") == 0)
            return sym_Bootstrapping;
        break;
    }
    case 'E':
    switch (str[1]) {
    default: return -1;
    case 'x':
    switch (str[2]) {
    default: return -1;
    case 'i':
    switch (str[3]) {
    default: return -1;
    case 't':
    switch (str[4]) {
    default: return -1;
    case 'L':
    switch (str[5]) {
    default: return -1;
    case 'e':
    switch (str[6]) {
    default: return -1;
    case 'v':
    switch (str[7]) {
    default: return -1;
    case 'e':
    switch (str[8]) {
    default: return -1;
    case 'l':
    switch (str[9]) {
    default: return -1;
    case 'L':
        if (strcmp(str + 10, "oop") == 0)
            return sym_ExitLevelLoop;
        break;
    case 'F':
        if (strcmp(str + 10, "unction") == 0)
            return sym_ExitLevelFunction;
        break;
    }
    }
    }
    }
    }
    }
    }
    case 't':
    switch (str[3]) {
    default: return -1;
    case 'r':
    switch (str[4]) {
    default: return -1;
    case 'a':
    switch (str[5]) {
    default: return -1;
    case 'R':
        if (strcmp(str + 6, "eturn") == 0)
            return sym_ExtraReturn;
        break;
    case 'O':
        if (strcmp(str + 6, "utputNotFound") == 0)
            return sym_ExtraOutputNotFound;
        break;
    }
    }
    }
    }
    }
    case 'D':
    switch (str[1]) {
    default: return -1;
    case 'i':
        if (strcmp(str + 2, "scard") == 0)
            return sym_Discard;
        break;
    case 'y':
        if (strcmp(str + 2, "namicMethodOutput") == 0)
            return sym_DynamicMethodOutput;
        break;
    case 'e':
        if (strcmp(str + 2, "fault") == 0)
            return sym_Default;
        break;
    case 'o':
        if (strcmp(str + 2, "ne") == 0)
            return sym_Done;
        break;
    }
    case 'F':
    switch (str[1]) {
    default: return -1;
    case 'i':
    switch (str[2]) {
    default: return -1;
    case 'r':
        if (strcmp(str + 3, "stStatIndex") == 0)
            return sym_FirstStatIndex;
        break;
    case 'l':
    switch (str[3]) {
    default: return -1;
    case 'e':
    switch (str[4]) {
    default: return -1;
    case 0:
            return sym_File;
    case 'N':
        if (strcmp(str + 5, "otFound") == 0)
            return sym_FileNotFound;
        break;
    }
    }
    }
    case 'a':
        if (strcmp(str + 2, "ilure") == 0)
            return sym_Failure;
        break;
    case 'u':
        if (strcmp(str + 2, "nctionName") == 0)
            return sym_FunctionName;
        break;
    case 'l':
        if (strcmp(str + 2, "atOutputs") == 0)
            return sym_FlatOutputs;
        break;
    }
    case 'I':
    switch (str[1]) {
    default: return -1;
    case 'n':
    switch (str[2]) {
    default: return -1;
    case 'P':
        if (strcmp(str + 3, "rogress") == 0)
            return sym_InProgress;
        break;
    case 'v':
        if (strcmp(str + 3, "alid") == 0)
            return sym_Invalid;
        break;
    case 'f':
        if (strcmp(str + 3, "ixOperator") == 0)
            return sym_InfixOperator;
        break;
    }
    }
    case 'H':
        if (strcmp(str + 1, "ighestExitLevel") == 0)
            return sym_HighestExitLevel;
        break;
    case 'K':
        if (strcmp(str + 1, "eyword") == 0)
            return sym_Keyword;
        break;
    case 'M':
        if (strcmp(str + 1, "ultiple") == 0)
            return sym_Multiple;
        break;
    case 'L':
    switch (str[1]) {
    default: return -1;
    case 'a':
    switch (str[2]) {
    default: return -1;
    case 's':
    switch (str[3]) {
    default: return -1;
    case 't':
    switch (str[4]) {
    default: return -1;
    case 'S':
        if (strcmp(str + 5, "tatIndex") == 0)
            return sym_LastStatIndex;
        break;
    case 'B':
        if (strcmp(str + 5, "uiltinName") == 0)
            return sym_LastBuiltinName;
        break;
    }
    }
    case 'z':
        if (strcmp(str + 3, "y") == 0)
            return sym_Lazy;
        break;
    }
    case 'o':
    switch (str[2]) {
    default: return -1;
    case 'o':
    switch (str[3]) {
    default: return -1;
    case 'p':
        if (strcmp(str + 4, "ProduceOutput") == 0)
            return sym_LoopProduceOutput;
        break;
    case 'k':
    switch (str[4]) {
    default: return -1;
    case 'u':
    switch (str[5]) {
    default: return -1;
    case 'p':
    switch (str[6]) {
    default: return -1;
    case 'A':
        if (strcmp(str + 7, "ny") == 0)
            return sym_LookupAny;
        break;
    case 'M':
        if (strcmp(str + 7, "odule") == 0)
            return sym_LookupModule;
        break;
    case 'T':
        if (strcmp(str + 7, "ype") == 0)
            return sym_LookupType;
        break;
    case 'F':
        if (strcmp(str + 7, "unction") == 0)
            return sym_LookupFunction;
        break;
    }
    }
    }
    }
    }
    }
    case 'O':
    switch (str[1]) {
    default: return -1;
    case 'u':
    switch (str[2]) {
    default: return -1;
    case 't':
    switch (str[3]) {
    default: return -1;
    case 0:
            return sym_Out;
    case 'p':
        if (strcmp(str + 4, "utsToList") == 0)
            return sym_OutputsToList;
        break;
    }
    }
    }
    case 'N':
    switch (str[1]) {
    default: return -1;
    case 'a':
    switch (str[2]) {
    default: return -1;
    case 'm':
        if (strcmp(str + 3, "e") == 0)
            return sym_Name;
        break;
    case 't':
        if (strcmp(str + 3, "ivePatch") == 0)
            return sym_NativePatch;
        break;
    }
    case 'e':
        if (strcmp(str + 2, "wline") == 0)
            return sym_Newline;
        break;
    case 'o':
    switch (str[2]) {
    default: return -1;
    case 't':
        if (strcmp(str + 3, "EnoughInputs") == 0)
            return sym_NotEnoughInputs;
        break;
    case 'n':
        if (strcmp(str + 3, "e") == 0)
            return sym_None;
        break;
    }
    }
    case 'P':
    switch (str[1]) {
    default: return -1;
    case 'a':
        if (strcmp(str + 2, "tchBlock") == 0)
            return sym_PatchBlock;
        break;
    case 'r':
        if (strcmp(str + 2, "imary") == 0)
            return sym_Primary;
        break;
    }
    case 'S':
    switch (str[1]) {
    default: return -1;
    case 'u':
        if (strcmp(str + 2, "ccess") == 0)
            return sym_Success;
        break;
    case 't':
    switch (str[2]) {
    default: return -1;
    case 'r':
        if (strcmp(str + 3, "uctType") == 0)
            return sym_StructType;
        break;
    case 'o':
    switch (str[3]) {
    default: return -1;
    case 'r':
    switch (str[4]) {
    default: return -1;
    case 'a':
    switch (str[5]) {
    default: return -1;
    case 'g':
    switch (str[6]) {
    default: return -1;
    case 'e':
    switch (str[7]) {
    default: return -1;
    case 'T':
    switch (str[8]) {
    default: return -1;
    case 'y':
    switch (str[9]) {
    default: return -1;
    case 'p':
    switch (str[10]) {
    default: return -1;
    case 'e':
    switch (str[11]) {
    default: return -1;
    case 'B':
        if (strcmp(str + 12, "ool") == 0)
            return sym_StorageTypeBool;
        break;
    case 'F':
        if (strcmp(str + 12, "loat") == 0)
            return sym_StorageTypeFloat;
        break;
    case 'I':
        if (strcmp(str + 12, "nt") == 0)
            return sym_StorageTypeInt;
        break;
    case 'H':
    switch (str[12]) {
    default: return -1;
    case 'a':
    switch (str[13]) {
    default: return -1;
    case 's':
        if (strcmp(str + 14, "htable") == 0)
            return sym_StorageTypeHashtable;
        break;
    case 'n':
        if (strcmp(str + 14, "dle") == 0)
            return sym_StorageTypeHandle;
        break;
    }
    }
    case 'L':
        if (strcmp(str + 12, "ist") == 0)
            return sym_StorageTypeList;
        break;
    case 'O':
    switch (str[12]) {
    default: return -1;
    case 'p':
        if (strcmp(str + 13, "aquePointer") == 0)
            return sym_StorageTypeOpaquePointer;
        break;
    case 'b':
        if (strcmp(str + 13, "ject") == 0)
            return sym_StorageTypeObject;
        break;
    }
    case 'N':
        if (strcmp(str + 12, "ull") == 0)
            return sym_StorageTypeNull;
        break;
    case 'S':
        if (strcmp(str + 12, "tring") == 0)
            return sym_StorageTypeString;
        break;
    case 'T':
    switch (str[12]) {
    default: return -1;
    case 'y':
        if (strcmp(str + 13, "pe") == 0)
            return sym_StorageTypeType;
        break;
    case 'e':
        if (strcmp(str + 13, "rm") == 0)
            return sym_StorageTypeTerm;
        break;
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    case 'R':
    switch (str[1]) {
    default: return -1;
    case 'e':
    switch (str[2]) {
    default: return -1;
    case 'p':
        if (strcmp(str + 3, "eat") == 0)
            return sym_Repeat;
        break;
    case 't':
        if (strcmp(str + 3, "urn") == 0)
            return sym_Return;
        break;
    }
    }
    case 'U':
    switch (str[1]) {
    default: return -1;
    case 'n':
    switch (str[2]) {
    default: return -1;
    case 'i':
        if (strcmp(str + 3, "formListType") == 0)
            return sym_UniformListType;
        break;
    case 'k':
    switch (str[3]) {
    default: return -1;
    case 'n':
    switch (str[4]) {
    default: return -1;
    case 'o':
    switch (str[5]) {
    default: return -1;
    case 'w':
    switch (str[6]) {
    default: return -1;
    case 'n':
    switch (str[7]) {
    default: return -1;
    case 0:
            return sym_Unknown;
    case 'I':
        if (strcmp(str + 8, "dentifier") == 0)
            return sym_UnknownIdentifier;
        break;
    }
    }
    }
    }
    }
    case 'e':
        if (strcmp(str + 3, "valuated") == 0)
            return sym_Unevaluated;
        break;
    case 'c':
        if (strcmp(str + 3, "aptured") == 0)
            return sym_Uncaptured;
        break;
    case 't':
        if (strcmp(str + 3, "yped") == 0)
            return sym_Untyped;
        break;
    }
    }
    case 'T':
    switch (str[1]) {
    default: return -1;
    case 'y':
        if (strcmp(str + 2, "peName") == 0)
            return sym_TypeName;
        break;
    case 'e':
        if (strcmp(str + 2, "rmName") == 0)
            return sym_TermName;
        break;
    case 'o':
        if (strcmp(str + 2, "oManyInputs") == 0)
            return sym_TooManyInputs;
        break;
    }
    case 'W':
        if (strcmp(str + 1, "hitespace") == 0)
            return sym_Whitespace;
        break;
    case 'o':
    switch (str[1]) {
    default: return -1;
    case 'p':
    switch (str[2]) {
    default: return -1;
    case '_':
    switch (str[3]) {
    default: return -1;
    case 'C':
    switch (str[4]) {
    default: return -1;
    case 'a':
    switch (str[5]) {
    default: return -1;
    case 's':
        if (strcmp(str + 6, "eBlock") == 0)
            return op_CaseBlock;
        break;
    case 'l':
        if (strcmp(str + 6, "lBlock") == 0)
            return op_CallBlock;
        break;
    }
    case 'l':
        if (strcmp(str + 5, "osureCall") == 0)
            return op_ClosureCall;
        break;
    case 'o':
        if (strcmp(str + 5, "ntinue") == 0)
            return op_Continue;
        break;
    }
    case 'B':
        if (strcmp(str + 4, "reak") == 0)
            return op_Break;
        break;
    case 'E':
    switch (str[4]) {
    default: return -1;
    case 'x':
        if (strcmp(str + 5, "itPoint") == 0)
            return op_ExitPoint;
        break;
    case 'r':
    switch (str[5]) {
    default: return -1;
    case 'r':
    switch (str[6]) {
    default: return -1;
    case 'o':
    switch (str[7]) {
    default: return -1;
    case 'r':
    switch (str[8]) {
    default: return -1;
    case 'T':
        if (strcmp(str + 9, "ooManyInputs") == 0)
            return op_ErrorTooManyInputs;
        break;
    case 'N':
        if (strcmp(str + 9, "otEnoughInputs") == 0)
            return op_ErrorNotEnoughInputs;
        break;
    }
    }
    }
    }
    }
    case 'D':
    switch (str[4]) {
    default: return -1;
    case 'y':
        if (strcmp(str + 5, "namicCall") == 0)
            return op_DynamicCall;
        break;
    case 'i':
        if (strcmp(str + 5, "scard") == 0)
            return op_Discard;
        break;
    }
    case 'F':
    switch (str[4]) {
    default: return -1;
    case 'i':
    switch (str[5]) {
    default: return -1;
    case 'r':
        if (strcmp(str + 6, "eNative") == 0)
            return op_FireNative;
        break;
    case 'n':
    switch (str[6]) {
    default: return -1;
    case 'i':
    switch (str[7]) {
    default: return -1;
    case 's':
    switch (str[8]) {
    default: return -1;
    case 'h':
    switch (str[9]) {
    default: return -1;
    case 'L':
        if (strcmp(str + 10, "oop") == 0)
            return op_FinishLoop;
        break;
    case 'F':
        if (strcmp(str + 10, "rame") == 0)
            return op_FinishFrame;
        break;
    }
    }
    }
    }
    }
    case 'o':
        if (strcmp(str + 5, "rLoop") == 0)
            return op_ForLoop;
        break;
    }
    case 'I':
        if (strcmp(str + 4, "nlineCopy") == 0)
            return op_InlineCopy;
        break;
    case 'N':
        if (strcmp(str + 4, "oOp") == 0)
            return op_NoOp;
        break;
    case 'P':
        if (strcmp(str + 4, "ause") == 0)
            return op_Pause;
        break;
    case 'S':
        if (strcmp(str + 4, "etNull") == 0)
            return op_SetNull;
        break;
    case 'R':
        if (strcmp(str + 4, "eturn") == 0)
            return op_Return;
        break;
    }
    }
    }
    case 's':
    switch (str[1]) {
    default: return -1;
    case 't':
    switch (str[2]) {
    default: return -1;
    case 'a':
    switch (str[3]) {
    default: return -1;
    case 't':
    switch (str[4]) {
    default: return -1;
    case '_':
    switch (str[5]) {
    default: return -1;
    case 'C':
    switch (str[6]) {
    default: return -1;
    case 'a':
    switch (str[7]) {
    default: return -1;
    case 's':
    switch (str[8]) {
    default: return -1;
    case 't':
    switch (str[9]) {
    default: return -1;
    case '_':
    switch (str[10]) {
    default: return -1;
    case 'P':
        if (strcmp(str + 11, "ushFrameWithInputs") == 0)
            return stat_Cast_PushFrameWithInputs;
        break;
    case 'L':
        if (strcmp(str + 11, "istCastElement") == 0)
            return stat_Cast_ListCastElement;
        break;
    case 'F':
        if (strcmp(str + 11, "inishFrame") == 0)
            return stat_Cast_FinishFrame;
        break;
    }
    }
    }
    }
    case 'o':
    switch (str[7]) {
    default: return -1;
    case 'p':
    switch (str[8]) {
    default: return -1;
    case 'y':
    switch (str[9]) {
    default: return -1;
    case '_':
    switch (str[10]) {
    default: return -1;
    case 'P':
    switch (str[11]) {
    default: return -1;
    case 'u':
    switch (str[12]) {
    default: return -1;
    case 's':
    switch (str[13]) {
    default: return -1;
    case 'h':
    switch (str[14]) {
    default: return -1;
    case 'e':
    switch (str[15]) {
    default: return -1;
    case 'd':
    switch (str[16]) {
    default: return -1;
    case 'I':
    switch (str[17]) {
    default: return -1;
    case 'n':
    switch (str[18]) {
    default: return -1;
    case 'p':
    switch (str[19]) {
    default: return -1;
    case 'u':
    switch (str[20]) {
    default: return -1;
    case 't':
    switch (str[21]) {
    default: return -1;
    case 'M':
        if (strcmp(str + 22, "ultiNewFrame") == 0)
            return stat_Copy_PushedInputMultiNewFrame;
        break;
    case 'N':
        if (strcmp(str + 22, "ewFrame") == 0)
            return stat_Copy_PushedInputNewFrame;
        break;
    }
    }
    }
    }
    }
    }
    }
    case 'F':
        if (strcmp(str + 15, "rameWithInputs") == 0)
            return stat_Copy_PushFrameWithInputs;
        break;
    }
    }
    }
    }
    case 'L':
    switch (str[11]) {
    default: return -1;
    case 'i':
        if (strcmp(str + 12, "stDuplicate") == 0)
            return stat_Copy_ListDuplicate;
        break;
    case 'o':
        if (strcmp(str + 12, "opCopyRebound") == 0)
            return stat_Copy_LoopCopyRebound;
        break;
    }
    }
    }
    }
    }
    }
    case 'B':
        if (strcmp(str + 6, "lockNameLookups") == 0)
            return stat_BlockNameLookups;
        break;
    case 'D':
    switch (str[6]) {
    default: return -1;
    case 'i':
        if (strcmp(str + 7, "ctHardCopy") == 0)
            return stat_DictHardCopy;
        break;
    case 'y':
    switch (str[7]) {
    default: return -1;
    case 'n':
    switch (str[8]) {
    default: return -1;
    case 'a':
    switch (str[9]) {
    default: return -1;
    case 'm':
    switch (str[10]) {
    default: return -1;
    case 'i':
    switch (str[11]) {
    default: return -1;
    case 'c':
    switch (str[12]) {
    default: return -1;
    case 'C':
        if (strcmp(str + 13, "all") == 0)
            return stat_DynamicCall;
        break;
    case 'M':
        if (strcmp(str + 13, "ethodCall") == 0)
            return stat_DynamicMethodCall;
        break;
    }
    }
    }
    }
    }
    }
    }
    case 'F':
        if (strcmp(str + 6, "inishDynamicCall") == 0)
            return stat_FinishDynamicCall;
        break;
    case 'I':
    switch (str[6]) {
    default: return -1;
    case 'n':
    switch (str[7]) {
    default: return -1;
    case 't':
    switch (str[8]) {
    default: return -1;
    case 'e':
    switch (str[9]) {
    default: return -1;
    case 'r':
    switch (str[10]) {
    default: return -1;
    case 'p':
        if (strcmp(str + 11, "reterCastOutputFromFinishedFrame") == 0)
            return stat_InterpreterCastOutputFromFinishedFrame;
        break;
    case 'n':
    switch (str[11]) {
    default: return -1;
    case 'e':
    switch (str[12]) {
    default: return -1;
    case 'd':
    switch (str[13]) {
    default: return -1;
    case 'N':
    switch (str[14]) {
    default: return -1;
    case 'a':
    switch (str[15]) {
    default: return -1;
    case 'm':
    switch (str[16]) {
    default: return -1;
    case 'e':
    switch (str[17]) {
    default: return -1;
    case 'C':
        if (strcmp(str + 18, "reate") == 0)
            return stat_InternedNameCreate;
        break;
    case 'L':
        if (strcmp(str + 18, "ookup") == 0)
            return stat_InternedNameLookup;
        break;
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    case 'L':
    switch (str[6]) {
    default: return -1;
    case 'i':
    switch (str[7]) {
    default: return -1;
    case 's':
    switch (str[8]) {
    default: return -1;
    case 't':
    switch (str[9]) {
    default: return -1;
    case 'H':
        if (strcmp(str + 10, "ardCopy") == 0)
            return stat_ListHardCopy;
        break;
    case 's':
    switch (str[10]) {
    default: return -1;
    case 'C':
        if (strcmp(str + 11, "reated") == 0)
            return stat_ListsCreated;
        break;
    case 'G':
        if (strcmp(str + 11, "rown") == 0)
            return stat_ListsGrown;
        break;
    }
    case 'S':
        if (strcmp(str + 10, "oftCopy") == 0)
            return stat_ListSoftCopy;
        break;
    }
    }
    }
    case 'o':
    switch (str[7]) {
    default: return -1;
    case 'o':
    switch (str[8]) {
    default: return -1;
    case 'p':
    switch (str[9]) {
    default: return -1;
    case 'W':
        if (strcmp(str + 10, "riteOutput") == 0)
            return stat_LoopWriteOutput;
        break;
    case 'F':
        if (strcmp(str + 10, "inishIteration") == 0)
            return stat_LoopFinishIteration;
        break;
    }
    }
    }
    }
    case 'P':
        if (strcmp(str + 6, "ushFrame") == 0)
            return stat_PushFrame;
        break;
    case 'S':
    switch (str[6]) {
    default: return -1;
    case 'e':
    switch (str[7]) {
    default: return -1;
    case 't':
    switch (str[8]) {
    default: return -1;
    case 'I':
        if (strcmp(str + 9, "ndex") == 0)
            return stat_SetIndex;
        break;
    case 'F':
        if (strcmp(str + 9, "ield") == 0)
            return stat_SetField;
        break;
    }
    }
    case 't':
    switch (str[7]) {
    default: return -1;
    case 'r':
    switch (str[8]) {
    default: return -1;
    case 'i':
    switch (str[9]) {
    default: return -1;
    case 'n':
    switch (str[10]) {
    default: return -1;
    case 'g':
    switch (str[11]) {
    default: return -1;
    case 'S':
        if (strcmp(str + 12, "oftCopy") == 0)
            return stat_StringSoftCopy;
        break;
    case 'R':
    switch (str[12]) {
    default: return -1;
    case 'e':
    switch (str[13]) {
    default: return -1;
    case 's':
    switch (str[14]) {
    default: return -1;
    case 'i':
    switch (str[15]) {
    default: return -1;
    case 'z':
    switch (str[16]) {
    default: return -1;
    case 'e':
    switch (str[17]) {
    default: return -1;
    case 'I':
        if (strcmp(str + 18, "nPlace") == 0)
            return stat_StringResizeInPlace;
        break;
    case 'C':
        if (strcmp(str + 18, "reate") == 0)
            return stat_StringResizeCreate;
        break;
    }
    }
    }
    }
    }
    }
    case 'C':
        if (strcmp(str + 12, "reate") == 0)
            return stat_StringCreate;
        break;
    case 'T':
        if (strcmp(str + 12, "oStd") == 0)
            return stat_StringToStd;
        break;
    case 'D':
        if (strcmp(str + 12, "uplicate") == 0)
            return stat_StringDuplicate;
        break;
    }
    }
    }
    }
    case 'e':
        if (strcmp(str + 8, "pInterpreter") == 0)
            return stat_StepInterpreter;
        break;
    }
    }
    case 'T':
    switch (str[6]) {
    default: return -1;
    case 'e':
    switch (str[7]) {
    default: return -1;
    case 'r':
    switch (str[8]) {
    default: return -1;
    case 'm':
    switch (str[9]) {
    default: return -1;
    case 'P':
    switch (str[10]) {
    default: return -1;
    case 'r':
    switch (str[11]) {
    default: return -1;
    case 'o':
    switch (str[12]) {
    default: return -1;
    case 'p':
    switch (str[13]) {
    default: return -1;
    case 'A':
    switch (str[14]) {
    default: return -1;
    case 'c':
        if (strcmp(str + 15, "cess") == 0)
            return stat_TermPropAccess;
        break;
    case 'd':
        if (strcmp(str + 15, "ded") == 0)
            return stat_TermPropAdded;
        break;
    }
    }
    }
    }
    }
    case 's':
        if (strcmp(str + 10, "Created") == 0)
            return stat_TermsCreated;
        break;
    }
    }
    }
    case 'o':
        if (strcmp(str + 7, "uch_ListCast") == 0)
            return stat_Touch_ListCast;
        break;
    }
    case 'W':
        if (strcmp(str + 6, "riteTermBytecode") == 0)
            return stat_WriteTermBytecode;
        break;
    case 'V':
    switch (str[6]) {
    default: return -1;
    case 'a':
    switch (str[7]) {
    default: return -1;
    case 'l':
    switch (str[8]) {
    default: return -1;
    case 'u':
    switch (str[9]) {
    default: return -1;
    case 'e':
    switch (str[10]) {
    default: return -1;
    case 'C':
    switch (str[11]) {
    default: return -1;
    case 'a':
    switch (str[12]) {
    default: return -1;
    case 's':
    switch (str[13]) {
    default: return -1;
    case 't':
    switch (str[14]) {
    default: return -1;
    case 0:
            return stat_ValueCast;
    case 'D':
        if (strcmp(str + 15, "ispatched") == 0)
            return stat_ValueCastDispatched;
        break;
    }
    }
    }
    case 'r':
        if (strcmp(str + 12, "eates") == 0)
            return stat_ValueCreates;
        break;
    case 'o':
        if (strcmp(str + 12, "pies") == 0)
            return stat_ValueCopies;
        break;
    }
    case 'T':
        if (strcmp(str + 11, "ouch") == 0)
            return stat_ValueTouch;
        break;
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    case 't':
    switch (str[1]) {
    default: return -1;
    case 'o':
    switch (str[2]) {
    default: return -1;
    case 'k':
    switch (str[3]) {
    default: return -1;
    case '_':
    switch (str[4]) {
    default: return -1;
    case 'A':
    switch (str[5]) {
    default: return -1;
    case 'm':
        if (strcmp(str + 6, "persand") == 0)
            return tok_Ampersand;
        break;
    case 't':
            return tok_At;
    case 'n':
        if (strcmp(str + 6, "d") == 0)
            return tok_And;
        break;
    }
    case 'C':
    switch (str[5]) {
    default: return -1;
    case 'a':
        if (strcmp(str + 6, "se") == 0)
            return tok_Case;
        break;
    case 'o':
    switch (str[6]) {
    default: return -1;
    case 'm':
    switch (str[7]) {
    default: return -1;
    case 'm':
    switch (str[8]) {
    default: return -1;
    case 'a':
            return tok_Comma;
    case 'e':
        if (strcmp(str + 9, "nt") == 0)
            return tok_Comment;
        break;
    }
    }
    case 'l':
    switch (str[7]) {
    default: return -1;
    case 'o':
    switch (str[8]) {
    default: return -1;
    case 'r':
            return tok_Color;
    case 'n':
    switch (str[9]) {
    default: return -1;
    case 0:
            return tok_Colon;
    case 'S':
        if (strcmp(str + 10, "tring") == 0)
            return tok_ColonString;
        break;
    case 'E':
        if (strcmp(str + 10, "quals") == 0)
            return tok_ColonEquals;
        break;
    }
    }
    }
    case 'n':
        if (strcmp(str + 7, "tinue") == 0)
            return tok_Continue;
        break;
    }
    }
    case 'B':
    switch (str[5]) {
    default: return -1;
    case 'r':
        if (strcmp(str + 6, "eak") == 0)
            return tok_Break;
        break;
    case 'o':
        if (strcmp(str + 6, "ol") == 0)
            return tok_Bool;
        break;
    }
    case 'E':
    switch (str[5]) {
    default: return -1;
    case 'q':
        if (strcmp(str + 6, "uals") == 0)
            return tok_Equals;
        break;
    case 'l':
    switch (str[6]) {
    default: return -1;
    case 'i':
        if (strcmp(str + 7, "f") == 0)
            return tok_Elif;
        break;
    case 's':
        if (strcmp(str + 7, "e") == 0)
            return tok_Else;
        break;
    case 'l':
        if (strcmp(str + 7, "ipsis") == 0)
            return tok_Ellipsis;
        break;
    }
    case 'o':
        if (strcmp(str + 6, "f") == 0)
            return tok_Eof;
        break;
    }
    case 'D':
    switch (str[5]) {
    default: return -1;
    case 'i':
        if (strcmp(str + 6, "scard") == 0)
            return tok_Discard;
        break;
    case 'e':
        if (strcmp(str + 6, "f") == 0)
            return tok_Def;
        break;
    case 'o':
    switch (str[6]) {
    default: return -1;
    case 'u':
    switch (str[7]) {
    default: return -1;
    case 'b':
    switch (str[8]) {
    default: return -1;
    case 'l':
    switch (str[9]) {
    default: return -1;
    case 'e':
    switch (str[10]) {
    default: return -1;
    case 'A':
        if (strcmp(str + 11, "mpersand") == 0)
            return tok_DoubleAmpersand;
        break;
    case 'S':
        if (strcmp(str + 11, "lash") == 0)
            return tok_DoubleSlash;
        break;
    case 'E':
        if (strcmp(str + 11, "quals") == 0)
            return tok_DoubleEquals;
        break;
    case 'C':
        if (strcmp(str + 11, "olon") == 0)
            return tok_DoubleColon;
        break;
    case 'V':
        if (strcmp(str + 11, "erticalBar") == 0)
            return tok_DoubleVerticalBar;
        break;
    }
    }
    }
    }
    case 't':
    switch (str[7]) {
    default: return -1;
    case 0:
            return tok_Dot;
    case 'A':
        if (strcmp(str + 8, "t") == 0)
            return tok_DotAt;
        break;
    }
    }
    }
    case 'G':
    switch (str[5]) {
    default: return -1;
    case 'T':
    switch (str[6]) {
    default: return -1;
    case 'h':
    switch (str[7]) {
    default: return -1;
    case 'a':
    switch (str[8]) {
    default: return -1;
    case 'n':
    switch (str[9]) {
    default: return -1;
    case 0:
            return tok_GThan;
    case 'E':
        if (strcmp(str + 10, "q") == 0)
            return tok_GThanEq;
        break;
    }
    }
    }
    }
    }
    case 'F':
    switch (str[5]) {
    default: return -1;
    case 'a':
        if (strcmp(str + 6, "lse") == 0)
            return tok_False;
        break;
    case 'l':
        if (strcmp(str + 6, "oat") == 0)
            return tok_Float;
        break;
    case 'o':
        if (strcmp(str + 6, "r") == 0)
            return tok_For;
        break;
    }
    case 'I':
    switch (str[5]) {
    default: return -1;
    case 'n':
    switch (str[6]) {
    default: return -1;
    case 0:
            return tok_In;
    case 'c':
        if (strcmp(str + 7, "lude") == 0)
            return tok_Include;
        break;
    case 't':
        if (strcmp(str + 7, "eger") == 0)
            return tok_Integer;
        break;
    }
    case 'd':
        if (strcmp(str + 6, "entifier") == 0)
            return tok_Identifier;
        break;
    case 'f':
            return tok_If;
    }
    case 'H':
        if (strcmp(str + 5, "exInteger") == 0)
            return tok_HexInteger;
        break;
    case 'M':
    switch (str[5]) {
    default: return -1;
    case 'i':
    switch (str[6]) {
    default: return -1;
    case 'n':
    switch (str[7]) {
    default: return -1;
    case 'u':
    switch (str[8]) {
    default: return -1;
    case 's':
    switch (str[9]) {
    default: return -1;
    case 0:
            return tok_Minus;
    case 'E':
        if (strcmp(str + 10, "quals") == 0)
            return tok_MinusEquals;
        break;
    }
    }
    }
    }
    }
    case 'L':
    switch (str[5]) {
    default: return -1;
    case 'P':
        if (strcmp(str + 6, "aren") == 0)
            return tok_LParen;
        break;
    case 'B':
    switch (str[6]) {
    default: return -1;
    case 'r':
    switch (str[7]) {
    default: return -1;
    case 'a':
    switch (str[8]) {
    default: return -1;
    case 'c':
    switch (str[9]) {
    default: return -1;
    case 'k':
        if (strcmp(str + 10, "et") == 0)
            return tok_LBracket;
        break;
    case 'e':
            return tok_LBrace;
    }
    }
    }
    }
    case 'e':
        if (strcmp(str + 6, "ftArrow") == 0)
            return tok_LeftArrow;
        break;
    case 'T':
    switch (str[6]) {
    default: return -1;
    case 'h':
    switch (str[7]) {
    default: return -1;
    case 'a':
    switch (str[8]) {
    default: return -1;
    case 'n':
    switch (str[9]) {
    default: return -1;
    case 0:
            return tok_LThan;
    case 'E':
        if (strcmp(str + 10, "q") == 0)
            return tok_LThanEq;
        break;
    }
    }
    }
    }
    }
    case 'O':
        if (strcmp(str + 5, "r") == 0)
            return tok_Or;
        break;
    case 'N':
    switch (str[5]) {
    default: return -1;
    case 'a':
        if (strcmp(str + 6, "mespace") == 0)
            return tok_Namespace;
        break;
    case 'u':
        if (strcmp(str + 6, "ll") == 0)
            return tok_Null;
        break;
    case 'e':
        if (strcmp(str + 6, "wline") == 0)
            return tok_Newline;
        break;
    case 'o':
    switch (str[6]) {
    default: return -1;
    case 't':
    switch (str[7]) {
    default: return -1;
    case 0:
            return tok_Not;
    case 'E':
        if (strcmp(str + 8, "quals") == 0)
            return tok_NotEquals;
        break;
    }
    }
    }
    case 'Q':
        if (strcmp(str + 5, "uestion") == 0)
            return tok_Question;
        break;
    case 'P':
    switch (str[5]) {
    default: return -1;
    case 'a':
        if (strcmp(str + 6, "ckage") == 0)
            return tok_Package;
        break;
    case 'e':
        if (strcmp(str + 6, "rcent") == 0)
            return tok_Percent;
        break;
    case 'l':
    switch (str[6]) {
    default: return -1;
    case 'u':
    switch (str[7]) {
    default: return -1;
    case 's':
    switch (str[8]) {
    default: return -1;
    case 0:
            return tok_Plus;
    case 'E':
        if (strcmp(str + 9, "quals") == 0)
            return tok_PlusEquals;
        break;
    }
    }
    }
    case 'o':
        if (strcmp(str + 6, "und") == 0)
            return tok_Pound;
        break;
    }
    case 'S':
    switch (str[5]) {
    default: return -1;
    case 'e':
    switch (str[6]) {
    default: return -1;
    case 'c':
        if (strcmp(str + 7, "tion") == 0)
            return tok_Section;
        break;
    case 'm':
        if (strcmp(str + 7, "icolon") == 0)
            return tok_Semicolon;
        break;
    }
    case 't':
    switch (str[6]) {
    default: return -1;
    case 'a':
    switch (str[7]) {
    default: return -1;
    case 'r':
    switch (str[8]) {
    default: return -1;
    case 0:
            return tok_Star;
    case 'E':
        if (strcmp(str + 9, "quals") == 0)
            return tok_StarEquals;
        break;
    }
    case 't':
        if (strcmp(str + 8, "e") == 0)
            return tok_State;
        break;
    }
    case 'r':
        if (strcmp(str + 7, "ing") == 0)
            return tok_String;
        break;
    }
    case 'w':
        if (strcmp(str + 6, "itch") == 0)
            return tok_Switch;
        break;
    case 'l':
    switch (str[6]) {
    default: return -1;
    case 'a':
    switch (str[7]) {
    default: return -1;
    case 's':
    switch (str[8]) {
    default: return -1;
    case 'h':
    switch (str[9]) {
    default: return -1;
    case 0:
            return tok_Slash;
    case 'E':
        if (strcmp(str + 10, "quals") == 0)
            return tok_SlashEquals;
        break;
    }
    }
    }
    }
    }
    case 'R':
    switch (str[5]) {
    default: return -1;
    case 'i':
        if (strcmp(str + 6, "ghtArrow") == 0)
            return tok_RightArrow;
        break;
    case 'P':
        if (strcmp(str + 6, "aren") == 0)
            return tok_RParen;
        break;
    case 'B':
    switch (str[6]) {
    default: return -1;
    case 'r':
    switch (str[7]) {
    default: return -1;
    case 'a':
    switch (str[8]) {
    default: return -1;
    case 'c':
    switch (str[9]) {
    default: return -1;
    case 'k':
        if (strcmp(str + 10, "et") == 0)
            return tok_RBracket;
        break;
    case 'e':
            return tok_RBrace;
    }
    }
    }
    }
    case 'e':
    switch (str[6]) {
    default: return -1;
    case 'q':
        if (strcmp(str + 7, "uire") == 0)
            return tok_Require;
        break;
    case 't':
        if (strcmp(str + 7, "urn") == 0)
            return tok_Return;
        break;
    }
    }
    case 'U':
    switch (str[5]) {
    default: return -1;
    case 'n':
    switch (str[6]) {
    default: return -1;
    case 'r':
        if (strcmp(str + 7, "ecognized") == 0)
            return tok_Unrecognized;
        break;
    case 'u':
    switch (str[7]) {
    default: return -1;
    case 's':
    switch (str[8]) {
    default: return -1;
    case 'e':
    switch (str[9]) {
    default: return -1;
    case 'd':
    switch (str[10]) {
    default: return -1;
    case 'N':
    switch (str[11]) {
    default: return -1;
    case 'a':
    switch (str[12]) {
    default: return -1;
    case 'm':
    switch (str[13]) {
    default: return -1;
    case 'e':
    switch (str[14]) {
    default: return -1;
    case '1':
            return tok_UnusedName1;
    case '3':
            return tok_UnusedName3;
    case '2':
            return tok_UnusedName2;
    }
    }
    }
    }
    }
    }
    }
    }
    }
    }
    case 'T':
    switch (str[5]) {
    default: return -1;
    case 'y':
        if (strcmp(str + 6, "pe") == 0)
            return tok_Type;
        break;
    case 'r':
    switch (str[6]) {
    default: return -1;
    case 'i':
    switch (str[7]) {
    default: return -1;
    case 'p':
    switch (str[8]) {
    default: return -1;
    case 'l':
    switch (str[9]) {
    default: return -1;
    case 'e':
    switch (str[10]) {
    default: return -1;
    case 'L':
        if (strcmp(str + 11, "Than") == 0)
            return tok_TripleLThan;
        break;
    case 'G':
        if (strcmp(str + 11, "Than") == 0)
            return tok_TripleGThan;
        break;
    }
    }
    }
    }
    case 'u':
        if (strcmp(str + 7, "e") == 0)
            return tok_True;
        break;
    }
    case 'w':
        if (strcmp(str + 6, "oDots") == 0)
            return tok_TwoDots;
        break;
    }
    case 'W':
    switch (str[5]) {
    default: return -1;
    case 'h':
    switch (str[6]) {
    default: return -1;
    case 'i':
    switch (str[7]) {
    default: return -1;
    case 'l':
        if (strcmp(str + 8, "e") == 0)
            return tok_While;
        break;
    case 't':
        if (strcmp(str + 8, "espace") == 0)
            return tok_Whitespace;
        break;
    }
    }
    }
    }
    }
    }
    }
    }

    return -1;
}
} // namespace circa
