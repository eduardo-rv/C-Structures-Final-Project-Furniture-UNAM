#include <stdio.h>
#include <string.h>
#include "../include/mueble.h"
#ifdef _WIN32
#include <graphics.h>
#endif

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

	printf("\nProducto guardado correctamente.\n\n");
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

    	printf("\nEDITAR PRODUCTO\n\n");
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
            		printf("\nProducto actualizado.\n\n");
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

    	printf("\nELIMINAR PRODUCTO\n\n");
    	printf("Ingresa la clave del producto a eliminar: ");
    	scanf("%3s", clave_buscar);
	while(getchar() != '\n');

	while(fread(&m, sizeof(Mueble), 1, archivo) == 1)
	{
		if(strcmp(m.clave, clave_buscar) == 0 && m.activo == 1)
		{
			encontrado = 1;
			m.activo = 0;

			fseek(archivo, -sizeof(Mueble), SEEK_CUR);
			fwrite(&m, sizeof(Mueble), 1, archivo);
			printf("\nProducto '%s' eliminado correctamente\n", m.clave);
			break;
		}
	}

	if(!encontrado)
	{
		printf("\nProducto no encontrado.\n");
	}
	fclose(archivo);
}

void grafica_columnas()
{
	FILE *archivo = fopen("data/muebles.dat", "rb");
	Mueble m;
	
	if (archivo == NULL)
	{
		printf("\nError: No hay productos registrados para graficar.\n");
		return;
	}

#ifdef _WIN32
	// codigo para graficar en codeblocks
	int gd = DETECT, gm;
	initgraph(&gd, &gm, ""); // Inicializa ventana grafica
	int x = 50; // Posicion inicial en X
	outtextxy(200, 20, "Unidades Vendidas por Producto");
	
	while (fread(&m, sizeof(Mueble), 1, archivo) == 1)
	{
		if (m.activo == 1)
		{
			int altura = (int)m.unidades_vendidas * 2; // Escalar altura
			setfillstyle(SOLID_FILL, x % 14 + 1); // Color aleatorio consecutivo
			bar(x, 400 - altura, x + 40, 400); // Dibuja la barra
			outtextxy(x, 410, m.clave); // Etiqueta abajo
			x += 60; // Separacion entre barras
		}
	}
	getch();
	closegraph();
#else
	// bodigo para graficar en linux
	printf("\nGRAFICA DE COLUMNAS\n");
	
	while (fread(&m, sizeof(Mueble), 1, archivo) == 1)
	{
		if (m.activo == 1)
		{
			printf("%-6s | ", m.clave);
			int barras = (int)(m.unidades_vendidas / 5); // Escala para que quepa en pantalla
			if (barras == 0 && m.unidades_vendidas > 0) barras = 1;
			
			for(int i = 0; i < barras; i++)
			{
				printf("█");
			}
			
			printf(" (%.0f)\n", m.unidades_vendidas);
		}
	}
#endif
	fclose(archivo);
}

void grafica_circular()
{
	FILE *archivo = fopen("data/muebles.dat", "rb");
	Mueble m;
	float ganancia_total = 0;
	
	if (archivo == NULL)
	{
		printf("\nError: No hay productos registrados para graficar.\n");
		return;
	}
	
	// Primer recorrido: Calcular el 100% de la ganancia
	while (fread(&m, sizeof(Mueble), 1, archivo) == 1)
	{
		if (m.activo == 1)
		{
			ganancia_total += (m.precio - m.costo) * m.unidades_vendidas;
		}
	}

	if (ganancia_total <= 0)
	{
		printf("\nNo hay ganancias registradas para graficar.\n");
		fclose(archivo);
		return;
	}
	
	rewind(archivo); // Regressa al inicio del archivo


#ifdef _WIN32
	// grafica en codeblocks
	int gd = DETECT, gm;
	initgraph(&gd, &gm, "");
	
	int angulo_inicio = 0;
	int angulo_fin = 0;
	int color = 1;
	int leyenda_y = 50;
	
	outtextxy(200, 20, "Porcentaje de Ganancias Totales");
	
	while (fread(&m, sizeof(Mueble), 1, archivo) == 1)
	{
		if (m.activo == 1)
		{
			float ganancia_prod = (m.precio - m.costo) * m.unidades_vendidas;
			float porcentaje = ganancia_prod / ganancia_total;
			angulo_fin = angulo_inicio + (int)(porcentaje * 360);
			
			setfillstyle(SOLID_FILL, color);
			// Dibuja la rebanada del pastel
			pieslice(300, 250, angulo_inicio, angulo_fin, 150);
			bar(400, leyenda_y, 415, leyenda_y + 15);
			outtextxy(425, leyenda_y + 3, m.clave);
			leyenda_y += 30;

			angulo_inicio = angulo_fin;
			color++;
			if(color > 14) color = 1; // Reiniciar colores si hay muchos productos
		}
	}
	getch();
	closegraph();
#else
	// grafica en linux
	printf("\nGRAFICA CIRCULAR\n\n");
	printf("Ganancia Total (100%%): $%.2f\n\n", ganancia_total);
	
	while (fread(&m, sizeof(Mueble), 1, archivo) == 1)
	{
		if (m.activo == 1)
		{
			float ganancia_prod = (m.precio - m.costo) * m.unidades_vendidas;
			float porcentaje = (ganancia_prod / ganancia_total) * 100;
			printf("%-6s | %-20s | Ganancia: $%-9.2f | %5.2f%%\n", m.clave, m.descripcion, ganancia_prod, porcentaje);
		}
	}
#endif
	fclose(archivo);
}
