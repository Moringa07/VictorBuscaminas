#pragma once
#include <iostream>
#include <time.h>  //para la hora y fecha actual o en tiempo real
#include <fstream> //manejo de archivos
#include "logica.h"

using namespace std;

class LOG
{
	private:
		string nombre;
		int jugadas;
	    string HoraActual();
	    string FechaActual();
	public:
		LOG();
		LOG(string n);
		void setNombre(string nombre);
	    string getNombre();
	    int getJugadas();
	    void aumentarJugadas();
	    void limpiar();
	    void crearHistorial();
	    void agregarHistorial(Tablero* tablero);
	    void mostrarHistorial();
	    void guardarTablero(Tablero* tablero);
	    void cargarTablero(Tablero* tablero);
};
