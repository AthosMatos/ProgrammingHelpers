#include "Grafo.h"
#include <fstream>
#include <iostream>

void GrafoTest1();
void GrafoTest2();

Grafo* G1;

int main()
{
	G1 = new Grafo(L"G1");
	
	GrafoTest1();
	//GrafoTest2();
	
	

	G1->PesoMin();



	G1->AllVerticesArestasInfo(); //info dos vertices e arestas
	G1->Grafoinfo(); //info geral do grafo

	return 0;
}

void GrafoTest1()
{
	G1->Add_Vertice(L"H");
	G1->Add_Vertice(L"D");
	G1->Add_Vertice(L"B");
	G1->Add_Vertice(L"C");
	G1->Add_Vertice(L"F");
	G1->Add_Vertice(L"E");
	G1->Add_Vertice(L"A");
	G1->Add_Vertice(L"G");
	


	G1->Add_Aresta(L"A1", L"A", L"G", 5);
	G1->Add_Aresta(L"A2", L"A", L"B", 10);
	G1->Add_Aresta(L"A3", L"B", L"H", 8);
	G1->Add_Aresta(L"A4", L"B", L"C", 4);
	G1->Add_Aresta(L"A5", L"C", L"F", 9);
	G1->Add_Aresta(L"A6", L"F", L"E", 6);
	G1->Add_Aresta(L"A7", L"E", L"D", 10);
	G1->Add_Aresta(L"A8", L"D", L"H", 20);


}

void GrafoTest2()
{
	G1->Add_Vertice(L"A");
	G1->Add_Vertice(L"B");
	G1->Add_Vertice(L"C");
	G1->Add_Vertice(L"D");
	G1->Add_Vertice(L"E");
	G1->Add_Vertice(L"F");


	G1->Add_Aresta(L"A1", L"A", L"B", 4);
	G1->Add_Aresta(L"A2", L"A", L"E", 4);
	G1->Add_Aresta(L"A3", L"A", L"D", 3);

	G1->Add_Aresta(L"A4", L"B", L"C", 8);
	G1->Add_Aresta(L"A6", L"B", L"F", 5);
	G1->Add_Aresta(L"A7", L"B", L"E", 9);

	G1->Add_Aresta(L"A8", L"C", L"D", 9);
	G1->Add_Aresta(L"A9", L"C", L"F", 2);

	G1->Add_Aresta(L"A10", L"D", L"F", 7);

	G1->Add_Aresta(L"A11", L"F", L"E", 2);
}
