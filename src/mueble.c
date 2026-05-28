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

void mostrar_productos() 
{
	FILE *archivo;
	Mueble m;
	float ganancia;
	
	archivo = fopen("data/muebles.dat", "rb");
	
	if (archivo == NULL)
	{
        	printf("\nNo hay datos guardados o hubo un error al abrir el archivo.\n");
        	return;
	}

	printf("\n%-6s %-25s %-12s %-12s %-18s %-12s\n", "Clave", "Producto", "Costo", "Precio", "Unidades vendidas", "Ganancia");

	while (fread(&m, sizeof(Mueble), 1, archivo) == 1) 
	{
        
		if (m.activo == 1) 
		{
			ganancia = (m.precio - m.costo) * m.unidades_vendidas;
            		printf("%-6s %-25s $%11.2f $%11.2f %18.2f $%11.2f\n", m.clave, m.descripcion, m.costo, m.precio, m.unidades_vendidas, ganancia);
        	}
    	}
	
	fclose(archivo);
}

void editar_producto() 
{
    
	FILE *archivo;
    	Mueble m;
    	char clave_buscar[4];
    	int encontrado = 0;

    	archivo = fopen("data/muebles.dat", "r+b");
    	if (archivo == NULL) 
    	{
        	printf("\nError: No hay productos registrados.\n");
        	return;
    	}

    	printf("\nEDITAR PRODUCTO\n");
    	printf("Ingresa la clave del producto a editar: ");
    	scanf("%3s", clave_buscar);
    	while(getchar() != '\n'); 

    	while (fread(&m, sizeof(Mueble), 1, archivo) == 1) 
	{
        	if (strcmp(m.clave, clave_buscar) == 0 && m.activo == 1) 
		{
            		encontrado = 1;
            		printf("Producto encontrado: %s\n", m.descripcion);
            
            		printf("Nueva Descripcion: ");
            		fgets(m.descripcion, 51, stdin);
            		m.descripcion[strcspn(m.descripcion, "\n")] = 0; 

            		printf("Nuevo Costo de produccion: ");
            		scanf("%f", &m.costo);

            		printf("Nuevo Precio de venta: ");
            		scanf("%f", &m.precio);

            		printf("Nuevas Unidades vendidas: ");
            		scanf("%f", &m.unidades_vendidas);

            		// Retrocedemos el cursor un bloque para sobrescribir
            		fseek(archivo, -sizeof(Mueble), SEEK_CUR);
            		fwrite(&m, sizeof(Mueble), 1, archivo);
            		printf("\n¡Producto actualizado correctamente!\n");
            		break;
        	}
    	}

    	if (!encontrado) 
    	{
        	printf("\nProducto no encontrado o fue eliminado previamente.\n");
    	}
    	fclose(archivo);
}

void eliminar_producto() 
{
    	FILE *archivo;
    	Mueble m;
    	char clave_buscar[4];
    	int encontrado = 0;

    	archivo = fopen("data/muebles.dat", "r+b");
    	if (archivo == NULL) 
	{
        	printf("\nError: No hay productos registrados.\n");
        	return;
    	}

    	printf("\n--- ELIMINAR PRODUCTO ---\n");
    	printf("Ingresa la clave del producto a eliminar: ");
    	scanf("%3s", clave_buscar);
    	while(getchar() != '\n');

    	while (fread(&m, sizeof(Mueble), 1, archivo) == 1) 
	{
        	if (strcmp(m.clave, clave_buscar) == 0 && m.activo == 1) 
		{
            		encontrado = 1;
            		m.activo = 0; // Borrado logico
            
            		fseek(archivo, -sizeof(Mueble), SEEK_CUR);
            		fwrite(&m, sizeof(Mueble), 1, archivo);
            		printf("\n¡Producto '%s' eliminado (borrado logico) correctamente!\n", m.clave);
            		break;
        	}
    	}

    	if (!encontrado) 
	{
        	printf("\nProducto no encontrado.\n");
    	}
    	fclose(archivo);
}
