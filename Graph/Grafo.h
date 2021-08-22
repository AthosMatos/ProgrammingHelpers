#pragma once
#include "GrafStruct.h"
#include <iostream>

class Grafo
{
public:
	Grafo(const wchar_t* name);

public:
	void Add_Vertice(const wchar_t* NomeVertice);
	void Add_Aresta(const wchar_t* NomeAresta, const wchar_t* V1, const wchar_t* V2, float valor);
	
	void Del_Vertice(const wchar_t* NomeVertice);
	void Del_Vertice_E_Arestas_Conectadas(const wchar_t* NomeVertice);
	void Del_Aresta(const wchar_t* NomeAresta);
	void PesoMin();


	void AllVerticesArestasInfo();
	void Grafoinfo();

private:
	Vertices* V_HEAD;
	Arestas* A_HEAD;
	MinVnames* Vnames;

	const wchar_t* Gname;
	bool Pesomin;
	int ValorMin;
	
private:
	string ConvertString(const wchar_t* Nome);
	void FullDelete(const wchar_t* Nome);
	void OrderArestas();
};

