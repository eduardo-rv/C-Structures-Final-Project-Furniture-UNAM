#include <stdio.h>
#include <string.h>
#include "../include/mueble.h"

void alta_producto()
{
	Mueble nuevo_mueble;
	FILE *archivo;
	
	printf("\nALTA DE PRODUCTO.\n\n");
	printf("Ingresa la clave (ejemplo P01): ");
	scanf("%3s", nuevo_mueble.clave);

	while(getchar() != '\n');

	printf("Ingresa la descripcion: ");
	fgets(nuevo_mueble.descripcion, 51, stdin);

	nuevo_mueble.descripcion[strcspn(nuevo_mueble.descripcion, "\n")] = 0; //borra el salto de linea que fgets genera
	
	printf("Ingresa el costo de produccion: ");
	scanf("%f", &nuevo_mueble.costo);

	printf("Ingresa el precio de venta: ");
	scanf("%f", &nuevo_mueble.precio);

	printf("Ingresa las unidades vendidas: ");
	scanf("%f", &nuevo_mueble.unidades_vendidas);

	nuevo_mueble.activo = 1; // Asignamos el borrado logico como activo.
	
	// guardamos
	archivo = fopen("data/muebles.dat", "ab");

	if(archivo == NULL)
	{
		printf("Error al abrir o crear archivo de datos\n");
		return;
	}

	// Escribimos un bloque de memoria del tamanio del struct 
	fwrite(&nuevo_mueble, sizeof(Mueble), 1, archivo);
	fclose(archivo);

	printf("Producto guardado correctamente en la direccion muebles.dat\n");
}
