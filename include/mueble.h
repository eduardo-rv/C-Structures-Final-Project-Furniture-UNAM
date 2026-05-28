#ifndef MUEBLE_H
#define MUEBLE_H

typedef struct
{
	char clave[4]; //3 caracteres mas el nulo
	char descripcion[51]; //50 caracteres mas el nulo
	float costo;
	float precio;
	float unidades_vendidas;
	int activo; // 1 = activo, 2 = borrado
} Mueble;

//agregamos la funcion para dar de alta un producto
void alta_producto();

#endif
