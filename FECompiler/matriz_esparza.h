/*! \file matriz_esparza.h
* \brief Define la estructura de datos de la Matriz Esparsa
*/
#pragma once
#ifndef MATRIZ_H
#define MATRIZ_H

#include "list.h"

/*! \class Nodo
* \brief Nodo de la Matriz Esparsa
*/
template <typename T>
class Nodo{
public:
	T Dato;
	int f;
	int c;
	Nodo<T> *pSigf;
	Nodo<T> *pSigc;
	Nodo(T Dato, int fil, int col){
		this -> Dato = Dato;
		f = fil;
		c = col;
		pSigf = pSigc = 0;
	}
	void DestroyFila(void){ //Libera el puntero a fila
		if(this -> pSigf)
			pSigf -> DestroyFila(); 
		delete this;
	}
	void DestroyColumna(void){ //Libera el puntero a columna
		if(this -> pSigc)
			pSigf -> DestroyColumna();
		delete this;
	}
};



/*! \class Cabecera
* \brief Cabecera de la matriz esparza
*/
template <typename T>
class Cabecera{
public:
	int pos;
    Nodo<T> *pNodo;
    Cabecera(int p, Nodo<T> *q = 0){
        pos = p;
        pNodo = q;
    }
    bool operator==(Cabecera<T> &A){ //A = Referencia a la cabecera
        return pos == A.pos;
    }
    bool operator>(Cabecera<T> &A){ //A = Referencia a la cabecera
        return pos > A.pos;
	}
};


/*! \class Matriz
* \brief Estructura de datos Matriz Esparsa
*/
template <typename T>
class Matriz{
public:
	Matriz(){}
	~Matriz(){}
	bool Findf( int f, int c, Nodo<T> **&p );
	bool Findc( int f, int c, Nodo<T> **&q );
	bool Add( T dato, int f, int c );
	bool Delete( int f, int c );
	T & getDato(int f, int c,bool &flag);
      
private:
	cList<Cabecera<T> > Fil;
	cList<Cabecera<T> > Col;
};


//! Encuentra un Nodo recorriendo fila por fila
/*!
\param  f numero de fila
\param  c numero de columna
\param  p Referencia al nodo encontrado
*/
template <typename T>
bool Matriz<T>::Findf(int f, int c, Nodo<T> **&p){
	cNode<Cabecera<T> > **ptr;
	if(Col.Find(Cabecera<T>(c), ptr)){
		p = &((*ptr) -> Dato.pNodo);
		while(*p){
			if((*p) -> f == f)
				return 1;
			if((*p) -> f > f)
				return 0;
			p = &((*p) -> pSigf);
		}
		return 0;
	}
	return 0;
}

//! Encuentra un Nodo recorriendo columna por columna
/*!
\param  f numero de fila
\param  c numero de columna
\param  p Referencia al nodo encontrado
*/
template <typename T>
bool Matriz<T>::Findc(int f, int c, Nodo<T>**&q){
	cNode<Cabecera<T> > **ptr;
	if(Fil.Find(Cabecera<T>(f), ptr)){
		q = &((*ptr) -> Dato.pNodo);
		while(*q){
			if((*q) -> c == c)return 1;
			if((*q) -> c > c)return 0;
			q = &((*q) -> pSigc);
      }
      return 0;
	}
	return 0;
}
	
//!Añade un Dato en una posicion dada
/*!
\param  T dato a añadir
\param  f numero de fila
\param  c numero de columna
*/
template <typename T>
bool Matriz<T>::Add(T dato, int f, int c){
	Nodo<T> **p, **q;
	Fil.Add(Cabecera<T>(f));
	Col.Add(Cabecera<T>(c));
	if( !Findf( f, c, p ) && !Findc(f, c, q)){
		Nodo<T> *N = new Nodo<T>(dato, f, c);
		N -> pSigf = *p;
		N -> pSigc = *q;
		*p = *q = N;
		return 1;
	}
	return 0;
}

//!Borra un Dato de una posicion dada
/*!
\param  f numero de fila
\param  c numero de columna
\return bool
*/
template <typename T>
bool Matriz<T>::Delete(int f, int c){
	Nodo<T> **p, **q;
	if(Findf(f, c, p) && Findc(f, c, q)){
		Nodo<T> *tmp = *p;
		*p = (*p) -> pSigf;
		*q = (*q) -> pSigc;
		delete tmp;
		return 1;
	}
	return 0;
}

//!Retorna un Dato de una posicion dada
/*!
\param  f numero de fila
\param  c numero de columna
\param  flag Indicador de exito
\return T
*/
template <typename T>
T & Matriz<T>::getDato(int f, int c,bool &flag){	
	T *dato=new T();
	Nodo<T> **p, **q;
	if(Findf(f, c, p) && Findc(f, c, q)){	
		dato=&((*p)->Dato);
		flag=1 ; //encontrado
		return *dato;			
	}
	flag=0;//no fue encontrado
	return f;
	//return *dato;
}
#endif