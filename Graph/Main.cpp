#include "Grafo.h"
#include <fstream>
#include <iostream>

int main()
{
	Grafo* G1;

	G1 = new Grafo(L"G1");
	
	G1->Add_Vertice(L"V1");
	G1->Add_Vertice(L"V2");
	G1->Add_Vertice(L"V3");
	G1->Add_Vertice(L"V4");
	G1->Add_Vertice(L"V5");

	G1->Add_Aresta(L"A1", L"V1", L"V2", 0);
	G1->Add_Aresta(L"A2", L"V2", L"V3", 10);
	G1->Add_Aresta(L"A3", L"V2", L"V5", 5);
	G1->Add_Aresta(L"A4", L"V3", L"V4", 7);
	G1->Add_Aresta(L"A5", L"V4", L"V5", 18);

	//G1->Del_Vertice(L"V2");
	//G1->Del_Aresta(L"A2");
	G1->Del_Vertice_E_Arestas_Conectadas(L"V2");



	G1->AllVerticesArestasInfo(); //info dos vertices e arestas
	G1->Grafoinfo(); //info geral do grafo

	return 0;
}

