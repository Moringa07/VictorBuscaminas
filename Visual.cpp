#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "Visual.h"
#include "logica.h"
#include "Archivos.h"

using namespace std;

Visual::Visual() {}

void Visual::configurar_partida(Tablero* t, LOG* datos)
{
	int op;
	string jugadorNuevo;
	
	cout << "\n" << "\n" << "\n" << setw(60) << "--> Nombre del jugador: ";
	cin >> jugadorNuevo;
	datos->setNombre(jugadorNuevo);
    system("cls");

	cout << "\n" << "\n" << "\n";
	cout << setw(65) << "Selecciona la dificultad de juego " << endl;
	cout << setw(65) << "-----------------------------------" << endl << "\n";
	cout << setw(51) << "1) Fácil." << endl;
	cout << setw(55) << "2) Intermedio." << endl;
	cout << setw(53) << "3) Díficil." << endl;
	cout << setw(52) << "-> opcion: ";
	cin >> op;

	while (op < 1 || op > 3)
	{
		//system("cls");
		cout << "Opción inválida. Por favor, ingrese una opción válida. " << endl;
		cin >> op;
	}
	system("cls");
	switch (op){
	case 1:
		cout << setw(55) << "Nivel facil" << endl;
		cout << setw(55) << "-----------" << endl;
		t->crear(4,4,4);
		//datos->setConfTablero(4,4,4);
		break;
	case 2:
		cout << setw(56) << "Nivel intermedio" << endl;
		cout << setw(56) << "----------------" << endl;
		t->crear(6,6,10);
		//datos->setConfTablero(6,6,10);
		break;
	case 3:
		cout << setw(55) << "Nivel dificil" << endl;
		cout << setw(55) << "-------------" << endl;
		t->crear(8,8,12);
		//datos->setConfTablero(8,8,12);
		break;
	}
};

void Visual::jugar(Tablero* tablero, LOG* datos)
{
	int opcion, fila, columna;
	
	do
	{
		system("cls");
		mostrar_Tablero(tablero);
		
		cout << "\n" << setw(60) << "--Opciones de juego--" << endl << "\n";
		cout << setw(59) << "1) Abrir casilla." << endl;
		cout << setw(59) << "2) Colocar bandera." << endl;
		cout << setw(59) << "3) Quitar bandera." << endl;
		cout << setw(52) << "4) Rendirse." << endl;
		cout << setw(52) << "5) Guardar partida." << endl;
		cout << setw(52) << "-> jugada seleccionada: ";
		cin >> opcion;
		
		while(opcion < 1 || opcion > 5)
		{
			cout << setw(65) << "Inserte una opcion valida." << endl;
			cin >> opcion;
		}
		
		if(opcion == 4)
			break;
			
		if(opcion == 5){
			datos->guardarTablero(tablero);
			break;
		}
		
		cout << "Ingrese la fila: ";
		cin >> fila;
		cout << "Ingrese la columna: ";
		cin >> columna;
		
		Casilla* casilla = tablero->getCasilla(fila,columna);
			cout << "Entro";
		switch(opcion){
			case 1:
				system("cls");
				if(!casilla->isOpen() && casilla->isDisponible()){
					cout << "Abrirá la casilla (" << fila << "," << columna << ").";
					tablero->abrir_alrededor(casilla);
					datos->aumentarJugadas();	
				}
				else
					cout << "La casilla ya esta abierta." << endl;
				break;
				
			case 2:
				system("cls");
				if(!casilla->isMarcada() && casilla->isDisponible()){
					cout << "Marcará la casilla (" << fila << "," << columna << ").";
					casilla->marcarCasilla(true);	
					datos->aumentarJugadas();
				}
				else
					cout << "Casilla ya marcada.";
				break;
			case 3:
				system("cls");
				if(casilla->isMarcada() && !casilla->isDisponible()){
					cout << "Desmarcará la casilla (" << fila << "," << columna << ").";
					casilla->marcarCasilla(false);	
					datos->aumentarJugadas();
				}
				else
					cout << "Accion invalida.";
				break;
		}
		cout << endl << endl;
		mostrar_Tablero(tablero);
	}while(tablero->seguir_partida()); 
	system("cls");
	
	if(opcion != 5)
		datos->agregarHistorial(tablero);
};

void Visual::mensaje_winOrLose(Tablero* tablero)
{
	int resultado = tablero->verificar_resultado();
	
	switch(resultado){
		case 0:
			cout << "BOOOOOM. Ha explotado una mina" << endl << endl;
			mostrar_Minas(tablero);
			cout << setw(63) << "--Juego finalizado--" << endl;
			cout << setw(63) << "¡Quiza la proxima!" << endl;
			system("pause");
			system("cls");
			break;
		case 1:
			cout <<"Ha marcado todas las minas. Felicitaciones.";
			break;
		case 2:
			cout <<"Ha abierto todas las casillas con éxito. Felicitaciones.";
			break;
		case 3:
			cout << "Vuelve pronto a terminar tu partida. No te rindas";
		case 4:
			system("cls");
			mostrar_Minas(tablero);
			cout << setw(63) << "Será para la proxima" << endl;
			cout << setw(63) << "No te rindas." << endl;
			break;
	}
}

void Visual::reanudarPartida(Tablero* tablero, LOG* datos)
{
	cout << "Cargando partida" << endl;
	datos->cargarTablero(tablero);
	cout << "Partida cargada.";
	system("pause");
}

void Visual::mostrar_Tablero(Tablero* t)
{
    cout << "\n" << "\n";
    cout << "  ";
    for (int col = 0; col < t->getColumnas(); col++)
        cout << col << " ";
    cout << endl << "  ";
	for (int col = 0; col < t->getColumnas(); col++)
        cout << "--";
    cout << endl;
    
    for (int fila = 0; fila < t->getFilas(); fila++)
    {
        cout << fila << "|";

        for (int columna = 0; columna < t->getColumnas(); columna++)
        {
            Casilla *casilla = t->getCasilla(fila, columna);
            if (casilla->isOpen())
            {
                if (casilla->getMina())
                    cout << "M ";
                else
                    cout << casilla->getMinasAlrededor() << " ";
            }
            else if (casilla->isMarcada())
                cout << "B ";
            else
                cout << "* ";
        }
        cout << endl;
    }
}

void Visual::mostrar_Minas(Tablero* t)
{
	cout << "\n" << "\n";
	cout << "Ubicacion de las Minas" << endl;
    cout << " ";
    for (int col = 0; col < t->getColumnas(); col++)
        cout <<" "<< col;;
    cout << endl << "  ";
	for (int col = 0; col < t->getColumnas(); col++)
        cout << "--";
    cout << endl;
	
	for (int fila = 0; fila < t->getFilas(); fila++)
	{
		cout << fila << "|";
		for (int columna = 0; columna < t->getColumnas(); columna++)
		{
			Casilla *casilla = t->getCasilla(fila, columna);
			cout << casilla->getMina() << " ";
		}
		cout << endl;
	}
}