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

//agregamos la funcion para mostrar productos registrados
void mostrar_productos();

//agregamos la funcion para editar productos
void editar_producto();

//agregamos la funcion para eliminar producto
void eliminar_producto();

//agregamos la funcion grafica de columnas
void grafica_columnas();

//agregamos la funcion grafica circular
void grafica_circular();

#endif
