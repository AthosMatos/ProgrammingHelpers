#include "Grafo.h"

void clear()
{
	cout << endl << endl << endl;
}

Grafo::Grafo(const wchar_t* name)
{
	V_HEAD = NULL;
	A_HEAD = NULL;

	Gname = name;
}

void Grafo::Add_Vertice(const wchar_t* name)
{
	if (V_HEAD == NULL)
	{
		V_HEAD = (Vertices*)malloc(sizeof(Vertices));

		V_HEAD->name = name;
		V_HEAD->isConnected = false;

		V_HEAD->next = NULL;
		V_HEAD->prev = NULL;	

		return;
	}
	else
	{
		Vertices* NV;
		NV = (Vertices*)malloc(sizeof(Vertices));
		NV->name = name;
		NV->isConnected = false;
		NV->next = NULL;

		if (V_HEAD->next == NULL)
		{
			NV->prev = V_HEAD;
			V_HEAD->next = NV;

			return;
		}
		else
		{
			Vertices* V_Temp = V_HEAD;
			while (V_Temp->next != NULL)V_Temp = V_Temp->next;
			V_Temp->next = NV;
			NV->prev = V_Temp;

			return;
		}
	}
}

void Grafo::Add_Aresta(const wchar_t* name, const wchar_t* V1, const wchar_t* V2, float valor)
{		
	if (A_HEAD == NULL)
	{
		A_HEAD = (Arestas*)malloc(sizeof(Arestas));

		A_HEAD->name = name;
		A_HEAD->ID = 1;
		A_HEAD->Valor = valor;		

		A_HEAD->V1 = V1;
		Vertices* tempV = V_HEAD;
		while (tempV->name != V1)tempV = tempV->next;
		tempV->isConnected = true;

		A_HEAD->V2 = V2;
		tempV = V_HEAD;
		while (tempV->name != V2)tempV = tempV->next;
		tempV->isConnected = true;

		A_HEAD->next = NULL;
		A_HEAD->prev = NULL;
	}
	else
	{
		Arestas* NA;
		NA = (Arestas*)malloc(sizeof(Arestas));

		NA->name = name;
		NA->Valor = valor;
		
		NA->V1 = V1;
		Vertices* tempV = V_HEAD;
		while (tempV->name != V1)tempV = tempV->next;
		tempV->isConnected = true;

		NA->V2 = V2;
		tempV = V_HEAD;
		while (tempV->name != V2)tempV = tempV->next;
		tempV->isConnected = true;

		NA->next = NULL;

		if (A_HEAD->next == NULL)
		{
			NA->prev = A_HEAD;
			NA->ID = A_HEAD->ID + 1;
			A_HEAD->next = NA;
		}
		else
		{
			Arestas* A_Temp = A_HEAD;
			while (A_Temp->next != NULL)A_Temp = A_Temp->next;
			A_Temp->next = NA;
			NA->prev = A_Temp;
			NA->ID = A_Temp->ID + 1;
		}
	}
}

void Grafo::AllVerticesArestasInfo()
{
	Vertices* TempV = V_HEAD;
	Arestas* TempA = A_HEAD;
	
	while (true)
	{
		clear();
		cout << "///////VERTICE " << ConvertString(TempV->name) << " ///////" << endl;

		while (true)
		{
			if ((TempA->V1 == TempV->name) || (TempA->V2 == TempV->name))
			{
				if (TempA->V1 != TempV->name)
				{
					cout << "||ARESTA " << ConvertString(TempA->name) << "||" <<
						" conectada ao vertice " << ConvertString(TempA->V1) <<
						" com o valor " << TempA->Valor << endl;
				}
				if (TempA->V2 != TempV->name)
				{
					cout << "||ARESTA " << ConvertString(TempA->name) << "||" <<
						" conectada ao vertice " << ConvertString(TempA->V2) <<
						" com o valor " << TempA->Valor << endl;
				}
				if ((TempA->V1 == TempV->name) && (TempA->V2 == TempV->name))
				{
					cout << "||ARESTA " << ConvertString(TempA->name) << "||" <<
						" conectada ao vertice " << ConvertString(TempA->V2) <<
						" com o valor " << TempA->Valor << endl;
				}
			}

			if (TempA->next != NULL)TempA = TempA->next;
			else { TempA = A_HEAD; break; }
		}
		if (TempV->next != NULL)TempV = TempV->next;
		else return;
	}
}

void Grafo::Del_Vertice(const wchar_t* name)
{
	Vertices* TempV = V_HEAD;
	while (TempV->name != name)
	{
		if (TempV->next != NULL) TempV = TempV->next;
		else { cout << "Vertice Nao encontrado" << endl; return; }
	}
		
	if (TempV->prev != NULL)TempV->prev->next = TempV->next;	
	if (TempV->next != NULL)TempV->next->prev = TempV->prev;
	
	if (TempV->prev == NULL)V_HEAD = TempV->next;

	free(TempV);
}

void Grafo::Del_Vertice_E_Arestas_Conectadas(const wchar_t* name)
{
	Vertices* TempV = V_HEAD;
	while (TempV->name != name)
	{
		if (TempV->next != NULL) TempV = TempV->next;
		else { cout << "Vertice Nao encontrado" << endl; return; }
	}

	if (TempV->prev != NULL)TempV->prev->next = TempV->next;
	if (TempV->next != NULL)TempV->next->prev = TempV->prev;

	if (TempV->prev == NULL)V_HEAD = TempV->next;

	free(TempV);

	FullDelete(name);
}

void Grafo::Del_Aresta(const wchar_t* name)
{
	Arestas* TempA = A_HEAD;
	while (TempA->name != name)
	{
		if (TempA->next != NULL) TempA = TempA->next;
		else { cout << "Aresta Nao encontrada" << endl; return; }
	}

	if (TempA->prev != NULL)TempA->prev->next = TempA->next;
	if (TempA->next != NULL)TempA->next->prev = TempA->prev;

	if (TempA->prev == NULL)A_HEAD = TempA->next;

	free(TempA);
}

void Grafo::Grafoinfo()
{
	wstring ws(Gname);
	string nomegrafo(ws.begin(), ws.end());

	clear();

	int x = 1;
	Vertices* TempV = V_HEAD;
	Arestas* TempA = A_HEAD;

	cout << "////////GRAFO " << nomegrafo <<"////////"<< endl;

	while (TempV->next != NULL) { TempV = TempV->next; x++; }
	cout << "Numero total de Vertices: " << x << endl;

	x = 1;

	while (TempA->next != NULL) { TempA = TempA->next; x++; }
	cout << "Numero total de Arestas: " << x << endl;

	clear();
}

string Grafo::ConvertString(const wchar_t* Nome)
{
	wstring ws(Nome);
	string s(ws.begin(), ws.end());

	return s;
}

void Grafo::FullDelete(const wchar_t* Nome)
{
	Arestas* TempA = A_HEAD;
	
	while (true)
	{
		if ((TempA->V1 == Nome) || (TempA->V2 == Nome))
		{
			if (TempA->prev == NULL)
			{
				if (TempA->next != NULL)
				{
					TempA->next->prev = NULL;
					A_HEAD = TempA->next;
					free(TempA);
					TempA = A_HEAD;
					continue;
				}
				else { free(TempA); A_HEAD = NULL; TempA = A_HEAD; }
			}
			else
			{
				Arestas* TTemp;
				TempA->prev->next = TempA->next;
				TTemp = TempA->next;
				free(TempA);
				TempA = TTemp;
				continue;
			}
		}

		if (TempA->next != NULL)TempA = TempA->next;
		else return;
	}
}











