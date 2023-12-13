#pragma once
#include <iostream>
#include "logica.h"
#include "Archivos.h"
using namespace std;

class Visual
{
public:
	Visual();
	void configurar_partida(Tablero* t, LOG* datos);
	void jugar(Tablero* tablero, LOG* datos);
	void reanudarPartida(Tablero* tablero, LOG* datos);
	void mostrar_Tablero(Tablero* t);
	void mostrar_Minas(Tablero* t);
	void mensaje_winOrLose(Tablero* tablero);
};