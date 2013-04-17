#ifndef LEXICO_H
#define LEXICO_H

#include "globales.h" 
#include "token.h"
#include "tabla_simbolos.h"
#include "matriz_esparza.h"
#include "errores_lexicos.h"

#define CLINEA -1
#define CBLOQUE -2

class Lexico{
private:
	int numlinea; //numero linea actual
	int linepos; //posicion en la linea actual
	char caracterLeido; //caracter actual
	bool correcto; //es correcto el analisis lexico
	bool espacio; // espacio en blanco en lectura
	bool encontrado; // posicion en la matriz encontrada
	bool llenar;
	bool reemplazo;
	int comentario; //en lectura comentariolinea=0,comentariobloque=1
	TokenType tokenActual;
	string lexemaActual;
	int poscaracter; //columna del caracter leido en el automata
	bool nuevalinea;
	int numlineant;

	vector<errorLexico*>erroresL;

	Matriz<int>M; //matriz de transicion para los tokens
	int state; //estados actual en el automata
	bool traza;

public:
	Lexico(bool tr);
	~Lexico(){}
	TokenType getToken();
	void imprimirTokens(TokenType &token);
	TokenType BuscarTS(char*s);
	void darpos(char &c);
	void saltarComentarios();
	void saltarEspacios();
	void mostrar_error();
	
};

Lexico::Lexico(bool tr){
	if(tr){
		reporte<<"--------------------------Analisis Lexico--------------------------"<<endl;
		traza=1;
	}
	else traza=0;

	correcto=1;
	numlinea=1;
	linepos=0;
	espacio=1;
	comentario=-1;
	llenar=0;
	reemplazo=0;
	nuevalinea=0;

	M.Add(1,0,0); M.Add(2,0,1); M.Add(5,0,'\''); M.Add(9,0,'"'); M.Add(27,0,'.'); M.Add(11,0,'='); M.Add(17,0,'>'); M.Add(14,0,'<'); M.Add(19,0,':'); M.Add(21,0,'+'); M.Add(22,0,'-'); M.Add(25,0,'*'); M.Add(24,0,'/'); M.Add(30,0,'('); M.Add(31,0,')'); M.Add(32,0,'['); M.Add(33,0,']'); M.Add(34,0,'{'); M.Add(35,0,'}'); M.Add(36,0,';'); M.Add(37,0,',');
	M.Add(1,1,0); M.Add(1,1,1);
	M.Add(2,2,1); M.Add(3,2,'.');
	M.Add(4,3,1);
	M.Add(4,4,1);
	M.Add(6,5,0); M.Add(6,5,1); M.Add(6,5,'\''); M.Add(6,5,'"'); M.Add(6,5,'.'); M.Add(6,5,'='); M.Add(6,5,'>'); M.Add(6,5,'<'); M.Add(6,5,':'); M.Add(6,5,'+'); M.Add(6,5,'-'); M.Add(6,5,'*'); M.Add(6,5,'/'); M.Add(6,5,'('); M.Add(6,5,')'); M.Add(6,5,'['); M.Add(6,5,']'); M.Add(6,5,'{'); M.Add(6,5,'}'); M.Add(6,5,';'); M.Add(7,5,'\\');M.Add(6,5,2);
	M.Add(8,6,'\''); 
	M.Add(6,7,0); M.Add(6,7,1); M.Add(6,7,'\''); M.Add(6,7,'"'); M.Add(6,7,'.'); M.Add(6,7,'='); M.Add(6,7,'>'); M.Add(6,7,'<'); M.Add(6,7,':'); M.Add(6,7,'+'); M.Add(6,7,'-'); M.Add(6,7,'*'); M.Add(6,7,'/'); M.Add(6,7,'('); M.Add(6,7,')'); M.Add(6,7,'['); M.Add(6,7,']'); M.Add(6,7,'{'); M.Add(6,7,'}'); M.Add(6,7,';'); M.Add(6,7,'\\');M.Add(6,7,2);
	M.Add(9,9,0); M.Add(9,9,1); M.Add(10,9,'\"'); M.Add(9,0,'"'); M.Add(9,9,'.'); M.Add(9,9,'='); M.Add(9,9,'>'); M.Add(9,9,'<'); M.Add(9,9,':'); M.Add(9,9,'+'); M.Add(9,9,'-'); M.Add(9,9,'*'); M.Add(9,9,'/'); M.Add(9,9,'('); M.Add(9,9,')'); M.Add(9,9,'['); M.Add(9,9,']'); M.Add(9,9,'{'); M.Add(9,9,'}'); M.Add(9,9,';'); M.Add(9,9,'\\'); M.Add(9,9,2);
	M.Add(12,11,'=');
	M.Add(13,12,'>');
	M.Add(15,14,'='); M.Add(16,14,'>');
	M.Add(18,17,'=');
	M.Add(20,19,'=');
	M.Add(23,22,'>'); M.Add(CLINEA,22,'-');	
	M.Add(CBLOQUE,24,'*');
	M.Add(26,25,'*');
	M.Add(28,27,'.');
	M.Add(29,28,'.');
}

TokenType Lexico::getToken(){
	state=0; 
	encontrado=1;
	espacio=1;

	numlineant=numlinea;

	while(espacio){
		caracterLeido=(char)codigo.get();
		saltarEspacios();
		if(!espacio && caracterLeido==10)
			numlinea--;
	}
	codigo.unget(),linepos--;
	
	while(!codigo.eof()){ 
		caracterLeido=(char)codigo.get();

		saltarEspacios();

		if(comentario!=-1)
			saltarComentarios();

		if(!espacio && comentario==-1 && state!=CLINEA && state!=CBLOQUE){
			darpos(caracterLeido);

			state=M.getDato(state,poscaracter,encontrado);

			if(state==CLINEA) comentario=1,state=0,lexemaActual.clear(),llenar=0;
			else if(state==CBLOQUE) comentario=0,state=0,lexemaActual.clear(),llenar=0;
			else llenar=1;
		}
		if(llenar && encontrado && !espacio)
			lexemaActual+=caracterLeido;

		if((espacio && comentario==-1 && !lexemaActual.empty()) ||!encontrado){
			if(caracterLeido==10)
				numlinea--;
			codigo.unget(),linepos--;
			break;
		}
	}

	if(codigo.eof()){
		if(traza){
			reporte<<"\n\n------------------------FIN DEL ANALISIS LEXICO------------------------"<<endl<<endl;
			if(correcto)
				reporte<<">>>> Analisis lexico correcto <<<<";
			else{
				reporte<<">>>> Analisis lexico con errores <<<<"<<endl;
				reporte<<"Numero de errores: "<<erroresL.size()<<endl;
				int i=0;
				while(i<erroresL.size()){
					reporte<<"ERROR #"<<i+1<<" :"<<" Tipo error: "<<errores[erroresL[i]->tipoerror]<<"\tLinea: "<<erroresL[i]->numlinea<<"\terror: "<<erroresL[i]->error<<endl;
					i++;
				}
			}
		}

		return FINTEXTO;
	}

	if((nuevalinea && numlinea!=numlineant) || (numlinea==1 && nuevalinea==0)){
		if(traza)
			reporte<<"\nLinea "<<numlinea<<" :"<<endl;
		nuevalinea=0;
	}

	if(traza)
		reporte<<"\t";
	if(state==0 || state==3 || state==5 || state==6 || state==7 || state==9 || state==28){
		(char)codigo.get();
		correcto=0;
		if(traza)
			mostrar_error();
		return ERROR;
	}
	else if(TS.existe_reg(lexemaActual) && TS.especifico(lexemaActual)){
		TS.add_lineas(lexemaActual,numlinea);
		if(traza)
			TS.get_registro(lexemaActual).mostrar_registro();
	}

	else if(TS.existe_reg(lexemaActual) && !TS.especifico(lexemaActual)){
		TS.add_lineas(lexemaActual,numlinea);
		if(traza)
			TS.get_registro(lexemaActual).mostrar_registro();
	}
	else if(!TS.existe_reg(lexemaActual)){
		if(state==1)
			TS.insertarRegistro(lexemaActual,T_ID,"T_ID",0);	
		else if(state==2)
			TS.insertarRegistro(lexemaActual,T_NUMERO,"T_NUMERO",0);	
		else if(state==4)
			TS.insertarRegistro(lexemaActual,T_NUMREAL,"T_NUMREAL",0);	
		else if(state==8)
			TS.insertarRegistro(lexemaActual,T_CARACTER,"T_CARACTER",0);	
		else if(state==10)
			TS.insertarRegistro(lexemaActual,T_CADENA,"T_CADENA",0);	
		TS.add_lineas(lexemaActual,numlinea);
		if(traza)
			TS.get_registro(lexemaActual).mostrar_registro();
	}

	lexemaActual.clear();
	if(traza)
		reporte<<endl<<endl;
	return tokenActual;
}

void Lexico::mostrar_error(){
	reporte<<"ERROR: ";
	if(state==0){
		string lexAct;lexAct+=caracterLeido;
		if(caracterLeido>=0 && caracterLeido<=126){
			reporte<<errores[0]<<" "<<caracterLeido;
			erroresL.push_back(new errorLexico(numlinea,0,lexAct));
		}
		else{
			reporte<<errores[1]<<" "<<caracterLeido;
			erroresL.push_back(new errorLexico(numlinea,1,lexAct));
		}
	}
	else if(state==3){
		erroresL.push_back(new errorLexico(numlinea,2,lexemaActual));
		reporte<<errores[2];
	}
	else if(state==6){
		erroresL.push_back(new errorLexico(numlinea,3,lexemaActual));
		reporte<<errores[3];
	}
	else if(state==28){
		erroresL.push_back(new errorLexico(numlinea,4,lexemaActual));
		reporte<<errores[4];
	}
}

void Lexico::darpos(char &c){
	if((c>=65 && c<=90) //A-Z
		|| (c>=97 && c<=122) //a-z
		|| c=='$'
		|| c=='_') //$
		poscaracter=0; //c - pertenecientes a T_ID
	else if(c>=48 && c<=57) //0-9
		poscaracter=1; //d - numeros
	else if(c=='\'' 
		|| c=='"' 
		|| c=='"' 
		|| c=='.' 
		|| c=='=' 
		|| c=='>' 
		|| c=='<' 
		|| c==':' 
		|| c=='+' 
		|| c=='-' 
		|| c=='*' 
		|| c=='/' 
		|| c=='(' 
		||c==')' 
		|| c=='[' 
		|| c==']' 
		|| c=='{' 
		|| c=='}' 
		|| c==';' 
		|| c==',' 
		|| c=='\\') 
		poscaracter=c; //columnas de la MT
	else
		poscaracter=2; //otro caracter
}

void Lexico::saltarComentarios(){
	if(comentario==0){ //Com bloque
		switch(state){
			case 0:
				if(caracterLeido=='*') state=1;
				break;
			case 1:
				if(caracterLeido=='*') state=1;
				else if(caracterLeido=='/') espacio=1,comentario=-1,state=0;
				else state=0;
				break;
		}
	}
	if(comentario==1 && caracterLeido==10)//Com linea
		comentario=-1,state=0;
}

void Lexico::saltarEspacios(){
	if(caracterLeido==10){
		numlinea++,linepos=1,espacio=1;//salto de linea
		nuevalinea=1;
	}
	else if(caracterLeido==32)
		linepos++,espacio=1;//espacio
	else if(caracterLeido==9)
		linepos+=4,espacio=1;//tabulador
	else
		espacio=0,linepos++,espacio=0;
}

#endif // LEXICO_H