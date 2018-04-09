#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"

#include <iostream> 
#include <cmath> 

void ComportamientoJugador::PintaPlan(list < Action > plan) {
	auto it = plan.begin(); 
	while (it != plan.end()) {
		if ( * it == actFORWARD) {
			cout << "A "; 
		}
		else if ( * it == actTURN_R) {
			cout << "D "; 
		}
		else if ( * it == actTURN_L) {
			cout << "I "; 
		}
		else {
			cout << "- "; 
		}
		it++; 
	}
	cout << endl; 
}

void AnularMatriz(vector < vector < unsigned char >  >  & m) {
	for (int i = 0; i < m[0].size(); i++) {
		for (int j = 0; j < m.size(); j++) {
			m[i][j] = 0; 
		}
	}
}

void ComportamientoJugador::VisualizaPlan(const estado & st, const list < Action >  & plan) {
AnularMatriz(mapaConPlan); 
	estado cst = st; 

	auto it = plan.begin(); 
	while (it != plan.end()) {
		if ( * it == actFORWARD) {
			switch (cst.orientacion) {
				case 0:cst.fila--; break; 
				case 1:cst.columna++; break; 
				case 2:cst.fila++; break; 
				case 3:cst.columna--; break; 
			}
			mapaConPlan[cst.fila][cst.columna] = 1; 
		}
		else if ( * it == actTURN_R) {
			cst.orientacion = (cst.orientacion + 1) % 4; 
		}
		else {
			cst.orientacion = (cst.orientacion + 3) % 4; 
		}
		it++; 
	}
}


bool ComportamientoJugador::pathFinding(const estado & origen, const estado & destino, list < Action >  & plan) {
	
	queue <Action> colaAcciones;
	bool visitados[100][100] = {false};
	queue <estado> colaEstados;
	colaEstados.push(origen);
	visitados[origen.fila][origen.columna] = true;
	while(!colaEstados.empty()){
		estado v = colaEstados.front();
		colaEstados.pop();
		if(v == destino){
			return true;
		}
		estado eInsertar;
		if(!visitados[v.fila][v.columna-1] && puedeAvanzar(v.fila,v.columna-1)){
			visitados[v.fila][v.columna-1] = true;
			eInsertar.fila = v.fila;
			eInsertar.columna = v.columna-1;
			colaEstados.push(eInsertar);
		}else if (!visitados[v.fila-1][v.columna] && puedeAvanzar(v.fila-1,v.columna)){
			visitados[v.fila-1][v.columna] = true;
			eInsertar.fila = v.fila-1;
			eInsertar.columna = v.columna;
			colaEstados.push(eInsertar);

		}else if (!visitados[v.fila][v.columna+1] && puedeAvanzar(v.fila,v.columna+1)){
			visitados[v.fila][v.columna+1] = true;
			eInsertar.fila = v.fila;
			eInsertar.columna = v.columna-+1;
			colaEstados.push(eInsertar);

		}else if (!visitados[v.fila+1][v.columna] && puedeAvanzar(v.fila+1,v.columna)){
			visitados[v.fila+1][v.columna] = true;
			eInsertar.fila = v.fila+1;
			eInsertar.columna = v.columna;
			colaEstados.push(eInsertar);
		}
	}
	return false; 
}


Action ComportamientoJugador::think(Sensores sensores) {
	if(!hayPlan){
		estado origen;
		origen.fila = sensores.mensajeF;
		origen.columna = sensores.mensajeC;
		origen.orientacion = 0;
		destino.columna = sensores.destinoC;
		destino.fila =  sensores.destinoF;
		hayPlan = pathFinding(origen, destino,plan);
	}
	Action accion = Action::actFORWARD;
	if(hayPlan){
		std::list<Action>::iterator it = plan.begin();
		accion = *it;
		plan.erase(it);
	}

	return accion; 
}

int ComportamientoJugador::interact(Action accion, int valor) {
return false; 
}


//Cosas que he incluido
vector < vector < double >> ComportamientoJugador::calcularPotencialMapa(const estado & destino) {
	vector < vector < double >> mapaMuros; 
	vector < vector < double >> mapaDistancia; 
	for (int f = 0; f < 100; f++) {
		for (int c = 0; c < 100; c++) {
			//Si no se puede avanzar por ese bloque se pone a 500 directamente
			if ( ! puedeAvanzar(f, c))
				mapaMuros[f][c] = 500; 

			int distanciaFila = destino.fila - f; 
			int distanciaColumna = destino.columna - c; 
			mapaDistancia[f][c] = sqrt(pow(distanciaFila, 2) + pow(distanciaColumna, 2)); 
		}
	}
	//Sumo los vectores
	vector < vector < double >> mapaDevolver; 
	for(int f = 0 ; f < 100; f++)
		for(int c = 0; c<100;  c ++)
			mapaDevolver[f][c] =  mapaDistancia[f][c] + mapaMuros[f][c];
	
	return  mapaDevolver;
}

bool ComportamientoJugador::puedeAvanzar(int fila, int columna) {
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