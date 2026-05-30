#include <stdio.h>
#include <stdlib.h>
#include "../include/mueble.h"

void Presentacion();
int Menu();
void Limpiar_Pantalla();

int main()
{
	int opcion;

	Presentacion();

	do
	{
		opcion = Menu();

		switch(opcion)
		{
			case 1:
				// funcion para dar de alta algun producto
				alta_producto();
				break;
			case 2:
				// funcion mostrar todos los productos
				mostrar_productos();
				break;
			case 3:
				// funcion para editar un producto
				editar_producto();
				break;
			case 4:
				// funcion para eliminar un produco
				eliminar_producto();
				break;
			case 5:
				// funcion para crear la grafica de columnas
				grafica_columnas();
				break;
			case 6:
				// funcion para la grafica circular
				grafica_circular();
				break;
			case 7:
				printf("\nCerrando programa...");
				break;
			default:
				printf("\nOpcion no valida\n\n");

		}

		if(opcion != 7)
		{
			printf("\nPresiona ENTER para continuar...");
			getchar();
			getchar();
		}

	} while(opcion != 7);

	return 0;

}

void Limpiar_Pantalla()
{
	printf("\033[H\033[J");
	//getchar();
	//system("clear");
	//system("cls");
}

void Presentacion()
{
	Limpiar_Pantalla();

	printf("\n\nProyecto final: IA-MUEBLES\n\n");
	printf("Descripcion: Programa que permite hacer un diagnostico de como se esta realizando el trabajo en IA-MUEBLES.\n\n");

	printf("Equipo 08: \nContreras Aviles Jose Raul\nRegalado Ramirez Evan Elliot\nRosas Vazquez Eduardo\n\n");
	printf("Presiona ENTER para continuar...");

	getchar();
}

int Menu()
{
	int opcion;

	Limpiar_Pantalla();

	printf("\n\nMenu de opciones.\n\n");
	printf("1. Dar de alta un producto.\n");
	printf("2. Mostrar todos los productos.\n");
	printf("3. Editar un producto.\n");
	printf("4. Eliminar un producto.\n");
	printf("5. Crear grafica de columna.\n");
	printf("6. Crear grafica circular.\n");
	printf("7. Salir.\n");
	printf("Elige una opcion: ");
	scanf("%d", &opcion);
	
	return opcion;
}
