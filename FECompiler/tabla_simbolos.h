#pragma once
/*! \file tabla_simbolos.h
* \brief Define la tabla de simbolos
*/

#ifndef TABLA_SIMBOLOS_H
#define TABLA_SIMBOLOS_H

#include <hash_map>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include "token.h"
#include "globales.h"

using namespace std;


class Registro{    
private:
	TokenType tipo_token;
	bool especifico;
	string lexema;
	string token_string;
	string tipo_variable;
	list<int>lineas;
public:
	~Registro(){};
	Registro(){};
	Registro(string lexema,TokenType tipo_t,string token_string,bool esp){
		this->lexema=lexema;
		this->tipo_token= tipo_t;
		this->token_string=token_string;
		this->especifico=esp;
	}
	void set_tipo(string tipo){
		this->tipo_variable=tipo;
	}
	void add_linea(int linea){
		lineas.push_back(linea);
	}
	string get_lexema(){
		return lexema;
	}
	TokenType get_token(){
		return tipo_token;
	}
	string get_tokenstring(){
		return token_string;
	}
	bool es_especifico(){
		return especifico;
	}
	void mostrar_registro(){

		list<int>::iterator itR;
		if(especifico)reporte<<"ESPECIFICO:";
		else reporte<<"NO ESPECIFICO:";
		reporte<<"\t Lexema: "<<lexema<<"\t Token: "<<token_string;
		if(!especifico){
			reporte<<"\t Tipo: "<<tipo_variable<<endl;
			reporte<<"\tLineas: ";
			for(itR=lineas.begin();itR!=lineas.end();++itR){
				if(itR!=lineas.begin())
					reporte<<", ";
				reporte<<*itR;
			}
		}
	}
};

class Tabla_simbolos{
private:
	hash_map<string,Registro>TS;
public:
	Tabla_simbolos(){};
	~Tabla_simbolos(){};
	void insertarRegistro(string lexema,TokenType tipo,string token_string,bool esp);
	void set_tipo(string lexema,string tipo_variable);
	void add_lineas(string lexema,int linea);
	Registro get_registro(string lexema);
	TokenType get_token(string lexema);
	string get_lexema(string lexema);
	string get_tokenstring(string lexema);
	bool existe_reg(string lexema);
	bool especifico(string lexema);
	void mostrar_tabla();
	bool vacia();
};


void Tabla_simbolos::insertarRegistro(string lexema,TokenType tipo,string token_string,bool esp){	
	Registro r = Registro(lexema,tipo,token_string,esp);
	TS[lexema]=r;
}
void Tabla_simbolos::set_tipo(string lexema,string tipo_variable){
	TS[lexema].set_tipo(tipo_variable);		
}

void Tabla_simbolos::add_lineas(string lexema,int linea){
	TS[lexema].add_linea(linea);
}
	
Registro Tabla_simbolos::get_registro(string lexema){
	return TS[lexema];
}

string Tabla_simbolos::get_lexema(string lexema){
	return TS[lexema].get_lexema();
}

TokenType Tabla_simbolos::get_token(string lexema){
	return TS[lexema].get_token();
}

bool Tabla_simbolos::existe_reg(string lexema){
	if(TS[lexema].get_tokenstring().empty())
		return false;
	return true;
}

string Tabla_simbolos::get_tokenstring(string lexema){
	return TS[lexema].get_tokenstring();
}

bool Tabla_simbolos::especifico(string lexema){
	return TS[lexema].es_especifico();
}

void Tabla_simbolos::mostrar_tabla(){

	hash_map <string,Registro>::iterator itTS;
	bool k=1;
	reporte<<"-----------------------TOKENS ESPECIFICOS----------------------"<<endl<<endl;
	for(itTS=TS.begin();itTS!=TS.end();itTS++){
		if(!(itTS->second.es_especifico()) && k){
			reporte<<endl<<"----------------------TOKENS NO ESPECIFICOS---------------------"<<endl<<endl;
			k=0;
		}
		reporte<<"Lex: "<<itTS->first<<"\t";
		itTS->second.mostrar_registro();
		reporte<<endl;
	}
}

bool Tabla_simbolos::vacia(){
	return TS.empty();
}

#endif