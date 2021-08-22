#pragma once
#include <string>

using namespace std;

struct Arestas
{
	int ID;
	const wchar_t* name;

	float Valor;

	const wchar_t* V1;
	const wchar_t* V2;

	Arestas* next;
	Arestas* prev;
};


struct Vertices
{
	const wchar_t* name;

	bool isConnected; // nem usei kkk

	Vertices* next;
	Vertices* prev;
};



