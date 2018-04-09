#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"
#include <queue>
#include <iostream>
#include <cmath>
using std::queue;

void ComportamientoJugador::PintaPlan(list<Action> plan)
{
	auto it = plan.begin();
	while (it != plan.end())
	{
		if (*it == actFORWARD)
		{
			cout << "A ";
		}
		else if (*it == actTURN_R)
		{
			cout << "D ";
		}
		else if (*it == actTURN_L)
		{
			cout << "I ";
		}
		else
		{
			cout << "- ";
		}
		it++;
	}
	cout << endl;
}

void AnularMatriz(vector<vector<unsigned char>> &m)
{
	for (int i = 0; i < m[0].size(); i++)
	{
		for (int j = 0; j < m.size(); j++)
		{
			m[i][j] = 0;
		}
	}
}

void ComportamientoJugador::VisualizaPlan(const estado &st, const list<Action> &plan)
{
	AnularMatriz(mapaConPlan);
	estado cst = st;

	auto it = plan.begin();
	while (it != plan.end())
	{
		if (*it == actFORWARD)
		{
			switch (cst.orientacion)
			{
			case 0:
				cst.fila--;
				break;
			case 1:
				cst.columna++;
				break;
			case 2:
				cst.fila++;
				break;
			case 3:
				cst.columna--;
				break;
			}
			mapaConPlan[cst.fila][cst.columna] = 1;
		}
		else if (*it == actTURN_R)
		{
			cst.orientacion = (cst.orientacion + 1) % 4;
		}
		else
		{
			cst.orientacion = (cst.orientacion + 3) % 4;
		}
		it++;
	}
}

bool ComportamientoJugador::pathFinding(const estado &origen, const estado &destino, list<Action> &plan)
{

	bool visitados[100][100] = {false};
	queue<list<estado>> colaEstados;
	queue<list<Action>> colaAcciones;

	list<estado> lorigen;
	list<Action> primeraAccion;

	primeraAccion.push_back(Action::actIDLE);
	lorigen.push_back(origen);

	colaEstados.push(lorigen);
	colaAcciones.push(primeraAccion);

	visitados[origen.fila][origen.columna] = true;
	while (!colaEstados.empty())
	{
		list<estado> frenteEstados = colaEstados.front();
		list<Action> frenteAcciones = colaAcciones.front();

		colaEstados.pop();
		colaAcciones.pop();

		estado ultimoEstado = frenteEstados.back();

		if (sonMismoPunto(ultimoEstado, destino))
		{
			plan = frenteAcciones;
			return true;
		}
		estado eInsertar;
		if (!visitados[ultimoEstado.fila][ultimoEstado.columna - 1] && puedeAvanzar(ultimoEstado.fila, ultimoEstado.columna - 1))
		{
			visitados[ultimoEstado.fila][ultimoEstado.columna - 1] = true;

			eInsertar.fila = ultimoEstado.fila;
			eInsertar.columna = ultimoEstado.columna - 1;
			eInsertar.orientacion = nuevaOrientacion(ultimoEstado, eInsertar);

			list<Action> nuevasAcciones = frenteAcciones;
			if (ultimoEstado.orientacion == 0)
			{
				nuevasAcciones.push_back(Action::actTURN_L);
				nuevasAcciones.push_back(Action::actFORWARD);
			}
			else if (ultimoEstado.orientacion == 1)
			{
				nuevasAcciones.push_back(Action::actTURN_L);
				nuevasAcciones.push_back(Action::actTURN_L);
				nuevasAcciones.push_back(Action::actFORWARD);
			}
			else if (ultimoEstado.orientacion == 2)
			{

				nuevasAcciones.push_back(Action::actTURN_R);
				nuevasAcciones.push_back(Action::actFORWARD);
			}
			else if (ultimoEstado.orientacion == 3)
			{
				nuevasAcciones.push_back(Action::actFORWARD);
			}

			frenteEstados.push_back(eInsertar);

			colaEstados.push(frenteEstados);
			colaAcciones.push(nuevasAcciones);

			frenteEstados.pop_back();
		}
		if (!visitados[ultimoEstado.fila - 1][ultimoEstado.columna] && puedeAvanzar(ultimoEstado.fila - 1, ultimoEstado.columna))
		{
			visitados[ultimoEstado.fila - 1][ultimoEstado.columna] = true;

			eInsertar.fila = ultimoEstado.fila - 1;
			eInsertar.columna = ultimoEstado.columna;
			eInsertar.orientacion = nuevaOrientacion(ultimoEstado, eInsertar);

			frenteEstados.push_back(eInsertar);
			colaEstados.push(frenteEstados);
			frenteEstados.pop_back();

			list<Action> nuevasAcciones = frenteAcciones;
			if (ultimoEstado.orientacion == 0)
			{
				nuevasAcciones.push_back(Action::actFORWARD);
			}
			else if (ultimoEstado.orientacion == 1)
			{
				nuevasAcciones.push_back(Action::actTURN_L);
				nuevasAcciones.push_back(Action::actFORWARD);
			}
			else if (ultimoEstado.orientacion == 2)
			{
				nuevasAcciones.push_back(Action::actTURN_L);
				nuevasAcciones.push_back(Action::actTURN_L);
				nuevasAcciones.push_back(Action::actFORWARD);
			}
			else if (ultimoEstado.orientacion == 3)
			{
				nuevasAcciones.push_back(Action::actTURN_R);
				nuevasAcciones.push_back(Action::actFORWARD);
			}
			colaAcciones.push(nuevasAcciones);
		}
		if (!visitados[ultimoEstado.fila][ultimoEstado.columna + 1] && puedeAvanzar(ultimoEstado.fila, ultimoEstado.columna + 1))
		{
			visitados[ultimoEstado.fila][ultimoEstado.columna + 1] = true;

			eInsertar.fila = ultimoEstado.fila;
			eInsertar.columna = ultimoEstado.columna + 1;
			eInsertar.orientacion = nuevaOrientacion(ultimoEstado, eInsertar);

			frenteEstados.push_back(eInsertar);
			colaEstados.push(frenteEstados);
			frenteEstados.pop_back();

			list<Action> nuevasAcciones = frenteAcciones;
			if (ultimoEstado.orientacion == 0)
			{
				nuevasAcciones.push_back(Action::actTURN_R);
				nuevasAcciones.push_back(Action::actFORWARD);
			}
			else if (ultimoEstado.orientacion == 1)
			{
				nuevasAcciones.push_back(Action::actFORWARD);
			}
			else if (ultimoEstado.orientacion == 2)
			{
				nuevasAcciones.push_back(Action::actTURN_L);
				nuevasAcciones.push_back(Action::actFORWARD);
			}
			else if (ultimoEstado.orientacion == 3)
			{
				nuevasAcciones.push_back(Action::actTURN_L);
				nuevasAcciones.push_back(Action::actTURN_L);
				nuevasAcciones.push_back(Action::actFORWARD);
			}
			colaAcciones.push(nuevasAcciones);
		}
		if (!visitados[ultimoEstado.fila + 1][ultimoEstado.columna] && puedeAvanzar(ultimoEstado.fila + 1, ultimoEstado.columna))
		{
			visitados[ultimoEstado.fila + 1][ultimoEstado.columna] = true;
			eInsertar.fila = ultimoEstado.fila + 1;
			eInsertar.columna = ultimoEstado.columna;
			eInsertar.orientacion = nuevaOrientacion(ultimoEstado, eInsertar);
			frenteEstados.push_back(eInsertar);
			colaEstados.push(frenteEstados);
			frenteEstados.pop_back();

			list<Action> nuevasAcciones = frenteAcciones;
			if (ultimoEstado.orientacion == 0)
			{
				nuevasAcciones.push_back(Action::actTURN_L);
				nuevasAcciones.push_back(Action::actTURN_L);
				nuevasAcciones.push_back(Action::actFORWARD);
			}
			else if (ultimoEstado.orientacion == 1)
			{
				nuevasAcciones.push_back(Action::actTURN_R);
				nuevasAcciones.push_back(Action::actFORWARD);
			}
			else if (ultimoEstado.orientacion == 2)
			{
				nuevasAcciones.push_back(Action::actFORWARD);
			}
			else if (ultimoEstado.orientacion == 3)
			{
				nuevasAcciones.push_back(Action::actTURN_L);
				nuevasAcciones.push_back(Action::actFORWARD);
			}
			colaAcciones.push(nuevasAcciones);
		}
	}
	return false;
}

Action ComportamientoJugador::think(Sensores sensores)
{
	estado origen;
	origen.fila = sensores.mensajeF;
	origen.columna = sensores.mensajeC;
	origen.orientacion = 0;
	if (!hayPlan)
	{
		

		destino.columna = sensores.destinoC;
		destino.fila = sensores.destinoF;
		//cout << " a buscar un plan" << endl;

		hayPlan = pathFinding(origen, destino, plan);		cout << " a buscar un plan" << endl;

	}
	Action accion = Action::actFORWARD;

	if (hayPlan && !plan.empty())
	{
		//cout << " hay plan" << endl;
		//VisualizaPlan(origen, plan);

		std::list<Action>::iterator it = plan.begin();
		accion = *it;
		plan.pop_front();
	}
	return accion;
}

int ComportamientoJugador::interact(Action accion, int valor)
{
	return false;
}

//Cosas que he incluido
vector<vector<double>> ComportamientoJugador::calcularPotencialMapa(const estado &destino)
{
	vector<vector<double>> mapaMuros;
	vector<vector<double>> mapaDistancia;
	for (int f = 0; f < 100; f++)
	{
		for (int c = 0; c < 100; c++)
		{
			//Si no se puede avanzar por ese bloque se pone a 500 directamente
			if (!puedeAvanzar(f, c))
				mapaMuros[f][c] = 500;

			int distanciaFila = destino.fila - f;
			int distanciaColumna = destino.columna - c;
			mapaDistancia[f][c] = sqrt(pow(distanciaFila, 2) + pow(distanciaColumna, 2));
		}
	}
	//Sumo los vectores
	vector<vector<double>> mapaDevolver;
	for (int f = 0; f < 100; f++)
		for (int c = 0; c < 100; c++)
			mapaDevolver[f][c] = mapaDistancia[f][c] + mapaMuros[f][c];

	return mapaDevolver;
}

bool ComportamientoJugador::puedeAvanzar(int fila, int columna)
{
	if (mapaResultado[fila][columna] == 'B' || mapaResultado[fila][columna] == 'A' || mapaResultado[fila][columna] == 'P' ||
		mapaResultado[fila][columna] == 'M' || mapaResultado[fila][columna] == 'D')
		return false;
	else
		return true;
}

/*
void ComportamientoJugador::distanciaMuro(int fila, int columna, vector < vector < double >>  & mapaMuros) {
	for (int distancia = 1; distancia <= 10; distancia++) {
		for (int f = -distancia; f <= distancia; f++) {
			for (int c = -distancia; c <= distancia; c++) {
				if ! (puedeAvanzar(fila+f,columna+c))

			}
		}
	}
}
*/
int nuevaOrientacion(estado anterior, estado actual)
{
	int orientacion;
	if (anterior.fila == actual.fila)
		if (anterior.columna - actual.columna < 0)
			orientacion = 1;
		else
			orientacion = 3;
	else{
		if (anterior.fila - actual.fila > 0)
			orientacion = 0;
		else
			orientacion = 2;
	}
	return orientacion; 
}
bool sonMismoPunto(estado primero, estado segundo)
{

	if (primero.fila == segundo.fila && primero.columna == segundo.columna)
		return true;

	return false;
}
