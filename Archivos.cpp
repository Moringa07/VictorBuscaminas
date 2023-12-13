#include <iostream>
#include <time.h>  //libreria con la que se maneja la hora y la fecha real
#include <ctime>   // Obtener tiempo real del juego
#include <fstream> //para el manejo de los archivos
#include <iomanip>
#include "Archivos.h"
#include "Logica.h"

using namespace std;
ofstream archivo;

LOG::LOG(): nombre(" "), jugadas(0){}

LOG::LOG(string n): nombre(n) {}

void LOG::setNombre(string nombre){
	this->nombre = nombre;
    }

string LOG::getNombre(){
        return this->nombre;
    }

void LOG::aumentarJugadas(){
	jugadas++;
}

int LOG::getJugadas(){
	return this->jugadas;
}

void LOG::limpiar(){
	this->nombre = " ";
	this->jugadas = 0;
}

void LOG::crearHistorial(){
	ofstream archivo("Historial.txt");
	if(!archivo.is_open()){
		cout << "chimbo";
	}
	else{
		archivo << "Nombre     " << "Fecha        " << "Hora     " << "Tablero     " <<
			"Minas     " << "Jugadas     " << "Resultado     " << endl;
		archivo.close();
	}
}

void LOG::agregarHistorial(Tablero* tablero)
{
	ofstream archivo("Historial.txt", std::ios::app);
	string resultado;
	
	if(tablero->verificar_resultado() == 1 || tablero->verificar_resultado() == 2)
		resultado = "Victoria";
	else
		resultado = "Derrota";
	/*
		0 = mina
		1 = minas marcadas
		2 = casillas abiertas
		3 = se rinde
	*/
	if(archivo.is_open()){
		
		
		archivo << nombre <<"     "<< this->FechaActual() <<"     "<< this->HoraActual()
			<<"     " << tablero->getFilas() << "x" << tablero->getColumnas() << "          " 
			<< tablero->getMinas() <<"          "<< jugadas <<"          "<< resultado << endl;		
		archivo.close();
	}
	else{
        cout << "Error." << endl;
	}
}

// Funcion que permite obtener la hora actual en formato HH:MM
string LOG::HoraActual()
{
    time_t tiempoActual = time(0); 
    tm *tiempo = localtime(&tiempoActual);
    char hora[6];
    strftime(hora, sizeof(hora), "%H:%M", tiempo); 
    string horaFormateada(hora);                  
    return horaFormateada;
}

// Funcion para obtener fecha actual en formato DD/MM/YY
string LOG::FechaActual()
{
    time_t tiempoActual = time(0); // guarda el tiempo actual.
    tm *time = localtime(&tiempoActual);
    char fecha[9];
    strftime(fecha, sizeof(fecha), "%d/%m/%y", time);
    return fecha;
}

void LOG::mostrarHistorial()
{

    ifstream archivo("Historial.txt");

    if (archivo.is_open())
    {

        string datos, line;
        while (getline(archivo, line))
        {
            datos += line + "\n";
        }
        cout << datos << endl;

        archivo.close();
    }
}

void LOG::guardarTablero(Tablero* tablero)
{
	Casilla* casilla;
	ofstream archivo("Partida Guardada.txt",ios::trunc);
    if (archivo.is_open())
    {
        archivo << tablero->getFilas() << " " << tablero->getColumnas() << " " << tablero->getMinas() << "\n";  // Escribir información del tablero

        for (int i = 0; i < tablero->getFilas(); i++)
        {
            for (int j = 0; j < tablero->getColumnas(); j++)
            {
            	casilla = tablero->getCasilla(i,j);
                archivo << casilla->getX() << " " << casilla->getY() << " "
                        << casilla->getMinasAlrededor() << " " << casilla->getMina() << " "
                        << casilla->isOpen() << " " << casilla->isMarcada() << " "
                        << casilla->isDisponible() << "\n";
            }
        }

        archivo.close();
    }
    else
    {
        //std::cerr << "Error al abrir el archivo para escritura." << std::endl;
    }
}

void LOG::cargarTablero(Tablero* tablero)
{
    ifstream archivo("Partida Guardada.txt");
    
    if (archivo.is_open())
    {
    	int filas, columnas, minas;
		int x, y, minas_alrededor;
	    bool mina, abierta, marcada, disponible;
	    Casilla* nuevaCasilla;
    	
        archivo >> filas >> columnas >> minas;  
        tablero->setFilas(filas);
        tablero->setColumnas(columnas);
        tablero->setMinas(minas);
        
        for (int i = 0; i < tablero->getFilas(); i++)
        {
            for (int j = 0; j < tablero->getColumnas(); j++)
            {
            	nuevaCasilla = tablero->getCasilla(i,j);
                archivo >> x >> y >> minas_alrededor >> mina >> abierta >> marcada >> disponible;
				nuevaCasilla->setX(x);
				nuevaCasilla->setY(y);
				nuevaCasilla->setMinasAlrededor(minas_alrededor);
				nuevaCasilla->setMina(mina);
				nuevaCasilla->setAbierta(abierta);
				nuevaCasilla->marcarCasilla(marcada);
				nuevaCasilla->setDisponible(disponible);
            }
        }
        archivo.close(); 
	}
    else
    {
        cerr << "Error al abrir el archivo para lectura." << endl;
    }
}