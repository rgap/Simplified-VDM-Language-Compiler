#ifndef TOKEN_H
#define TOKEN_H

static enum TokenType{
//-------------------------------------RESERVADAS-------------------------------------
/*   TOKEN			   LEXEMA   */
/*general:*/     
	T_CLASS,		//  class
	T_TYPES,		//	types
	T_VALUES,		//	values
	T_INSTANCE,		//	instance
	T_VARIABLES,	//	variables
	T_OPERATS,		//	operations
	T_TRACES,		//	traces
	T_END,			//	end
//acceso:
	T_PRIVATE,		//	private
	T_PUBLIC,		//	public
//estructuras de control:
	T_IF,			//	if
	T_ELSE,			//	else
	T_THEN,			//	then
	T_ELSEIF,		//	elseif

	T_CASES,		//	cases
	T_OTHERS,		//	others

	T_WHILE,		//	while
	T_DO,			//	do
	T_FOR,			//	for
	T_TO,			//	to
	T_BY,			//	by
	T_IN,			//	in
	T_LET,			//	let
	T_SET,			//	set
//declaracion:
	T_DECLARE,		//	dcl
	T_NEW,			//	new
//tipo de dato:
	T_NAT,			//	nat
	T_NAT1,			//	nat1
	T_INT,			//	int
	T_REAL,			//	real
	T_BOOL,			//	bool
	T_CHAR,			//	char
	T_SEQ,			//	seq
	T_OF,			//	of
//control:
	T_RETURN,		//	return
//otras:
	T_TRUE,			//	true
	T_FALSE,		//	false
//funciones predef:
	T_LENGTH,		//	len
//-------------------------------------MULTICARACTER-------------------------------------
	T_ID,			//	aaaa
					//	$aaa
					//	$$aaa
					//	1a   no es ID
					//	_a   no es ID
//numeros:
	T_NUMERO,		//	333
	T_NUMREAL,		//	1.1
					//   .1   no es real
//cadenas:	
	T_CARACTER,		//	'c'
	T_CADENA,		//	"cad"		
//--------------------------------------SIMBOLOS-------------------------------------
//operadores logicos:
	T_NOT,			//	not
	T_AND,			//	and
	T_OR,			//	or
	T_IGUAL,		//	=
	T_DIF,			//	<>
	T_MENOR,		//	<
	T_MAYOR,		//	>
	T_MENORIGUAL,	//	<=
	T_MAYORIGUAL,	//	>=
//operadores aritmeticos:			
	T_ASIGNE,		//	:=
	T_MAS,			//	+
	T_MENOS,		//	-
	T_MULT,			//	*
	T_DIV,			//	/
	T_POTENC,		//	**
	T_MOD,			//	mod
//otros operadores:
	T_PUNTO,		//	.
	T_COMA,			//	,
	T_DOSPUNTOS,	//	:
	T_OPDECL_OP,	//	==>
	T_OPDEF_OP,		//	==
	T_FLECHA,		//	->
	T_TRESPUNTOS,	//		...
//delimitadores:
	T_PAR_A,		//	(
	T_PAR_C,		//	)
	T_COR_A,		//	[
	T_COR_C,		//	]
	T_LLAVE_A,		//	{
	T_LLAVE_C,		//	}
	T_PCOMA, 		//	;
	//--------------------------------------ESPECIALES-------------------------------------
	ERROR,
	INICIOTEXTO,
	FINTEXTO,
	$
};

#endif // TOKEN_H