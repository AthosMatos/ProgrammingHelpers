#include "Grafo.h"

void clear()
{
	cout << endl << endl << endl;
}

Grafo::Grafo(const wchar_t* name)
{
	V_HEAD = NULL;
	A_HEAD = NULL;
	Vnames = NULL;
	Pesomin = false;
	ValorMin = 0;
	Gname = name;
}

void Grafo::Add_Vertice(const wchar_t* name)
{
	if (V_HEAD == NULL)
	{
		V_HEAD = (Vertices*)malloc(sizeof(Vertices));

		V_HEAD->name = name;
		V_HEAD->isConnected = false;
		V_HEAD->CountPMin = false;

		V_HEAD->next = NULL;
		V_HEAD->prev = NULL;	

		return;
	}
	else
	{
		wstring ws(name);
		string nomeV(ws.begin(), ws.end());

		Vertices* TempV = V_HEAD;
		while (true)
		{
			if (TempV->name == name) { cout << "\nVertice " <<nomeV<< " jah existe" << endl; return; }
			if (TempV->next != NULL)TempV = TempV->next;
			else break;
		}

		Vertices* NV;
		NV = (Vertices*)malloc(sizeof(Vertices));
		NV->name = name;
		NV->isConnected = false;
		NV->CountPMin = false;
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
		A_HEAD->BV1 = false;
		A_HEAD->BV2 = false;

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
		wstring ws(name);
		string nomeA(ws.begin(), ws.end());

		Arestas* TempA = A_HEAD;	

		while (true)
		{
			if (TempA->name == name) { cout << "\Aresta " << nomeA << " jah existe" << endl; return; }
			if (TempA->next != NULL)TempA = TempA->next;
			else break;
		}

		Arestas* NA;
		NA = (Arestas*)malloc(sizeof(Arestas));

		NA->name = name;
		NA->Valor = valor;
		NA->BV1 = false;
		NA->BV2 = false;

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
	
	if (A_HEAD == NULL || V_HEAD == NULL)return;

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
	if (A_HEAD == NULL || V_HEAD == NULL)return;

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

	if (A_HEAD == NULL || V_HEAD == NULL)return;

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

void Grafo::PesoMin()
{
	if (A_HEAD == NULL || V_HEAD == NULL)return;

	if (!Pesomin)
	{
		int groupid = 1;
		OrderArestas();
		Arestas* TempA = A_HEAD;
	
		while (true)
		{		
			if (Vnames == NULL)
			{
				Vertices* TempV = V_HEAD;

				Vnames = (MinVnames*)malloc(sizeof(MinVnames));
				Vnames->prev = NULL;
				Vnames->GroupID = 0;

				MinVnames* NVnames = (MinVnames*)malloc(sizeof(MinVnames));
				NVnames->GroupID = 0;
				NVnames->next = NULL;

				Vnames->name = TempA->V1;
				NVnames->name = TempA->V2;

				while (TempV->name != TempA->V1)TempV = TempV->next;
				TempV->CountPMin = true;
				TempV = V_HEAD;
				while (TempV->name != TempA->V2)TempV = TempV->next;
				TempV->CountPMin = true;

				Vnames->next = NVnames;
				NVnames->prev = Vnames;

				Vnames->GroupID = groupid;
				NVnames->GroupID = groupid;

				ValorMin += TempA->Valor;
			}
			else
			{
				//cout << "fds ";

				MinVnames* TempVname = Vnames;
				int G1 = 0;
				int G2 = 0;

				while (true)
				{
					if (TempA->V1 == TempVname->name) 
					{ 		
						G1 = TempVname->GroupID;
						TempVname = Vnames; 
						break; 
					}

					if (TempVname->next != NULL)TempVname = TempVname->next;
					else
					{
						Vertices* TempV = V_HEAD;
						while (TempV->name != TempA->V1)TempV = TempV->next;
						TempV->CountPMin = true;

						MinVnames* NVnames = (MinVnames*)malloc(sizeof(MinVnames));
						NVnames->GroupID = 0;

						NVnames->next = NULL;

						NVnames->name = TempA->V1;
						TempA->BV1 = true;

						TempVname->next = NVnames;
						NVnames->prev = TempVname;
						TempVname = Vnames;
						break;
					}
				}
				
				while (true)
				{				
					if (TempA->V2 == TempVname->name) 
					{ 
						G2 = TempVname->GroupID;
						TempVname = Vnames; 
						break; 
					}

					if (TempVname->next != NULL)TempVname = TempVname->next;
					else
					{
						Vertices* TempV = V_HEAD;
						while (TempV->name != TempA->V2)TempV = TempV->next;
						TempV->CountPMin = true;

						MinVnames* NVnames = (MinVnames*)malloc(sizeof(MinVnames));
						NVnames->GroupID = 0;

						NVnames->next = NULL;
						
						NVnames->name = TempA->V2;
						TempA->BV2 = true;

						TempVname->next = NVnames;
						NVnames->prev = TempVname;
						TempVname = Vnames;
						break;
					}
				}

				if (!(TempA->BV1) || !(TempA->BV2))
				{						
					int Gid;
					if (!TempA->BV1)
					{
						MinVnames* temp = Vnames;
						while (temp->name != TempA->V1)temp = temp->next;
						Gid = temp->GroupID;

						while (TempVname->name != TempA->V2)TempVname = TempVname->next;
						TempVname->GroupID = Gid;
					}
					else if (!TempA->BV2)
					{
						MinVnames* temp = Vnames;
						while (temp->name != TempA->V2)temp = temp->next;
						Gid = temp->GroupID;

						while (TempVname->name != TempA->V1)TempVname = TempVname->next;
						TempVname->GroupID = Gid;
					}												
				}

				if (G1 != 0 && G2 != 0)
				{
					MinVnames* temp = Vnames;
					if (G1 != G2)
					{
						while (true)
						{
							if (temp->GroupID == G2)
							{
								temp->GroupID = G1;
								if (temp->next != NULL)temp = temp->next;
								else break;
							}
							else
							{
								if (temp->next != NULL)temp = temp->next;
								else break;
							}
						}
						TempA->BV1 = true;
					}
				}

				if ((TempA->BV1) && (TempA->BV2))
				{
					while (TempVname->name != TempA->V1)TempVname = TempVname->next;
					groupid++;
					TempVname->GroupID = groupid;

					TempVname = Vnames;

					while (TempVname->name != TempA->V2)TempVname = TempVname->next;
					TempVname->GroupID = groupid;
				}

				if ((TempA->BV1) || (TempA->BV2))
				{	
					ValorMin += TempA->Valor;
				}
				else
				{
					Arestas* TTempA;
					if (TempA->next != NULL)TTempA = TempA->next;
					else return;

					if (TempA->prev != NULL)TempA->prev->next = TempA->next;
					if (TempA->next != NULL)TempA->next->prev = TempA->prev;
					free(TempA);
					
					TempA = TTempA;
					continue;
				}
				
				Vertices* TempV = V_HEAD;

				while (true)
				{	
					bool flag = false;
					MinVnames* TempVN = Vnames;

					while (true)
					{		
						if (TempVN->next != NULL)
						{
							if (TempVN->GroupID == TempVN->next->GroupID)
							{							
								TempVN = TempVN->next;
							}
							else break;
						}
						else
						{
							flag = true;
							break;
						};
					}

					if (TempV->CountPMin && flag)
					{
						if (TempV->next != NULL)TempV = TempV->next;
						else
						{
							Arestas* TNext = TempA->next;
							TempA->next = NULL;
							while (true)
							{
								if (TNext->next != NULL)
								{
									Arestas* Temp = TNext->next;
									free(TNext);
									TNext = Temp;
								}
								else { free(TNext); return; }
							}
						}
					}
					else break;		
				}
			}
			
			if (TempA->next != NULL)TempA = TempA->next;
			else return;
		}
		
		Pesomin = true;
	}

	
}

void Grafo::Grafoinfo()
{
	if (A_HEAD == NULL || V_HEAD == NULL)return;

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

	
	cout << "VALOR MIN " << ValorMin << endl;

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

void Grafo::OrderArestas()
{
	Arestas* TempA, * TTempA;
	TempA = A_HEAD;

	if (TempA->next != NULL)TTempA = TempA->next;
	else return;

	while (true)
	{
		if (TempA->Valor > TTempA->Valor)
		{
			Arestas* TTTemp = NULL;
			Arestas* TTT = NULL;

			if (TTempA->next != NULL)
			{
				TTTemp = TTempA->next;
				TTTemp->prev = TempA;
			}
			if (TempA->next != NULL) { TTempA->next = TempA->next; TTempA->next->prev = TTempA; }
			TempA->next = TTTemp;
			if (TempA->prev != NULL) { TTT = TempA->prev; TTT->next = TTempA; }
			TempA->prev = TTempA->prev;
			if (TTempA->prev != NULL)TTempA->prev->next = TempA;
			TTempA->prev = TTT;

			Arestas* Temp = TTempA;
			TTempA = TempA;
			TempA = Temp;
		}

		if (TTempA->next != NULL) { TTempA = TTempA->next; }
		else
		{
			if (TempA->next != NULL)
			{
				TempA = TempA->next;
				if (TempA->next != NULL)TTempA = TempA->next;
				else
				{
					while (TempA->prev != NULL)TempA = TempA->prev;
					A_HEAD = TempA;
					return;
				}
			}
			else
			{
				while (TempA->prev != NULL)TempA = TempA->prev;
				A_HEAD = TempA;
				return;
			}
		}
	}
}











