/****************************************************/ 
/* File: globals.h                                  */ 
/****************************************************/ 
#ifndef _GLOBALS_H_ 
#define _GLOBALS_H_

#include <fstream>
#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h> 
#include <string.h>

#include <iostream>
#include <vector>

using namespace std;
static fstream codigo; /*Fichero de entrada*/
static fstream reporte;

#include "tabla_simbolos.h"

string codefn; 
string reportefn;

Tabla_simbolos TS;

void iniciar_TS(){
	TS.insertarRegistro("class",T_CLASS,"T_CLASS",1);
	TS.insertarRegistro("types",T_TYPES,"T_TYPES",1);
	TS.insertarRegistro("values",T_VALUES,"T_VALUES",1);
	TS.insertarRegistro("instance",T_INSTANCE,"T_INSTANCE",1);
	TS.insertarRegistro("variables",T_VARIABLES,"T_VARIABLES",1);
	TS.insertarRegistro("operations",T_OPERATS,"T_OPERATS",1);
	TS.insertarRegistro("traces",T_TRACES,"T_TRACES",1);
	TS.insertarRegistro("end",T_END,"T_END",1);
	TS.insertarRegistro("private",T_PRIVATE,"T_PRIVATE",1);
	TS.insertarRegistro("public",T_PUBLIC,"T_PUBLIC",1);
	TS.insertarRegistro("if",T_IF,"T_IF",1);
	TS.insertarRegistro("else",T_ELSE,"T_ELSE",1);
	TS.insertarRegistro("then",T_THEN,"T_THEN",1);
	TS.insertarRegistro("elseif",T_ELSEIF,"T_ELSEIF",1);
	TS.insertarRegistro("cases",T_CASES,"T_CASES",1);
	TS.insertarRegistro("others",T_OTHERS,"T_OTHERS",1);
	TS.insertarRegistro("while",T_WHILE,"T_WHILE",1);
	TS.insertarRegistro("do",T_DO,"T_DO",1);
	TS.insertarRegistro("for",T_FOR,"T_FOR",1);
	TS.insertarRegistro("to",T_TO,"T_TO",1);
	TS.insertarRegistro("by",T_BY,"T_BY",1);
	TS.insertarRegistro("in",T_IN,"T_IN",1);
	TS.insertarRegistro("let",T_LET,"T_LET",1);
	TS.insertarRegistro("set",T_SET,"T_SET",1);
	TS.insertarRegistro("dcl",T_DECLARE,"T_DECLARE",1);
	TS.insertarRegistro("new",T_NEW,"T_NEW",1);
	TS.insertarRegistro("nat",T_NAT,"T_NAT",1);
	TS.insertarRegistro("nat1",T_NAT1,"T_NAT1",1);
	TS.insertarRegistro("int",T_INT,"T_INT",1);
	TS.insertarRegistro("real",T_REAL,"T_REAL",1);
	TS.insertarRegistro("bool",T_BOOL,"T_BOOL",1);
	TS.insertarRegistro("char",T_CHAR,"T_CHAR",1);
	TS.insertarRegistro("seq",T_SEQ,"T_SEQ",1);
	TS.insertarRegistro("of",T_OF,"T_OF",1);
	TS.insertarRegistro("return",T_RETURN,"T_RETURN",1);
	TS.insertarRegistro("true",T_TRUE,"T_TRUE",1);
	TS.insertarRegistro("false",T_FALSE,"T_FALSE",1);
	TS.insertarRegistro("len",T_LENGTH,"T_LENGTH",1);
	TS.insertarRegistro("not",T_NOT,"T_NOT",1);
	TS.insertarRegistro("and",T_AND,"T_AND",1);
	TS.insertarRegistro("or",T_OR,"T_OR",1);
	TS.insertarRegistro("=",T_IGUAL,"T_IGUAL",1);
	TS.insertarRegistro("<>",T_DIF,"T_DIF",1);
	TS.insertarRegistro("<",T_MENOR,"T_MENOR",1);
	TS.insertarRegistro(">",T_MAYOR,"T_MAYOR",1);
	TS.insertarRegistro("<=",T_MENORIGUAL,"T_MENORIGUAL",1);
	TS.insertarRegistro(">=",T_MAYORIGUAL,"T_MAYORIGUAL",1);
	TS.insertarRegistro(":=",T_ASIGNE,"T_ASIGNE",1);
	TS.insertarRegistro("+",T_MAS,"T_MAS",1);
	TS.insertarRegistro("-",T_MENOS,"T_MENOS",1);
	TS.insertarRegistro("*",T_MULT,"T_MULT",1);
	TS.insertarRegistro("/",T_DIV,"T_DIV",1);
	TS.insertarRegistro("**",T_POTENC,"T_POTENC",1);
	TS.insertarRegistro("mod",T_MOD,"T_MOD",1);
	TS.insertarRegistro(".",T_PUNTO,"T_PUNTO",1);
	TS.insertarRegistro(",",T_COMA,"T_COMA",1);
	TS.insertarRegistro(":",T_DOSPUNTOS,"T_DOSPUNTOS",1);
	TS.insertarRegistro("==>",T_OPDECL_OP,"T_OPDECL_OP",1);
	TS.insertarRegistro("==",T_OPDEF_OP,"T_OPDEF_OP",1);
	TS.insertarRegistro("->",T_FLECHA,"T_FLECHA",1);
	TS.insertarRegistro("...",T_TRESPUNTOS,"T_TRESPUNTOS",1);
	TS.insertarRegistro("(",T_PAR_A,"T_PAR_A",1);
	TS.insertarRegistro(")",T_PAR_C,"T_PAR_C",1);
	TS.insertarRegistro("[",T_COR_A,"T_COR_A",1);
	TS.insertarRegistro("]",T_COR_C,"T_COR_C",1);
	TS.insertarRegistro("{",T_LLAVE_A,"T_LLAVE_A",1);
	TS.insertarRegistro("}",T_LLAVE_C,"T_LLAVE_C",1);
	TS.insertarRegistro(";",T_PCOMA,"T_PCOMA",1);
}

#endif 
