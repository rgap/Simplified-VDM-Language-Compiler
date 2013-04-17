/*! \file List.h
* \brief Define la estructura de datos lista
*/

#pragma once
#ifndef LIST_H 
#define LIST_H

/*! \class cNode
* \brief Declara un nodo a usarse en la lista
*/
template <typename T>
class cNode{
public:
	T Dato;
	cNode<T> *pSig;
	cNode( T D ):Dato( D ), pSig( 0 ){}
	void Matate(){
		if(pSig)
			pSig -> Matate();
		delete this;
	}
};



/*! \class cList
* \brief Estructura de datos lista
*/
template <typename T>
class cList{
public:
	cList():pHead(0){}
    ~cList(){
		if(pHead) 
			pHead->Matate();
	}
    int Find(T dato, cNode<T> **&p);
    bool Add(T dato);
    bool Delete(T dato);
    cNode<T> *getHead(){ 
		return pHead;
	}
private:
	cNode<T> *pHead;
};

template <typename T>
int cList<T>::Find(T dato, cNode<T> **&p){
	p = &pHead;
	while(*p){
		if((*p)->Dato == dato)
			return 1;
		if( (*p) -> Dato > dato )
			return 0;
		p = &( (*p) -> pSig);
	}
	return 0;
}

template <typename T>
bool cList<T>::Add(T dato){
	cNode<T> **q;
	if(Find(dato, q))
		return 0;
	cNode<T> *Nuevo = new cNode<T>(dato);
	Nuevo -> pSig = *q;
	*q = Nuevo;
	return 1;
}

template <typename T>
bool cList<T>::Delete(T dato){
	cNode<T> **q;
	if(Find(dato, q)){
		cNode<T> *pAux = *q;
		*q = pAux -> pSig;
		delete pAux;
		return 1;
	}
	return 0;
}

#endif