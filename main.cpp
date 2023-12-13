#include <iostream>
#include <iomanip>
#include "Visual.h"

int main()
{
	Visual visual;
	LOG d;
	LOG* datos = &d;
	Tablero t;
	Tablero* tablero = &t;
	int op;
	
	datos->crearHistorial();
	
	while(1)
	{
		cout << setw(70) << "-----------------------" << endl;
		cout << setw(70) << "| B U S C A M I N A S |" << endl;
		cout << setw(70) << "-----------------------" << endl;
		cout << "\n";
		cout << setw(62) << "1)  Nueva Partida. " << endl;
		cout << setw(74) << "2)  Renaudar Partida guardada. " << endl;
		cout << setw(62) << "3)  Mostrar Historial" << endl;
		cout << setw(64) << "4)  Salir del juego. " << endl << endl;
	
		cout << setw(70) << "--Seleccione una opcion: ";
	
		cin >> op;
		while (op < 1 || op > 4)
		{
			cout << "Opción inválida. Por favor, ingrese una opción válida: " << endl;
			cin >> op;
		}
		system("cls");
	
		switch (op)
		{
		case 1:
			visual.configurar_partida(tablero,datos); 
			break;
		case 2:
			visual.reanudarPartida(tablero,datos); 
			break;
		case 3:
			datos->mostrarHistorial();
			system("pause");
			break;
		case 4:
			cout << "\n" << "\n" << "\n";
			cout << setw(75) << "Hasta luego, presione una tecla para salir..." << endl;
			return 0;
		}
		
		if(op != 3){
			visual.jugar(tablero,datos);
			visual.mensaje_winOrLose(tablero);
		}
			
		tablero->limpiar();
		datos->limpiar();
	}
	return 0;
}



