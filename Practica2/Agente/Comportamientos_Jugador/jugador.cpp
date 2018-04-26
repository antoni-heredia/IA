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
		++it;
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

	lorigen.push_back(origen);

	colaEstados.push(lorigen);
	colaAcciones.push(primeraAccion);

	visitados[origen.fila][origen.columna] = true;
	if(hayAldeanoEnfrente){
		switch (origen.orientacion){
			case 0:
				visitados[origen.fila-1][origen.columna] = true;
			break;
			case 1:
				visitados[origen.fila][origen.columna+1] = true;
			break;
			case 2:
				visitados[origen.fila+1][origen.columna] = true;
			break;
			case 3:
				visitados[origen.fila][origen.columna-1] = true;
			break;
		}
	}
	while (!colaEstados.empty())
	{
		list<estado> frenteEstados = colaEstados.front();
		list<Action> frenteAcciones = colaAcciones.front();

		colaEstados.pop();
		if(!colaAcciones.empty())
			colaAcciones.pop();

		estado ultimoEstado = frenteEstados.back();

		if (sonMismoPunto(ultimoEstado, destino))
		{
			plan = frenteAcciones;
			plan.push_back(Action::actIDLE);
			VisualizaPlan(origen, plan);

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
			aniadirMovimientos(ultimoEstado,eInsertar, nuevasAcciones);
			
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
			aniadirMovimientos(ultimoEstado,eInsertar, nuevasAcciones);

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
			aniadirMovimientos(ultimoEstado,eInsertar, nuevasAcciones);

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
			aniadirMovimientos(ultimoEstado,eInsertar, nuevasAcciones);

			colaAcciones.push(nuevasAcciones);
		}


	}
	return false;
}

Action ComportamientoJugador::think(Sensores sensores)
{

	if (sensores.mensajeF != -1){
		fil = sensores.mensajeF;
		col = sensores.mensajeC;
	}else 
	if (hayPlan and (sensores.destinoF != destino.fila or sensores.destinoC != destino.columna)){
		cout << "El destino ha cambiado\n";
		hayPlan = false;
	}

	estado origen;
	origen.fila = fil;
	origen.columna = col;
	origen.orientacion = brujula;
	Action accion = Action::actIDLE;

	if(fil == 99 && col == 99){
		int i;
		bool seVePk = false;
		for(i = 0; i < 16 && !seVePk; i++){
			if(sensores.terreno[i] == 'k')
				seVePk = true;
		}
		if(!seVePk && puedeAvanzar(sensores.terreno[2]))
			accion = Action::actFORWARD;
		else if(!seVePk)
			accion = Action::actTURN_L;

	}else if (!hayPlan && !(sensores.superficie[2] == 'a'))
	{
 
		hayPlan = false;
		hayAldeanoEnfrente = false;

		destino.columna = sensores.destinoC;
		destino.fila = sensores.destinoF;
		plan.clear();

		hayPlan = pathFinding(origen, destino, plan);

	}else if(sensores.superficie[2] == 'a'){
	

		hayPlan = false;
		hayAldeanoEnfrente = true;
		plan.clear();
		hayPlan = pathFinding(origen, destino, plan);
		
	}

	if (hayPlan && !plan.empty())
	{

		std::list<Action>::iterator it = plan.begin();
		accion = *it;
		//Muevo la posicion del jugador
		if(accion == Action::actFORWARD){
			switch (brujula){
			case 0:
				fil--;
				break;
			case 1:
				col++;
				break;
			case 2:
				fil++;
				break;
			case 3:
				col--;
				break;
	}
		}
		plan.pop_front();
	}

	brujula = orientacionBrujula(accion, brujula);

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
bool ComportamientoJugador::puedeAvanzar(char letra){
	if (letra == 'B' || letra == 'A' || letra == 'P' || letra == 'M' || letra == 'D')
		return false;
	else
		return true;
}
bool ComportamientoJugador::puedeAvanzar(int fila, int columna)
{
	if(fila < 0 || columna < 0 || fila >= mapaResultado.size() || columna >= mapaResultado.size())
		return false;
	return puedeAvanzar(mapaResultado[fila][columna]);
}


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

void aniadirMovimientos(estado anterior, estado actual, list<Action> & nuevasAcciones){
	switch (mod(anterior.orientacion-actual.orientacion,4)){
		case 1:
			nuevasAcciones.push_back(Action::actTURN_L);
			break;
		case 2:
			nuevasAcciones.push_back(Action::actTURN_R);
			nuevasAcciones.push_back(Action::actTURN_R);
			break;
		case 3:
			nuevasAcciones.push_back(Action::actTURN_R);
			break;
		case 0:
			break;
	}
	nuevasAcciones.push_back(Action::actFORWARD);

}

int orientacionBrujula(Action accion, int brujula){
	int nuevaBrujula = brujula;
	switch (accion){
		case Action::actTURN_L:
			nuevaBrujula = mod(brujula-1,4);
			break;
		case Action::actTURN_R:
			nuevaBrujula = mod(brujula+1,4);
			break;

	}
	return nuevaBrujula;
}

int mod(int x, int m) {
	return ((x%m) + m)%m;
}