#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"

#include <list>
struct estado {
  int fila;
  int columna;
  int orientacion;
};
int nuevaOrientacion(estado anterior, estado actual);
bool sonMismoPunto(estado primero, estado segundo);
void aniadirMovimientos(estado anterior, estado actual, list<Action> & nuevasAcciones);
int orientacionBrujula(Action accion, int brujula);
int mod(int x, int m);
class ComportamientoJugador : public Comportamiento {
  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size) {
      // Inicializar Variables de Estado
      fil = col = 99;
      brujula = cantGiros = movimientos = 0; // 0: Norte, 1:Este, 2:Sur, 3:Oeste
      destino.fila = -1;
      destino.columna = -1;
      destino.orientacion = -1;
      hayPlan = false;
      hayAldeanoEnfrente = false;
    }
    ComportamientoJugador(std::vector< std::vector< unsigned char> > mapaR) : Comportamiento(mapaR) {
      // Inicializar Variables de Estado
      fil = col = 99;
      brujula = cantGiros = movimientos = 0; // 0: Norte, 1:Este, 2:Sur, 3:Oeste
      destino.fila = -1;
      destino.columna = -1;
      destino.orientacion = -1;
      hayAldeanoEnfrente = false;
    }
    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);
    void VisualizaPlan(const estado &st, const list<Action> &plan);
    ComportamientoJugador * clone(){return new ComportamientoJugador(*this);}

  private:
    // Declarar Variables de Estado
    int fil, col, brujula;
    int cantGiros, movimientos;
    bool hayPlan;
    estado destino;
    list<Action> plan;
    bool hayAldeanoEnfrente;
	  bool puedeAvanzar(char letra);
    bool puedeAvanzar(int fila, int columna);
    vector <vector<double>> calcularPotencialMapa(const estado &destino);
    
    bool pathFinding(const estado &origen, const estado &destino, list<Action> &plan);
    bool busquedaAnchura(const estado &origen, const estado &destino, list<Action> &plan, vector< vector< unsigned char> > mapa);

    void PintaPlan(list<Action> plan);
};

#endif
