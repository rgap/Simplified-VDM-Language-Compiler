#ifndef SINTACTICO_H
#define SINTACTICO_H

#include "stdafx.h"
#include <iostream>
#include "token.h"
#include "lexico.h"
#include "tabla_simbolos.h"
#include "sintactico.h"
#include <vector>
#include <stack>
#include <string>

using namespace std;


#define VACIO -2
#define ERROR -1

//enum TokenType{
//	/*Terminales*/
//	ID,OP_MAS,OP_PROD,PAR_A,PAR_C,$
//};

class TS{
private:
	char*lexema;
	TokenType tipo;
public:
	TS(){};
	TS(char*lex,TokenType t){
		lexema=lex;
		tipo=t;
	}
	~TS(){}
	char*getLexema(){return lexema;}
	TokenType getTipo(){return tipo;}
};

TS elemento[5];



enum Noterm{
	/*No terminales*/
	E=6,E1,T,T1,F
};

int producciones[8][3]={
	//E
	{VACIO,T,E1},
	//E'
	{,T,E1},
	{VACIO,VACIO,VACIO},
	//T
	{VACIO,F,T1},
	//T'
	{OP_PROD,F,T1},
	{VACIO,VACIO,VACIO},
	//F
	{PAR_A,PAR_C},
	{VACIO,VACIO,ID}
};

//Tabla de Analisis Sintactico
int M[5][6]={
		   /*  id      +       *       (       )       $*/
	/*E  */	{  0,    ERROR,  ERROR,    0,    ERROR,  ERROR},
	/*E' */ {ERROR,    1,    ERROR,  ERROR,    2,      2  },
	/*T  */ {  3,    ERROR   ERROR,    3,    ERROR,  ERROR},
	/*T' */ {ERROR,    5,      4,    ERROR,    5,      5  },
	/*F' */ {  7,    ERROR,  ERROR,    6,    ERROR,  ERROR}
};

class produccion{
private:
	char*prod;
	vector<int>vals;
public:
	produccion(char*p,vector<int>v){
		prod=p;
		vals=v;
	}
	~produccion(){};
};

class Sintactico{
private:
	vector<int>pila;
	vector<int>entrada;
	vector<string>Noterm;

	int ip; //posicion de puntero en la entrada

	Lexico Lex;

public:
	bool traza;

	Sintactico();
	~Sintactico(){};
	void analyze(); //analiza la entrada actual
	void meteren_pila(int numprod);
	void mostrar_pila();
	void set_entrada(vector<int>entrada);
	void mostrar_entrada();
	void mostrar_linea_tr();
	void error();
};

Sintactico::Sintactico(){
	Noterm.push_back("E");
	Noterm.push_back("E'");
	Noterm.push_back("T");
	Noterm.push_back("T'");
	Noterm.push_back("F");

	pila.push_back($);

	ip=0;
}

void Sintactico::analyze(){
	if(traza)
		cout<<"Pila\tENTRADA\n$E\n";

	pila.push_back(E);

	entrada.push_back($);
	Lex.getToken();

	ip=0;
	int X=pila.back();

	while(X != $){
		if(X==entrada[ip]){
			pila.pop_back(),ip++;
			mostrar_linea_tr();
		}
		else if(X>=0 && X<=4){
			error();
			break;
		}
		else if(M[X-6][entrada[ip]]==ERROR){
			error();
			break;
		}
		else{
			pila.pop_back();
			meteren_pila(M[X-6][entrada[ip]]);
			mostrar_linea_tr();
		}
		X=pila.back();
	}
}

void Sintactico::error(){
	cout<<"Error sintactico";
}

void Sintactico::meteren_pila(int numprod){
	int j=2;
	while(j>=0 && producciones[numprod][j]!=VACIO){
		pila.push_back(producciones[numprod][j]);
		j--;
	}
}

void Sintactico::mostrar_pila(){
	for(int i=0;i<pila.size();++i){
		if(pila[i]>=0 && pila[i]<=5)
			cout<<elemento[pila[i]].getLexema();
		else
			cout<<Noterm[pila[i]-6];
	}
}

void Sintactico::set_entrada(vector<int>e){
	entrada=e;
}

void Sintactico::mostrar_entrada(){
	for(int i=ip;i<entrada.size();++i)
		cout<<elemento[entrada[i]].getLexema();
}

void Sintactico::mostrar_linea_tr(){
	mostrar_pila();
	cout<<'\t';
	mostrar_entrada();
	cout<<'\n';
}


int main(){
	elemento[0]=TS("id",ID);
	elemento[1]=TS("+",OP_MAS);
	elemento[2]=TS("*",OP_PROD);
	elemento[3]=TS("(",PAR_A);
	elemento[4]=TS(")",PAR_C);
	elemento[5]=TS("$",$);

	//Lexico
	int e[] = {PAR_C,ID,OP_MAS,ID,OP_PROD,ID};
	vector<int> entrada(e,e+6);
	//Sintactico
	sintactico sint;
	sint.traza=true;
	sint.set_entrada(entrada);
	sint.analyze();

	return 0;
}

#endif // SINTACTICO_H