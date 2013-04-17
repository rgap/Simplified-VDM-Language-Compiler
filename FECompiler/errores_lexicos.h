#ifndef ERRORES_LEXICOS_H
#define ERRORES_LEXICOS_H

#include <string>

string errores[5]={
	"Caracter no valido",
	"Caracter no valido (No ASCII)",
	"Se esperaba un numero despues del punto",
	"Delimitador faltante ( ' )",
	"Se esperaba un ( . )"
};

class errorLexico{
public:
	int numlinea;
	int tipoerror;
	string error;

	errorLexico(int numlinea,int tipoerror,string error){
		this->numlinea=numlinea;
		this->tipoerror=tipoerror;
		this->error=error;
	}
	~errorLexico(){};
};

#endif // ERRORES_LEXICO_H