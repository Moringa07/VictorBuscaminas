#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

class Casilla
{
private:
    int x, y, minas_alrededor;
    bool mina, abierta,marcada, disponible;

public:
	Casilla();
    Casilla(int a, int b);
    void setX(int a);
    int getX();
	void setY(int a);
	int getY();
	void setMinasAlrededor(int minas);
	int getMinasAlrededor();
	void setMina(bool mina);
    bool getMina();
    void setAbierta(bool abierta);
	void abrirCasilla();
    bool isOpen();
    void marcarCasilla(bool bandera);
    bool isMarcada();
    void setDisponible(bool disponible);
    bool isDisponible();
    
    void incrementarMinasAlrededor();
    void abrir_alrededor();
    
};

class Tablero
{
private:
    int filas, columnas, minas;
    Casilla *tablero[8][8];
    bool guardado;

    void asignar_minas();
    void actualizar_minas_alrededor();
    void aumentar(int fila, int columna);
    bool dentro_limites(int fila, int columna);

public:
	Tablero();
    void crear(int filas, int columnas, int minas);
    void limpiar();
    int verificar_resultado();
    bool seguir_partida();
    void colocarBandera(int fila, int columna);
    void setGuardado(bool guardado);
	bool getGuardado();
    int getFilas();
    int getColumnas();
    int getMinas();
    void setFilas(int filas);
    void setColumnas(int columnas);
    void setMinas(int minas);
    Casilla* getCasilla(int fila, int columna);
    vector<Casilla*> Obtener_Casillas_Alrededor(Casilla* casilla);
    void mostrar_alrededor(vector<Casilla*> lista);
    void abrir_alrededor(Casilla* casilla);
};