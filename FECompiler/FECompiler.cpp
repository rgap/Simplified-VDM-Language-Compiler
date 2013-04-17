#include "stdafx.h"
/****************************************************/ 
/* File: FECompiler.cpp                             */ 
/****************************************************/ 

#include "globales.h" 
#include "token.h"
//#include "sintactico.h"
#include "lexico.h"
#include "matriz_esparza.h"
#include "tabla_simbolos.h"

using namespace std;

int main(){
	codefn="ejemplo2.txt"; 
	reportefn="reporte.txt";

	//reporte=(fstream)stdout;
	reporte.open(reportefn, ofstream::out);

	codigo.open(codefn, ifstream::in);
	if (codigo==NULL){ 
		reporte<<"ERROR: Archivo de ruta \""<<codefn<< "\" no encontrado."; 
		exit(1); 
	} 

	iniciar_TS();
	
	reporte<<"\nArchivo de reporte: "<<reportefn; 
	reporte<<"\nReporte Compilacion de archivo: "<<codefn<<"\n\n"; 

	/*---------------------------------------------------*/

	Lexico lex = Lexico(1);
	//Sintactico sint;

	TokenType tokenEntrada=INICIOTEXTO;

	while(tokenEntrada!=FINTEXTO){
		tokenEntrada=lex.getToken();
	}

	//TS.mostrar_tabla();
	//Sintactico sint;
	//sint.traza=true;
	//sint.analyze();

	/*----------------------------------------------------*/

	reporte.close();
	codigo.close();
	return 0; 
} 
