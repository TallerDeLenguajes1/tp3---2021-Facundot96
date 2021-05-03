#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


const char* tiposProductos[] = { "Galletas","Snack","Cigarrillos","Caramelos","Bebidas" };

typedef struct Producto
{
    int ProductoID; //Numerado en ciclo iterativo
    int Cantidad; // entre 1 y 10
    char* TipoProducto; // Algún valor del arreglo TiposProductos
    float PrecioUnitario; // entre 10 - 100

}producto;

typedef struct Cliente
{
    int ClienteID; // Numerado en el ciclo iterativo
    char* NombreCliente; // Ingresado por usuario
    int CantidadProductosAPedir; // (alteatorio entre 1 y 5)
    producto* Productos; //El tamaño de este arreglo depende de la variable “CantidadProductosAPedir”

}cliente;

void cargarCliente(cliente*, int);
void agregarProductos(producto*, int);
void mostrarClientes(cliente*, int);
void mostrarProductos(producto* , int );
float costoFinal(producto*);



int main(){

    srand((unsigned int)time(0));

    int cantidad;
    cliente* clientes;

    printf("Ingrese la cantidad de clientes : ");
    scanf_s(" %d", &cantidad);

    clientes = (cliente*)(malloc(sizeof(cliente) * cantidad));

    cargarCliente(clientes, cantidad);

    mostrarClientes(clientes, cantidad);

    free(clientes);

	return 0;
}


void cargarCliente(cliente* clientes, int cantidad) {

    char nombreCliente[50];

    for (int i = 0; i < cantidad; i++)
    {
        (clientes + i)->ClienteID = i + 1;

        fflush(stdin);
        printf("Ingrese el nombre del cliente a agregar: ");
        fflush(stdin);
        scanf(" %s", &nombreCliente);
        fflush(stdin);
        (clientes + i)->NombreCliente = (char*) malloc (sizeof(char) * strlen(nombreCliente));

        strcpy( (clientes + i)->NombreCliente , nombreCliente);

        (clientes + i)->CantidadProductosAPedir = rand() % 5 + 1;
        (clientes + i)->Productos = (producto*)malloc(sizeof(producto*) * (clientes + i)->CantidadProductosAPedir);

        agregarProductos((clientes + i)->Productos, (clientes + i)->CantidadProductosAPedir);
    }


    return;
}

void agregarProductos(producto* nuevosProd, int cantidad){

    int bandera;

    for (int i = 0; i < cantidad; i++)
    {

        (nuevosProd + i)->ProductoID = i + 1;
        (nuevosProd + i)->Cantidad = rand() % 10 + 1;

        bandera = rand() % 5;

        (nuevosProd + i)->TipoProducto = (char*)malloc(sizeof(char*) * strlen(tiposProductos[bandera]));
        strcpy( (nuevosProd + i)->TipoProducto, tiposProductos[bandera] );

        (nuevosProd + i)->PrecioUnitario = (float)(rand() % 910 + 1000) / 10;

    }

    return;
}

void mostrarClientes(cliente* clientes, int cantidad) {

    for (int i = 0; i < cantidad; i++)
    {
        printf("\n Cliente Nº: %d", (clientes + i)->ClienteID);
        printf("\n Nombre del cliente: %s", (clientes + i)->NombreCliente);
        printf("\n Cantidad de productos pedidos: %d", (clientes + i)->CantidadProductosAPedir);
        printf("\n Los productos pedidos son: ");

        mostrarProductos((clientes + i)->Productos , (clientes + i)->CantidadProductosAPedir );

    }

    return;
}

void mostrarProductos(producto* prods, int cantidad) {

    float precio= 0, precioTotal=0;

    for (int i = 0; i < cantidad; i++)
    {

        printf("\n\n Producto Nº: %d", i + 1);
        printf("\n Cantidad: %d", (prods + i)->Cantidad);
        printf("\n Tipo: %s", (prods + i)->TipoProducto);
        printf("\n Precio por unidad: $%.2f", (prods + i)->PrecioUnitario);

        precio = precioFinal((prods + i));

        printf("\n Precio total: $%.2f", precio);
        
        precioTotal = precioTotal + precio;

    }

    printf("\n\nPrecio total de la compra: %.2f\n\n", precioTotal);

    return;
}

float precioFinal(producto * pedido) {

    float precioF;

    precioF = pedido->Cantidad * pedido->PrecioUnitario;

    return precioF;
}