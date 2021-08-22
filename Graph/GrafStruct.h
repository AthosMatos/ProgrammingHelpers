#pragma once
#include <string>

using namespace std;

struct Arestas
{
	int ID;
	const wchar_t* name;

	float Valor;

	const wchar_t* V1;
	bool BV1;
	const wchar_t* V2;
	bool BV2;

	Arestas* next;
	Arestas* prev;
};


struct Vertices
{
	const wchar_t* name;

	bool isConnected; // nem usei kkk
	bool CountPMin;

	Vertices* next;
	Vertices* prev;
};

struct MinVnames
{
	const wchar_t* name;
	int GroupID;

	MinVnames* next;
	MinVnames* prev;
};


